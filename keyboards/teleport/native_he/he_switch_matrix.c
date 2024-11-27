/* Copyright 2024 Cipulot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "he_switch_matrix.h"
#include "analog.h"
#include "atomic_util.h"
#include "math.h"
#include "print.h"
#include "wait.h"

#if defined(__AVR__)
#    error "AVR platforms not supported due to a variety of reasons. Among them there are limited memory, limited number of pins and ADC not being able to give satisfactory results."
#endif

#define OPEN_DRAIN_SUPPORT defined(PAL_MODE_OUTPUT_OPENDRAIN)

eeprom_he_config_t eeprom_he_config;
he_config_t        he_config;

// Pin and port array
const pin_t amux_sel_pins[]                            = AMUX_SEL_PINS;
const pin_t amux_en_pins[]                             = AMUX_EN_PINS;
const pin_t amux_n_col_sizes[]                         = AMUX_COL_CHANNELS_SIZES;
const pin_t amux_n_col_channels[][AMUX_MAX_COLS_COUNT] = {AMUX_COL_CHANNELS};
const pin_t analog_channels[]                          = ANALOG_PORT;

#define AMUX_SEL_PINS_COUNT ARRAY_SIZE(amux_sel_pins)
#define EXPECTED_AMUX_SEL_PINS_COUNT ceil(log2(AMUX_MAX_COLS_COUNT)
// Checks for the correctness of the configuration
_Static_assert(ARRAY_SIZE(amux_en_pins) == AMUX_COUNT, "AMUX_EN_PINS doesn't have the minimum number of bits required to enable all the multiplexers available");
// Check that number of select pins is enough to select all the channels
_Static_assert(AMUX_SEL_PINS_COUNT == EXPECTED_AMUX_SEL_PINS_COUNT), "AMUX_SEL_PINS doesn't have the minimum number of bits required address all the channels");
// Check that number of elements in AMUX_COL_CHANNELS_SIZES is enough to specify the number of channels for all the multiplexers available
_Static_assert(ARRAY_SIZE(amux_n_col_sizes) == AMUX_COUNT, "AMUX_COL_CHANNELS_SIZES doesn't have the minimum number of elements required to specify the number of channels for all the multiplexers available");

static uint16_t sw_value[MATRIX_ROWS][MATRIX_COLS];

static adc_mux adcMux0;
static adc_mux adcMux1;
static adc_mux adcMux2;
static adc_mux adcMux3;
static adc_mux adcMux4;
static adc_mux adcMux5;


// Initialize the multiplexers
void init_amux(void) {
    for (uint8_t idx = 0; idx < AMUX_COUNT; idx++) {
        gpio_set_pin_output(amux_en_pins[idx]); // set the enable pins as output
        gpio_write_pin_low(amux_en_pins[idx]);  // disable all the multiplexers for power saving
    }
    for (uint8_t idx = 0; idx < AMUX_SEL_PINS_COUNT; idx++) {
        gpio_set_pin_output(amux_sel_pins[idx]); // set the select pins as output
    }
}

// Select the multiplexer channel of the specified multiplexer
void select_amux_channel(uint8_t channel, uint8_t col) {
    // Get the channel for the specified multiplexer
    uint8_t ch = amux_n_col_channels[channel][col];
    // momentarily disable specified multiplexer
    // gpio_write_pin_high(amux_en_pins[channel]);
    // Select the multiplexer channel
    for (uint8_t i = 0; i < AMUX_SEL_PINS_COUNT; i++) {
        gpio_write_pin(amux_sel_pins[i], ch & (1 << i));
    }
    // re enable specified multiplexer
    // gpio_write_pin_low(amux_en_pins[channel]);
}

// Disable all the unused multiplexers
void disable_unused_amux(uint8_t channel) {
    // disable all the other multiplexers apart from the current selected one and the next one
    for (uint8_t idx = 0; idx < AMUX_COUNT; idx++) {
        if (idx != channel && idx != (channel + 1) % AMUX_COUNT) {
            gpio_write_pin_high(amux_en_pins[idx]);
        } else {
            gpio_write_pin_low(amux_en_pins[idx]);
        }
    }
}

// Initialize the peripherals pins
int he_init(void) {
    // Initialize AMUXs
    init_amux();

    // Initialize ADC
    palSetLineMode(analog_channels[0], PAL_MODE_INPUT_ANALOG);
    palSetLineMode(analog_channels[1], PAL_MODE_INPUT_ANALOG);
    palSetLineMode(analog_channels[2], PAL_MODE_INPUT_ANALOG);
    palSetLineMode(analog_channels[3], PAL_MODE_INPUT_ANALOG);
    adcMux0 = pinToMux(analog_channels[0]);
    adcMux1 = pinToMux(analog_channels[1]);
    adcMux2 = pinToMux(analog_channels[2]);
    adcMux3 = pinToMux(analog_channels[3]);
    adcMux4 = pinToMux(analog_channels[4]);
    adcMux5 = pinToMux(analog_channels[5]);


    // Dummy call to make sure that adcStart() has been called in the appropriate state
    adc_read(adcMux0);
    adc_read(adcMux1);
    adc_read(adcMux2);
    adc_read(adcMux3);
    adc_read(adcMux4);
    adc_read(adcMux5);

    return 0;
}

// Get the noise floor
void he_noise_floor(void) {
    // Initialize the noise floor
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            he_config.noise_floor[row][col] = 0;
        }
    }

    // Sample the noise floor
    for (uint8_t i = 0; i < DEFAULT_NOISE_FLOOR_SAMPLING_COUNT; i++) {
        for (uint8_t amux = 0; amux < AMUX_COUNT; amux++) {
            //disable_unused_amux(amux);
            for (uint8_t col = 0; col < amux_n_col_sizes[amux]; col++) {
                he_config.noise_floor[amux][col] += he_readkey_raw(amux, col);
            }
            wait_ms(5);
        }
    }

    // Average the noise floor
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            he_config.noise_floor[row][col] /= DEFAULT_NOISE_FLOOR_SAMPLING_COUNT;
        }
    }
}

// Scan key values and update matrix state
bool he_matrix_scan(matrix_row_t current_matrix[]) {
    bool updated = false;

    for (uint8_t amux = 0; amux < AMUX_COUNT; amux++) {
        //disable_unused_amux(amux);
        //wait_us(DISCHARGE_TIME);
        for (uint8_t col = 0; col < amux_n_col_sizes[amux]; col++) {
            sw_value[amux][col] = he_readkey_raw(amux, col);

            if (he_config.bottoming_calibration) {
                if (he_config.bottoming_calibration_starter[amux][col]) {
                    he_config.bottoming_reading[amux][col]             = sw_value[amux][col];
                    he_config.bottoming_calibration_starter[amux][col] = false;
                } else if (sw_value[amux][col] > he_config.bottoming_reading[amux][col]) {
                    he_config.bottoming_reading[amux][col] = sw_value[amux][col];
                }
            } else {
                updated |= he_update_key(&current_matrix[amux], amux, col, sw_value[amux][col]);
            }
        }
    }

    return he_config.bottoming_calibration ? false : updated;
}

// Read the capacitive sensor value
uint16_t he_readkey_raw(uint8_t channel, uint8_t col) {
    uint16_t sw_value = 0;

    // Select the multiplexer
    select_amux_channel(channel, col);

    ATOMIC_BLOCK_FORCEON {
        // Read the ADC value
        switch (channel) {
            case 0:
                sw_value = adc_read(adcMux0);
                ;
                break;
            case 1:
                sw_value = adc_read(adcMux1);
                break;
            case 2:
                sw_value = adc_read(adcMux2);
                break;
            case 3:
                sw_value = adc_read(adcMux3);
                break;
            case 4:
                sw_value = adc_read(adcMux4);
                break;
            case 5:
                sw_value = adc_read(adcMux5);
                break;
            default:
                break;
        }
    }
    // Waiting for the ghost capacitor to discharge fully
    // wait_us(DISCHARGE_TIME);

    return sw_value;
}

// Update press/release state of key
bool he_update_key(matrix_row_t* current_row, uint8_t amux, uint8_t col, uint16_t sw_value) {
    bool current_state = (*current_row >> col) & 1;

    // Real Time Noise Floor Calibration
    if (sw_value < (he_config.noise_floor[amux][col] - NOISE_FLOOR_THRESHOLD)) {
        uprintf("Noise Floor Change: %d, %d, %d\n", amux, col, sw_value);
        he_config.noise_floor[amux][col]                             = sw_value;
        he_config.rescaled_mode_0_actuation_threshold[amux][col]     = rescale(he_config.mode_0_actuation_threshold, 0, 1023, he_config.noise_floor[amux][col], eeprom_he_config.bottoming_reading[amux][col]);
        he_config.rescaled_mode_0_release_threshold[amux][col]       = rescale(he_config.mode_0_release_threshold, 0, 1023, he_config.noise_floor[amux][col], eeprom_he_config.bottoming_reading[amux][col]);
        he_config.rescaled_mode_1_initial_deadzone_offset[amux][col] = rescale(he_config.mode_1_initial_deadzone_offset, 0, 1023, he_config.noise_floor[amux][col], eeprom_he_config.bottoming_reading[amux][col]);
    }

    // Normal board-wide APC
    if (he_config.actuation_mode == 0) {
        if (current_state && sw_value < he_config.rescaled_mode_0_release_threshold[amux][col]) {
            *current_row &= ~(1 << col);
            uprintf("Key released: %d, %d, %d\n", amux, col, sw_value);
            return true;
        }
        if ((!current_state) && sw_value > he_config.rescaled_mode_0_actuation_threshold[amux][col]) {
            *current_row |= (1 << col);
            uprintf("Key pressed: %d, %d, %d\n", amux, col, sw_value);
            return true;
        }
    }
    // Rapid Trigger
    else if (he_config.actuation_mode == 1) {
        // Is key in active zone?
        if (sw_value > he_config.rescaled_mode_1_initial_deadzone_offset[amux][col]) {
            // Is key pressed while in active zone?
            if (current_state) {
                // Is the key still moving down?
                if (sw_value > he_config.extremum[amux][col]) {
                    he_config.extremum[amux][col] = sw_value;
                    uprintf("Key pressed: %d, %d, %d\n", amux, col, sw_value);
                }
                // Has key moved up enough to be released?
                else if (sw_value < he_config.extremum[amux][col] - he_config.mode_1_release_offset) {
                    he_config.extremum[amux][col] = sw_value;
                    *current_row &= ~(1 << col);
                    uprintf("Key released: %d, %d, %d\n", amux, col, sw_value);
                    return true;
                }
            }
            // Key is not pressed while in active zone
            else {
                // Is the key still moving up?
                if (sw_value < he_config.extremum[amux][col]) {
                    he_config.extremum[amux][col] = sw_value;
                }
                // Has key moved down enough to be pressed?
                else if (sw_value > he_config.extremum[amux][col] + he_config.mode_1_actuation_offset) {
                    he_config.extremum[amux][col] = sw_value;
                    *current_row |= (1 << col);
                    uprintf("Key pressed: %d, %d, %d\n", amux, col, sw_value);
                    return true;
                }
            }
        }
        // Key is not in active zone
        else {
            // Check to avoid key being stuck in pressed state near the active zone threshold
            if (sw_value < he_config.extremum[amux][col]) {
                he_config.extremum[amux][col] = sw_value;
                *current_row &= ~(1 << col);
                return true;
            }
        }
    }
    return false;
}

// Print the matrix values
void he_print_matrix(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS - 1; col++) {
            uprintf("%4d,", sw_value[row][col]);
        }
        uprintf("%4d\n", sw_value[row][MATRIX_COLS - 1]);
    }
    print("\n");
}

// Rescale the value to a different range
uint16_t rescale(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
