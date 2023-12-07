/* rgb_anim.c - pain27 - (C) 2023 a dinosaur */

#include "rgb_anim.h"
#include "light_ws2812.h"
#include "timer.h"
#include "progmem.h"
#include <string.h>
#include <stdbool.h>

#define ANIMATE_START_INDEX 2
#define ANIMATE_LENGTH (RGBLED_NUM - ANIMATE_START_INDEX)


// Physical positions of the pain27's RGB LEDs
typedef struct { uint8_t x, y; } Point;
static const Point pixel_positions[9] PROGMEM =
{
	[0] = { 30, 27 }, { 54, 27 },                         // Spacebar
	[2] = { 57, 27 }, { 35, 27 }, { 13, 27 },             // Bottom row
	[5] = {  9,  7 }, { 25,  7 }, { 41,  7 }, { 57,  7 }  // Top row
};


/////////////////////////
/// Helpers and utitilies
static uint16_t xorshift16(void)
{
	static uint16_t state = 1ul;
	state ^= state << 7; state ^= state >> 9; state ^= state << 8;
	return state;
}

static struct cRGB hue(const uint8_t theta)
{
	const uint16_t theta6 = ((uint16_t)theta << 1) + ((uint16_t)theta << 2);
	if (theta6 < 0x100)
		return (struct cRGB){ .r = 0xFF, .g = theta6, .b = 0x00 };
	else if (theta6 < 0x200)
		return (struct cRGB){ .r = 0x1FF - theta6, .g = 0xFF, .b = 0x00 };
	else if (theta6 < 0x300)
		return (struct cRGB){ .r = 0x00, .g = 0xFF, .b = theta6 - 0x200 };
	else if (theta6 < 0x400)
		return (struct cRGB){ .r = 0x00, .g = 0x3FF - theta6, .b = 0xFF };
	else if (theta6 < 0x500)
		return (struct cRGB){ .r = theta6 - 0x400, .g = 0x00, .b = 0xFF };
	else
		return (struct cRGB){ .r = 0xFF, .g = 0x00, .b = 0x5FF - theta6 };
}

// Adapted & minified from TMK sleep_led.c
#define BREATHING_TABLE_LEN 22
static const uint8_t breathing_table[BREATHING_TABLE_LEN] PROGMEM =
{
	1,   2,   4,   6,  10,  15,  23,  32,  44,  58,  74,
   93, 113, 135, 157, 179, 199, 218, 233, 245, 252, 255
};
static inline uint8_t read_breathing_table(uint8_t idx)
{
	return (idx >= 11 && idx <= 53)
		? pgm_read_byte(&breathing_table[idx < 33 ? idx - 11 : 53 - idx])
		: 0;
}


//////////////////////////
/// Animation lookup table
typedef uint16_t (*rgbanim_func)(struct cRGB*, uint8_t, bool);

static uint16_t rgbanim_racing(struct cRGB*, uint8_t, bool);
static uint16_t rgbanim_clear(struct cRGB*, uint8_t, bool);
static uint16_t rgbanim_random(struct cRGB*, uint8_t, bool);
static uint16_t rgbanim_circular_random(struct cRGB*, uint8_t, bool);
static uint16_t rgbanim_breathe(struct cRGB*, uint8_t, bool);
static uint16_t rgbanim_wave(struct cRGB*, uint8_t, bool);
static uint16_t rgbanim_rainbow(struct cRGB*, uint8_t, bool);

static const rgbanim_func rgbanim_functions[NUM_RGBANIM] =
{
	[RGBANIM_NONE]     = rgbanim_clear,
	[RGBANIM_RAINBOW]  = rgbanim_rainbow,
	[RGBANIM_BREATHE]  = rgbanim_breathe,
	[RGBANIM_RANDOM]   = rgbanim_random,
	[RGBANIM_WAVE]     = rgbanim_wave,
	[RGBANIM_CIRCULAR] = rgbanim_circular_random,
	[RGBANIM_RACING]   = rgbanim_racing
};


