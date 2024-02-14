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

//
// Custom autoshift behaviour for custom NUM/SYM layers
//

bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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

#define CASE_REGISTER_AUTOSHIFT(KEY, SHIFTED)        \
    case KEY:                                        \
        register_code16((!shifted) ? KEY : SHIFTED); \
        break;

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch (keycode) {
        CASE_REGISTER_AUTOSHIFT(KC_0, KC_SCLN)
        CASE_REGISTER_AUTOSHIFT(KC_1, KC_ASTR)
        CASE_REGISTER_AUTOSHIFT(KC_2, KC_RCBR)
        CASE_REGISTER_AUTOSHIFT(KC_3, KC_RBRC)
        CASE_REGISTER_AUTOSHIFT(KC_4, KC_MINS)
        CASE_REGISTER_AUTOSHIFT(KC_5, KC_EQL)
        CASE_REGISTER_AUTOSHIFT(KC_6, KC_RABK)
        CASE_REGISTER_AUTOSHIFT(KC_7, KC_PLUS)
        CASE_REGISTER_AUTOSHIFT(KC_8, KC_LCBR)
        CASE_REGISTER_AUTOSHIFT(KC_9, KC_LBRC)
        CASE_REGISTER_AUTOSHIFT(KC_AMPR, KC_DLR)
        CASE_REGISTER_AUTOSHIFT(KC_ASTR, KC_1)
        CASE_REGISTER_AUTOSHIFT(KC_AT, KC_LABK)
        CASE_REGISTER_AUTOSHIFT(KC_BSLS, KC_GRV)
        CASE_REGISTER_AUTOSHIFT(KC_CIRC, KC_TILD)
        CASE_REGISTER_AUTOSHIFT(KC_COLN, KC_PIPE)
        CASE_REGISTER_AUTOSHIFT(KC_COMM, KC_LPRN)
        CASE_REGISTER_AUTOSHIFT(KC_DLR, KC_AMPR)
        CASE_REGISTER_AUTOSHIFT(KC_EQL, KC_5)
        CASE_REGISTER_AUTOSHIFT(KC_EXLM, KC_QUES)
        CASE_REGISTER_AUTOSHIFT(KC_GRV, KC_BSLS)
        CASE_REGISTER_AUTOSHIFT(KC_HASH, KC_PERC)
        CASE_REGISTER_AUTOSHIFT(KC_LABK, KC_AT)
        CASE_REGISTER_AUTOSHIFT(KC_LBRC, KC_9)
        CASE_REGISTER_AUTOSHIFT(KC_LCBR, KC_8)
        CASE_REGISTER_AUTOSHIFT(KC_PERC, KC_HASH)
        CASE_REGISTER_AUTOSHIFT(KC_PIPE, KC_COLN)
        CASE_REGISTER_AUTOSHIFT(KC_PLUS, KC_7)
        CASE_REGISTER_AUTOSHIFT(KC_QUES, KC_EXLM)
        CASE_REGISTER_AUTOSHIFT(KC_RABK, KC_6)
        CASE_REGISTER_AUTOSHIFT(KC_RBRC, KC_3)
        CASE_REGISTER_AUTOSHIFT(KC_RCBR, KC_2)
        CASE_REGISTER_AUTOSHIFT(KC_SCLN, KC_0)
        CASE_REGISTER_AUTOSHIFT(KC_SLSH, KC_DOT)
        CASE_REGISTER_AUTOSHIFT(KC_TILD, KC_CIRC)
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

#define CASE_UNREGISTER_AUTOSHIFT(KEY, SHIFTED)        \
    case KEY:                                          \
        unregister_code16((!shifted) ? KEY : SHIFTED); \
        break;

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch (keycode) {
        CASE_UNREGISTER_AUTOSHIFT(KC_0, KC_SCLN)
        CASE_UNREGISTER_AUTOSHIFT(KC_1, KC_ASTR)
        CASE_UNREGISTER_AUTOSHIFT(KC_2, KC_RCBR)
        CASE_UNREGISTER_AUTOSHIFT(KC_3, KC_RBRC)
        CASE_UNREGISTER_AUTOSHIFT(KC_4, KC_MINS)
        CASE_UNREGISTER_AUTOSHIFT(KC_5, KC_EQL)
        CASE_UNREGISTER_AUTOSHIFT(KC_6, KC_RABK)
        CASE_UNREGISTER_AUTOSHIFT(KC_7, KC_PLUS)
        CASE_UNREGISTER_AUTOSHIFT(KC_8, KC_LCBR)
        CASE_UNREGISTER_AUTOSHIFT(KC_9, KC_LBRC)
        CASE_UNREGISTER_AUTOSHIFT(KC_AMPR, KC_DLR)
        CASE_UNREGISTER_AUTOSHIFT(KC_ASTR, KC_1)
        CASE_UNREGISTER_AUTOSHIFT(KC_AT, KC_LABK)
        CASE_UNREGISTER_AUTOSHIFT(KC_BSLS, KC_GRV)
        CASE_UNREGISTER_AUTOSHIFT(KC_CIRC, KC_TILD)
        CASE_UNREGISTER_AUTOSHIFT(KC_COLN, KC_PIPE)
        CASE_UNREGISTER_AUTOSHIFT(KC_COMM, KC_LPRN)
        CASE_UNREGISTER_AUTOSHIFT(KC_DLR, KC_AMPR)
        CASE_UNREGISTER_AUTOSHIFT(KC_EQL, KC_5)
        CASE_UNREGISTER_AUTOSHIFT(KC_EXLM, KC_QUES)
        CASE_UNREGISTER_AUTOSHIFT(KC_GRV, KC_BSLS)
        CASE_UNREGISTER_AUTOSHIFT(KC_HASH, KC_PERC)
        CASE_UNREGISTER_AUTOSHIFT(KC_LABK, KC_AT)
        CASE_UNREGISTER_AUTOSHIFT(KC_LBRC, KC_9)
        CASE_UNREGISTER_AUTOSHIFT(KC_LCBR, KC_8)
        CASE_UNREGISTER_AUTOSHIFT(KC_PERC, KC_HASH)
        CASE_UNREGISTER_AUTOSHIFT(KC_PIPE, KC_COLN)
        CASE_UNREGISTER_AUTOSHIFT(KC_PLUS, KC_7)
        CASE_UNREGISTER_AUTOSHIFT(KC_QUES, KC_EXLM)
        CASE_UNREGISTER_AUTOSHIFT(KC_RABK, KC_6)
        CASE_UNREGISTER_AUTOSHIFT(KC_RBRC, KC_3)
        CASE_UNREGISTER_AUTOSHIFT(KC_RCBR, KC_2)
        CASE_UNREGISTER_AUTOSHIFT(KC_SCLN, KC_0)
        CASE_UNREGISTER_AUTOSHIFT(KC_SLSH, KC_DOT)
        CASE_UNREGISTER_AUTOSHIFT(KC_TILD, KC_CIRC)
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
// Extend cmd/ctl swap magic
//

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

//
// OLED
//

#ifdef OLED_ENABLE

//
// Sync cmd/ctl swap magic for OLEDs
//

#    define SYNC_INTERVAL 500

void user_sync_slave_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    keymap_config.swap_lctl_lgui = *((const bool *)in_data);
    keymap_config.swap_rctl_rgui = keymap_config.swap_lctl_lgui;
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        static uint32_t last_sync = 0;
        static bool     swapped   = false;
        bool            swapped_sync;

        if (swapped != keymap_config.swap_lctl_lgui && timer_elapsed32(last_sync) > SYNC_INTERVAL) {
            swapped_sync = keymap_config.swap_lctl_lgui;
            if (transaction_rpc_send(USER_SYNC_MAGIC, sizeof(swapped_sync), &swapped_sync)) {
                swapped   = swapped_sync;
                last_sync = timer_read32();
            }
        }
    }
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_MAGIC, user_sync_slave_handler);
}

