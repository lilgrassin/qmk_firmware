// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#include "transactions.h"

enum m_layers {
    _BASE,
    _EXTRA,
    _TAP,
    _BUTTON,
    _NAV,
    _MOUSE,
    _MEDIA,
    _NUM,
    _SYM,
    _FUN,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Remap Miryoku's clipboard CTRL+Y to Mac's CMD+SHFT+Z if in Mac mode
    if (keycode == C(KC_Y) && keymap_config.swap_lctl_lgui && !get_mods()) {
        if (record->event.pressed) {
            register_code16(SCMD(KC_Z));
        } else {
            unregister_code16(SCMD(KC_Z));
        }
        return false;
    }
    return true;
}

bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_AMPR:
        case KC_ASTR:
        case KC_AT:
        case KC_CIRC:
        case KC_COLN:
        case KC_DLR:
        case KC_EXLM:
        case KC_HASH:
        case KC_LABK:
        case KC_LCBR:
        case KC_PERC:
        case KC_PIPE:
        case KC_PLUS:
        case KC_QUES:
        case KC_RABK:
        case KC_RCBR:
        case KC_TILD:
            return true;
        default:
            return false;
    }
}

#define U_CASE_REGISTER_AUTOSHIFT(KEY, SHIFTED) \
case KEY: register_code16((!shifted) ? KEY : SHIFTED); break;

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        U_CASE_REGISTER_AUTOSHIFT(KC_0, KC_SCLN)
        U_CASE_REGISTER_AUTOSHIFT(KC_1, KC_ASTR)
        U_CASE_REGISTER_AUTOSHIFT(KC_2, KC_RCBR)
        U_CASE_REGISTER_AUTOSHIFT(KC_3, KC_RBRC)
        U_CASE_REGISTER_AUTOSHIFT(KC_4, KC_MINS)
        U_CASE_REGISTER_AUTOSHIFT(KC_5, KC_EQL)
        U_CASE_REGISTER_AUTOSHIFT(KC_6, KC_RABK)
        U_CASE_REGISTER_AUTOSHIFT(KC_7, KC_PLUS)
        U_CASE_REGISTER_AUTOSHIFT(KC_8, KC_LCBR)
        U_CASE_REGISTER_AUTOSHIFT(KC_9, KC_LBRC)
        U_CASE_REGISTER_AUTOSHIFT(KC_AMPR, KC_DLR)
        U_CASE_REGISTER_AUTOSHIFT(KC_ASTR, KC_1)
        U_CASE_REGISTER_AUTOSHIFT(KC_AT, KC_LABK)
        U_CASE_REGISTER_AUTOSHIFT(KC_BSLS, KC_GRV)
        U_CASE_REGISTER_AUTOSHIFT(KC_CIRC, KC_TILD)
        U_CASE_REGISTER_AUTOSHIFT(KC_COLN, KC_PIPE)
        U_CASE_REGISTER_AUTOSHIFT(KC_COMM, KC_LPRN)
        U_CASE_REGISTER_AUTOSHIFT(KC_DLR, KC_AMPR)
        U_CASE_REGISTER_AUTOSHIFT(KC_EQL, KC_5)
        U_CASE_REGISTER_AUTOSHIFT(KC_EXLM, KC_QUES)
        U_CASE_REGISTER_AUTOSHIFT(KC_GRV, KC_BSLS)
        U_CASE_REGISTER_AUTOSHIFT(KC_HASH, KC_PERC)
        U_CASE_REGISTER_AUTOSHIFT(KC_LABK, KC_AT)
        U_CASE_REGISTER_AUTOSHIFT(KC_LBRC, KC_9)
        U_CASE_REGISTER_AUTOSHIFT(KC_LCBR, KC_8)
        U_CASE_REGISTER_AUTOSHIFT(KC_PERC, KC_HASH)
        U_CASE_REGISTER_AUTOSHIFT(KC_PIPE, KC_COLN)
        U_CASE_REGISTER_AUTOSHIFT(KC_PLUS, KC_7)
        U_CASE_REGISTER_AUTOSHIFT(KC_QUES, KC_EXLM)
        U_CASE_REGISTER_AUTOSHIFT(KC_RABK, KC_6)
        U_CASE_REGISTER_AUTOSHIFT(KC_RBRC, KC_3)
        U_CASE_REGISTER_AUTOSHIFT(KC_RCBR, KC_2)
        U_CASE_REGISTER_AUTOSHIFT(KC_SCLN, KC_0)
        U_CASE_REGISTER_AUTOSHIFT(KC_SLSH, KC_DOT)
        U_CASE_REGISTER_AUTOSHIFT(KC_TILD, KC_CIRC)
        case KC_DOT:
            if (layer_state_cmp(layer_state | default_layer_state, _NUM)) {
                register_code16((!shifted) ? KC_DOT : KC_SLSH);
            } else {
                register_code16((!shifted) ? KC_DOT : KC_RPRN);
            }
            break;
        case KC_MINS:
            if (layer_state_cmp(layer_state | default_layer_state, _SYM)) {
                register_code16((!shifted) ? KC_MINS : KC_4);
                break;
            }
            // fallthrough otherwise
        default:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

