/* Copyright 2021 Moritz Plattner
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
#include "bigswitch.h"

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { NO_LED, NO_LED, NO_LED }
}, {
  // LED Index to Physical Position
  { 170, 50 }, { 150, 50 }, { 131, 50 }, { 112, 50 }, {  93, 50 }, {  73, 50 }, {  54, 50 }, \
  {  54, 50 }, {  73, 50 }, {  93, 50 }, { 112, 50 }, { 131, 50 }, { 150, 50 }, { 170, 50 }, \
  { 224, 64 }, { 224, 51 }, { 224, 38 }, { 224, 26 }, { 224, 13 }, { 224,  0 }, { 110,  0 }, \
  {  51,  0 }, {   0,  0 }, {   0, 13 }, {   0, 26 }, {   0, 38 }, {   0, 51 }, {   0, 64 }  \
}, {
  // LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
} };