/////////////////////////////
/// Animation implementations
uint16_t rgbanim_clear(struct cRGB* leds, uint8_t num, bool first)
{
	if (!first) return 0;
	for (uint8_t i = 0; i < num; ++i)
		leds[i] = (struct cRGB){ 0, 0, 0 };
	return 0;
}

static uint8_t tick256 = 0;

uint16_t rgbanim_racing(struct cRGB* leds, uint8_t num, bool first)
{
#define SUBTICK_COUNT 4
#define BLEND_MUL (0x100 / SUBTICK_COUNT)
#define CALCULATE_PIXEL() (struct cRGB){        \
		((tick256 >> 1) + i * 10) & 0xFF,       \
		(((tick256 >> 1) + i + 1) * 10) & 0xFF, \
		((tick256 + i + 2) * 10) & 0xFF }
	static uint8_t subtick = 0;
	static struct cRGB backbuffer[ANIMATE_LENGTH];

	if (first || !subtick--)
	{
		for (uint8_t i = 0; i < num; ++i)
			backbuffer[i] = CALCULATE_PIXEL();
		memcpy(leds, backbuffer, num);
		++tick256;
		subtick = SUBTICK_COUNT;
	}
	else
	{
		for (uint8_t i = 0; i < num; ++i)
		{
			const struct cRGB front = CALCULATE_PIXEL();
			leds[i] = (struct cRGB){
				.g = (backbuffer[i].g * subtick * BLEND_MUL
					+ front.g * (SUBTICK_COUNT - subtick) * BLEND_MUL) >> 8,
				.r = (backbuffer[i].r * subtick * BLEND_MUL
					+ front.r * (SUBTICK_COUNT - subtick) * BLEND_MUL) >> 8,
				.b = (backbuffer[i].b * subtick * BLEND_MUL
					+ front.b * (SUBTICK_COUNT - subtick) * BLEND_MUL) >> 8
			};
		}
	}
	return 80 / SUBTICK_COUNT;
}

uint16_t rgbanim_random(struct cRGB* leds, uint8_t num, bool first)
{
	if (first)
	{
		for (uint8_t i = 0; i < num; ++i)
		{
			const uint16_t r12 = xorshift16(), r3 = xorshift16();
			leds[i] = (struct cRGB){ (uint8_t)r12, (uint8_t)(r12 >> 8), (uint8_t)r3 };
		}
		return 420;
	}

	uint16_t change_bits = xorshift16();
	uint8_t num_changes = 0;
	for (uint8_t i = 0; i < num; ++i)
	{
		if (change_bits & 0x1)
		{
			const uint16_t r12 = xorshift16(), r3 = xorshift16();
			leds[i] = (struct cRGB){ (uint8_t)r12, (uint8_t)(r12 >> 8), (uint8_t)r3 };
			++num_changes;
		}
		change_bits >>= 1;
	}
	return 94 * (num - num_changes + 1);
}

uint16_t rgbanim_circular_random(struct cRGB* leds, uint8_t num, bool first)
{
	static uint8_t tick, sub;
	if (first)
	{
		for (uint8_t i = 0; i < num; ++i)
			leds[i] = (struct cRGB){ 0, 0, 0 };
		tick = sub = 0;
	}
	else
	{
		for (uint8_t i = 0; i < num; ++i)
			leds[i] = (struct cRGB){
				(leds[i].g >> 1) + (leds[i].g >> 2),
				(leds[i].r >> 1) + (leds[i].r >> 2),
				(leds[i].b >> 1) + (leds[i].b >> 2)
			};
	}

	if (!sub--)
	{
		const uint16_t r12 = xorshift16(), r3 = xorshift16();
		leds[tick] = (struct cRGB){ (uint8_t)r12, (uint8_t)(r12 >> 8), (uint8_t)r3 };
		if (++tick >= num)
			tick = 0;
		sub = 2;
	}

	return 88;
}

static uint8_t breathe_tick = 0;

