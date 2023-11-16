#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "led.h"

#define CAPLOCK_BIT (1 << USB_LED_CAPS_LOCK)
#define NUMLOCK_BIT (1 << USB_LED_NUM_LOCK)
#define SCRLOCK_BIT (1 << USB_LED_SCROLL_LOCK)

static uint8_t ledstate = 0;
bool swap_num_scroll = false;

void update_leds(void)
{
  CONFIG_LED_IO;

  if (ledstate & CAPLOCK_BIT)
  { USB_LED_CAPS_LOCK_ON; } else { USB_LED_CAPS_LOCK_OFF; }

  if (ledstate & (swap_num_scroll ? SCRLOCK_BIT : NUMLOCK_BIT))
  { USB_LED_NUM_LOCK_ON; } else { USB_LED_NUM_LOCK_OFF; }

  if (ledstate & (swap_num_scroll ? NUMLOCK_BIT : SCRLOCK_BIT))
  { USB_LED_SCROLL_LOCK_ON; } else { USB_LED_SCROLL_LOCK_OFF; }
}

void led_set(uint8_t usb_led)
{
  ledstate = usb_led & (CAPLOCK_BIT | NUMLOCK_BIT | SCRLOCK_BIT);
  update_leds();
}
