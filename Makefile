# use pkg-config for getting CFLAGS and LDLIBS
FFMPEG_LIBS=    libavdevice                        \
                libavformat                        \
                libavfilter                        \
                libavcodec                         \
                libswresample                      \
                libswscale                         \
                libavutil                          \

NVIDIA_LIBS=    nppi-7.5 nppc-7.5

PKG_CONFIG_DIR= _build/lib/pkgconfig:/usr/local/cuda-7.5/pkgconfig 
CFLAGS := -Wall -O2 -g -ggdb 
CFLAGS += $(shell export PKG_CONFIG_PATH=$(PKG_CONFIG_DIR); pkg-config --cflags $(FFMPEG_LIBS))
CFLAGS += $(shell export PKG_CONFIG_PATH=$(PKG_CONFIG_DIR); pkg-config --cflags $(NVIDIA_LIBS)) 
CFLAGS += $(shell freetype-config --cflags)
CFLAGS += $(shell sdl2-config --cflags) 

LDLIBS := $(shell export PKG_CONFIG_PATH=$(PKG_CONFIG_DIR); pkg-config --libs $(FFMPEG_LIBS)) 
LDLIBS += $(shell export PKG_CONFIG_PATH=$(PKG_CONFIG_DIR); pkg-config --libs $(NVIDIA_LIBS)) 
LDLIBS += $(shell freetype-config --libs) 
LDLIBS += $(shell sdl2-config --libs)

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
	$(RM) frame*.ppm frame*.pgm test.h264 test.mp2 test.sw test.mpg

clean: clean-test
	$(RM) $(EXAMPLES) $(OBJS)

run-tutorial01:
	export LD_LIBRARY_PATH=_build/lib:$(LD_LIBRARY_PATH)
	./tutorial01 test_data/centaur_1.mpg
