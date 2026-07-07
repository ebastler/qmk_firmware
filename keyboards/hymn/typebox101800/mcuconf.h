// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include_next <mcuconf.h>

/* Set PLL M divider from 4 (F411 GENERIC default) to 8, because of 16 MHz crystal on board */
#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE                    8

/* Move system from TIM2 (default) to TIM3 (since TIM2 is needed for underglow) */
#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3                  FALSE
#undef STM32_ST_USE_TIMER
#define STM32_ST_USE_TIMER                  3

/* Enable TIM2 hardware peripheral */
#undef STM32_PWM_USE_TIM2
#define STM32_PWM_USE_TIM2 TRUE

