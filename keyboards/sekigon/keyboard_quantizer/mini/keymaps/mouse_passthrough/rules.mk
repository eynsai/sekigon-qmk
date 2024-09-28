SRC += quantizer_mouse.c

include keyboards/sekigon/keyboard_quantizer/mini/keymaps/mouse_passthrough/dynamic_config/rules.mk
include keyboards/sekigon/keyboard_quantizer/mini/keymaps/mouse_passthrough/cli/rules.mk

VPATH += keyboards/sekigon/keyboard_quantizer/mini/keymaps/mouse_passthrough/dynamic_config/
VPATH += keyboards/sekigon/keyboard_quantizer/mini/keymaps/mouse_passthrough/cli/

KEY_OVERRIDE_ENABLE = yes
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes
LEADER_ENABLE = yes
OS_DETECTION_ENABLE = yes

GIT_DESCRIBE := $(shell git describe --tags --long --dirty="\\*" 2>/dev/null)
CFLAGS += -DGIT_DESCRIBE=$(GIT_DESCRIBE)

# eynsai
RAW_ENABLE = yes
USERSPACE_DIR = $(TOP_DIR)/../qmk_firmware/users/eynsai
SRC += $(USERSPACE_DIR)/mouse_passthrough_sender.c
VPATH += $(USERSPACE_DIR)
# LTO_ENABLE = yes  # won't build with LTO
OPT = 3  # -O3 optimization