FFmpeg-tutorial-samples
=======================

Original code came from updated version of source code from http://dranger.com/ffmpeg/ffmpeg.html
However, I could not get it to compile or work on my version of ffmpeg. Some changes were required. 

Matching up the proper version of ffmpeg is not easy.  Currently I am compiliing against ffmpeg-3.3. The build tree looks like the following:

```
.
├── _archives
│   ├── ffmpeg-3.3
│   │   ├── ~
│   │   ├── arch.mak
│   │   ├── Changelog
│   │   ├── cmdutils.c
│   │   ├── cmdutils_common_opts.h
│   │   ├── cmdutils.d
│   │   ├── cmdutils.h
│   │   ├── cmdutils.o
│   │   ├── cmdutils_opencl.c
│   │   ├── common.mak
│   │   ├── compat
│   │   ├── config.asm
│   │   ├── config.fate
│   │   ├── config.h
│   │   ├── config.log
│   │   ├── config.mak
│   │   ├── configure
│   │   ├── CONTRIBUTING.md
│   │   ├── COPYING.GPLv2
│   │   ├── COPYING.GPLv3
│   │   ├── COPYING.LGPLv2.1
│   │   ├── COPYING.LGPLv3
│   │   ├── CREDITS
│   │   ├── cscope.out
│   │   ├── doc
│   │   ├── erl.mak
│   │   ├── ffmpeg
│   │   ├── ffmpeg.c
│   │   ├── ffmpeg_cuvid.c
│   │   ├── ffmpeg_cuvid.d
│   │   ├── ffmpeg_cuvid.o
│   │   ├── ffmpeg.d
│   │   ├── ffmpeg_dxva2.c
│   │   ├── ffmpeg_filter.c
│   │   ├── ffmpeg_filter.d
│   │   ├── ffmpeg_filter.o
│   │   ├── ffmpeg_g
│   │   ├── ffmpeg.h
│   │   ├── ffmpeg.o
│   │   ├── ffmpeg_opt.c
│   │   ├── ffmpeg_opt.d
│   │   ├── ffmpeg_opt.o
│   │   ├── ffmpeg_qsv.c
│   │   ├── ffmpeg_vaapi.c
│   │   ├── ffmpeg_vdpau.c
│   │   ├── ffmpeg_videotoolbox.c
│   │   ├── ffplay
│   │   ├── ffplay.c
│   │   ├── ffplay.d
│   │   ├── ffplay_erl
│   │   ├── ffplay_erl.c
│   │   ├── ffplay_erl.d
│   │   ├── ffplay_erl_g
│   │   ├── ffplay_erl.o
│   │   ├── ffplay_g
│   │   ├── ffplay.o
│   │   ├── ffprobe
│   │   ├── ffprobe.c
│   │   ├── ffprobe.d
│   │   ├── ffprobe_g
│   │   ├── ffprobe.o
│   │   ├── ffserver
│   │   ├── ffserver.c
│   │   ├── ffserver_config.c
│   │   ├── ffserver_config.d
│   │   ├── ffserver_config.h
│   │   ├── ffserver_config.o
│   │   ├── ffserver.d
│   │   ├── ffserver_g
│   │   ├── ffserver.o
│   │   ├── INSTALL.md
│   │   ├── libavcodec
│   │   ├── libavdevice
│   │   ├── libavfilter
│   │   ├── libavformat
│   │   ├── libavresample
│   │   ├── libavutil
│   │   ├── libpostproc
│   │   ├── library.mak
│   │   ├── libswresample
│   │   ├── libswscale
│   │   ├── LICENSE.md
│   │   ├── MAINTAINERS
│   │   ├── Makefile
│   │   ├── presets
│   │   ├── README.md
│   │   ├── RELEASE
│   │   ├── RELEASE_NOTES
│   │   ├── tests
│   │   ├── tools
│   │   ├── VERSION
│   │   └── version.sh
│   └── ffmpeg-3.3.tar.bz2
├── _build
│   ├─ bin
│   │   ├── ffmpeg
│   │   ├── ffplay
│   │   ├── ffplay_erl
│   │   ├── ffprobe
│   │   └── ffserver
│   ├── include
│   │   ├── libavcodec
│   │   ├── libavdevice
│   │   ├── libavfilter
│   │   ├── libavformat
│   │   ├── libavutil
│   │   ├── libswresample
│   │   └── libswscale
│   ├── lib
│   │   ├── libavcodec.a
│   │   ├── libavdevice.a
│   │   ├── libavfilter.a
│   │   ├── libavformat.a
│   │   ├── libavutil.a
│   │   ├── libswresample.a
│   │   ├── libswscale.a
│   │   └── pkgconfig
│   └── share
│       ├── ffmpeg
│       └── man
├── Makefile
├── README.md
├── test_data
│   └── centaur_1.mpg
├── tutorial01.c
├── tutorial02.c
├── tutorial03.c
├── tutorial04.c
├── tutorial05.c
├── tutorial06.c
└── tutorial07.c


```

As you can see in the Makefile, we are using pkg-config to get the compile and linking set up properly.

Here are the parameters of my build:

```

ffplay version 3.3 Copyright (c) 2003-2017 the FFmpeg developers
  built with gcc 4.8 (Ubuntu 4.8.4-2ubuntu1~14.04.3)
  configuration: --prefix=/home/ychakiris/myprojects/ffmpeg-tutorial/_build
  libavutil      55. 58.100 / 55. 58.100
  libavcodec     57. 89.100 / 57. 89.100
  libavformat    57. 71.100 / 57. 71.100
  libavdevice    57.  6.100 / 57.  6.100
  libavfilter     6. 82.100 /  6. 82.100
  libswscale      4.  6.100 /  4.  6.100
  libswresample   2.  7.100 /  2.  7.100
Simple media player
usage: ffplay [options] input_file

```

I also have a Nvida K2000 card with cuda installed. 


Goals for this Project
==========================

My main goals are:
1. Get all the tutorial code to compile and work properly with a predicatable version of ffmpeg that is installed as shown above
2. Demonstrate that the packets can be read on one machine, sent over the wire to a second machine, decoded and displayed on the second machine.
3. In #2 try and preserve (as much as possible) the great ability of ffplay to go forwards and backwards ("trick play") at high speed with low latency.

The project may have to be continued using JavaCPP (see https://github.com/bytedeco/javacpp and the ffmpeg presets) since the messaging solutions may be better in Java, as far as latency and speed are concerned (see the project Aeron https://github.com/real-logic/aeron, and the videos on the design of that project).
