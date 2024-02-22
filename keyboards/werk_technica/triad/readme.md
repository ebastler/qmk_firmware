# werk.technica one

A 65% keyboard with curved topside.

* Keyboard Maintainer: [ebastler](https://github.com/ebastler)
* Hardware Supported: Rev1 solder and hotswap PCB (please use `via` or `default` layout for hotswap)
* Hardware Availability: Groupbuy

Bootmagic Lite key: Escape (top leftmost key)
Physical reset switch present on the bottom of the PCB

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb werk_technica/triad -km default

Flash example for this keyboard (after setting up your build environment):

    qmk flash -kb werk_technica/triad -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).