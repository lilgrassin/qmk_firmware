// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#define XXX KC_NO

#define LAYOUT_miryoku(\
     K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09,\
     K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19,\
     K20, K21, K22, K23, K24,                K25, K26, K27, K28, K29,\
     N30, N31, K32, K33, K34,                K35, K36, K37, N38, N39\
)\
LAYOUT(\
XXX, XXX, XXX, XXX, XXX, XXX,                    XXX, XXX, XXX, XXX, XXX, XXX,\
XXX, K00, K01, K02, K03, K04,                    K05, K06, K07, K08, K09, XXX,\
XXX, K10, K11, K12, K13, K14,                    K15, K16, K17, K18, K19, XXX,\
XXX, K20, K21, K22, K23, K24, KC_MUTE,  RGB_TOG, K25, K26, K27, K28, K29, XXX,\
            QK_RBT, K32, K33, K34,          K35, K36, K37, CG_TOGG\
)

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_MAGIC

#undef ENABLE_RGB_MATRIX_SOLID_COLOR
#undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_BREATHING
#undef ENABLE_RGB_MATRIX_BAND_SAT
#undef ENABLE_RGB_MATRIX_BAND_VAL

#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define RGB_MATRIX_DEFAULT_SPD 75
#define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS / 2
#define RGB_MATRIX_TIMEOUT 1000 * 60 * 10


#define ENCODER_RESOLUTION 2
