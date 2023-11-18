#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "matrix.h"

#define BIT(N) (1 << (N))
#define READ_PORT(ID, INPORT, INPIN) ((PIN##INPORT & BIT(INPIN)) ? 0 : BIT(ID))
#define INIT_PORT(OUTPORT, PINS) \
	DDR##OUTPORT &= ~(PINS); PORT##OUTPORT |= (PINS);
#define UNSELECT_PORT(OUTPORT, PINS) \
	DDR##OUTPORT &= ~(PINS); PORT##OUTPORT &= ~(PINS);
#define SELECT_PORT(ID, OUTPORT, PIN) \
	case (ID): DDR##OUTPORT |= BIT(PIN); PORT##OUTPORT &= ~BIT(PIN); break;

#ifndef DEBOUNCE
#  define DEBOUNCE 5
#endif


// Column pins: Left to right
// col:  0  1  2  3  4  5  6  7
// pin: F0 F1 F4 F5 F6 F7 E6 B1

// Row pins: Top to bottom
// row:  0  1  2  3  4  5  6  7  8  9
// pin: B2 C7 C6 B6 B5 B0 B3 D5 D3 D2

static matrix_row_t read_cols(void)
{
	return
		READ_PORT(0, F, 0) |
		READ_PORT(1, F, 1) |
		READ_PORT(2, F, 4) |
		READ_PORT(3, F, 5) |
		READ_PORT(4, F, 6) |
		READ_PORT(5, F, 7) |
		READ_PORT(6, E, 6) |
		READ_PORT(7, B, 1);
}

static void init_cols(void)
{
	// Input with pull-up (DDR:0, PORT:1)
	INIT_PORT(F, BIT(0) | BIT(1) | BIT(4) | BIT(5) | BIT(6) | BIT(7))
	INIT_PORT(E, BIT(6))
	INIT_PORT(B, BIT(1))
}

static void unselect_rows(void)
{
	// Hi-Z (DDR:0, PORT:0) to unselect
	UNSELECT_PORT(B, BIT(0) | BIT(2) | BIT(3) | BIT(5) | BIT(6))
	UNSELECT_PORT(C, BIT(6) | BIT(7))
	UNSELECT_PORT(D, BIT(2) | BIT(3) | BIT(5))
}

static void select_row(uint8_t row)
{
	// Output low (DDR:1, PORT:0) to select
	switch (row)
	{
	SELECT_PORT(0, B, 2)
	SELECT_PORT(1, C, 7)
	SELECT_PORT(2, C, 6)
	SELECT_PORT(3, B, 6)
	SELECT_PORT(4, B, 5)
	SELECT_PORT(5, B, 0)
	SELECT_PORT(6, B, 3)
	SELECT_PORT(7, D, 5)
	SELECT_PORT(8, D, 3)
	SELECT_PORT(9, D, 2)
	default:
		break;
	}
}


static uint8_t debouncing = DEBOUNCE;

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

void matrix_init(void)
{
	// Setup row and column pins
	unselect_rows();
	init_cols();

	// Initialise matrix state to all keys off
	for (uint8_t i = 0; i < MATRIX_ROWS; ++i)
	{
		matrix[i] = 0;
		matrix_debouncing[i] = 0;
	}
}

static __attribute__((always_inline)) void do_debounce(void)
//static void do_debounce(void)
{
	if (--debouncing)
	{
		_delay_ms(1);
		return;
	}

	for (uint8_t i = 0; i < MATRIX_ROWS; ++i)
		matrix[i] = matrix_debouncing[i];
}

uint8_t matrix_scan(void)
{
	for (uint8_t i = 0; i < MATRIX_ROWS; ++i)
	{
		select_row(i);
		// Short delay to allow matrix reads to stabilise
		_delay_us(30);
		const matrix_row_t cols = read_cols();
		if (matrix_debouncing[i] != cols)
		{
			matrix_debouncing[i] = cols;
			debouncing = DEBOUNCE;
		}
		unselect_rows();
	}

	if (debouncing)
		do_debounce();

	return 1;
}

inline matrix_row_t matrix_get_row(uint8_t row)
{
	return matrix[row];
}
