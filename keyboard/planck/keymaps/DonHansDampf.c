#include "planck.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define PREVENT_STUCK_MODIFIERS

#define _NEO 0
#define _FN 1
#define _RAISE 2

// Macro name shortcuts
#define NEO M(_NEO)
#define FN M(_FN)
#define RAISE M(_RAISE)
// #define LOWER M(_LOWER)
#define M_BL 5

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* NEO */
[_NEO] = {
  {KC_TAB,  KC_X,    KC_V,    KC_L,    KC_C,    KC_W,    KC_K,    KC_H,    KC_G,    KC_F,    KC_Q,    KC_BSPC},
  {KC_LGUI, KC_U,    KC_I,    KC_A,    KC_E,    KC_O,    KC_S,    KC_N,    KC_R,    KC_T,    KC_D,    KC_QUOT},
  {KC_ESC, KC_SCLN,  KC_SLSH, KC_J,    KC_P,    KC_Z,    KC_B,    KC_M,    KC_Y,    KC_COMM, KC_DOT,  KC_ENT },
  {FN,     KC_PGDOWN,KC_PGUP, KC_LALT, KC_SPC,  RAISE,   KC_LCTL, KC_LSFT, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* FN */
[_FN] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},
/* Raise */
[_RAISE] = {
  {_______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_PIPE, KC_LCBR, KC_RCBR, KC_UNDS, KC_PLUS, KC_DEL},
  {_______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, KC_LPRN, KC_RPRN, KC_MINS, KC_EQL,  _______},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______, KC_LBRC, KC_RBRC, KC_GRV,  KC_TILD, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, BL_DEC,  BL_INC,  KC_MPLY}
}
};

const uint16_t PROGMEM fn_actions[] = {

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case _NEO:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_NEO);
          }
          break;
        case _FN:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_FN);
          }
          break;
        case _RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
          } else {
            layer_off(_RAISE);
          }
          break;
        case M_BL:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};

uint8_t starting_note = 0x0C;
int offset = 0;
