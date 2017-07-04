# use pkg-config for getting CFLAGS and LDLIBS
FFMPEG_PKG_CONFIG= $(shell echo $(HOME)/ffmpeg_build/lib/pkgconfig):$(shell echo $(PKG_CONFIG_PATH))
FFMPEG_LIBS=    libavdevice                        \
                libavformat                        \
                libavfilter                        \
                libavcodec                         \
                libswresample                      \
                libswscale                         \
                libavutil                          \

CFLAGS += -Wall -O2 -g -ggdb
CFLAGS := $(shell export PKG_CONFIG_PATH=$(FFMPEG_PKG_CONFIG); pkg-config --cflags $(FFMPEG_LIBS)) $(CFLAGS)
CFLAGS := $(shell freetype-config --cflags) $(CFLAGS)
CFLAGS := $(shell sdl-config --cflags) $(CFLAGS)

LDLIBS := $(shell export PKG_CONFIG_PATH=$(FFMPEG_PKG_CONFIG); pkg-config --libs $(FFMPEG_LIBS)) $(LDLIBS)
LDLIBS := $(shell freetype-config --libs) $(LDLIBS)
LDLIBS := $(shell sdl-config --libs) $(LDLIBS)

EXAMPLES=        tutorial01                         \
#                tutorial02                         \
#                tutorial03                         \
#                tutorial04                         \
#                tutorial05                         \
#                tutorial06                         \
#                tutorial07

OBJS=$(addsuffix .o,$(EXAMPLES))

# the following examples make explicit use of the math library
decoding_encoding: LDLIBS += -lm
muxing:            LDLIBS += -lm

.phony: all clean-test clean

all: $(OBJS) $(EXAMPLES)

clean-test:
	$(RM) test*.pgm test.h264 test.mp2 test.sw test.mpg frame*.ppm

clean: clean-test
	$(RM) $(EXAMPLES) $(OBJS)