//
// OLED bitmaps
//

#    include "bitmaps.h"

// Magic indicator 1*8+4
static const char PROGMEM magic_bitmaps[ICON_STATE_COUNT][ICON_WIDTH][ICON_HEIGHT] = {{ICON_WIN}, {ICON_MAC}};

// Layer lock 13*8+4
static const char PROGMEM lock_bitmaps[ICON_STATE_COUNT][ICON_WIDTH][ICON_HEIGHT] = {{ICON_UNLOCK}, {ICON_LOCK}};

// Right side layers
static const char PROGMEM right_bitmaps[LAYER_ICON_COUNT][ICON_STATE_COUNT][ICON_WIDTH][ICON_HEIGHT] = {
    // Media 4*8+4
    {{ICON_MEDIA_OFF}, {ICON_MEDIA_ON}},
    // Navigation 7*8+4
    {{ICON_NAV_OFF}, {ICON_NAV_ON}},
    // Mouse 10*8+4
    {{ICON_MOUSE_OFF}, {ICON_MOUSE_ON}}};

// Left side layers
static const char PROGMEM left_bitmaps[LAYER_ICON_COUNT][ICON_STATE_COUNT][ICON_WIDTH][ICON_HEIGHT] = {
    // Function 4*8+4
    {{ICON_FUNC_OFF}, {ICON_FUNC_ON}},
    // Number 7*8+4
    {{ICON_NUM_OFF}, {ICON_NUM_ON}},
    // Symbol 10*8+4
    {{ICON_SYM_OFF}, {ICON_SYM_ON}}};

