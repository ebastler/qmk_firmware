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
#include QMK_KEYBOARD_H

/* Tapdance declaration */
enum {
  TD_ONEKEY = 0
};

/* Tapdance definition */
void dance_onekey_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    rgblight_toggle();
  }
  else if (state->count == 2) {
    rgblight_step();
  }
  else {
    rgblight_increase_hue();
  }
}

void dance_onekey_reset(qk_tap_dance_state_t *state, void *user_data) {
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ONEKEY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_onekey_finished, dance_onekey_reset),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_1x3(
    RGB_VAD, RGB_VAI, TD(TD_ONEKEY)
    ),

  [1] = LAYOUT_1x3(
    KC_TRNS, KC_TRNS, KC_TRNS
    ),

  [2] = LAYOUT_1x3(
    KC_TRNS, KC_TRNS, KC_TRNS
    ),

  [3] = LAYOUT_1x3(
    KC_TRNS, KC_TRNS, KC_TRNS
    ),
};
