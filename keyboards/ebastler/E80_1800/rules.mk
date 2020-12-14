# MCU name
MCU = STM32F072

# Build Options
# SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes		  # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
EXTRAKEY_ENABLE = yes	  # Audio control and System control(+450)
BACKLIGHT_ENABLE = yes
OLED_DRIVER_ENABLE = yes
BOOTMAGIC_ENABLE = lite   # Enable lite mode of bootmagic (boot into BL my pressing ESC at power-up)


# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
OPT_DEFS += -DSTM32_DMA_REQUIRED=TRUE
