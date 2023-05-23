# Studio ASP

Studio ASP is a southpaw 75% keyboard with numpad and a rotary encoder.

* Keyboard Maintainer: [ToastyStoemp](https://github.com/ToastyStoemp)
* Hardware Supported: Geistmaschine Studio ASP Rev1 PCB
* Hardware Availability: [geistmaschine.io](https://geistmaschine.io/)


Make example for this keyboard (after setting up your build environment):

	`qmk compile geistmaschine/studioasp -km default`

Since this keyboard uses a uf2 bootloader, copy the compiled firmware onto the USB storage drive which will be detected once the board enters bootloader mode.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader Enter the bootloader in 2 ways: 
* **Bootmagic reset**: Hold down the key ESC key and plug in the keyboard (Top Left most switch)
