RGB_MATRIX_CUSTOM_KB = yes
CUSTOM_MATRIX = lite
ANALOG_DRIVER_REQUIRED = yes
SRC += matrix.c he_switch_matrix.c
OPT=2
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = embedded_flash