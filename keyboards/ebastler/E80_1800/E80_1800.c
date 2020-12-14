#include "E80_1800.h"

void matrix_init_kb(void) {
  matrix_init_user();
  led_init_ports();
}

/* Set lock LEDs as outputs */
void led_init_ports(void) {
    setPinOutput(B4);
    setPinOutput(B5);
    setPinOutput(B6);
}

/* Set lock LEDs to their states*/
bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        writePin(B6, !led_state.num_lock);
        writePin(B5, !led_state.caps_lock);
        writePin(B4, !led_state.scroll_lock);
    }
    return true;
}


/* Temporary OLED setup for testing - better use should follow */
#ifdef OLED_DRIVER_ENABLE
void render_layer_state(void) {
    oled_write(PSTR(" - LAYER: "), false);
    if(layer_state_is(1)) {
        oled_write(PSTR("L1"), false);
    } else {
        oled_write(PSTR("L0"), false);
    }
}

void render_keyboard_name(led_t led_state) {
    oled_write(PSTR("E80-1800"), led_state.caps_lock);
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(qmk_logo, false);
}

void oled_task_user(void) {
    render_logo();
    render_keyboard_name(host_keyboard_led_state());
    render_layer_state();
}
#endif

/* turn OLED (if enabled) and backlight (if enabled) off on USB host suspend */
void suspend_power_down_user(void) {
#ifdef OLED_DRIVER_ENABLE
    oled_off();
#endif
}