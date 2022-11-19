/*
!                 (             )     *                      )       )       (     (     
!  (  (           )\ )   (   ( /(   (  `           *   )  ( /(    ( /(       )\ )  )\ )  
!  )\))(   ' (   (()/(   )\  )\())  )\))(   (    ` )  /(  )\())   )\()) (   (()/( (()/(  
! ((_)()\ )  )\   /(_))(((_)((_)\  ((_)()\  )\    ( )(_))((_)\   ((_)\  )\   /(_)) /(_)) 
! _(())\_)()((_) (_))  )\___  ((_) (_()((_)((_)  (_(_())   ((_)   _((_)((_) (_))  (_))   
! \ \((_)/ /| __|| |  ((/ __|/ _ \ |  \/  || __| |_   _|  / _ \  | || || __|| |   | |    
!  \ \/\/ / | _| | |__ | (__| (_) || |\/| || _|    | |   | (_) | | __ || _| | |__ | |__  
!   \_/\_/  |___||____| \___|\___/ |_|  |_||___|   |_|    \___/  |_||_||___||____||____| 
*/

#include QMK_KEYBOARD_H

//* Tapdance States and Variables


// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

//* Custom tapdance keys

// enum tap_dance_codes {
//   SCLN_COLN,
// };

enum {
    ENT_NAV, // > Our custom tap dance key; add any other tap dance keys to this enum
    QWERTY_LOWER, // : custom layer swithchin 2
    // CT_SCLN, //: tap [;] | double-tap [:]
    SCLN_COLN,
    COMM_LABK,
    DOT_RABK,
    SLSH_QUES,
};



//* Macros settings
//- Super ALT↯TAB
bool is_alt_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.
//.
bool is_caps_active = false; //: for SFT_CAPS

//* Custom Keycodes
enum custom_keycodes {          // Make sure have the awesome keycode ready
  ALT_TAB = SAFE_RANGE, //Super ALT↯TAB
  SFT_CAPS,
  TEST
};
//& ////////////////////////////

//* Aliases for readability
//- Layers
#define QWERTY DF(_QWERTY)
#define RAISE DF(_RAISE)
#define LOWER DF(_LOWER)
#define NAV DF(_NAV)
#define ADJUST DF(_ADJUST)
#define GAMING DF(_GAMING)

//- Layer Toggle
#define LT_LOWER_TAB LT(LOWER, KC_TAB)
#define LT_RAISE_SPC LT(RAISE, KC_SPC)
#define LT_NAV_ENT LT(NAV, KC_ENT)



//- Modifiers
#define SFT_ALT LSFT(MOD_LALT)
#define CTL_ALT LCTL(MOD_LALT)
#define CTL_SFT_ALT MOD_MEH

//- Oneshot Mods
#define OS_SFT OSM(MOD_LSFT)
#define OS_CTL OSM(MOD_LCTL)
#define OS_ALT OSM(MOD_LALT)
#define OS_GUI OSM(MOD_LGUI)
// #define OS_SFT_ALT OSM(SFT_ALT)
// #define OS_CTL_ALT OSM(SFT_CTL)

//- Tap-dance
// #define TD_CT_SCLN TD(CT_SCLN)
// #define TD_CT_COMM TD(CT_COMM)
// #define TD_CT_DOT TD(CT_DOT)

