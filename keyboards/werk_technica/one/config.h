/*
Copyright 2021 Moritz Plattner

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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x7774 // "wt"
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    werk_technica
#define PRODUCT         one

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { A0, A1, A2, A3, B9, B8 }
#define MATRIX_COL_PINS { A6, A7, B0, B1, B10, B12, B13, B14, B15, A8, A10, A13, A5, A4, C15 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

/* Rotary encoder - set the resolution fitting your encoder.
Most will need a value of 4. If 1 encoder click results in 2 keycodes sent
increase the value. If you need 2 clicks for 1 keycode, decrease*/
#define ENCODER_RESOLUTION 4
#define ENCODERS_PAD_A { B5 }
#define ENCODERS_PAD_B { A15 }
#define TAP_CODE_DELAY 10


/* Some hardware configs */
#ifndef STM32_HSECLK
#    define STM32_HSECLK 16000000U
#endif

#ifndef EARLY_INIT_PERFORM_BOOTLOADER_JUMP
#    define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE
#endif
