// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

#define MIRYOKU_CLIPBOARD_WIN

#define MIRYOKU_LAYER_BASE \
KC_Q,              KC_W,              KC_F,              KC_P,              KC_B,              KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT,           \
LGUI_T(KC_A),      LALT_T(KC_R),      LCTL_T(KC_S),      LSFT_T(KC_T),      KC_G,              KC_M,              RSFT_T(KC_N),      RCTL_T(KC_E),      LALT_T(KC_I),      RGUI_T(KC_O),      \
KC_Z,              KC_X,              KC_C,              KC_D,              KC_V,              KC_K,              KC_H,              KC_COMM,           KC_DOT,            KC_MINS,           \
U_NP,              U_NP,              LT(U_MEDIA,KC_ESC),LT(U_NAV,KC_SPC),  LT(U_MOUSE,KC_TAB),LT(U_SYM,KC_ENT),  LT(U_NUM,KC_BSPC), LT(U_FUN,KC_DEL),  U_NP,              U_NP

#define MIRYOKU_LAYER_NUM \
KC_HASH,           KC_9,              KC_8,              KC_7,              KC_QUES,           U_NA,              TD(U_TD_U_BASE),   TD(U_TD_U_EXTRA),  TD(U_TD_U_TAP),    TD(U_TD_BOOT),     \
KC_AT,             KC_6,              KC_5,              KC_4,              KC_DLR,            U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           \
KC_TILD,           KC_3,              KC_2,              KC_1,              KC_COLN,           U_NA,              TD(U_TD_U_NUM),    TD(U_TD_U_NAV),    KC_ALGR,           U_NA,              \
U_NP,              U_NP,              KC_GRV,            KC_0,              KC_DOT,            U_NA,              U_NA,              U_NA,              U_NP,              U_NP

#define MIRYOKU_LAYER_SYM \
KC_PERC,           KC_LBRC,           KC_LCBR,           KC_PLUS,           KC_EXLM,           U_NA,              TD(U_TD_U_BASE),   TD(U_TD_U_EXTRA),  TD(U_TD_U_TAP),    TD(U_TD_BOOT),     \
KC_LABK,           KC_RABK,           KC_EQL,            KC_MINS,           KC_AMPR,           U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           \
KC_CIRC,           KC_RBRC,           KC_RCBR,           KC_ASTR,           KC_PIPE,           U_NA,              TD(U_TD_U_SYM),    TD(U_TD_U_MOUSE),  KC_ALGR,           U_NA,              \
U_NP,              U_NP,              KC_BSLS,           KC_SCLN,           KC_SLSH,           U_NA,              U_NA,              U_NA,              U_NP,              U_NP

//                          j	l	u	y	'
//                          m	n	e	i	o
//                          k	h	,	.	-

//                          j	l	u	y	"
//                          m	n	e	i	o
//                          k	h	(	)	_

//  #	9	8	7	?
//  @	6	5	4	$
//  ~	3	2	1	:
// 			`	0	.

//  %	[	{	+	!
//  <	>	=	-	&
//  ^	]	}	*	|
// 			\	;	/

// KC_UNDS
// KC_LPRN
// KC_RPRN

#define U_CUSTOM_SHIFT_OVERRIDE(_key, _replace, _layer) \
ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, (_key), (_replace), (1 << (_layer)), MOD_MASK_CAG)

