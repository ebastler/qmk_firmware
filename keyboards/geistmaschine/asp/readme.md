# Studio ASP

![ASP](imgur.com image replace me!)

Studio ASP is a southpaw 75% keyboard with numpad and a rotary encoder.

* Keyboard Maintainer: [ebastler](https://github.com/ebastler)
* Hardware Supported: Geistmaschine Studio ASP Rev1 PCB
* Hardware Availability: [geistmaschine.io](https://geistmaschine.io/)


Make example for this keyboard (after setting up your build environment):

    qmk compile geistmaschine/geist -km default

Flashing example for this keyboard:

    qmk flash geistmaschine/geist -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
