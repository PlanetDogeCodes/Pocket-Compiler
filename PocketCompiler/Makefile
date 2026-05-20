.SUFFIXES:

ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=/opt/devkitpro")
endif

TLS_BACKEND ?= mbedtls
TOPDIR ?= $(CURDIR)
include $(DEVKITPRO)/devkitARM/3ds_rules

TARGET := PocketCompiler
BUILD := build
SOURCES := source
INCLUDES := include

APP_TITLE := Pocket Compiler
APP_DESCRIPTION := HTML CSS JavaScript compiler/browser playground
APP_AUTHOR := Galaxy AI Scaffold

ARCH := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft
CFLAGS := -g -Wall -O2 -mword-relocations -ffunction-sections $(ARCH)
CFLAGS += $(INCLUDE) -D__3DS__ -DHAVE_ZLIB=1
ASFLAGS := -g $(ARCH)
LDFLAGS = -specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

LIBS := -lcitro2d -lcitro3d -lctru -lz -lm

ifeq ($(TLS_BACKEND),mbedtls)
CFLAGS += -DUSE_MBEDTLS=1
LIBS := -lmbedtls -lmbedx509 -lmbedcrypto $(LIBS)
else ifeq ($(TLS_BACKEND),wolfssl)
CFLAGS += -DUSE_WOLFSSL=1
LIBS := -lwolfssl $(LIBS)
else
CFLAGS += -DUSE_NO_TLS=1
endif

ifneq ($(BUILD),$(notdir $(CURDIR)))
export OUTPUT := $(CURDIR)/$(TARGET)
export TOPDIR := $(CURDIR)
export VPATH := $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
export DEPSDIR := $(CURDIR)/$(BUILD)
CFILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
export OFILES := $(CFILES:.c=.o)
export INCLUDE := $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) -I$(CURDIR)/$(BUILD)
export LIBPATHS :=

.PHONY: all clean info
all: info $(BUILD)
info:
	@echo "Building $(TARGET) with TLS_BACKEND=$(TLS_BACKEND)"
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile
clean:
	@rm -fr $(BUILD) $(TARGET).3dsx $(TARGET).smdh $(TARGET).elf $(TARGET).map
else
DEPENDS := $(OFILES:.o=.d)
$(OUTPUT).3dsx: $(OUTPUT).elf
$(OUTPUT).elf: $(OFILES)
%.o: %.c
	@$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d $(CFLAGS) -c $< -o $@
-include $(DEPENDS)
endif
