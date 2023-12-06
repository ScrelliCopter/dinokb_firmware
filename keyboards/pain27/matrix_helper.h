/* matrix_helper.h - pain27 - (C) 2023 a dinosaur */

#ifndef MATRIX_HELPER_H
#define MATRIX_HELPER_H

#include "config.h"
#include "matrix.h"
#include "wait.h"
#include "timer.h"

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


static void init_columns(void);
static matrix_row_t read_columns(void);
static void select_row(uint8_t row);
static void deselect_row(uint8_t row);


static inline void matrix_init_col2row(void)
{
	for (uint8_t row = 0; row < MATRIX_ROWS; ++row)
		deselect_row(row);
	init_columns();
}

#ifndef DEBOUNCE
#  define DEBOUNCE 5
#endif

static inline bool matrix_read_columns(matrix_row_t* mtx, uint8_t row)
{
	select_row(row);
	wait_us(30);  // Stabilise matrix reads with a short delay
	const matrix_row_t columns = read_columns();

	if (columns != mtx[row])
	{
		mtx[row] = columns;
		deselect_row(row);
		return true;
	}

	deselect_row(row);
	return false;
}

static inline bool do_debounce(matrix_row_t* outmtx, matrix_row_t* debmtx, uint16_t timer)
{
	if (timer_elapsed(timer) < DEBOUNCE)
		return true;

	for (uint8_t i = 0; i < MATRIX_ROWS; ++i)
		outmtx[i] = debmtx[i];
	return false;
}

#define MATRIX_DEFAULT_GET_ROW(MATRIX)       \
	matrix_row_t matrix_get_row(uint8_t row) \
	{                                        \
		return MATRIX[row];                  \
	}

#if DEBOUNCE > 0
#  define MATRIX_DEFAULT_CLEAR(MATRIX, DEBOUNCE)        \
	void matrix_clear(void)                             \
	{                                                   \
		for (uint8_t row = 0; row < MATRIX_ROWS; ++row) \
			MATRIX[row] = DEBOUNCE[row] = 0;            \
	}
#else
#  define MATRIX_DEFAULT_CLEAR(MATRIX, DEBOUNCE)        \
	void matrix_clear(void)                             \
	{                                                   \
		for (uint8_t row = 0; row < MATRIX_ROWS; ++row) \
			MATRIX[row] = 0;                            \
	}
#endif

#endif//MATRIX_HELPER_H
