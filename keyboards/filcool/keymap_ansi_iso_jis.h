
static const uint8_t PROGMEM keymaps[][MATRIX_COLS][MATRIX_ROWS] = {
    /* Layer 0: Standard ANSI layer */
    KEYMAP(\
         ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,    PSCR,SLCK,PAUS,                         \
         GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,   INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS, \
         TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,   DEL, END, PGDN,    P7,  P8,  P9,  PPLS, \
         LCAP,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,                       P4,  P5,  P6,        \
         LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RSFT,        UP,           P1,  P2,  P3,  PENT, \
         LCTL,LGUI,LALT,               SPC,                RALT,RGUI, FN0,RCTL,   LEFT,DOWN,RGHT,    P0,  PDOT),          \
    /* Layer 1: Colemak */
    KEYMAP(\
         ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,    PSCR,SLCK,PAUS,                         \
         GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,   INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS, \
         TAB, Q,   W,   F,   P,   G,   J,   L,   U,   Y,   SCLN,LBRC,RBRC,BSLS,   DEL, END, PGDN,    P7,  P8,  P9,  PPLS, \
         LCAP,A,   R,   S,   T,   D,   H,   N,   E,   I,   O,   QUOT,     ENT,                       P4,  P5,  P6,        \
         LSFT,NUBS,Z,   X,   C,   V,   B,   K,   M,   COMM,DOT, SLSH,     RSFT,        UP,           P1,  P2,  P3,  PENT, \
         LCTL,LGUI,LALT,               SPC,                RALT,RGUI, FN0,RCTL,   LEFT,DOWN,RGHT,    P0,  PDOT),          \
    /* Layer 2: Function layer */
    KEYMAP(\
         BTLD,     NO  ,NO,  NO,  NO,  FN3, FN4, NO,  NO,  NO,  NO,  NO,  NO,     NO,  FN2, NO,                           \
         NLCK,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,     VOLD,MUTE,VOLU,    NO,  NO,  NO,  NO,   \
         CALC,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,     MPRV,MPLY,MNXT,    NO,  NO,  NO,  NO,   \
         NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,       NO,                        NO,  NO,  NO,        \
         NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,       NO,          NO,           NO,  NO,  NO,  NO,   \
         NO,  NO,  NO,                 NO,                 NO,  NO,  TRNS,NO,     NO,  NO,  NO,      NO,  NO)
};

enum macro_id {
    DOUBLE_ZERO,
    GREGGO,
};

const action_t PROGMEM fn_actions[] =
{
    [0] = ACTION_LAYER_MOMENTARY(2),
    [1] = ACTION_MACRO(DOUBLE_ZERO),
    [2] = ACTION_MACRO(GREGGO),
    [3] = ACTION_DEFAULT_LAYER_SET(0),
    [4] = ACTION_DEFAULT_LAYER_SET(1)
};

const macro_t* action_get_macro(keyrecord_t* record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case DOUBLE_ZERO:
            return (record->event.pressed ?
                MACRO( T(0), T(0), END ) :
                MACRO_NONE );
        case GREGGO:
            return (record->event.pressed ?
                MACRO( D(LSFT), T(SCLN), T(G), U(LSFT), T(R), T(E), T(G), T(G), T(O), D(LSFT), T(SCLN), END ) :
                MACRO_NONE );
    }
    return MACRO_NONE;
}
