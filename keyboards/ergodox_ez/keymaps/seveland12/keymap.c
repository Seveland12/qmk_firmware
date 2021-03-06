#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  RGB_SLD,
  
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox( //base layer
	   // left hand
	   KC_EQUAL,       KC_1,          KC_2,            KC_3,    KC_4,     KC_5,     TG(1),
	   KC_DELETE,      KC_Q,          KC_W,            KC_E,    KC_R,     KC_T,     KC_HYPR,
	   CTL_T(KC_NO),   KC_A,          KC_S,            KC_D,    KC_F,     KC_G,
	   KC_LSHIFT,      CTL_T(KC_Z),   KC_X,            KC_C,    KC_V,     KC_B,     ALT_T(KC_NO),
	   LT(1,KC_GRAVE), KC_QUOTE,      LALT(KC_LSHIFT), KC_LEFT, KC_RIGHT,
	                                                                ALT_T(KC_APPLICATION), KC_LGUI,
	                                                                                       KC_HOME,
	                                                                  KC_SPACE, KC_TAB,    KC_END,

	   // right hand
	   TG(1),          KC_6,          KC_7,            KC_8,        KC_9,            KC_0,             KC_MINUS,
	   KC_MEH,         KC_Y,          KC_U,            KC_I,        KC_O,            KC_P,             KC_BSLASH,
	   KC_H,           KC_J,          KC_K,            KC_L,        LT(2,KC_SCOLON), RCTL_T(KC_QUOTE),
	   RALT_T(KC_NO),  KC_N,          KC_M,            KC_COMMA,    KC_DOT,          RCTL_T(KC_SLASH), KC_RSHIFT,
	   KC_UP,          KC_DOWN,       KC_LBRACKET,     KC_RBRACKET, MO(1),
	   KC_LALT,   CTL_T(KC_ESCAPE),
	   KC_PGUP,
	   KC_PGDOWN, KC_BSPACE, KC_ENTER),

  [1] = LAYOUT_ergodox( // symbol and numpad layer
	   // left hand
	   KC_ESCAPE,      KC_F1,    KC_F2,    KC_F3,       KC_F4,         KC_F5,     KC_TRANSPARENT,
	   KC_TRANSPARENT, KC_EXLM,  KC_AT,    KC_LCBR,     KC_RCBR,       KC_PIPE,   KC_TRANSPARENT,
	   KC_TRANSPARENT, KC_HASH,  KC_DLR,   KC_LPRN,     KC_RPRN,       KC_GRAVE,
	   KC_TRANSPARENT, KC_PERC,  KC_CIRC,  KC_LBRACKET, KC_RBRACKET,   KC_TILD,   KC_TRANSPARENT,
	   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
	                                                                   RGB_MOD,   KC_TRANSPARENT,
	                                                                              KC_TRANSPARENT,
	                                                          RGB_VAD, RGB_VAI,   KC_TRANSPARENT,

       // right hand
	   KC_TRANSPARENT, KC_F6,     KC_F7,   KC_F8,       KC_F9,          KC_F10,         KC_F11,
	   KC_TRANSPARENT, KC_UP,     KC_7,    KC_8,        KC_9,           KC_ASTR,        KC_F12,
	   KC_DOWN,        KC_4,      KC_5,    KC_6,        KC_PLUS,        KC_TRANSPARENT,
	   KC_TRANSPARENT, KC_AMPR,   KC_1,    KC_2,        KC_3,           KC_BSLASH,      KC_TRANSPARENT,
	   KC_TRANSPARENT, KC_DOT,    KC_0,    KC_EQUAL,    KC_TRANSPARENT,
	   RGB_TOG,        RGB_SLD,
	   KC_TRANSPARENT,
	   KC_TRANSPARENT, RGB_HUD, RGB_HUI),

  [2] = LAYOUT_ergodox(// mouse layer
	   // left hand
	   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
	   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_UP,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
	   KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_TRANSPARENT,
	   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
	   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_WH_UP,    KC_MS_WH_DOWN,
	                                                                                   KC_TRANSPARENT, KC_TRANSPARENT,
	                                                                                                   KC_TRANSPARENT,
	                                                                       KC_MS_BTN1, KC_MS_BTN2,     KC_TRANSPARENT,

	   // right hand
	   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT,      KC_TRANSPARENT,      KC_TRANSPARENT, KC_TRANSPARENT,
	   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT,      KC_TRANSPARENT,      KC_TRANSPARENT, KC_TRANSPARENT,
	                   KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT,      KC_TRANSPARENT,      KC_TRANSPARENT, KC_MEDIA_PLAY_PAUSE,
	   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,  KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_TRANSPARENT, KC_TRANSPARENT,
	                                   KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN,   KC_AUDIO_MUTE,       KC_TRANSPARENT, KC_TRANSPARENT,
	   KC_TRANSPARENT, KC_TRANSPARENT,
	   KC_TRANSPARENT,
	   KC_TRANSPARENT, KC_TRANSPARENT, KC_WWW_BACK),

};

bool suspended = false;
const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
      break;
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 1:
        ergodox_right_led_1_on();
        break;
      case 2:
        ergodox_right_led_2_on();
        break;
      case 3:
        ergodox_right_led_3_on();
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      default:
        break;
    }
    return state;

};