#define U_CUSTOM_KEYCODE_OVERRIDE_LIST \
KEYCODE_OVERRIDE_X(comm_base, U_CUSTOM_SHIFT_OVERRIDE, KC_COMM, KC_LPRN, U_BASE) \
KEYCODE_OVERRIDE_X(dot_base, U_CUSTOM_SHIFT_OVERRIDE, KC_DOT, KC_RPRN, U_BASE) \
KEYCODE_OVERRIDE_X(hash_num, U_CUSTOM_SHIFT_OVERRIDE, KC_HASH, KC_PERC, U_NUM) \
KEYCODE_OVERRIDE_X(perc_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_PERC, KC_HASH, U_SYM) \
KEYCODE_OVERRIDE_X(nine_num, U_CUSTOM_SHIFT_OVERRIDE, KC_9, KC_LBRC, U_NUM) \
KEYCODE_OVERRIDE_X(lbrc_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_LBRC, KC_9, U_SYM) \
KEYCODE_OVERRIDE_X(eigh_num, U_CUSTOM_SHIFT_OVERRIDE, KC_8, KC_LCBR, U_NUM) \
KEYCODE_OVERRIDE_X(lcbr_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_LCBR, KC_8, U_SYM) \
KEYCODE_OVERRIDE_X(sev_num, U_CUSTOM_SHIFT_OVERRIDE, KC_7, KC_PLUS, U_NUM) \
KEYCODE_OVERRIDE_X(plus_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_PLUS, KC_7, U_SYM) \
KEYCODE_OVERRIDE_X(ques_num, U_CUSTOM_SHIFT_OVERRIDE, KC_QUES, KC_EXLM, U_NUM) \
KEYCODE_OVERRIDE_X(exlm_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_EXLM, KC_QUES, U_SYM) \
KEYCODE_OVERRIDE_X(at_num, U_CUSTOM_SHIFT_OVERRIDE, KC_AT, KC_LABK, U_NUM) \
KEYCODE_OVERRIDE_X(labk_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_LABK, KC_AT, U_SYM) \
KEYCODE_OVERRIDE_X(six_num, U_CUSTOM_SHIFT_OVERRIDE, KC_6, KC_RABK, U_NUM) \
KEYCODE_OVERRIDE_X(rabk_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_RABK, KC_6, U_SYM) \
KEYCODE_OVERRIDE_X(five_num, U_CUSTOM_SHIFT_OVERRIDE, KC_5, KC_EQL, U_NUM) \
KEYCODE_OVERRIDE_X(eql_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_EQL, KC_5, U_SYM) \
KEYCODE_OVERRIDE_X(four_num, U_CUSTOM_SHIFT_OVERRIDE, KC_4, KC_MINS, U_NUM) \
KEYCODE_OVERRIDE_X(mins_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_MINS, KC_4, U_SYM) \
KEYCODE_OVERRIDE_X(dlr_num, U_CUSTOM_SHIFT_OVERRIDE, KC_DLR, KC_AMPR, U_NUM) \
KEYCODE_OVERRIDE_X(ampr_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_AMPR, KC_DLR, U_SYM) \
KEYCODE_OVERRIDE_X(tild_num, U_CUSTOM_SHIFT_OVERRIDE, KC_TILD, KC_CIRC, U_NUM) \
KEYCODE_OVERRIDE_X(circ_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_CIRC, KC_TILD, U_SYM) \
KEYCODE_OVERRIDE_X(thre_num, U_CUSTOM_SHIFT_OVERRIDE, KC_3, KC_RBRC, U_NUM) \
KEYCODE_OVERRIDE_X(rbrc_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_RBRC, KC_3, U_SYM) \
KEYCODE_OVERRIDE_X(two_num, U_CUSTOM_SHIFT_OVERRIDE, KC_2, KC_RCBR, U_NUM) \
KEYCODE_OVERRIDE_X(rcbr_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_RCBR, KC_2, U_SYM) \
KEYCODE_OVERRIDE_X(one_num, U_CUSTOM_SHIFT_OVERRIDE, KC_1, KC_ASTR, U_NUM) \
KEYCODE_OVERRIDE_X(astr_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_ASTR, KC_1, U_SYM) \
KEYCODE_OVERRIDE_X(coln_num, U_CUSTOM_SHIFT_OVERRIDE, KC_COLN, KC_PIPE, U_NUM) \
KEYCODE_OVERRIDE_X(pipe_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_PIPE, KC_COLN, U_SYM) \
KEYCODE_OVERRIDE_X(grv_num, U_CUSTOM_SHIFT_OVERRIDE, KC_GRV, KC_BSLS, U_NUM) \
KEYCODE_OVERRIDE_X(bsls_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_BSLS, KC_GRV, U_SYM) \
KEYCODE_OVERRIDE_X(zero_num, U_CUSTOM_SHIFT_OVERRIDE, KC_0, KC_SCLN, U_NUM) \
KEYCODE_OVERRIDE_X(scln_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_SCLN, KC_0, U_SYM) \
KEYCODE_OVERRIDE_X(dot_num, U_CUSTOM_SHIFT_OVERRIDE, KC_DOT, KC_SLSH, U_NUM) \
KEYCODE_OVERRIDE_X(slsh_sym, U_CUSTOM_SHIFT_OVERRIDE, KC_SLSH, KC_DOT, U_SYM)
