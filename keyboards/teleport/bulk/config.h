/* Copyright 2025 QMK
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

/* SPI config */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_SCK_PAL_MODE 5
#define SPI_MISO_PIN A6
#define SPI_MISO_PAL_MODE 5
#define SPI_MOSI_PIN A7
#define SPI_MOSI_PAL_MODE 5

/* AW20216S config */
#define AW20216S_CS_PIN_1 A4
#define AW20216S_CS_PIN_2 C4
#define AW20216S_EN_PIN A3
// #define AW20216S_SPI_MODE
#define AW20216S_SPI_DIVISOR 8

/* AW20216S current control */
#define AW20216S_GLOBAL_CURRENT_MAX 150
#define AW20216S_SCALING_MAX 150

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_SINGLE_COLOR_RAINDROPS

#define ENABLE_RGB_MATRIX_CUSTOM_SINGLE_COLOR_RAINDROPS // 0 Single color raindrops, random keys lighting up at randomized intensity
#define ENABLE_RGB_MATRIX_CUSTOM_STATIC_GAME_MODE       // - Game mode sets the entire matrix (static) once, then stops LED refreshes

/* Define indicator LED indices, used for lighting effects  */
#define W_LED_INDEX 43
#define A_LED_INDEX 65
#define S_LED_INDEX 66
#define D_LED_INDEX 67

#define CAPS_LED_INDEX 64

#define WIN_LED_INDEX 104

#define NUM_1_LED_INDEX 21
#define NUM_2_LED_INDEX 22
#define NUM_3_LED_INDEX 23
#define NUM_4_LED_INDEX 24
#define NUM_5_LED_INDEX 25

#define M_LED_INDEX 89
#define K_LED_INDEX 72
#define O_LED_INDEX 50
#define NUM_0_LED_INDEX 30
#define P_LED_INDEX 51
#define SCLN_LED_INDEX 74
#define SLSH_LED_INDEX 92

/* Since the typing heatmap is broken on duplex matrix boards, force it to "slim" mode */
#ifdef ENABLE_RGB_MATRIX_TYPING_HEATMAP
    #define RGB_MATRIX_TYPING_HEATMAP_SLIM
#endif

