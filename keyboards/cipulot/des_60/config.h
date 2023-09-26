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

#define MATRIX_ROWS 4
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS \
    { B15, A8, A9, B14 }

#define AMUX_COUNT 2
#define AMUX_MAX_COLS_COUNT 8

#define AMUX_EN_PINS \
    { B6, B7 }

#define AMUX_SEL_PINS \
    { B3, B4, B5 }

#define AMUX_COL_CHANNELS_SIZES \
    { 8, 7 }

#define AMUX_0_COL_CHANNELS \
    { 0, 1, 2, 3, 4, 5, 6, 7 }

#define AMUX_1_COL_CHANNELS \
    { 3, 1, 0, 2, 4, 6, 7 }

#define AMUX_COL_CHANNELS AMUX_0_COL_CHANNELS, AMUX_1_COL_CHANNELS

#define DISCHARGE_PIN C14
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

#define EECONFIG_KB_DATA_SIZE 130

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
/*
#define L_MASK 0x08
#define R_MASK 0x10

00001000  // L_MASK | 0
00001001  // L_MASK | 1
00001010  // L_MASK | 2
00001011  // L_MASK | 3
00001100  // L_MASK | 4
00001101  // L_MASK | 5
00001110  // L_MASK | 6
00001111  // L_MASK | 7
00010011  // R_MASK | 3
00010001  // R_MASK | 1
00010000  // R_MASK | 0
00010010  // R_MASK | 2
00010100  // R_MASK | 4
00010110  // R_MASK | 6
00010111  // R_MASK | 7
*/
