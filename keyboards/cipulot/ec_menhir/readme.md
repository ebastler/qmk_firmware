# EC Menhir

![EC Menhir Unified Spacebar](https://i.imgur.com/Qpa4oESh.png)
![EC Menhir Split Spacebar](https://i.imgur.com/3PBjbsRh.png)

EC version of the Menhir.

* Keyboard Maintainer: [cipulot](https://github.com/cipulot)
* Hardware Supported: EC Menhir
* Hardware Availability: [fruitykeeb](https://fruitykeeb.xyz/)

Make example for this keyboard (after setting up your build environment):

    make cipulot/ec_menhir:default

Flashing example for this keyboard:

    make cipulot/ec_menhir:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset**: Long short the exposed pads on the top of the PCB
* **Keycode in layout**: Press the key mapped to QK_BOOT if it is available
