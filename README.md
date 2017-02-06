FFmpeg-tutorial-samples
=======================

Original code came from updated version of source code from http://dranger.com/ffmpeg/ffmpeg.html
However, I could not get it to compile or work on my version of ffmpeg. Some changes were required. 

Here is the version of ffmpeg I am using and the compiler flags used to build it.
I replaced my true home directory with "my-home-directory." 

ffmpeg version N-78176-gb340bd8 Copyright (c) 2000-2016 the FFmpeg developers
  built with gcc 4.8 (Ubuntu 4.8.4-2ubuntu1~14.04)
  configuration: --prefix=/home/my-home-directory/ffmpeg_build --pkg-config-flags=--static --extra-cflags=-I/home/my-home-directory/ffmpeg_build/include --extra-ldflags=-L/home/my-home-directory/ffmpeg_build/lib --bindir=/home/my-home-directory/bin --enable-gpl --enable-libass --enable-libfdk-aac --enable-libfreetype --enable-libmp3lame --enable-libopus --enable-libtheora --enable-libvorbis --enable-libvpx --enable-libx264 --enable-libx265 --enable-nonfree
  libavutil      55. 16.100 / 55. 16.100
  libavcodec     57. 22.102 / 57. 22.102
  libavformat    57. 23.100 / 57. 23.100
  libavdevice    57.  0.100 / 57.  0.100
  libavfilter     6. 27.100 /  6. 27.100
  libswscale      4.  0.100 /  4.  0.100
  libswresample   2.  0.101 /  2.  0.101
  libpostproc    54.  0.100 / 54.  0.100 

I am gradually changing it so all the lessons compile and work with this version of ffmpeg. There are still a number of compiler warnings about the use of depreciated functions.