//* Layers  
enum layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _NAV,
    _ADJUST,
    _GAMING
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // [_QWERTY] = LAYOUT(
    //   KC_LGUI,      KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    //   OS_ALT,      KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                                           KC_H,    KC_J,    KC_K,    KC_L,    TD(SCLN_COLN), KC_QUOT,
    //   ALT_TAB,      KC_Z,   KC_X,   KC_C,   KC_V,   KC_B, _______, KC_CAPS,                       KC_NUM, _______,  KC_N,   KC_M,    TD(COMM_LABK), TD(DOT_RABK),  TD(SLSH_QUES), KC_ESC,
    //          KC_MPLY, OS_CTL , OS_SFT, LT(_LOWER, KC_TAB), TD(ENT_NAV),          KC_BSPC, LT(_RAISE, KC_SPC), OS_SFT, OS_CTL, KC_MPLY
            //  KC_MPLY, _______ , TD(ENT_NAV), MT(MOD_MEH, KC_SPC), OS_SFT,  /*   */    OS_CTL, OSL(RAISE), MT(NAV, KC_BSPC), _______, KC_MPLY
    // ),

    [_QWERTY] = LAYOUT(
      KC_LGUI,      KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
      KC_LALT,      KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                               KC_H,    KC_J,    KC_K,    KC_L,    TD(SCLN_COLN), KC_QUOT,
      ALT_TAB,      KC_Z,   KC_X,   KC_C,   KC_V,   KC_B, _______, TD(QWERTY_LOWER),  /*   */  _______, _______,  KC_N,   KC_M,    TD(COMM_LABK), TD(DOT_RABK),  TD(SLSH_QUES), KC_ESC,
                                    KC_MPLY, _______ , TD(ENT_NAV), KC_SPC, OS_SFT,  /*   */    OS_CTL, OSL(RAISE), KC_BSPC, _______, KC_MPLY
    ),
// : modifiers for sft/ctl should probably be used with a combo or tap-dance
    [_LOWER] = LAYOUT(
      _______, KC_ESC, _______, _______, _______, _______,                                                    _______, KC_7, KC_8, KC_9, KC_BSPC, _______,
      _______, KC_TAB, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,                                                    _______, KC_4, KC_5, KC_6, KC_ENT, _______,
      _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_CAPS, TO(ADJUST),/*       */ TO(_GAMING), KC_NUM, KC_0, KC_1, KC_2, KC_3, _______, _______,
                                 _______, _______, _______, XXXXXXX, SFT_ALT,/*       */ CTL_ALT, XXXXXXX, _______, _______, _______
                                //  _______, _______, _______, TO(QWERTY), KC_LGUI,/*     */ KC_LALT, XXXXXXX, _______, _______, _______
    ),

    [_RAISE] = LAYOUT(
      _______, KC_ESC, KC_EXLM, KC_LCBR, KC_RCBR, KC_AT,                                                  KC_GRV , KC_TILD, KC_AMPR, KC_ASTR, KC_BSPC, _______,
      _______, KC_TAB, KC_DLR,  KC_LPRN, KC_RPRN, KC_HASH,                                                KC_UNDS, KC_MINS, KC_EQL , KC_PIPE, KC_ENT, _______,
      _______, _______, KC_CIRC, KC_LBRC, KC_RBRC, KC_PERC, _______, _______,/*      */ _______, TEST, _______, KC_PLUS, KC_BSLS, _______, _______, _______,
                                 _______, _______, _______, TD(QWERTY_LOWER), KC_LSFT,/*   */ KC_LCTL, XXXXXXX, _______, _______, _______
                                //  _______, _______, _______, TO(QWERTY), MOD_MEH,/*   */ KC_LALT, TO(LOWER), _______, _______, _______
    ),

     [_NAV] = LAYOUT(
    //    _______, _______, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2, KC_MS_WH_UP,                                          KC_HOME, KC_PGDN, KC_PGUP, KC_END , _______, _______,
       _______, KC_ESC, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2, KC_MS_WH_UP,                                          _______, KC_HOME, KC_END, _______ , KC_BSPC, _______,
       _______, KC_LCTL, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_MS_WH_DOWN,                                     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
       _______, KC_LSFT, _______, _______, _______, _______, _______, _______,      _______, _______,KC_MS_BTN1,_______, KC_PGDN,  KC_PGUP, _______, _______, 
                                  _______, _______, _______, _______, KC_LSFT,      KC_LCTL, XXXXXXX, KC_MS_BTN2, _______, _______
     ),

    [_ADJUST] = LAYOUT( 
      _______, _______, _______, _______, _______, _______,                                          _______, KC_F7   , KC_F8   , KC_F9   , KC_F12, _______,
      _______, _______, _______, _______, _______, _______,                                          _______, KC_F4   , KC_F5   , KC_F6   , KC_F11, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, /**/ _______, _______, _______, KC_F1   , KC_F2   , KC_F3   , KC_F10, _______,
                                 _______, _______, _______, _______, _______, /**/ _______, XXXXXXX, _______, _______, _______
    ),

    [_GAMING] = LAYOUT(
      KC_ESC,  KC_Q,  KC_W,  KC_E,   KC_R,   KC_T,                                                  KC_Y,   KC_U,    KC_I,          KC_O,          KC_P,          KC_BSPC,
      KC_TAB,  KC_A,  KC_S,  KC_D,   KC_F,   KC_G,                                                  KC_H,   KC_J,    KC_K,          KC_L,          TD(SCLN_COLN), KC_QUOT,
      KC_LCTL, KC_Z,  KC_X,  KC_C,   KC_V,   KC_B, KC_CAPS, KC_LGUI,  /*   */  TO(QWERTY), KC_NUM,  KC_N,   KC_M,    TD(COMM_LABK), TD(DOT_RABK),  TD(SLSH_QUES), KC_ESC,
             KC_MPLY, KC_LALT , KC_ENT, KC_SPC, KC_LSFT,  /*               */  KC_LCTL, OSL(RAISE), MT(NAV, KC_BSPC), _______,      KC_MPLY
    ),

