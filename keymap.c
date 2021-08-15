/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _GAME,
    _GAME_RAISE,
    _LOWER,
    _RAISE,
    _MAGIC,
    _DEBUG
};

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,
    KC_HNUM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bspc  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | Del  | LGUI |  | RGUI | | \  |   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      | LCTR | LALT | Lower| Enter|  | Space| Raise| RAlt | RCTR |      |
 *                         `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
      KC_TAB,               KC_Q, KC_W, KC_E,    KC_R,     KC_T,                                              KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,    KC_BSPC,
      MT(MOD_LCTL, KC_ESC), KC_A, KC_S, KC_D,    KC_F,     KC_G,                                              KC_H,    KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT,              KC_Z, KC_X, KC_C,    KC_V,     KC_B,    KC_DEL,     KC_LGUI, KC_RGUI, KC_BSLS,    KC_N,    KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                        KC_MUTE, KC_LCTRL, KC_LALT, MO(_LOWER), KC_ENT,  KC_SPC,  MO(_RAISE), KC_RALT, KC_RCTRL, XXXXXXX
    ),
/*
 * Base Layer: Game
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bspc  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Ctrl  |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | Esc  | LGUI |  | RGUI | | \  |   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      | Del  | LALT | Lower| Space|  | Enter| Raise| RAlt | RCTR |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAME] = LAYOUT(
      KC_TAB,   KC_Q,  KC_W,   KC_E,    KC_R,   KC_T,                                              KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,    KC_BSPC,
      KC_LCTRL, KC_A,  KC_S,   KC_D,    KC_F,   KC_G,                                              KC_H,    KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT,  KC_Z,  KC_X,   KC_C,    KC_V,   KC_B,    KC_ESC,     KC_LGUI, KC_RGUI, KC_BSLS,    KC_N,    KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                               XXXXXXX, KC_DEL, KC_LALT, MO(_LOWER), KC_SPC,  KC_ENT,  MO(_GAME_RAISE), KC_RALT, KC_RCTRL, XXXXXXX
    ),
/*
 * Lower Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Grave |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |  Del   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |  [   |  ]   |WheelU|                              |   +  |  (   |  )   |  =   |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | RClk | MClk | LClk |WheelD|NumLck|      |  |      |      |   _  |  -   |      |      |      | - _    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT(
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
      _______, _______, _______, KC_LBRC, KC_RBRC, KC_HNUM,                                     KC_PLUS, KC_LPRN, KC_RPRN, KC_EQL,  _______, _______,
      _______, _______, KC_BTN2, KC_BTN3, KC_BTN1, _______, _______, _______, _______, _______, KC_UNDS, KC_MINS, _______, _______, _______, _______,
                                 XXXXXXX, _______, _______, _______, _______, _______, MO(_DEBUG), _______, _______, XXXXXXX
    ),
/*
 * Raise Layer: Number keys, media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |      |                              |      |      |  Ins | Print| Pause|  Del   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  | Caps |                              | Left | Down | Up   | Right|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F9  |  F10 |  F11 |  F12 |      |      |      |  |      |      | Home | PgUp | PgDn | End  |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_RAISE] = LAYOUT(
      _______, KC_F1, KC_F2,  KC_F3,  KC_F4,  _______,                                     _______, _______, KC_INS,  MO(_MAGIC), KC_PAUS, KC_DEL,
      _______, KC_F5, KC_F6,  KC_F7,  KC_F8,  KC_CAPS,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,    _______, _______,
      _______, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,     _______, _______,
                            XXXXXXX, _______, _______, MO(_DEBUG), _______, _______, _______, _______, _______, XXXXXXX
    ),
/*
 * Magic SysRq layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |   E  |   R  |      |                              |      |   U  |   I  |      | Print|        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |   S  |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |   B  |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MAGIC] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, KC_E,    KC_R,    XXXXXXX,                                     XXXXXXX, KC_U,    KC_I,    XXXXXXX, KC_PSCR, XXXXXXX,
      XXXXXXX, XXXXXXX, KC_S,    XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_B,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX, XXXXXXX, KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX
    ),
/*
 * Debug Layer: Function keys, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |LClick| Up   |RClick|      |                              |Qwerty| Game |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Left | Down | Right|WheelU|                              |      | VolD | Mute | VolU |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |WheelL|      |WheelR|WheelD|      |      |  |      |      |      | Prev | Play | Next |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_DEBUG] = LAYOUT(
      XXXXXXX, XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX,                                 DF(_QWERTY), DF(_GAME), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U,                                     XXXXXXX, KC_VOLD,   KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
      KC_ACL2, XXXXXXX, KC_WH_L, XXXXXXX, KC_WH_R, KC_WH_D, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV,   KC_MPLY, KC_MNXT, XXXXXXX, KC_ACL0,
                                 XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______,   XXXXXXX
    ),
/*
 * Base Layer: Game raise
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |  Up  |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      | Left | Down | Right|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAME_RAISE] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, KC_UP,   _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                     _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
                              XXXXXXX, _______, _______, MO(_DEBUG), _______, _______, _______, _______, _______, XXXXXXX
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

bool is_num_lock_lit = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_HNUM:
            if ((record->event.pressed && !is_num_lock_lit)
                || (!record->event.pressed && is_num_lock_lit)
            ) {
                tap_code(KC_NUMLOCK);
            }

            break;
    }
    return true;
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0,
        0xe0, 0xf0, 0x70, 0x78, 0x38, 0x3c, 0x1c, 0x1e, 0x0e, 0x0e, 0x0e, 0x07, 0x07, 0x07, 0x07, 0x07,
        0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0e, 0x0e, 0x0e, 0x1e, 0x1c,
        0x3c, 0x38, 0x78, 0x70, 0xf0, 0xe0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0x7c, 0x3e, 0x1f, 0x0f, 0x07, 0x03,
        0x01, 0x80, 0xc0, 0xe0, 0xf0, 0x78, 0x38, 0x3c, 0x1c, 0x1e, 0x0e, 0x0e, 0x07, 0x07, 0x87, 0xe7,
        0x7f, 0x1f, 0xff, 0xff, 0x1f, 0x7f, 0xe7, 0x87, 0x07, 0x07, 0x0e, 0x0e, 0x1e, 0x1c, 0x3c, 0x38,
        0x78, 0xf0, 0xe0, 0xc0, 0x80, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3e, 0x7c, 0xf0, 0xe0, 0xc0, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xf0, 0xfc, 0xff, 0x1f, 0x07, 0x01, 0x00, 0x00, 0xc0, 0xf0, 0xfc, 0xfe,
        0xff, 0xf7, 0xf3, 0xb1, 0xb0, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0xfe, 0x87, 0x01,
        0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x01, 0x87, 0xfe, 0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
        0x30, 0xb0, 0xb1, 0xf3, 0xf7, 0xff, 0xfe, 0xfc, 0xf0, 0xc0, 0x00, 0x00, 0x01, 0x07, 0x1f, 0xff,
        0xfc, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0x01, 0x01,
        0x07, 0x1e, 0x78, 0xe1, 0x81, 0x83, 0x83, 0x86, 0x86, 0x8c, 0x8c, 0x98, 0x98, 0xb1, 0xb7, 0xfe,
        0xf8, 0xe0, 0xff, 0xff, 0xe0, 0xf8, 0xfe, 0xb7, 0xb1, 0x98, 0x98, 0x8c, 0x8c, 0x86, 0x86, 0x83,
        0x83, 0x81, 0xe1, 0x78, 0x1e, 0x07, 0x01, 0x01, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xc0, 0xc0, 0x30, 0x30, 0x00,
        0x00, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0xc0,
        0xc0, 0x30, 0x30, 0x30, 0x30, 0xc0, 0xc0, 0x00, 0x00, 0x30, 0x30, 0xf3, 0xf3, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0x80, 0x80,
        0xe0, 0x78, 0x1e, 0x87, 0x81, 0xc1, 0xc1, 0x61, 0x61, 0x31, 0x31, 0x19, 0x19, 0x8d, 0xed, 0x7f,
        0x1f, 0x07, 0xff, 0xff, 0x07, 0x1f, 0x7f, 0xed, 0x8d, 0x19, 0x19, 0x31, 0x31, 0x61, 0x61, 0xc1,
        0xc1, 0x81, 0x87, 0x1e, 0x78, 0xe0, 0x80, 0x80, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x03, 0x03, 0x0c, 0x0c, 0x30, 0x30, 0x00,
        0x00, 0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x0f, 0x0f, 0x00, 0x00, 0x3f, 0x3f, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x3f, 0x3f, 0x30, 0x30, 0x00,
        0x00, 0x0c, 0x0c, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x0f, 0x3f, 0xff, 0xf8, 0xe0, 0x80, 0x00, 0x00, 0x03, 0x0f, 0x3f, 0x7f,
        0xff, 0xef, 0xcf, 0x8d, 0x0d, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x1e, 0x7f, 0xe1, 0x80,
        0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x80, 0xe1, 0x7f, 0x1e, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
        0x0c, 0x0d, 0x8d, 0xcf, 0xef, 0xff, 0x7f, 0x3f, 0x0f, 0x03, 0x00, 0x00, 0x80, 0xe0, 0xf8, 0xff,
        0x3f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x3e, 0x7c, 0xf8, 0xf0, 0xe0, 0xc0,
        0x80, 0x01, 0x03, 0x07, 0x0f, 0x1e, 0x1c, 0x3c, 0x38, 0x78, 0x70, 0x70, 0xe0, 0xe0, 0xe1, 0xe7,
        0xfe, 0xf8, 0xff, 0xff, 0xf8, 0xfe, 0xe7, 0xe1, 0xe0, 0xe0, 0x70, 0x70, 0x78, 0x38, 0x3c, 0x1c,
        0x1e, 0x0f, 0x07, 0x03, 0x01, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0x7c, 0x3e, 0x0f, 0x07, 0x03, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03,
        0x07, 0x0f, 0x0e, 0x1e, 0x1c, 0x3c, 0x38, 0x78, 0x70, 0x70, 0x70, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
        0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x70, 0x70, 0x70, 0x78, 0x38,
        0x3c, 0x1c, 0x1e, 0x0e, 0x0f, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

    oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
        case _GAME_RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _MAGIC:
            oled_write_P(PSTR("SysRq REISUB\n"), false);
            break;
        case _DEBUG:
            oled_write_P(PSTR("Debug\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    oled_write_P(PSTR("\n"), false);

    // Host Keyboard LED Status
    led_t led_usb_state = host_keyboard_led_state();

    oled_write_P(PSTR("Lock: "), false);
    oled_write_P(led_usb_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_usb_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);

    is_num_lock_lit = led_usb_state.num_lock;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code16(LGUI(KC_PGDN));
        } else {
            tap_code16(LGUI(KC_PGUP));
        }
    }
    return true;
}
#endif

void suspend_power_down_user(void) {
    oled_off();
}
