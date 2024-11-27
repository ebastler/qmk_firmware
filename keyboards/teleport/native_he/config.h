/*
Copyright 2022 Moritz Plattner
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* i2C Config */
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN        A13
#define I2C1_SDA_PIN        A14
#define I2C1_SCL_PAL_MODE   4
#define I2C1_SDA_PAL_MODE   4

/*
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_16_9
#define I2C1_CLOCK_SPEED 400000
*/
#define IS31FL3733_I2C_ADDRESS_1 IS31FL3733_I2C_ADDRESS_GND_GND
#define IS31FL3733_I2C_ADDRESS_2 IS31FL3733_I2C_ADDRESS_GND_VCC
#define IS31FL3733_SDB_PIN A15

// #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_SINGLE_COLOR_RAINDROPS
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP


#define ENABLE_RGB_MATRIX_CUSTOM_SINGLE_COLOR_RAINDROPS // 0 Single color raindrops, random keys lighting up at randomized intensity
#define ENABLE_RGB_MATRIX_CUSTOM_STATIC_GAME_MODE       // - Game mode sets the entire matrix (static) once, then stops LED refreshes

/* Define indicator LED indices, used for lighting effects  */
#define W_LED_INDEX 35
#define A_LED_INDEX 51
#define S_LED_INDEX 52
#define D_LED_INDEX 53

#define CAPS_LED_INDEX 50

#define WIN_LED_INDEX 80

#define ANV_A_LED_INDEX 15
#define ANV_N_LED_INDEX 32
#define ANV_V_LED_INDEX 49
#define ANV_I_LED_INDEX 63
#define ANV_L_LED_INDEX 78

#define NUM_1_LED_INDEX 17
#define NUM_2_LED_INDEX 18
#define NUM_3_LED_INDEX 19
#define NUM_4_LED_INDEX 20
#define NUM_5_LED_INDEX 21

#define M_LED_INDEX 72
#define K_LED_INDEX 58
#define O_LED_INDEX 42
#define NUM_0_LED_INDEX 26
#define P_LED_INDEX 43
#define SCLN_LED_INDEX 60
#define SLSH_LED_INDEX 75

/* Since the typing heatmap is broken on duplex matrix boards, force it to "slim" mode */
#ifdef ENABLE_RGB_MATRIX_TYPING_HEATMAP
    #define RGB_MATRIX_TYPING_HEATMAP_SLIM
#endif

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

#define AMUX_COUNT 6
#define AMUX_MAX_COLS_COUNT 16

/* Define unused pins so far, so sensors are not strobed */
#define AMUX_EN_PINS \
    { A0, A1, A2, A3, A4, A8 }

#define AMUX_SEL_PINS \
    { B5, B3, C10, C11 }

#define AMUX_COL_CHANNELS_SIZES \
    { 16, 16, 16, 16, 16, 16 }

#define AMUX_0_COL_CHANNELS \
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }

#define AMUX_1_COL_CHANNELS AMUX_0_COL_CHANNELS
#define AMUX_2_COL_CHANNELS AMUX_0_COL_CHANNELS
#define AMUX_3_COL_CHANNELS AMUX_0_COL_CHANNELS
#define AMUX_4_COL_CHANNELS AMUX_0_COL_CHANNELS
#define AMUX_5_COL_CHANNELS AMUX_0_COL_CHANNELS

#define AMUX_COL_CHANNELS AMUX_0_COL_CHANNELS, AMUX_1_COL_CHANNELS, AMUX_2_COL_CHANNELS, AMUX_3_COL_CHANNELS, AMUX_4_COL_CHANNELS, AMUX_5_COL_CHANNELS

#define ANALOG_PORT \
    { A5, A6, A7, C4, B2, F1 }

#define DEFAULT_ACTUATION_MODE 0
#define DEFAULT_MODE_0_ACTUATION_LEVEL 550
#define DEFAULT_MODE_0_RELEASE_LEVEL 500
#define DEFAULT_MODE_1_INITIAL_DEADZONE_OFFSET DEFAULT_MODE_0_ACTUATION_LEVEL
#define DEFAULT_MODE_1_ACTUATION_OFFSET 70
#define DEFAULT_MODE_1_RELEASE_OFFSET 70
#define DEFAULT_EXTREMUM 1023
#define EXPECTED_NOISE_FLOOR 0
#define NOISE_FLOOR_THRESHOLD 50
#define BOTTOMING_CALIBRATION_THRESHOLD 50
#define DEFAULT_NOISE_FLOOR_SAMPLING_COUNT 30
#define DEFAULT_BOTTOMING_READING 1023
#define DEFAULT_CALIBRATION_STARTER true

#define DISCHARGE_TIME 10

// #define DEBUG_MATRIX_SCAN_RATE

#define EECONFIG_KB_DATA_SIZE 201

//#define DEBUG_MATRIX_SCAN_RATE