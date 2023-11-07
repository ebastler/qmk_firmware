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

/* Custom matrix pins and port select array */
#define MATRIX_ROWS 10
#define MATRIX_ROWS_PER_HAND 5
#define MATRIX_COLS 4

#define AMUX_COUNT 1
#define AMUX_EN_PINS        { F0 }
#define AMUX_COL_CHANNELS_SIZES { 4 }

#define MATRIX_ROW_PINS     { A5, A6, A15, A14, A13 }
#define AMUX_0_COL_CHANNELS { 3, 0, 1, 2 }
#define AMUX_COL_CHANNELS AMUX_0_COL_CHANNELS
#define MUX_SEL_PINS        { C15, C14, C13 }

/* Hardware peripherals pins */
#define DISCHARGE_PIN A0
#define ANALOG_PORT A3

/* EC defines */
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

/* solenoid stuff */
#define SOLENOID_PIN B2

/* Set up split communications */
#define SERIAL_USART_DRIVER SD3
#define SERIAL_USART_PIN_SWAP
#define SERIAL_USART_TX_PIN B10
#define SERIAL_USART_TX_PAL_MODE 7
#define SERIAL_USART_RX_PIN B11
#define SERIAL_USART_RX_PAL_MODE 7
#define SERIAL_USART_FULL_DUPLEX

#if defined(SOFT_SERIAL_PIN)
#    define SERIAL_USART_TX_PIN SOFT_SERIAL_PIN
#endif

//#define SELECT_SOFT_SERIAL_SPEED {0}  // Experimental, will make connection faster but may need tes
/* Set up various split configurations */
#define USB_VBUS_PIN A8                 // The side that manages to establish a USB connection will be master. Disabled because default on ARM targets.

#define SPLIT_HAND_PIN B9               // The MCUs will probe a pin to determine if they are left or right side. high = left, low = right

#define EECONFIG_KB_DATA_SIZE 60