uint16_t rgbanim_breathe(struct cRGB* leds, uint8_t num, bool)
{
	static struct cRGB colour = { 0xFF, 0xFF, 0xFF };

	const uint16_t scaler = read_breathing_table(breathe_tick);
	struct cRGB scaled = {
		.b = (colour.b * scaler) >> 8,
		.g = (colour.g * scaler) >> 8,
		.r = (colour.r * scaler) >> 8 };

	if (++breathe_tick == 0x40)
	{
		uint16_t r12 = xorshift16();
		colour = hue(r12 & 0xFF);
		r12 >>= 9;
		colour = (struct cRGB){
			.b = (colour.b * (0x80 + r12)) >> 8,
			.g = (colour.g * (0x80 + r12)) >> 8,
			.r = (colour.r * (0x80 + r12)) >> 8 };
		breathe_tick = 0;
	}

	for (uint8_t i = 0; i < num; ++i)
		leds[i] = scaled;

	return 66;
}

uint16_t rgbanim_wave(struct cRGB* leds, uint8_t num, bool first)
{
	static uint8_t tick = 0;
	static bool reverse;
	if (first) reverse = false;

	for (uint8_t i = 0; i < num; ++i)
	{
		const int16_t position = reverse ? (int16_t)tick - 22 : 127 - 22 - (int16_t)tick;
		int16_t distance = position - (int16_t)pgm_read_byte(&pixel_positions[i + ANIMATE_START_INDEX].x);
		distance = distance < 0 ? 0-distance : distance;
		distance >>= 1;
		const uint8_t intensity = distance < 22 ? pgm_read_byte(&breathing_table[21 - distance]) : 0;
		leds[i] = (struct cRGB){ intensity, intensity, intensity };
	}

	if (++tick == 200)
	{
		tick = 0;
		reverse = (xorshift16() & 0x1000) == 0x1000;
	}

	return 25;
}

static uint16_t rgbanim_rainbow(struct cRGB* leds, uint8_t num, bool)
{
	static uint8_t tick = 0;
	for (uint8_t i = 0; i < num; ++i)
		leds[i] = hue(tick + (pgm_read_byte(&pixel_positions[i + ANIMATE_START_INDEX].x) >> 2));
	++tick;
	return 38;
}


//////////////
/// Public API
static uint8_t rgb_program = RGBANIM_NONE;
static uint16_t timer_last = 0ul, duration = 0ul;
struct cRGB rgb_memory[RGBLED_NUM];


void rgb_set(uint8_t id, uint8_t rgb[3])
{
	rgb_memory[id] = (struct cRGB){ .g = rgb[1], .r = rgb[0], .b = rgb[2] };
}

void rgb_update(uint8_t num)
{
	ws2812_setleds(rgb_memory, num < RGBLED_NUM ? num : RGBLED_NUM);
}


void rgb_anim_init(void)
{
	// Clear non-animating LEDs
	for (uint8_t i = 0; i < ANIMATE_START_INDEX; ++i)
		rgb_memory[i] = (struct cRGB){ 0, 0, 0 };
	// Apply startup program
	duration = rgbanim_functions[rgb_program](rgb_memory + ANIMATE_START_INDEX, ANIMATE_LENGTH, true);
	ws2812_setleds(rgb_memory, RGBLED_NUM);
}

void rgb_anim_update(void)
{
	if (!duration || timer_elapsed(timer_last) < duration)
		return;
	duration = rgbanim_functions[rgb_program](rgb_memory + ANIMATE_START_INDEX, ANIMATE_LENGTH, false);
	ws2812_setleds(rgb_memory, RGBLED_NUM);
	timer_last = timer_read();
}

void rgb_anim_change_program(uint8_t program)
{
	if (program == rgb_program || program < RGBANIM_FIRST || program > RGBANIM_LAST)
		return;
	rgb_program = program;
	duration = rgbanim_functions[rgb_program](rgb_memory + ANIMATE_START_INDEX, ANIMATE_LENGTH, true);
	ws2812_setleds(rgb_memory, RGBLED_NUM);
}

void rgb_anim_cycle_program(void)
{
	uint8_t next_program = rgb_program + 1;
	if (next_program > RGBANIM_LAST)
		next_program = RGBANIM_FIRST; // Wrap at end
	rgb_anim_change_program(next_program);
}
