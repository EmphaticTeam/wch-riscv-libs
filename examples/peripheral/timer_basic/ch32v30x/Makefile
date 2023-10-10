TARGET = TimerBasic
BUILD_DIR = build
DEBUG = 1
OPTIMIZATION = -O0

PROJ_PATH = $(CURDIR)/..
WCH_LIBS_PATH = $(PROJ_PATH)/../../..
GCC_PATH = A:/Tools/riscv-none-embed-gcc
OPENOCD_PATH = A:/Tools/openocd_wch

SOURCE_FILES = \
$(WCH_LIBS_PATH)/components/ch32v30x/startup_ch32v30x.s \
$(WCH_LIBS_PATH)/components/ch32v30x/system_ch32v30x.c \
$(WCH_LIBS_PATH)/components/ch32v30x/core/core_riscv.c \
$(WCH_LIBS_PATH)/components/CxxFeaturies.cpp \
$(WCH_LIBS_PATH)/components/ch32v30x/hal/Gpio.cpp \
$(WCH_LIBS_PATH)/components/ch32v30x/hal/TimerBasic.cpp \
../main.cpp 

INCLUDE_PATHS = \
$(WCH_LIBS_PATH)/components \
$(WCH_LIBS_PATH)/components/ch32v30x \
$(WCH_LIBS_PATH)/components/ch32v30x/core \
$(WCH_LIBS_PATH)/components/ch32v30x/hal 

DEFINES = \

-include $(WCH_LIBS_PATH)/components/ch32v30x/Makefile.mcu
-include $(WCH_LIBS_PATH)/components/makefiles/Makefile.gcc.riscv

