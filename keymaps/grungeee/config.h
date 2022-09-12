/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
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

#pragma once

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_HUE_STEP  8
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  8
#    define RGBLIGHT_LIMIT_VAL 150
#endif

//: Lets you roll mod-tap keys
#define IGNORE_MOD_TAP_INTERRUPT
//> deactivated because it breakes oneshot keys
// #define TAPPING_FORCE_HOLD
//: Holding and releasing a dual function key without pressing another key will result in nothing happening. 
//: With retro tapping enabled, releasing the key without pressing another will send the original keycode even if it is outside the tapping term.
// #define RETRO_TAPPING
// #define RETRO_TAPPING_PER_KEY

//. Mouse
//#define MK_KINETIC_SPEED
#define MOUSEKEY_INITIAL_SPEED 3
#define MOUSEKEY_INTERVAL 20
#define MOUSEKEY_ACCELARATED_SPEED 0.1 
#define MOUSEKEY_MAX_SPEED 6
#define MOUSEKEY_TIME_TO_MAX 30 

//. Encoder
#ifdef ENCODER_ENABLE
// #    define ENCODER_DIRECTION_FLIP
#    define ENCODER_RESOLUTION 1
#endif

//. Oneshot Settings
// #define ONESHOT_TAP_TOGGLE 3
#define ONESHOT_TIMEOUT 250

//. Combos Settings
//#define COMBO_HOLD_TERM 200
#define EXTRA_SMALL_COMBOS

//. Tap-Toggle Settings 
#define TAPPING_TOGGLE 2

//. Global Tapping settings
// Tap-Dance Settings
#define TAPPING_TERM 250
#define TAPPING_TERM_PER_KEY
  
//. Power Settings
// #ifdef USB_MAX_POWER_CONSUMPTION
// #    define USB_MAX_POWER_CONSUMPTION 100
// #endif


