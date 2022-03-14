/*
Copyright 2020 Moritz Plattner

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
#define VENDOR_ID       0x6562 // "eb"
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    ebastler
#define PRODUCT         onekeyso

/* Switch pins */
#define DIRECT_PINS {{ D3 }}
#define UNUSED_PINS { B1, B2, B3, B4, B5, B6, B7, C6, C7, D0, D1, D4, D5, D7, E6, F0, F1, F4, F5, F6, F7 }

/* Tapdance configs */
#define TAPPING_TERM 250

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Underglow */
#define RGB_DI_PIN D2
#define RGBLED_NUM 7
#define RGBLIGHT_SLEEP // Turns LEDs off if the PC goes to sleep/shutdown
/* #define RGBLIGHT_EFFECT_BREATHING */
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
