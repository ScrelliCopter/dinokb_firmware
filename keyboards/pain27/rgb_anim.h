/* rgb_anim.h - pain27 - (C) 2023 a dinosaur */

#ifndef RGB_ANIM_H
#define RGB_ANIM_H

#include <stdint.h>

#ifdef UNDERGLOW_ENABLE

void rgb_set(uint8_t id, uint8_t rgb[3]);
void rgb_update(uint8_t num);

enum rgbanim_list
{
	RGBANIM_NONE = 0,
	RGBANIM_RAINBOW,
	RGBANIM_BREATHE,
	RGBANIM_RANDOM,
	RGBANIM_WAVE,
	RGBANIM_CIRCULAR,
	RGBANIM_RACING,

	NUM_RGBANIM,
	RGBANIM_FIRST = RGBANIM_NONE,
	RGBANIM_LAST = RGBANIM_RACING
};

void rgb_anim_init(void);
void rgb_anim_update(void);
void rgb_anim_change_program(uint8_t program);
void rgb_anim_cycle_program(void);

#endif

#endif//RGB_ANIM_H
