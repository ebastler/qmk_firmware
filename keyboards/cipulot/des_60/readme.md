# NEVEREST 60

![NEVEREST 60](https://i.imgur.com/w0igG9Oh.jpg)

Native QMK support for the NEVEREST 60.

* Keyboard Maintainer: [cipulot](https://github.com/cipulot)
* Hardware Supported: NEVEREST 60
* Hardware Availability: [DESKEYS](https://deskeys.io/)

Make example for this keyboard (after setting up your build environment):

    make cipulot/des_60:default

Flashing example for this keyboard:

    make cipulot/des_60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset**: Long short the exposed pads on the top of the PCB
* **Keycode in layout**: Press the key mapped to QK_BOOT if it is available
