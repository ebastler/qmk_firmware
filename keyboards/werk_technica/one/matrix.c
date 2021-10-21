/*
 * Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "debug.h"
#include "matrix.h"

/*
 *     col: { A7, B0, B1, B2, B10, B12, B13, B14, B15, A8, A9, A10, A6, A5, B8 }
 *     row: { A1, A2, A3, A4, B9, C15}
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_COLS];
static bool         debouncing      = false;
static uint16_t     debouncing_time = 0;

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

void matrix_init(void) {
    dprintf("matrix init\n");
    // debug_matrix = true;

    // actual matrix setup
    palSetPadMode(GPIOA, 7, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 0, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 1, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 2, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 10, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 12, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 13, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 14, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 15, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 8, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 9, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 10, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 6, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 5, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 8, PAL_MODE_OUTPUT_PUSHPULL);

    palSetPadMode(GPIOA, 1, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 2, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 3, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 9, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 15, PAL_MODE_INPUT_PULLDOWN);
    

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_COLS * sizeof(matrix_row_t));

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    // actual matrix
    for (int col = 0; col < MATRIX_COLS; col++) {
        matrix_row_t data = 0;

        // strobe col { A7, B0, B1, B2, B10, B12, B13, B14, B15, A8, A9, A10, A6, A5, B8 }
        switch (col) {
            case 0:
                palSetPad(GPIOA, 7);
                break;
            case 1:
                palSetPad(GPIOB, 0);
                break;
            case 2:
                palSetPad(GPIOB, 1);
                break;
            case 3:
                palSetPad(GPIOB, 2);
                break;
            case 4:
                palSetPad(GPIOB, 10);
                break;
            case 5:
                palSetPad(GPIOB, 12);
                break;
            case 6:
                palSetPad(GPIOB, 13);
                break;
            case 7:
                palSetPad(GPIOB, 14);
                break;
            case 8:
                palSetPad(GPIOB, 15);
                break;
            case 9:
                palSetPad(GPIOA, 8);
                break;
            case 10:
                palSetPad(GPIOA, 9);
                break;
            case 11:
                palSetPad(GPIOA, 10);
                break;
            case 12:
                palSetPad(GPIOA, 6);
                break;
            case 13:
                palSetPad(GPIOA, 5);
                break;
            case 14:
                palSetPad(GPIOB, 8);
                break;
        }

        // need wait to settle pin state
        wait_us(20);

        // read row data { A1, A2, A3, A4, B9, C15}
        data = ((palReadPad(GPIOA, 1) << 0) | (palReadPad(GPIOA, 2) << 1) | (palReadPad(GPIOA, 3) << 2) | (palReadPad(GPIOA, 4) << 3) | (palReadPad(GPIOB, 9) << 4) | (palReadPad(GPIOC, 15) << 5));

        // unstrobe  col { A7, B0, B1, B2, B10, B12, B13, B14, B15, A8, A9, A10, A6, A5, B8 }
        switch (col) {
            case 0:
                palClearPad(GPIOA, 7);
                break;
            case 1:
                palClearPad(GPIOB, 0);
                break;
            case 2:
                palClearPad(GPIOB, 1);
                break;
            case 3:
                palClearPad(GPIOB, 2);
                break;
            case 4:
                palClearPad(GPIOB, 10);
                break;
            case 5:
                palClearPad(GPIOB, 12);
                break;
            case 6:
                palClearPad(GPIOB, 13);
                break;
            case 7:
                palClearPad(GPIOB, 14);
                break;
            case 8:
                palClearPad(GPIOB, 15);
                break;
            case 9:
                palClearPad(GPIOA, 8);
                break;
            case 10:
                palClearPad(GPIOA, 9);
                break;
            case 11:
                palClearPad(GPIOA, 10);
                break;
            case 12:
                palClearPad(GPIOA, 6);
                break;
            case 13:
                palClearPad(GPIOA, 5);
                break;
            case 14:
                palClearPad(GPIOB, 8);
                break;
        }

        if (matrix_debouncing[col] != data) {
            matrix_debouncing[col] = data;
            debouncing             = true;
            debouncing_time        = timer_read();
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            matrix[row] = 0;
            for (int col = 0; col < MATRIX_COLS; col++) {
                matrix[row] |= ((matrix_debouncing[col] & (1 << row) ? 1 : 0) << col);
            }
        }
        debouncing = false;
    }

    matrix_scan_quantum();

    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & (1 << col)); }

matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {
    dprintf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        dprintf("%X0: ", row);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1 << col))
                dprintf("1");
            else
                dprintf("0");
        }
        dprintf("\n");
    }
}
