#include <stdint.h>
#include <avr/io.h>
#include "led.h"

void led_set(uint8_t usb_led)
{
  CONFIG_LED_IO;

  if (usb_led & (1 << USB_LED_CAPS_LOCK))
  { USB_LED_CAPS_LOCK_ON; } else { USB_LED_CAPS_LOCK_OFF; }

  if (usb_led & (1 << USB_LED_NUM_LOCK))
  { USB_LED_NUM_LOCK_ON; } else { USB_LED_NUM_LOCK_OFF; }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK))
  { USB_LED_SCROLL_LOCK_ON; } else { USB_LED_SCROLL_LOCK_OFF; }
}
