#include <stdint.h>
#include <stdbool.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"

void hook_early_init ( void )
{
	// JTAG disable for PORT F. write JTD bit twice within four cycles.
	MCUCR |= (1<<JTD);
	MCUCR |= (1<<JTD);
}
