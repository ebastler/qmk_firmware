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

#pragma once

#define MATRIX_ROWS 5
#define MATRIX_COLS 14

#define MATRIX_ROW_PINS \
    { B13, A15, B9, B8, A5 }

#define AMUX_COUNT 2
#define AMUX_MAX_COLS_COUNT 8

#define AMUX_EN_PINS \
    { A6, C13 }

#define AMUX_SEL_PINS \
    { B12, B0, A7 }

#define AMUX_COL_CHANNELS_SIZES \
    { 8, 6 }

#define AMUX_0_COL_CHANNELS \
    { 3, 0, 1, 2, 4, 6, 7, 5 }

#define AMUX_1_COL_CHANNELS \
    { 3, 0, 1, 2, 4, 6 }

#define AMUX_COL_CHANNELS AMUX_0_COL_CHANNELS, AMUX_1_COL_CHANNELS

#define DISCHARGE_PIN A3
#define ANALOG_PORT A2

#define DEFAULT_ACTUATION_MODE 0
#define DEFAULT_MODE_0_ACTUATION_LEVEL 550
#define DEFAULT_MODE_0_RELEASE_LEVEL 500
#define DEFAULT_MODE_1_INITIAL_DEADZONE_OFFSET DEFAULT_MODE_0_ACTUATION_LEVEL
#define DEFAULT_MODE_1_ACTUATION_SENSITIVITY 70
#define DEFAULT_MODE_1_RELEASE_SENSITIVITY 70
#define DEFAULT_EXTREMUM 1023
#define EXPECTED_NOISE_FLOOR 0
#define DEFAULT_NOISE_FLOOR_SAMPLING_COUNT 30
#define DEFAULT_BOTTOMING_READING 1023
#define DEFAULT_CALIBRATION_STARTER true

#define DISCHARGE_TIME 10

// #define DEBUG_MATRIX_SCAN_RATE

#define EECONFIG_KB_DATA_SIZE 154

#define CAPS_INDICATOR_INDEX 0
#define LAYERS_INDICATOR_INDEX_LEFT 1
#define LAYERS_INDICATOR_INDEX_RIGHT 2

/* RGB Strip */
#define RGB_MATRIX_LED_COUNT 3
#define RGB_MATRIX_DEFAULT_VAL 60
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
