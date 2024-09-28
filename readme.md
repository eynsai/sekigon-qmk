This is a fork of sekigon-gonnoc's fork of QMK. 
(It diverges from sekigon's fork at commit `6f4f9d4d6d18039a6106eba3944dc1d84de36b27` of the `keyboard/sekigon/keyboard_quantizer/mini-full` branch.)
It primarily exists to manage my customizations to sekigon's mini keyboard quantizer firmware.

To keep things clean, most of the keyboards and userspace components have been stripped out.

To build, run `qmk compile -kb sekigon/keyboard_quantizer/mini -km mouse_passthrough`.
