/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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
#include "debug.h"
#include "util.h"
#include "wait.h"
#include "matrix.h"


#ifndef DEBOUNCE
#  define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);


void matrix_init(void)
{
	// initialize row and col
	unselect_rows();
	init_cols();

	// initialize matrix state: all keys off
	for (uint8_t i=0; i < MATRIX_ROWS; i++) {
		matrix[i] = 0;
		matrix_debouncing[i] = 0;
	}
}

uint8_t matrix_scan(void)
{
	for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
		select_row(i);
		wait_us(30);  // without this wait read unstable value.
		matrix_row_t cols = read_cols();
		if (matrix_debouncing[i] != cols) {
			matrix_debouncing[i] = cols;
			if (debouncing) {
				debug("bounce!: "); debug_hex(debouncing); debug("\n");
			}
			debouncing = DEBOUNCE;
		}
		unselect_rows();
	}

	if (debouncing) {
		if (--debouncing) {
			wait_ms(1);
		} else {
			for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
				matrix[i] = matrix_debouncing[i];
			}
		}
	}

	return 1;
}


inline
matrix_row_t matrix_get_row(uint8_t row)
{
	return matrix[row];
}

// Column pin configuration
// col: 0  1  2  3  4
// pin: C5 C6 B6 B7 C7 
static void init_cols(void)
{
	// Input with pull-up(DDR:0, PORT:1)
	DDRC  &= ~0b11100000;
	PORTC |=  0b11100000;

	DDRB  &= ~0b11000000;
	PORTB |=  0b11000000;
}

static matrix_row_t read_cols(void)
{
	return
		( PINC & _BV(5) ? 0 : _BV(0) ) |
		( PINC & _BV(6) ? 0 : _BV(1) ) |
		( PINB & _BV(6) ? 0 : _BV(2) ) |
		( PINB & _BV(7) ? 0 : _BV(3) ) |
		( PINC & _BV(7) ? 0 : _BV(4) );
}

// ROWS: Top to bottom, COLS: Left to right
// Row pin configuration
// row: 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14
// pin: D6 B0 B1 B2 B3 B4 B5 C4 C2 D0 D1 D3 D2 D4 D5
static void unselect_rows(void)
{
	// Hi-Z(DDR:0, PORT:0) to unselect
	DDRD  &= ~0b01111111;
	PORTD &= ~0b01111111;

	DDRB  &= ~0b00111111;
	PORTB &= ~0b00111111;

	DDRC  &= ~0b00010100;
	PORTC &= ~0b00010100;
}

static void select_row(uint8_t row)
{
	// Output low(DDR:1, PORT:0) to select
	switch (row) {
		case  0: DDRD |= _BV(6); PORTD &= ~_BV(6); break;
		case  1: DDRB |= _BV(0); PORTB &= ~_BV(0); break;
		case  2: DDRB |= _BV(1); PORTB &= ~_BV(1); break;
		case  3: DDRB |= _BV(2); PORTB &= ~_BV(2); break;
		case  4: DDRB |= _BV(3); PORTB &= ~_BV(3); break;
		case  5: DDRB |= _BV(4); PORTB &= ~_BV(4); break;
		case  6: DDRB |= _BV(5); PORTB &= ~_BV(5); break;
		case  7: DDRC |= _BV(4); PORTC &= ~_BV(4); break;
		case  8: DDRC |= _BV(2); PORTC &= ~_BV(2); break;
		case  9: DDRD |= _BV(0); PORTD &= ~_BV(0); break;
		case 10: DDRD |= _BV(1); PORTD &= ~_BV(1); break;
		case 11: DDRD |= _BV(3); PORTD &= ~_BV(3); break;
		case 12: DDRD |= _BV(2); PORTD &= ~_BV(2); break;
		case 13: DDRD |= _BV(4); PORTD &= ~_BV(4); break;
		case 14: DDRD |= _BV(5); PORTD &= ~_BV(5); break;
	}
}
