CUSTOM_MATRIX = lite
QUANTUM_LIB_SRC += analog.c
SRC += keyboards/cipulot/common/matrix.c keyboards/cipulot/common/ec_switch_matrix.c
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = embedded_flash