//
// OLED rendering functions
//

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        // cancel out lulu defaults
        return OLED_ROTATION_0;
    }
    return rotation;
}

void render_right_state(void) {
    bool magic  = keymap_config.swap_lctl_lgui;
    bool lock   = get_highest_layer(default_layer_state) > _BASE;
    int  active = -1;

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _MEDIA:
            active = 0;
            break;
        case _NAV:
            active = 1;
            break;
        case _MOUSE:
            active = 2;
            break;
    }

    // Bitmaps are written in 8px lines vertically, starting from the bottom left
    // Icons are centered and stacked bottom to top:
    // Magic -> Media -> Nav -> Mouse -> Lock
    for (int line = 0; line < ICON_WIDTH; ++line) {
        oled_set_cursor(MAGIC_ICON_BASE, line + ICON_LINE_OFFSET);
        oled_write_raw_P(magic_bitmaps[magic][line], ICON_HEIGHT);
        for (int layer = 0; layer < LAYER_ICON_COUNT; ++layer) {
            oled_set_cursor(LAYER_ICON_BASE + (layer * 4), line + ICON_LINE_OFFSET);
            oled_write_raw_P(right_bitmaps[layer][layer == active][line], ICON_HEIGHT);
        }
        oled_set_cursor(LOCK_ICON_BASE, line + ICON_LINE_OFFSET);
        oled_write_raw_P(lock_bitmaps[lock][line], ICON_HEIGHT);
    }
}

void render_left_state(void) {
    bool magic  = keymap_config.swap_lctl_lgui;
    bool lock   = get_highest_layer(default_layer_state) > _BASE;
    int  active = -1;

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _FUN:
            active = 0;
            break;
        case _NUM:
            active = 1;
            break;
        case _SYM:
            active = 2;
            break;
    }

    // Bitmaps are written in 8px lines vertically, starting from the bottom left
    // Icons are centered and stacked bottom to top:
    // Magic -> Func -> Num -> Sym -> Lock
    for (int line = 0; line < ICON_WIDTH; ++line) {
        oled_set_cursor(MAGIC_ICON_BASE, line + ICON_LINE_OFFSET);
        oled_write_raw_P(magic_bitmaps[magic][line], ICON_HEIGHT);
        for (int layer = 0; layer < LAYER_ICON_COUNT; ++layer) {
            oled_set_cursor(LAYER_ICON_BASE + (layer * 4), line + ICON_LINE_OFFSET);
            oled_write_raw_P(left_bitmaps[layer][layer == active][line], ICON_HEIGHT);
        }
        oled_set_cursor(LOCK_ICON_BASE, line + ICON_LINE_OFFSET);
        oled_write_raw_P(lock_bitmaps[lock][line], ICON_HEIGHT);
    }
}

bool oled_task_user(void) {
    if (is_keyboard_left()) {
        render_left_state();
    } else {
        render_right_state();
    }
    return false;
}

#endif

//
// Encoders

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            rgb_matrix_increase_val_noeeprom();
        } else {
            rgb_matrix_decrease_val_noeeprom();
        }
    }
    return false;
}

#endif
