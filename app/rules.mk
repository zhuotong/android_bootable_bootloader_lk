LOCAL_DIR := $(GET_LOCAL_DIR)

MODULES += \
	lib/openssl \

ifeq ($(ENABLE_REVOLK),1)
MODULES += \
	lib/revolk
endif

OBJS += \
	$(LOCAL_DIR)/app.o

