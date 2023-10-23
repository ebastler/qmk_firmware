/* Copyright 2023 Cipulot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ec_switch_matrix.h"
#include "analog.h"
#include "atomic_util.h"
#include "math.h"
#include "print.h"
#include "wait.h"

eeprom_ec_config_t eeprom_ec_config;
ec_config_t        ec_config;
/* Pin and port array */
const uint32_t row_pins[] = MATRIX_ROW_PINS;

// static ec_config_t config;
static uint16_t sw_value[MATRIX_ROWS][MATRIX_COLS];

static adc_mux adcMux;

// Initialize the row pins
void init_row(void) {
    // Set all row pins as output and low
    for (uint8_t idx = 0; idx < MATRIX_ROWS; idx++) {
        setPinOutput(row_pins[idx]);
        writePinLow(row_pins[idx]);
    }
}

// Discharge the peak hold capacitor
void discharge_capacitor(void) {
    writePinLow(DISCHARGE_PIN);
}

// Charge the peak hold capacitor
void charge_capacitor(uint8_t row) {
    writePinHigh(DISCHARGE_PIN);
    writePinHigh(row_pins[row]);
}

// Initialize the peripherals pins
int ec_init(void) {
    // Initialize ADC
    palSetLineMode(ANALOG_PORT, PAL_MODE_INPUT_ANALOG);
    adcMux = pinToMux(ANALOG_PORT);

    // Dummy call to make sure that adcStart() has been called in the appropriate state
    adc_read(adcMux);

    // Initialize discharge pin as discharge mode
    writePinLow(DISCHARGE_PIN);
    setPinOutputOpenDrain(DISCHARGE_PIN);

    // Initialize drive lines
    init_row();

    return 0;
}

// Get the noise floor
void ec_noise_floor(void) {
    // Initialize the noise floor to 0
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        ec_config.noise_floor[row][0] = 0;
    }

    // Get the noise floor
    for (uint8_t i = 0; i < DEFAULT_NOISE_FLOOR_SAMPLING_COUNT; i++) {
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            ec_config.noise_floor[row][0] += ec_readkey_raw(0, row, 0);
        }
        wait_ms(5);
    }

    // Average the noise floor
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        ec_config.noise_floor[row][0] /= DEFAULT_NOISE_FLOOR_SAMPLING_COUNT;
    }
}

// Scan key values and update matrix state
bool ec_matrix_scan(matrix_row_t current_matrix[]) {
    bool updated = false;

    // Bottoming calibration mode: update bottoming out values and avoid keycode state change
    // IF statement is higher in the function to avoid the overhead of the execution of normal operation mode
    if (ec_config.bottoming_calibration) {
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            sw_value[row][0] = ec_readkey_raw(0, row, 0);
            if (ec_config.bottoming_calibration_starter[row][0]) {
                ec_config.bottoming_reading[row][0]             = sw_value[row][0];
                ec_config.bottoming_calibration_starter[row][0] = false;
            } else if (sw_value[row][0] > ec_config.bottoming_reading[row][0]) {
                ec_config.bottoming_reading[row][0] = sw_value[row][0];
            }
        }

        // Return false to avoid keycode state change
        return false;
    }
    // Normal operation mode: update key state
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        sw_value[row][0] = ec_readkey_raw(0, row, 0);
        updated |= ec_update_key(&current_matrix[row], row, 0, sw_value[row][0]);
    }
    return updated;
}

// Read the capacitive sensor value
uint16_t ec_readkey_raw(uint8_t channel, uint8_t row, uint8_t col) {
    uint16_t sw_value = 0;

    // Set the row pin to low state to avoid ghosting
    writePinLow(row_pins[row]);

    ATOMIC_BLOCK_FORCEON {
        // Set the row pin to high state and have capacitor charge
        charge_capacitor(row);
        // Read the ADC value
        sw_value = adc_read(adcMux);
    }
    // Discharge peak hold capacitor
    discharge_capacitor();
    // Waiting for the ghost capacitor to discharge fully
    wait_us(DISCHARGE_TIME);

    return sw_value;
}

// Update press/release state of key
bool ec_update_key(matrix_row_t* current_row, uint8_t row, uint8_t col, uint16_t sw_value) {
    bool current_state = (*current_row >> col) & 1;

    // Normal board-wide APC
    if (ec_config.actuation_mode == 0) {
        if (current_state && sw_value < ec_config.rescaled_mode_0_release_threshold[row][col]) {
            *current_row &= ~(1 << col);
            uprintf("Key released: %d, %d, %d\n", row, col, sw_value);
            return true;
        }
        if ((!current_state) && sw_value > ec_config.rescaled_mode_0_actuation_threshold[row][col]) {
            *current_row |= (1 << col);
            uprintf("Key pressed: %d, %d, %d\n", row, col, sw_value);
            return true;
        }
    }
    // Rapid trigger starting from the initial deadzone
    else if (ec_config.actuation_mode == 1) {
        if (sw_value > ec_config.rescaled_mode_1_initial_deadzone_offset[row][col]) {
            // In DA zone?
            if (current_state) {
                // Key is pressed
                // Is key still moving down?
                if (sw_value > ec_config.extremum[row][col]) {
                    ec_config.extremum[row][col] = sw_value;
                    uprintf("Key pressed: %d, %d, %d\n", row, col, sw_value);
                } else if (sw_value < ec_config.extremum[row][col] - DEFAULT_MODE_1_RELEASE_SENSITIVITY) {
                    // Has key moved up enough to be released?
                    ec_config.extremum[row][col] = sw_value;
                    *current_row &= ~(1 << col);
                    uprintf("Key released: %d, %d, %d\n", row, col, sw_value);
                    return true;
                }
            } else {
                // Key is not pressed
                // Is the key still moving up?
                if (sw_value < ec_config.extremum[row][col]) {
                    ec_config.extremum[row][col] = sw_value;
                } else if (sw_value > ec_config.extremum[row][col] + DEFAULT_MODE_1_ACTUATION_SENSITIVITY) {
                    // Has key moved down enough to be pressed?
                    ec_config.extremum[row][col] = sw_value;
                    *current_row |= (1 << col);
                    uprintf("Key pressed: %d, %d, %d\n", row, col, sw_value);
                    return true;
                }
            }
        } else {
            // Out of DA zone
            if (sw_value < ec_config.extremum[row][col]) {
                ec_config.extremum[row][col] = sw_value;
                *current_row &= ~(1 << col);
            }
        }
    }
    return false;
}

// Debug print key values
void ec_print_matrix(void) {
    uprintf("%4d, ", sw_value[0][0]);
    uprintf("%4d", sw_value[1][0]);
    print("\n");
}

// Rescale the value to a different range
uint16_t rescale(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
