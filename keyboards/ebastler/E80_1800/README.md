# E80-1800

![E80_1800_sample_image](https://raw.githubusercontent.com/ebastler/E80-1800/master/img/e80-1800-silk.jpg)

A replacement PCB for the Cherry G80-1800 keyboard. Supports ISO and ANSI, 6u offcenter or 7u bottom row, stepped and regular caps lock. Optional i2c header for OLED (no software support yet, but will follow). Type-C on the PCB (requires some case modifications). The PCB is open source and can be found in my [Github repo](https://github.com/ebastler/E80-1800).

* Keyboard Maintainer: [ebastler](https://github.com/ebastler)
* Hardware Supported: Rev1 PCB, see Github repo linked above
* Hardware Availability: None, feel free to order your own boards. jlcpcb compatible gerber/BOM/CPL files are included.

Bootmagic Lite key: Escape

Layer toggle on 6u bottom row keympas: right menu key

Layer toggle on 7u bottom row keymaps: right control key

Hardware control keys (All on layer 1):
* End: Toggle backlight
* Pg Up/Down: Increase/Decrease backlight brightness
* Scroll Lock: Toggle backlight breathing

Media control keys (All on layer 1):
* Numpad 2/8: Volume down/up
* Numpad 4/7: Previous/Next track
* Numpad 5: Mute audio
* Pause: Toggle play/pause

Make example for this keyboard (after setting up your build environment) - pick your layout:

    make ebastler/E80_1800:iso_6u
    make ebastler/E80_1800:iso_7u
    make ebastler/E80_1800:ansi_6u
    make ebastler/E80_1800:ansi_7u

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).