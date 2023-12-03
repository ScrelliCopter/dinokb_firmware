/* matrix.c - grandpad - matrix.c - (c) a dinosaur 2023 */

#include "config.h"
#include "matrix.h"
#include "wait.h"
#include <avr/io.h>


// Input with pull-up [PORT:1 (IN), DDR:0 (HIGH)]
#define INIT_INPORT(OUTPORT, PINS) (PORT##OUTPORT |= (PINS), DDR##OUTPORT &= ~(PINS))
// Test previously initialised input pin, output bitmask ID
#define READ_INPORT(ID, INPORT, INPIN) ((PIN##INPORT & _BV(INPIN)) ? 0 : _BV(ID))
// Output low [PORT:0 (OUT), DDR:1 (LOW)] to select
#define SELECT_OUTPORT(ID, OUTPORT, PIN) \
	case (ID): PORT##OUTPORT &= ~_BV(PIN), DDR##OUTPORT |= _BV(PIN); break;
// Hi-Z [PORT:0 (IN), DDR:0 (HIGH)] to deselect
#define DESELECT_OUTPORT(ID, OUTPORT, PIN) \
	case (ID): PORT##OUTPORT &= ~_BV(PIN), DDR##OUTPORT &= ~_BV(PIN); break;


// Diode direction: Column to anode, cathode facing row

// Column pins: Left to right
// col:  0,  1,  2,  3
// pin: D6, B0, B1, C5
static void init_columns(void)
{
	INIT_INPORT(D, _BV(6));
	INIT_INPORT(B, _BV(0) | _BV(1));
	INIT_INPORT(C, _BV(5));
}

static matrix_row_t read_columns(void)
{
	return
		READ_INPORT(0, D, 6) |
		READ_INPORT(1, B, 0) |
		READ_INPORT(2, B, 1) |
		READ_INPORT(3, C, 5);
}

// Row pins: Top to bottom
// col:  0,  2,  3,  4,  5,  6
// pin: C4, C2, D0, D5, D4, D1
static void select_row(uint8_t row)
{
	switch (row)
	{
	SELECT_OUTPORT(0, C, 4)
	SELECT_OUTPORT(1, C, 2)
	SELECT_OUTPORT(2, D, 0)
	SELECT_OUTPORT(3, D, 5)
	SELECT_OUTPORT(4, D, 4)
	SELECT_OUTPORT(5, D, 1)
	default: break;
	}
}

static void deselect_row(uint8_t row)
{
	switch (row)
	{
	DESELECT_OUTPORT(0, C, 4)
	DESELECT_OUTPORT(1, C, 2)
	DESELECT_OUTPORT(2, D, 0)
	DESELECT_OUTPORT(3, D, 5)
	DESELECT_OUTPORT(4, D, 4)
	DESELECT_OUTPORT(5, D, 1)
	default: break;
	}
}


#ifndef DEBOUNCE
#  define DEBOUNCE 5
#endif

static uint8_t debouncing = DEBOUNCE;

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t debounce[MATRIX_ROWS];

void matrix_init(void)
{
	// Initialise row & column pins
	for (uint8_t row = 0; row < MATRIX_ROWS; ++row)
		deselect_row(row);
	init_columns();

	// Clear matrix state
	for (uint8_t row = 0; row < MATRIX_ROWS; ++row)
		matrix[row] = 0, debounce[row] = 0;
}

uint8_t matrix_scan(void)
{
	for (uint8_t row = 0; row < MATRIX_ROWS; ++row)
	{
		select_row(row);
		wait_us(30);  // Stabilise matrix reads with a short delay

		const matrix_row_t columns = read_columns();
		if (columns != debounce[row])
		{
			debounce[row] = columns;
			debouncing = DEBOUNCE;
		}

		deselect_row(row);
	}

	switch (debouncing)
	{
	case 1:
		debouncing = 0;
		for (uint8_t i = 0; i < MATRIX_ROWS; ++i)
			matrix[i] = debounce[i];
	case 0: break;
	default:
		--debouncing;
		wait_ms(1);
		break;
	}

	return 1;
}

matrix_row_t matrix_get_row(uint8_t row)
{
	return matrix[row];
}
