REVOLK_LOCAL_PATH := $(GET_LOCAL_DIR)

MODULES += \
	lib/ext4

REVOLK_SRCS = \
	revolk.c

REVOLK_OBJS = $(REVOLK_SRCS:%.c=%.o)

INCLUDES += \
	-I$(REVOLK_LOCAL_PATH)/src \
	-I$(REVOLK_LOCAL_PATH)

OBJS += $(addprefix $(REVOLK_LOCAL_PATH)/, $(REVOLK_OBJS))


