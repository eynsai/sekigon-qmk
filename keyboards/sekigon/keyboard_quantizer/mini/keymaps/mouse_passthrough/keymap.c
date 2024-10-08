// Copyright 2023 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
// #include "full.h"

// #include "virtser.h"
// #include "os_detection.h"
#include "cli.h"
#include "dynamic_config.h"

#include "pointing_device.h"
#include "report_parser.h"
#include "quantizer_mouse.h"
#include "mouse_passthrough_sender.h"

// user_config_t user_config;
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {{{KC_NO}}};

// To compile keymap_introspection.c, declear combo here
extern combo_t key_combos[COMBO_LEN_MAX];

// int8_t virtser_send_wrap(uint8_t c) {
//     virtser_send(c);
//     return 0;
// }

void keyboard_pre_init_user(void) {
    cli_init();
    // print_set_sendchar(virtser_send_wrap);
    // dynamic_config_init();
}

// void keyboard_post_init_user(void) {
//     user_config.raw = eeconfig_read_user();
//     set_mouse_gesture_threshold(get_mouse_gesture_threshold());
// }

void housekeeping_task_user(void) {
    // static os_variant_t detected_os = OS_UNSURE;
    // if (detected_os != detected_host_os()) {
    //     dynamic_config_activate_default_apps();
    //     detected_os = detected_host_os();
    // }

    // dynamic_config_task();
    cli_exec();
}

// bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
//     return pre_process_record_mouse(keycode, record);
// }

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     bool cont = process_record_dynamic_config(keycode, record) //
//                 && process_record_mouse(keycode, record);

//     if (record->event.pressed) {
//         switch (keycode) {
//             case QK_KB_0 ... QK_KB_3:
//                 // Used for mouse gesture
//                 break;
//             case QK_KB_4:
//                 send_bootstrap_macro();
//                 break;
//             case QK_KB_5:
//                 set_keyboard_language(LANG_US);
//                 user_config.keyboard_lang_us_or_jp = 0;
//                 eeconfig_update_user(user_config.raw);
//                 break;
//             case QK_KB_6:
//                 set_keyboard_language(LANG_JP);
//                 user_config.keyboard_lang_us_or_jp = 1;
//                 eeconfig_update_user(user_config.raw);
//                 break;
//             case QK_KB_7:
//                 set_os_language(LANG_US);
//                 user_config.os_lang_us_or_jp = 0;
//                 eeconfig_update_user(user_config.raw);
//                 break;
//             case QK_KB_8:
//                 set_os_language(LANG_JP);
//                 user_config.os_lang_us_or_jp = 1;
//                 eeconfig_update_user(user_config.raw);
//                 break;
//         }
//     }

//     return cont;
// }

// void post_process_record_user(uint16_t keycode, keyrecord_t* record) {
//     post_process_record_mouse(keycode, record);
// }

//  void eeconfig_init_user(void) {
//     user_config.keyboard_lang_us_or_jp = get_keyboard_language() == LANG_JP ? 1 : 0;
//     user_config.os_lang_us_or_jp       = get_os_language() == LANG_JP ? 1 : 0;

//     eeconfig_update_user(user_config.raw);
//  }

extern bool mouse_send_flag;
static uint8_t last_buttons_sent = 0;

bool mouse_report_hook_user(mouse_parse_result_t const* report) {
    report_mouse_t mouse = pointing_device_get_report();
    mouse.buttons = report->button;
    mouse.x = report->x;
    mouse.y = report->y;
    mouse.v = report->v;
    mouse.h = report->h;
    mouse = mouse_passthrough_sender_pointing_device_task(mouse);
    if ((last_buttons_sent != mouse.buttons) || (mouse.x != 0) || (mouse.y != 0) || (mouse.v != 0) || (mouse.h != 0)) {
        mouse_send_flag = true;
        last_buttons_sent = mouse.buttons;
    }
    pointing_device_set_report(mouse);
    return false;
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    mouse_passthrough_sender_raw_hid_receive_task(data);
}

void matrix_scan_user() {
    mouse_passthrough_sender_matrix_scan_task();
}
