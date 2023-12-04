/* led.c - grandpad - (c) a dinosaur 2023 */

#include "led.h"
#include "light_ws2812.h"


__attribute__((weak)) struct cRGB led_rgb_numlock_off = { 0x00, 0x00, 0x00 };
__attribute__((weak)) struct cRGB led_rgb_numlock_on  = { 0x2F, 0x2F, 0x2F };

__attribute__((weak)) void led_set_user(uint8_t state)
{
	ws2812_setleds(state & _BV(USB_LED_NUM_LOCK)
		? &led_rgb_numlock_on
		: &led_rgb_numlock_off, 1);
}

void led_set(uint8_t state)
{
	led_set_user(state);
}
