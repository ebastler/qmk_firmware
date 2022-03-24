/* Copyright 2022 Moritz Plattner
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
#include "onekeyso.h"

led_config_t g_led_config = { {
    // Key Matrix to LED Index
    { 5 }
}, {
    // LED Index to Physical Position
    { 0,  4 }, { 14.5,  4 }, { 14.5,  18.5 }, { 0,  18.5 }, {  7.25,  11.25 }, {  7.25,  24 }, {7.25, 0}
}, {
    // LED Index to Flag
    2, 2, 2, 2, 4, 4, 4
} };

/* LED numbering: 
1: UG top left, 2: UG top right, 3: UG bot right, 4: UG bot left, 5: switch, 6: bot stab, 7: top stab
*/
