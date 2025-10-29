TARGET          := libcgsl
SOURCES         := source

CFILES   := $(foreach dir,$(SOURCES), $(wildcard $(dir)/*.c))
CPPFILES := $(foreach dir,$(SOURCES), $(wildcard $(dir)/*.cpp))
OBJS     := $(CFILES:.c=.o) $(CPPFILES:.cpp=.o)

SAMPLES     := $(foreach dir,$(wildcard samples/*), $(dir).smp)
SAMPLES_CLR := $(foreach dir,$(wildcard samples/*), $(dir).smpc)

PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
CXX     = $(PREFIX)-g++
AR      = $(PREFIX)-gcc-ar
CFLAGS  = -g -Wl,-q -O3 -ffast-math -mtune=cortex-a9 -mfpu=neon -Wno-incompatible-pointer-types -Wno-stringop-overflow
ASFLAGS = $(CFLAGS)

CXXFLAGS  = $(CFLAGS) -fexceptions -std=gnu++11 -Wno-write-strings

ifeq ($(NO_DEBUG),1)
CFLAGS += -DSKIP_ERROR_HANDLING
endif

ifeq ($(DEBUG_PREPROCESSOR),1)
CFLAGS += -DDEBUG_PREPROCESSOR
endif

all: $(TARGET).a

$(TARGET).a: $(OBJS)
	$(AR) -rc $@ $^
	
clean:
	@rm -rf $(TARGET).a $(TARGET).elf $(OBJS)
	
install: $(TARGET).a
	@mkdir -p $(VITASDK)/$(PREFIX)/lib/
	cp $(TARGET).a $(VITASDK)/$(PREFIX)/lib/
	@mkdir -p $(VITASDK)/$(PREFIX)/include/
	cp source/cgsl.h $(VITASDK)/$(PREFIX)/include/
