// Copyright 2022 moritz plattner (moritz plattner)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Rotary encoder - set the resolution fitting your encoder.
Most will need a value of 4. If 1 encoder click results in 2 keycodes sent
increase the value. If you need 2 clicks for 1 keycode, decrease*/
#define ENCODER_RESOLUTION 4
#define ENCODERS_PAD_A { B5 }
#define ENCODERS_PAD_B { A15 }
#define TAP_CODE_DELAY 10