#define U_CASE_UNREGISTER_AUTOSHIFT(KEY, SHIFTED) \
case KEY: unregister_code16((!shifted) ? KEY : SHIFTED); break;

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        U_CASE_UNREGISTER_AUTOSHIFT(KC_0, KC_SCLN)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_1, KC_ASTR)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_2, KC_RCBR)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_3, KC_RBRC)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_4, KC_MINS)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_5, KC_EQL)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_6, KC_RABK)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_7, KC_PLUS)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_8, KC_LCBR)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_9, KC_LBRC)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_AMPR, KC_DLR)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_ASTR, KC_1)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_AT, KC_LABK)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_BSLS, KC_GRV)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_CIRC, KC_TILD)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_COLN, KC_PIPE)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_COMM, KC_LPRN)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_DLR, KC_AMPR)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_EQL, KC_5)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_EXLM, KC_QUES)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_GRV, KC_BSLS)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_HASH, KC_PERC)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_LABK, KC_AT)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_LBRC, KC_9)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_LCBR, KC_8)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_PERC, KC_HASH)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_PIPE, KC_COLN)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_PLUS, KC_7)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_QUES, KC_EXLM)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_RABK, KC_6)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_RBRC, KC_3)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_RCBR, KC_2)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_SCLN, KC_0)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_SLSH, KC_DOT)
        U_CASE_UNREGISTER_AUTOSHIFT(KC_TILD, KC_CIRC)
        case KC_DOT:
            if (layer_state_cmp(layer_state | default_layer_state, _NUM)) {
                unregister_code16((!shifted) ? KC_DOT : KC_SLSH);
            } else {
                unregister_code16((!shifted) ? KC_DOT : KC_RPRN);
            }
            break;
        case KC_MINS:
            if (layer_state_cmp(layer_state | default_layer_state, _SYM)) {
                unregister_code16((!shifted) ? KC_MINS : KC_4);
                break;
            }
            // fallthrough otherwise
        default:
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            // The IS_RETRO check isn't really necessary here, always using
            // keycode & 0xFF would be fine.
            unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

//
// Sync cmd/ctl swap magic for OLEDs
//

// Slave half wakes after the master and will miss the initial sync if not delayed
#define U_WAKE_DELAY 2250
#define U_SYNC_DELAY 500

typedef struct _sync_magic_to_slave_t {
    bool swap_ctl_gui;
} sync_magic_to_slave_t;


void user_sync_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    keymap_config.swap_lctl_lgui = ((const sync_magic_to_slave_t*)in_data)->swap_ctl_gui;
    keymap_config.swap_rctl_rgui = keymap_config.swap_lctl_lgui;
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        static uint32_t last_sync = 0;
        static sync_magic_to_slave_t last_config = {0};
        if ((!last_sync || (keymap_config.swap_lctl_lgui != last_config.swap_ctl_gui)) && timer_elapsed32(last_sync) > (last_sync ? U_SYNC_DELAY : U_WAKE_DELAY)){
            last_config.swap_ctl_gui = keymap_config.swap_lctl_lgui;
            transaction_rpc_send(USER_SYNC_MAGIC, sizeof(last_config), &last_config);
            last_sync = timer_read32();
        }
    }
}


void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_MAGIC, user_sync_slave_handler);
}

#undef U_WAKE_DELAY
#undef U_SYNC_DELAY

//
// OLED functions
//
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    // cancel out lulu defaults
    return OLED_ROTATION_0;
  }
  return rotation;
}

