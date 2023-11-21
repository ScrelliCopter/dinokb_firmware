#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "action_layer.h"
#include "action_util.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"


/* Clueboard matrix layout
 * ,-----------------------------------------------------------.  ,---.
 * | 00| 01| 02| 03| 04| 05| 06| 07| 50| 51| 52| 53| 54| 55| 56|  | 57|
 * |-----------------------------------------------------------|  |---|
 * |   10| 11| 12| 13| 14| 15| 16| 17| 60| 61| 62| 63| 64|   65|  | 67|
 * |-----------------------------------------------------------|  `---'
 * |    20| 21| 22| 23| 24| 25| 26| 27| 70| 71| 72| 73| 74|  75|
 * |------------------------------------------------------------.
 * |  30| 31| 32| 33| 34| 35| 36| 37| 80| 81| 82| 83| 84|  85|86|
 * |------------------------------------------------------------------.
 * |  40| 41|  42|  43|   45|       46|   90|  92|  93| 94| 95| 96| 97|
 * `------------------------------------------------------------------'
 * ,-----------------------------------------------------------.  ,---.
 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Yen| BS|  |Ins|
 * |-----------------------------------------------------------|  |---|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  |Del|
 * |-----------------------------------------------------------|  `---'
 * |Caps  |  A|  S|  D|  F|  G|  H|  J|  k|  L|  ;|  '| # | Ent|
 * |--------------------------------------------------------------.
 * |Shift| \|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|  \|Shift| Up|
 * |------------------------------------------------------------------.
 * |Ctrl|Alt|Gui |MHen| Space| Space|Henk|Gui |Ctrl|  Fn|Left|Down|Rgt|
 * `------------------------------------------------------------------'
 */
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array

#define KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k50, k51, k52, k53, k54, k55, k56, k57, \
    k10, k11, k12, k13, k14, k15, k16, k17, k60, k61, k62, k63, k64, k65,      k67, \
    k20, k21, k22, k23, k24, k25, k26, k27, k70, k71, k72, k73, k74, k75,           \
    k30, k31, k32, k33, k34, k35, k36, k37, k80, k81, k82, k83, k84, k85, k86,      \
    k40, k41, k42, k43,      k45, k46,      k90,      k92, k93, k94, k95, k96, k97  \
) { \
    { KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05, KC_##k06, KC_##k07 }, \
    { KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15, KC_##k16, KC_##k17 }, \
    { KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25, KC_##k26, KC_##k27 }, \
    { KC_##k30, KC_##k31, KC_##k32, KC_##k33, KC_##k34, KC_##k35, KC_##k36, KC_##k37 }, \
    { KC_##k40, KC_##k41, KC_##k42, KC_##k43, KC_NO,    KC_##k45, KC_##k46, KC_NO    }, \
    { KC_##k50, KC_##k51, KC_##k52, KC_##k53, KC_##k54, KC_##k55, KC_##k56, KC_##k57 }, \
    { KC_##k60, KC_##k61, KC_##k62, KC_##k63, KC_##k64, KC_##k65, KC_NO,    KC_##k67 }, \
    { KC_##k70, KC_##k71, KC_##k72, KC_##k73, KC_##k74, KC_##k75, KC_NO,    KC_NO    }, \
    { KC_##k80, KC_##k81, KC_##k82, KC_##k83, KC_##k84, KC_##k85, KC_##k86, KC_NO    }, \
    { KC_##k90, KC_NO,    KC_##k92, KC_##k93, KC_##k94, KC_##k95, KC_##k96, KC_##k97 }  \
}

#ifdef KEYMAP_SECTION_ENABLE
#  define KEYMAP_SECTION __attribute__((section(".keymap.keymaps")))
#else
#  define KEYMAP_SECTION PROGMEM
#endif

#endif
