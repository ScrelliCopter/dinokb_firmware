/* matrix.c - pain27 - (C) 2023 a dinosaur */

#include "matrix_helper.h"
#include <avr/io.h>


// Column pins: Left to right
// col:  0,  1,  2,  3,  4,  5,  6,  7,  8
// pin: D7, C6, D4, D1, B3, F4, F5, B1, F6
static void init_columns(void)
{
	INIT_INPORT(D, _BV(7) | _BV(4) | _BV(1));
	INIT_INPORT(C, _BV(6));
	INIT_INPORT(B, _BV(3) | _BV(1));
	INIT_INPORT(F, _BV(4) | _BV(5) | _BV(6));
}

static matrix_row_t read_columns(void)
{
	return
		READ_INPORT(0, D, 7) |
		READ_INPORT(1, C, 6) |
		READ_INPORT(2, D, 4) |
		READ_INPORT(3, D, 1) |
		READ_INPORT(4, B, 3) |
		READ_INPORT(5, F, 4) |
		READ_INPORT(6, F, 5) |
		READ_INPORT(7, B, 1) |
		READ_INPORT(8, F, 6);
}

// Row pins: Top to bottom
// col:  0,  1,  2
// pin: F7, E6, B4
void select_row(uint8_t row)
{
	switch (row)
	{
		SELECT_OUTPORT(0, F, 7)
		SELECT_OUTPORT(1, E, 6)
		SELECT_OUTPORT(2, B, 4)
		default: break;
	}
}

void deselect_row(uint8_t row)
{
	switch (row)
	{
		DESELECT_OUTPORT(0, F, 7)
		DESELECT_OUTPORT(1, E, 6)
		DESELECT_OUTPORT(2, B, 4)
		default: break;
	}
}


#if DEBOUNCE > 0
static bool debouncing = false;
static uint16_t debounce_timer = 0ul;
static matrix_row_t debounce[MATRIX_ROWS];
#endif

static matrix_row_t matrix[MATRIX_ROWS];

void matrix_init(void)
{
	matrix_init_col2row();  // Initialise row & column pins
	matrix_clear();         // Clear matrix state
}

uint8_t matrix_scan(void)
{
	for (uint8_t row = 0; row < MATRIX_ROWS; ++row)
	{
#if DEBOUNCE > 0
		if (matrix_read_columns(debounce, row))
		{
			debounce_timer = timer_read();
			debouncing = true;
		}
#else
		matrix_read_columns(matrix, row);
#endif
	}

#if DEBOUNCE > 0
	if (debouncing)
		debouncing = do_debounce(matrix, debounce, debounce_timer);
#endif

	return 1;
}

MATRIX_DEFAULT_CLEAR(matrix, debounce)
MATRIX_DEFAULT_GET_ROW(matrix)