// osmagic 1*8+4
static const char PROGMEM osmagic_bitmaps[2][2][16] = {
    // Win
    {{0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x00, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x00},
     {0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x00, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x00}}
    , // Mac
    {{0x70, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0xfc, 0x78, 0x00, 0x00, 0x00, 0x00},
     {0x1c, 0x3f, 0x7f, 0x7f, 0x3f, 0x1f, 0x1f, 0x1f, 0x1f, 0x3f, 0x7f, 0x3c, 0x01, 0x03, 0x06, 0x04}}
};

// lock 13*8+4
static const char PROGMEM lock_bitmaps[2][2][16] = {
    {{0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x10, 0x30, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00},
     {0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x08, 0x08, 0x08, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00}}
    ,
    {{0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x10, 0x10, 0x30, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
     {0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x08, 0x08, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
};

static const char PROGMEM right_bitmaps[3][2][2][16] = {
    { // media 4*8+4
        {{0x00, 0x00, 0x0c, 0x1c, 0x34, 0x64, 0xc4, 0x84, 0x84, 0xc4, 0x64, 0x34, 0x1c, 0x0c, 0x00, 0x00},
         {0x00, 0x00, 0x36, 0x36, 0x36, 0x36, 0x36, 0x37, 0x37, 0x36, 0x36, 0x36, 0x36, 0x36, 0x00, 0x00}}
        ,
        {{0xfe, 0xff, 0xf3, 0xe3, 0xcb, 0x9b, 0x3b, 0x7b, 0x7b, 0x3b, 0x9b, 0xcb, 0xe3, 0xf3, 0xff, 0xfe},
         {0x7f, 0xff, 0xc9, 0xc9, 0xc9, 0xc9, 0xc9, 0xc8, 0xc8, 0xc9, 0xc9, 0xc9, 0xc9, 0xc9, 0xff, 0x7f}}
    }, 
    { // nav 7*8+4
        {{0x00, 0x00, 0xe0, 0x70, 0x18, 0x6c, 0xec, 0xc4, 0xc4, 0x8c, 0x0c, 0x18, 0x70, 0xe0, 0x00, 0x00},
         {0x00, 0x00, 0x07, 0x0e, 0x18, 0x30, 0x31, 0x23, 0x22, 0x37, 0x36, 0x18, 0x0e, 0x07, 0x00, 0x00}}
        ,
        {{0xfe, 0xff, 0x1f, 0x8f, 0xe7, 0x93, 0x13, 0x3b, 0x3b, 0x73, 0xf3, 0xe7, 0x8f, 0x1f, 0xff, 0xfe},
         {0x7f, 0xff, 0xf8, 0xf1, 0xe7, 0xcf, 0xce, 0xdc, 0xdd, 0xc8, 0xc9, 0xe7, 0xf1, 0xf8, 0xff, 0x7f}}
    },   
    { // mouse 10*8+4
        {{0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x70, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
         {0x00, 0x00, 0x18, 0x1c, 0x16, 0x13, 0x10, 0x10, 0x11, 0x13, 0x17, 0x1e, 0x1c, 0x18, 0x00, 0x00}}
        ,
        {{0xfe, 0xff, 0xff, 0xff, 0xff, 0x07, 0xc7, 0x8f, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe},
         {0x7f, 0xff, 0xf3, 0xf1, 0xf4, 0xf6, 0xf7, 0xf7, 0xf7, 0xf6, 0xf4, 0xf0, 0xf1, 0xf3, 0xff, 0x7f}}
    }
};

static const char PROGMEM left_bitmaps[3][2][2][16] = {
    { // fun 4*8+4
        {{0x00, 0x00, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0xfc, 0xfc, 0x0c, 0x0c, 0x0c, 0xfc, 0xf8, 0x00, 0x00},
         {0x00, 0x00, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x3f, 0x1f, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00}}
        ,
        {{0xfe, 0xff, 0x73, 0x73, 0x73, 0x73, 0x73, 0x03, 0x03, 0xf3, 0xf3, 0xf3, 0x03, 0x07, 0xff, 0xfe},
         {0x7f, 0xff, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0xc0, 0xe0, 0xff, 0xff, 0xfc, 0xfe, 0xff, 0x7f}}
    },
    { // num 7*8+4
        {{0x00, 0x00, 0xe0, 0x70, 0x10, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x30, 0xe0, 0xc0, 0x00, 0x00},
         {0x00, 0x00, 0x03, 0x06, 0x0c, 0x0c, 0x0e, 0x07, 0x03, 0x06, 0x0e, 0x0e, 0x07, 0x03, 0x00, 0x00}}
        ,
        {{0xfe, 0xff, 0x1f, 0x8f, 0xef, 0xff, 0xff, 0x7f, 0x7f, 0xff, 0xff, 0xcf, 0x1f, 0x3f, 0xff, 0xfe},
         {0x7f, 0xff, 0xfc, 0xf9, 0xf3, 0xf3, 0xf1, 0xf8, 0xfc, 0xf9, 0xf1, 0xf1, 0xf8, 0xfc, 0xff, 0x7f}}
    },
    { // sym 10*8+4
        {{0x00, 0x00, 0xf0, 0x38, 0x18, 0x18, 0x38, 0xf0, 0xe0, 0xf0, 0x30, 0x10, 0x30, 0xe0, 0x00, 0x00},
         {0x00, 0x00, 0x19, 0x0f, 0x06, 0x0e, 0x0b, 0x19, 0x00, 0x01, 0x03, 0x02, 0x03, 0x01, 0x00, 0x00}}
        ,
        {{0xfe, 0xff, 0x0f, 0xc7, 0xe7, 0xe7, 0xc7, 0x0f, 0x1f, 0x0f, 0xcf, 0xef, 0xcf, 0x1f, 0xff, 0xfe},
         {0x7f, 0xff, 0xe6, 0xf0, 0xf9, 0xf1, 0xf4, 0xe6, 0xff, 0xfe, 0xfc, 0xfd, 0xfc, 0xfe, 0xff, 0x7f}}
    }
};

#define OSMAGIC_ICON_BASE 1
#define LAYER_ICONS_BASE 6
#define LOCK_ICON_BASE 19
#define ICON_LN_OFFSET 1 

void render_right_layer_state(void) {
    bool os_magic = keymap_config.swap_lctl_lgui;
    bool lock = get_highest_layer(default_layer_state) > _BASE;
    bool active;
    int layer = -1;

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _MEDIA:
            layer = 0;
            break;
        case _NAV:
            layer = 1;
            break;
        case _MOUSE:
            layer = 2;
            break;
    }

    for (int ln = 0; ln < 2; ++ln) {
        oled_set_cursor(OSMAGIC_ICON_BASE, ln + ICON_LN_OFFSET);
        oled_write_raw_P(osmagic_bitmaps[os_magic][ln], sizeof(osmagic_bitmaps[os_magic][ln]));
        for (int i = 0; i < 3; ++i) {
            active = layer == i;
            oled_set_cursor(LAYER_ICONS_BASE + (i * 4), ln + ICON_LN_OFFSET);
            oled_write_raw_P(right_bitmaps[i][active][ln], sizeof(right_bitmaps[i][active][ln]));
        }
        oled_set_cursor(LOCK_ICON_BASE, ln + ICON_LN_OFFSET);
        oled_write_raw_P(lock_bitmaps[lock][ln], sizeof(lock_bitmaps[lock][ln]));
    }
}

void render_left_layer_state(void) {
    bool os_magic = keymap_config.swap_lctl_lgui;
    bool lock = get_highest_layer(default_layer_state) > _BASE;
    bool active;
    int layer = -1;

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _FUN:
            layer = 0;
            break;
        case _NUM:
            layer = 1;
            break;
        case _SYM:
            layer = 2;
            break;
    }

    for (int ln = 0; ln < 2; ++ln) {
        oled_set_cursor(OSMAGIC_ICON_BASE, ln + ICON_LN_OFFSET);
        oled_write_raw_P(osmagic_bitmaps[os_magic][ln], sizeof(osmagic_bitmaps[os_magic][ln]));
        for (int i = 0; i < 3; ++i) {
            active = layer == i;
            oled_set_cursor(LAYER_ICONS_BASE + (i * 4), ln + ICON_LN_OFFSET);
            oled_write_raw_P(left_bitmaps[i][active][ln], sizeof(left_bitmaps[i][active][ln]));
        }
        oled_set_cursor(LOCK_ICON_BASE, ln + ICON_LN_OFFSET);
        oled_write_raw_P(lock_bitmaps[lock][ln], sizeof(lock_bitmaps[lock][ln]));
    }
}

bool oled_task_user(void) {
    if (is_keyboard_left()) {
        render_left_layer_state();
    } else {
		render_right_layer_state();
	}
    return false;
}

#endif