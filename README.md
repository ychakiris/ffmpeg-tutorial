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