/*
 * Base Layer: QWERTY 
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  GUI   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  ALT   |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |        |      |      |      |      |      |                              |      | J+K = Escape|      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |ALT_TAB |   Z  |   X  |   C  |   V  |   B  |      | Caps |  |Numlk |      |   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        ||>/|| | CTL  |Shift | Tab  |Enter/|  | Bksp |Space/| Shift| CTL ||>/|| |
 *                        |      |      |      | Lower|  Nav |  |      | Raise|      |     |      |
 *                        `----------------------------------'  `---------------------------------'
 * >====> Lower + Raise = Adjust <====< 
 */
/*
 * Raise Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |  !   |  {   |  }   |  @   |                              |   `  |  ~   |  &   |  *   |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |  $   |  (   |  )   |  #   |                              |   _  |  -   |  =   |  |   | ' "  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |  ^   |  [   |  ]   |  %   |      |      |  |      |      |      |  +   |  \   |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
/*
 * Navigation Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |  LC  |  Up  |  RC  |ScrlUp|                              | pg dn| home | end  |pg up |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | SPD0 |  <-  | Down |  ->  |ScrlDw|                              | left | down |  up  | right|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | SPD1 |      |      |      |      |      |      |  |      |      |      |  LC  |  RC  |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
*/
/*
 * Adjust Layer: Function keys, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |  F7  |  F8  |  F9  | F12  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |  F4  |  F5  |  F6  | F11  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |  F1  |  F2  |  F3  | F11  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
/*
 * Lower Layer: Number keys, media
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |  7   |  8   |  9   |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Prev | Play | Next | VolUp|                              |      |  4   |  5   |  6   |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      | Mute | VolDn|      |      |  |      |      |  0   |  1   |  2   |  3   |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |QWERTY|      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |Dvorak|      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |Colmak|      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
 
    // [_ADJUST] = LAYOUT(
    //   _______, _______, _______, _______ , _______, _______,                                    _______, _______, _______, _______,  _______, _______,
    //   _______, _______, _______, _______ , _______, _______,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
    //   _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
    //                              _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    // ),


    
/*
 * Layer template
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};
//* Other ways of switching layers
// //: QWERTY + RAISE = LOWER
// layer_state_t layer_state_set_user(layer_state_t state) {
//     return update_tri_layer_state(state, _QWERTY, _RAISE, _LOWER);
// }

// //: Lower + Raise = Adjust
// layer_state_t layer_state_set_user(layer_state_t state) {
//     return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
// }

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}


//* Kayria Logo 

static void render_kyria_logo(void) {

    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

//*  QMK Logo 

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
    oled_write_P(PSTR("Welcome back\n\n"), false);

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
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Nav\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        case _GAMING:
            oled_write_P(PSTR("Game Mode\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
}

//* OLED Logo settings 

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
        // render_dude_logo();
    }
    return false;
}
#endif

//* Encoder 

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif

// //* Oneshot Layer 

// void oneshot_layer_changed_user(uint8_t layer) {
//   if (layer == 1) {
//     println("Oneshot layer 1 on");
//   }
//   if (!layer) {
//     println("Oneshot layer off");
//   }
// }


//* Combos 

enum combos {
    FST_EQL,
    VIM_ESC,
    VIM_ESC_HOME_1,
    VIM_ESC_HOME_2,
    LEFT_PINKY_IGNORE,
    RIGHT_PINKY_IGNORE,
    COMBO_LENGTH
};

// enum combo_events {
//     COMBO_LENGTH
// };
uint16_t COMBO_LEN = COMBO_LENGTH;


const uint16_t PROGMEM fst_eql[] = {LT_RAISE_SPC, KC_K, COMBO_END};
const uint16_t PROGMEM vim_esc[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM vim_esc_home_1[] = {KC_MINS, KC_EQL, COMBO_END};
const uint16_t PROGMEM vim_esc_home_2[] = {KC_4, KC_5, COMBO_END};
const uint16_t PROGMEM left_pinky_ignore[] = {KC_Q, KC_A, COMBO_END};
const uint16_t PROGMEM right_pinky_ignore[] = {KC_P, TD(SCLN_COLN), COMBO_END};


combo_t key_combos[] = {
    [FST_EQL] = COMBO(fst_eql, KC_EQL),
    [LEFT_PINKY_IGNORE] = COMBO(left_pinky_ignore, KC_Q),
    [RIGHT_PINKY_IGNORE] = COMBO(right_pinky_ignore, KC_P),
    [VIM_ESC] = COMBO(vim_esc, KC_ESC),
    [VIM_ESC_HOME_1] = COMBO_ACTION(vim_esc_home_1), //: -=
    [VIM_ESC_HOME_2] = COMBO_ACTION(vim_esc_home_2), //: 45
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case VIM_ESC_HOME_1:
    if (pressed){
        tap_code16(KC_ESC);
        layer_move(_QWERTY);
    }
      break;
    case VIM_ESC_HOME_2:
      if (pressed) {
        tap_code16(KC_ESC);
        layer_move(_QWERTY);
      }
      break;
  }
}

//* Macros 


uint8_t mod_state;  
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  mod_state = get_mods();
  switch (keycode) {

//. Super ALT↯TAB
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;

      //. Shift + Backspace = Delete
  case KC_BSPC:
  {
        static bool delkey_registered;
        if (record->event.pressed) {
            if (mod_state & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_DEL);
                delkey_registered = true;
                set_mods(mod_state);
                return false;
            }
        } else { //: on release of KC_BSPC
            if (delkey_registered) {
                unregister_code(KC_DEL);
                delkey_registered = false;
                return false;
            }
        }
        return true;
    }

//. go back from stuck RAISE layer with QWERTY_LOWER key
    case TD(QWERTY_LOWER):
        if (record->event.pressed) {
            //: do nothing
        }else{
           if ( layer_state_is(_RAISE)){
            layer_move(_QWERTY);
           }
        }
      break;
   }
  return true;
};

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}



//* Tap-dance   

//. Tap Dance funcitons
// Declare the functions to be used with your tap dance key(s)
// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);


//- Enter and NAV layer
// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_ENT);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_NAV);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_NAV)) {
                // If already set, then switch it off
                layer_off(_NAV);
            } else {
                // If not already set, then switch the layer on
                layer_on(_NAV);
            }
            break;
        default:
            break;
    }
}


void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_NAV);
    }
    ql_tap_state.state = TD_NONE;
}


//- QWERTY and LOWER layer
// Functions associated with individual tap dances
void qwerty_nav_finished(qk_tap_dance_state_t *state, void *user_data);
void qwerty_nav_reset(qk_tap_dance_state_t *state, void *user_data);

void qwerty_nav_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            layer_move(_LOWER);
            break;
        case TD_DOUBLE_TAP:
            if (layer_state_is(_LOWER)) {
                layer_off(_LOWER);
            } else {
                layer_on(_LOWER);
            }
            break;
        case TD_NONE:
            if (layer_state_is(_RAISE)) {
            layer_move(_QWERTY);
            }
            break;
        default:
            break;
    }
}

void qwerty_nav_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_move(_RAISE);
    }
    ql_tap_state.state = TD_NONE;
}

//&  ===========< test >==============
//&  ===========< test >==============

//^! ////////// Another Version //////////

// extern bool g_suspend_state;
// #define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF
// uint16_t last_keycode = KC_NO;
// uint8_t last_modifier = 0;


enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state = {
    .is_press_action = true,
    .step = 0
};

//- Send ; on Single Tap, : on Hold
void on_scln_end(qk_tap_dance_state_t *state, void *user_data);
uint8_t scln_end_dance_step(qk_tap_dance_state_t *state);
void scln_end_finished(qk_tap_dance_state_t *state, void *user_data);
void scln_end_reset(qk_tap_dance_state_t *state, void *user_data);

void on_scln_end(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_SCLN);
        tap_code16(KC_SCLN);
        tap_code16(KC_SCLN);
    }
    if(state->count > 3) {
        tap_code16(KC_SCLN);
    }
}

uint8_t scln_end_dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

void scln_end_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state.step = scln_end_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_SCLN); break;
        case SINGLE_HOLD: register_code16(KC_COLN); break;
        case DOUBLE_TAP: register_code16(KC_SCLN); register_code16(KC_SCLN); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_SCLN); register_code16(KC_SCLN);
    }
}

void scln_end_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_SCLN); break;
        case SINGLE_HOLD: unregister_code16(KC_COLN); break;
        case DOUBLE_TAP: unregister_code16(KC_SCLN); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_SCLN); break;
    }
    dance_state.step = 0;
}

//- Send . on Single Tap, > on Hold
void on_dot_end(qk_tap_dance_state_t *state, void *user_data);
uint8_t dot_end_dance_step(qk_tap_dance_state_t *state);
void dot_end_finished(qk_tap_dance_state_t *state, void *user_data);
void dot_end_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dot_end(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_DOT);
        tap_code16(KC_DOT);
        tap_code16(KC_DOT);
    }
    if(state->count > 3) {
        tap_code16(KC_DOT);
    }
}

uint8_t dot_end_dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

void dot_end_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state.step = dot_end_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_DOT); break;
        case SINGLE_HOLD: register_code16(KC_RABK); break;
        case DOUBLE_TAP: register_code16(KC_DOT); register_code16(KC_DOT); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_DOT); register_code16(KC_DOT);
    }
}

void dot_end_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_DOT); break;
        case SINGLE_HOLD: unregister_code16(KC_RABK); break;
        case DOUBLE_TAP: unregister_code16(KC_DOT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_DOT); break;
    }
    dance_state.step = 0;
}

//- Send , on Single Tap, < on Hold
void on_comm_end(qk_tap_dance_state_t *state, void *user_data);
uint8_t comm_end_dance_step(qk_tap_dance_state_t *state);
void comm_end_finished(qk_tap_dance_state_t *state, void *user_data);
void comm_end_reset(qk_tap_dance_state_t *state, void *user_data);

void on_comm_end(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_COMM);
        tap_code16(KC_COMM);
        tap_code16(KC_COMM);
    }
    if(state->count > 3) {
        tap_code16(KC_COMM);
    }
}

uint8_t comm_end_dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void comm_end_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state.step = comm_end_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_COMM); break;
        case SINGLE_HOLD: register_code16(KC_LABK); break;
        case DOUBLE_TAP: register_code16(KC_COMM); register_code16(KC_COMM); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_COMM); register_code16(KC_COMM);
    }
}

void comm_end_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_COMM); break;
        case SINGLE_HOLD: unregister_code16(KC_LABK); break;
        case DOUBLE_TAP: unregister_code16(KC_COMM); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_COMM); break;
    }
    dance_state.step = 0;
}

//. Send / on Single Tap, ? on Hold
void on_slash_end(qk_tap_dance_state_t *state, void *user_data);
uint8_t slash_end_dance_step(qk_tap_dance_state_t *state);
void slash_end_finished(qk_tap_dance_state_t *state, void *user_data);
void slash_end_reset(qk_tap_dance_state_t *state, void *user_data);

void on_slash_end(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_SLSH);
        tap_code16(KC_SLSH);
        tap_code16(KC_SLSH);
    }
    if(state->count > 3) {
        tap_code16(KC_SLSH);
    }
}

uint8_t slash_end_dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

void slash_end_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state.step = slash_end_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_SLSH); break;
        case SINGLE_HOLD: register_code16(KC_QUES); break;
        case DOUBLE_TAP: register_code16(KC_SLSH); register_code16(KC_SLSH); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_SLSH); register_code16(KC_SLSH);
    }
}

void slash_end_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_SLSH); break;
        case SINGLE_HOLD: unregister_code16(KC_QUES); break;
        case DOUBLE_TAP: unregister_code16(KC_SLSH); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_SLSH); break;
    }
    dance_state.step = 0;
}

//^! >===================/ /==================<

//- Send ; on Single Tap, : on Double Tap
void dance_scln_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_SCLN);
    } else {
        register_code16(KC_COLN);
    }
}

void dance_scln_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_SCLN);
    } else {
        unregister_code16(KC_COLN);
    }
}

//- <===================< Tapping Term settings >===================>

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        //. layer toggle settings:
        case LT_RAISE_SPC:
            return 170;
            // return TAPPING_TERM + 1250;
        case LT_LOWER_TAB:
            return 170;
        case LT_NAV_ENT:
            return 300;
            //. tapdance dual-keys settings
        case TD(QWERTY_LOWER):
        case TD(SLSH_QUES):
        case TD(SCLN_COLN):
        case TD(COMM_LABK):
        case TD(DOT_RABK):
            return 130;
        default:
            return TAPPING_TERM;
    }
}

// QWERTY_LOWER
// All tap dance functions would go here. 
// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    // [ENT_NAV]  ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 150),
    // [CT_SCLN] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_scln_finished, dance_scln_reset, 150),
    [ENT_NAV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset),
    [QWERTY_LOWER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, qwerty_nav_finished, qwerty_nav_reset),
    [SCLN_COLN] = ACTION_TAP_DANCE_FN_ADVANCED(on_scln_end, scln_end_finished, scln_end_reset),
    [COMM_LABK] = ACTION_TAP_DANCE_FN_ADVANCED(on_comm_end, comm_end_finished, comm_end_reset),
    [DOT_RABK] = ACTION_TAP_DANCE_FN_ADVANCED(on_dot_end, dot_end_finished, dot_end_reset),
    [SLSH_QUES] = ACTION_TAP_DANCE_FN_ADVANCED(on_slash_end, slash_end_finished, slash_end_reset),
}; 

//& //////////////// END /////////////////////
//& //////////////// END /////////////////////
//& //////////////// END /////////////////////
//& //////////////// END /////////////////////
//& //////////////// END /////////////////////
//& //////////////// END /////////////////////
//& //////////////// END /////////////////////
//& //////////////// END /////////////////////
//& //////////////// END /////////////////////
//& //////////////// END /////////////////////
//& //////////////// END /////////////////////
//& //////////////// END /////////////////////

// static void render_dude_logo(void) {
//     static const char PROGMEM dude_logo[] = {
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0xc0, 0x20, 0x10, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
// 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x18, 0x10, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 
// 0x7e, 0x61, 0x61, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
// 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x61, 0x61, 0x7e, 0x40, 0x40, 0x80, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0a, 0x09, 0x08, 0x08, 0x08, 
// 0xf0, 0x00, 0x00, 0xf8, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x84, 0x04, 0x08, 0xf0, 0xc0, 
// 0xc0, 0xc0, 0xc0, 0xf0, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x84, 0x04, 0x08, 0xf0, 0x08, 
// 0x09, 0x0a, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x19, 0x09, 
// 0xf0, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x04, 0x04, 0x02, 0x03, 0x00, 
// 0x00, 0xc0, 0xc0, 0xc3, 0xc2, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x04, 0xfc, 0x02, 0x03, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 
// 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x08, 0x08, 0x08, 
// 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0c, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//    };
//     oled_write_raw_P(dude_logo, sizeof(dude_logo));
// }

// #ifdef ENCODER_ENABLE
// bool encoder_update_user(uint8_t index, bool clockwise) {
//     if (index == 0) {
//         // Volume control
//         if (clockwise) {
//             tap_code(KC_VOLD);
//         } else {
//             tap_code(KC_VOLU);
//         }
//     }
//     else if (index == 1) {
//         // Page up/Page down
//         if (clockwise) {
//             tap_code(KC_PGDN);
//         } else {
//             tap_code(KC_PGUP);
//         }
//     }
//     return true;
// }
// #endif

//* Default:

// #include QMK_KEYBOARD_H

// enum layers {
//     _QWERTY = 0,
//     _DVORAK,
//     _COLEMAK_DH,
//     _NAV,
//     _SYM,
//     _FUNCTION,
//     _ADJUST,
// };


// // Aliases for readability
// #define QWERTY   DF(_QWERTY)
// #define COLEMAK  DF(_COLEMAK_DH)
// #define DVORAK   DF(_DVORAK)

// #define SYM      MO(_SYM)
// #define NAV      MO(_NAV)
// #define FKEYS    MO(_FUNCTION)
// #define ADJUST   MO(_ADJUST)

// #define CTL_ESC  MT(MOD_LCTL, KC_ESC)
// #define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
// #define CTL_MINS MT(MOD_RCTL, KC_MINUS)
// #define ALT_ENT  MT(MOD_LALT, KC_ENT)

// // Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// // The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// // produces the key `tap` when tapped (i.e. pressed and released).

// // clang-format off
// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// /*
//  * Base Layer: QWERTY
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "|
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * | LShift |   Z  |   X  |   C  |   V  |   B  | [ {  |CapsLk|  |F-keys|  ] } |   N  |   M  | ,  < | . >  | /  ? | RShift |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
//  *                        |      |      | Enter|      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_QWERTY] = LAYOUT(
//      KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_BSPC,
//      CTL_ESC , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H,   KC_J ,  KC_K ,   KC_L ,KC_SCLN,CTL_QUOT,
//      KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , KC_LBRC,KC_CAPS,     FKEYS  , KC_RBRC, KC_N,   KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
//                                 ADJUST , KC_LGUI, ALT_ENT, KC_SPC , NAV   ,     SYM    , KC_SPC ,KC_RALT, KC_RGUI, KC_APP
//     ),

// /*
//  * Base Layer: Dvorak
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |  Tab   | ' "  | , <  | . >  |   P  |   Y  |                              |   F  |   G  |   C  |   R  |   L  |  Bksp  |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |Ctrl/Esc|   A  |   O  |   E  |   U  |   I  |                              |   D  |   H  |   T  |   N  |   S  |Ctrl/- _|
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * | LShift | ; :  |   Q  |   J  |   K  |   X  | [ {  |CapsLk|  |F-keys|  ] } |   B  |   M  |   W  |   V  |   Z  | RShift |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
//  *                        |      |      | Enter|      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_DVORAK] = LAYOUT(
//      KC_TAB  ,KC_QUOTE,KC_COMM,  KC_DOT,   KC_P ,   KC_Y ,                                        KC_F,   KC_G ,  KC_C ,   KC_R ,  KC_L , KC_BSPC,
//      CTL_ESC , KC_A ,  KC_O   ,  KC_E  ,   KC_U ,   KC_I ,                                        KC_D,   KC_H ,  KC_T ,   KC_N ,  KC_S , CTL_MINS,
//      KC_LSFT ,KC_SCLN, KC_Q   ,  KC_J  ,   KC_K ,   KC_X , KC_LBRC,KC_CAPS,     FKEYS  , KC_RBRC, KC_B,   KC_M ,  KC_W ,   KC_V ,  KC_Z , KC_RSFT,
//                                  ADJUST, KC_LGUI, ALT_ENT, KC_SPC , NAV   ,     SYM    , KC_SPC ,KC_RALT, KC_RGUI, KC_APP
//     ),

// /*
//  * Base Layer: Colemak DH
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |  Tab   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |  Bksp  |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |Ctrl/Esc|   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  |Ctrl/' "|
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * | LShift |   Z  |   X  |   C  |   D  |   V  | [ {  |CapsLk|  |F-keys|  ] } |   K  |   H  | ,  < | . >  | /  ? | RShift |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
//  *                        |      |      | Enter|      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_COLEMAK_DH] = LAYOUT(
//      KC_TAB  , KC_Q ,  KC_W   ,  KC_F  ,   KC_P ,   KC_B ,                                        KC_J,   KC_L ,  KC_U ,   KC_Y ,KC_SCLN, KC_BSPC,
//      CTL_ESC , KC_A ,  KC_R   ,  KC_S  ,   KC_T ,   KC_G ,                                        KC_M,   KC_N ,  KC_E ,   KC_I ,  KC_O , CTL_QUOT,
//      KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_D ,   KC_V , KC_LBRC,KC_CAPS,     FKEYS  , KC_RBRC, KC_K,   KC_H ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
//                                  ADJUST, KC_LGUI, ALT_ENT, KC_SPC , NAV   ,     SYM    , KC_SPC ,KC_RALT, KC_RGUI, KC_APP
//     ),

// /*
//  * Nav Layer: Media, navigation
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              | PgUp | Home |   ↑  | End  | VolUp| Delete |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |  GUI |  Alt | Ctrl | Shift|      |                              | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |ScLck |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_NAV] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, KC_DEL,
//       _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS,
//       _______, _______, _______, _______, _______, _______, _______, KC_SLCK, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),

// /*
//  * Sym Layer: Numbers and symbols
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |    `   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |    ~   |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |   +    |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |    |   |   \  |  :   |  ;   |  -   |  [   |  {   |      |  |      |   }  |   ]  |  _   |  ,   |  .   |  /   |   ?    |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_SYM] = LAYOUT(
//       KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                       KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
//      KC_TILD , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
//      KC_PIPE , KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC, KC_LCBR, _______, _______, KC_RCBR, KC_RBRC, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_QUES,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),

// /*
//  * Function Layer: Function keys
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |  F9  | F10  | F11  | F12  |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |  F5  |  F6  |  F7  |  F8  |      |                              |      | Shift| Ctrl |  Alt |  GUI |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_FUNCTION] = LAYOUT(
//       _______,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                                     _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
//       _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),

// /*
//  * Adjust Layer: Default layer settings, RGB
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |QWERTY|      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |Dvorak|      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |Colmak|      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_ADJUST] = LAYOUT(
//       _______, _______, _______, QWERTY , _______, _______,                                    _______, _______, _______, _______,  _______, _______,
//       _______, _______, _______, DVORAK , _______, _______,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
//       _______, _______, _______, COLEMAK, _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
//                                  _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
//     ),

// // /*
// //  * Layer template
// //  *
// //  * ,-------------------------------------------.                              ,-------------------------------------------.
// //  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
// //  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
// //  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
// //  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
// //  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
// //  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
// //  *                        |      |      |      |      |      |  |      |      |      |      |      |
// //  *                        |      |      |      |      |      |  |      |      |      |      |      |
// //  *                        `----------------------------------'  `----------------------------------'
// //  */
// //     [_LAYERINDEX] = LAYOUT(
// //       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
// //       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
// //       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
// //                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
// //     ),
// };

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

/* DELETE THIS LINE TO UNCOMMENT (1/2)
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("QWERTY\n"), false);
                break;
            case _DVORAK:
                oled_write_P(PSTR("Dvorak\n"), false);
                break;
            case _COLEMAK_DH:
                oled_write_P(PSTR("Colemak-DH\n"), false);
                break;
            case _NAV:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case _SYM:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif
DELETE THIS LINE TO UNCOMMENT (2/2) */
