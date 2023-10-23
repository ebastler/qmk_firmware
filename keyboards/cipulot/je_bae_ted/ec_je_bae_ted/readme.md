# EC Je-BAE-Ted

![Je-BAE-Ted](https://i.imgur.com/IwVKHj3h.png)

EC version of the Je-BAE-Ted macropad.

* Keyboard Maintainer: [cipulot](https://github.com/cipulot)
* Hardware Supported: EC Je-BAE-Ted
* Hardware Availability: TBD

Make example for this keyboard (after setting up your build environment):

    make cipulot/je_bae_ted/ec_je_bae_ted:default

Flashing example for this keyboard:

    make cipulot/je_bae_ted/ec_je_bae_ted:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset**: Long short the exposed pads on the top of the PCB
* **Keycode in layout**: Press the key mapped to QK_BOOT if it is available
