/* light_ws2812_config.h - grandpad
   - User Configuration file for the light_ws2812_lib */

#ifndef WS2812_CONFIG_H
#define WS2812_CONFIG_H

#include "config.h"

//////////////////////////////////////////////////////////////////////
/// Define Reset time in µs.
///
/// This is the time the library spends waiting after writing the data
///
/// WS2813 needs 300 µs reset time
/// WS2812 and clones only need 50 µs
#define ws2812_resettime  300

//////////////////
/// Define I/O pin
#define ws2812_port RGB_DI_PORT  // Data port
#define ws2812_pin  RGB_DI_PIN   // Data out pin

#endif//WS2812_CONFIG_H
