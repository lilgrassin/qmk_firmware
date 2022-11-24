// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H
#include "oledbitmaps.h"

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

//
// Sync cmd/ctl swap magic for OLEDs
//

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
        if (!last_sync || (keymap_config.swap_lctl_lgui != last_config.swap_ctl_gui && timer_elapsed32(last_sync) > 500)){
            last_config.swap_ctl_gui = keymap_config.swap_lctl_lgui;
            transaction_rpc_send(USER_SYNC_MAGIC, sizeof(last_config), &last_config);
            last_sync = timer_read32();
        }
    }
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_MAGIC, user_sync_slave_handler);
}

#ifdef OLED_ENABLE

//
// OLED functions
//

void render_base_right_logo(void){
	// 'BaseL', 128x32px
	static const char PROGMEM layer_logo[] = {
		LULU_MIRYOKU_BASER
	};

    oled_write_raw_P(layer_logo, sizeof(layer_logo));
}

void render_base_left_logo(void){
	// 'BaseL', 128x32px
	static const char PROGMEM layer_logo[] = {
		LULU_MIRYOKU_BASEL
	};

    oled_write_raw_P(layer_logo, sizeof(layer_logo));
}

void render_mouse_right_logo(void){
	// 'Mouse', 128x32px
	static const char PROGMEM layer_logo[] = {
		LULU_MIRYOKU_MOUSER
	};

    oled_write_raw_P(layer_logo, sizeof(layer_logo));
}

void render_mouse_left_logo(void){
	// 'Mouse', 128x32px
	static const char PROGMEM layer_logo[] = {
		LULU_MIRYOKU_MOUSEL
	};

    oled_write_raw_P(layer_logo, sizeof(layer_logo));
}

void render_nav_right_logo(void){
	// 'Nav', 128x32px
	static const char PROGMEM layer_logo[] = {
		LULU_MIRYOKU_NAVR
	};

    oled_write_raw_P(layer_logo, sizeof(layer_logo));
}

void render_nav_left_logo(void){
	// 'Nav', 128x32px
	static const char PROGMEM layer_logo[] = {
		LULU_MIRYOKU_NAVL
	};

    oled_write_raw_P(layer_logo, sizeof(layer_logo));
}

void render_media_right_logo(void){
	// 'Media', 128x32px
	static const char PROGMEM layer_logo[] = {
		LULU_MIRYOKU_MEDIAR
	};

    oled_write_raw_P(layer_logo, sizeof(layer_logo));
}

void render_media_left_logo(void){
	// 'Media', 128x32px
	static const char PROGMEM layer_logo[] = {
		LULU_MIRYOKU_MEDIAL
	};

    oled_write_raw_P(layer_logo, sizeof(layer_logo));
}

void render_sym_right_logo(void){
	// 'Sym', 128x32px
	static const char PROGMEM layer_logo[] = {
		LULU_MIRYOKU_SYMR
	};

    oled_write_raw_P(layer_logo, sizeof(layer_logo));
}

void render_sym_left_logo(void){
	// 'Sym', 128x32px
	static const char PROGMEM layer_logo[] = {
		LULU_MIRYOKU_SYML
	};

    oled_write_raw_P(layer_logo, sizeof(layer_logo));
}

void render_num_right_logo(void){
    // 'Num', 128x32px
	static const char PROGMEM layer_logo[] = {
		LULU_MIRYOKU_NUMR
	};

    oled_write_raw_P(layer_logo, sizeof(layer_logo));
}

void render_num_left_logo(void){
    // 'Num', 128x32px
	static const char PROGMEM layer_logo[] = {
		LULU_MIRYOKU_NUML
	};

    oled_write_raw_P(layer_logo, sizeof(layer_logo));
}

void render_fun_right_logo(void){
	// 'Fun', 128x32px
	static const char PROGMEM layer_logo[] = {
		LULU_MIRYOKU_FUNR
	};

    oled_write_raw_P(layer_logo, sizeof(layer_logo));
}

void render_fun_left_logo(void){
	// 'Fun', 128x32px
	static const char PROGMEM layer_logo[] = {
		LULU_MIRYOKU_FUNL
	};

    oled_write_raw_P(layer_logo, sizeof(layer_logo));
}


void render_right_layer_state(void) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
		case _BASE:
            render_base_right_logo();
            break;
        case _EXTRA:
            oled_write("Extra", false);
            break;
        case _TAP:
            oled_write("Tap", false);
            break;
        case _BUTTON:
            oled_write("Button", false);
            break;
        case _NAV:
            render_nav_right_logo();
            break;
        case _MOUSE:
            render_mouse_right_logo();
            break;
        case _MEDIA:
            render_media_right_logo();
            break;
        case _NUM:
            render_num_right_logo();
            break;
        case _SYM:
            render_sym_right_logo();
            break;
        case _FUN:
            render_fun_right_logo();
            break;
    }
}
void render_left_layer_state(void) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _BASE:
            render_base_left_logo();
            break;
        case _EXTRA:
            oled_write("Extra", false);
            break;
        case _TAP:
            oled_write("Tap", false);
            break;
        case _BUTTON:
            oled_write("Button", false);
            break;
        case _NAV:
            render_nav_left_logo();
            break;
        case _MOUSE:
            render_mouse_left_logo();
            break;
        case _MEDIA:
            render_media_left_logo();
            break;
        case _NUM:
            render_num_left_logo();
            break;
        case _SYM:
            render_sym_left_logo();
            break;
        case _FUN:
            render_fun_left_logo();
            break;
    }
}

bool oled_task_user(void) {
    if (is_keyboard_left()) {
        render_left_layer_state();
    } else {
		render_right_layer_state();
	}

    if (keymap_config.swap_lctl_lgui){
        oled_write("swap", false);
    }
    
    return false;
}

#endif