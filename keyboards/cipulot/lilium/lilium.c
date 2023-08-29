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

#include "keyboards/cipulot/common/ec_switch_matrix.h"
#include "quantum.h"

void eeconfig_init_kb(void) {
    // Default values
    eeprom_ec_config.caps.h                         = 0;
    eeprom_ec_config.caps.s                         = 0;
    eeprom_ec_config.caps.v                         = 60;
    eeprom_ec_config.caps.enabled                   = true;
    eeprom_ec_config.layer_indicator_enabled        = true;
    eeprom_ec_config.actuation_mode                 = DEFAULT_ACTUATION_MODE;
    eeprom_ec_config.mode_0_actuation_threshold     = DEFAULT_MODE_0_ACTUATION_LEVEL;
    eeprom_ec_config.mode_0_release_threshold       = DEFAULT_MODE_0_RELEASE_LEVEL;
    eeprom_ec_config.mode_1_initial_deadzone_offset = DEFAULT_MODE_1_INITIAL_DEADZONE_OFFSET;
    eeprom_ec_config.mode_1_actuation_sensitivity   = DEFAULT_MODE_1_ACTUATION_SENSITIVITY;
    eeprom_ec_config.mode_1_release_sensitivity     = DEFAULT_MODE_1_RELEASE_SENSITIVITY;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            eeprom_ec_config.bottoming_reading[row][col] = DEFAULT_BOTTOMING_READING;
        }
    }
    // Write default value to EEPROM now
    eeconfig_update_kb_datablock(&eeprom_ec_config);
}

// On Keyboard startup
void keyboard_post_init_kb(void) {
    // Read custom menu variables from memory
    eeconfig_read_kb_datablock(&eeprom_ec_config);

    // Set runtime values to EEPROM values
    ec_config.actuation_mode                 = eeprom_ec_config.actuation_mode;
    ec_config.mode_0_actuation_threshold     = eeprom_ec_config.mode_0_actuation_threshold;
    ec_config.mode_0_release_threshold       = eeprom_ec_config.mode_0_release_threshold;
    ec_config.mode_1_initial_deadzone_offset = eeprom_ec_config.mode_1_initial_deadzone_offset;
    ec_config.mode_1_actuation_sensitivity   = eeprom_ec_config.mode_1_actuation_sensitivity;
    ec_config.mode_1_release_sensitivity     = eeprom_ec_config.mode_1_release_sensitivity;
    ec_config.bottoming_calibration          = false;
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            ec_config.bottoming_calibration_starter[row][col]           = true;
            ec_config.bottoming_reading[row][col]                       = eeprom_ec_config.bottoming_reading[row][col];
            ec_config.rescaled_mode_0_actuation_threshold[row][col]     = rescale(ec_config.mode_0_actuation_threshold, 0, 1023, ec_config.noise_floor[row][col], eeprom_ec_config.bottoming_reading[row][col]);
            ec_config.rescaled_mode_0_release_threshold[row][col]       = rescale(ec_config.mode_0_release_threshold, 0, 1023, ec_config.noise_floor[row][col], eeprom_ec_config.bottoming_reading[row][col]);
            ec_config.rescaled_mode_1_initial_deadzone_offset[row][col] = rescale(ec_config.mode_1_initial_deadzone_offset, 0, 1023, ec_config.noise_floor[row][col], eeprom_ec_config.bottoming_reading[row][col]);
        }
    }

    // Call the indicator callback to set the indicator color
    rgb_matrix_indicators_user();
}

// INDICATOR CALLBACK ------------------------------------------------------------------------------
/* LED index to physical position
 *
 * LED0 | LED1 | LED2
 * -----+------+-----
 * Caps |  OFF | OFF  | Layer 0 active
 * Caps |  OFF | ON   | Layer 1 active
 * Caps |  ON  | OFF  | Layer 2 active
 * Caps |  ON  | ON   | Layer 3 active
 */
bool rgb_matrix_indicators_user(void) {
    if (eeprom_ec_config.caps.enabled) {
        // The rgb_matrix_set_color function needs an RGB code to work, so first the indicator color is cast to an HSV value and then translated to RGB
        HSV hsv_caps_indicator_color = {eeprom_ec_config.caps.h, eeprom_ec_config.caps.s, eeprom_ec_config.caps.v};
        RGB rgb_caps_indicator_color = hsv_to_rgb(hsv_caps_indicator_color);
        if (host_keyboard_led_state().caps_lock)
            rgb_matrix_set_color(CAPS_INDICATOR_INDEX, rgb_caps_indicator_color.r, rgb_caps_indicator_color.g, rgb_caps_indicator_color.b);
        else
            rgb_matrix_set_color(CAPS_INDICATOR_INDEX, 0, 0, 0);
    } else {
        rgb_matrix_set_color(CAPS_INDICATOR_INDEX, 0, 0, 0);
    }

    if (eeprom_ec_config.layer_indicator_enabled) {
        if (IS_LAYER_ON(3)) {
            if (true) {
                // Trick if statement to execute the check and exit early if layer 3 is active
            }
        } else if (IS_LAYER_ON(2)) {
            rgb_matrix_set_color(LAYERS_INDICATOR_INDEX_RIGHT, 0, 0, 0);
        } else if (IS_LAYER_ON(1)) {
            rgb_matrix_set_color(LAYERS_INDICATOR_INDEX_LEFT, 0, 0, 0);
        } else if (IS_LAYER_ON(0)) {
            rgb_matrix_set_color(LAYERS_INDICATOR_INDEX_LEFT, 0, 0, 0);
            rgb_matrix_set_color(LAYERS_INDICATOR_INDEX_RIGHT, 0, 0, 0);
        }
    } else {
        rgb_matrix_set_color(LAYERS_INDICATOR_INDEX_LEFT, 0, 0, 0);
        rgb_matrix_set_color(LAYERS_INDICATOR_INDEX_RIGHT, 0, 0, 0);
    }
    return true;
}
