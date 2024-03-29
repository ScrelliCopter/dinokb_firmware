/*
  Copyright 2014 Ralf Schmitt <ralf@bunkertor.net>

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

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "matrix.h"

#ifndef DEBOUNCE
#  define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t scan_row(void)
{
  return MATRIX_ROW_SCAN;
}

static void select_row(uint8_t row)
{
  switch (row)
  {
    MATRIX_ROW_SELECT;
  default:
    break;
  }
}

void matrix_init(void)
{
  // Initialise row and col
  CONFIG_MATRIX_IO;

  // Initialise matrix state to all keys off
  for (uint8_t i = 0; i < MATRIX_ROWS; ++i)
  {
    matrix[i] = 0;
    matrix_debouncing[i] = 0;
  }

  //debug
  //debug_matrix = true;
}

uint8_t matrix_scan(void)
{
  for (uint8_t row = 0; row < MATRIX_ROWS; ++row)
  {
    select_row(row);
    _delay_us(3);
    matrix_row_t row_scan = scan_row();
    for (uint8_t col = 0; col < MATRIX_COLS; ++col)
    {
      bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1 << col);
      bool curr_bit = row_scan & (1 << col);
      if (prev_bit != curr_bit)
      {
        matrix_debouncing[row] ^= (matrix_row_t)1 << col;
        debouncing = DEBOUNCE;
      }
    }
  }

  if (debouncing)
  {
    if (--debouncing)
    {
      _delay_ms(1);
    }
    else
    {
      for (uint8_t i = 0; i < MATRIX_ROWS; ++i)
        matrix[i] = matrix_debouncing[i];
    }
  }

  return 1;
}

inline matrix_row_t matrix_get_row(uint8_t row)
{
  return matrix[row];
}

void matrix_print(void)
{
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; ++row)
    xprintf("%02X: %032lb\n", row, bitrev32(matrix[row]));
}
