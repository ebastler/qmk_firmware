# heavymetalkeyboards BOR60

![BOR60 sample image](TBD)

The Bornheim 60 is a family of keyboards from hmkb in various layouts, that are all 60% based. They feature a novel approach to fit arrow keys onto a 60% keyboard and extensive support for small spacebars (6u, 4.5u, 4u and 3u on solder PCBs, 6u, 4u and 3u on hotswap PCBs). 

* Keyboard Maintainer: [ebastler](https://github.com/ebastler)
* Hardware Supported: BOR60 rev1 PCBs
* Hardware Availability: Groupbuy, visit https://heavymetalkeyboards.com/ for more information

How to enter the Bootloader:
* Follow instructions on the PCB (Hold Boot/Flash button for approx. 1s)
* Bootmagic reset: Hold the top leftmost key (ESC) while plugging in the board

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb hmkb/bor60 -km default

Flash example for this keyboard (after setting up your build environment):

    qmk flash -kb hmkb/bor60 -km default


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).