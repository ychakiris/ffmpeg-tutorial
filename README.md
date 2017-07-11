FFmpeg-tutorial-samples
=======================

Original code came from updated version of source code from http://dranger.com/ffmpeg/ffmpeg.html
However, I could not get it to compile or work on my version of ffmpeg. Some changes were required. 

Here is the version of ffmpeg I am using and the compiler flags used to build it.
I replaced my true home directory with "my-home-directory."


```

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

```

I am gradually changing it so all the lessons can compile and work with this version of ffmpeg. There are still a number of compiler warnings about the use of depreciated functions. The Makefile is still a bit primitive. You will have to change it by hand to compiler each lesson. I believe I have fixed only lessons 1-3. Lesson 1 works when used on an mpg video file. 

To get things to compile, using the present Makefile, you will also have to change the PKG_CONFIG_PATH, so that pkg-config will be able to find the *.pc files that come with the ffmpeg build. They are found in the lib subdirectory. First check it by:

```
env | grep PKG_CONFIG_PATH

```
If a path to /home/my-home-directory/ffmpeg_build/lib/pkgconfig does not appear then you need to add it as follows:

```
export PKG_CONFIG_PATH=/home/my-home-directory/ffmpeg_build/lib/pkgconfig:$PKG_CONFIG_PATH

```

Now the Makefile should work provided you installed everything as above and built the right version of ffmpeg. I decided to do things this way since ffmpeg is a fast moving project and I have on my system several versions of it. This particular version uses SDL1.2. Several versions latter from the above one, ffmpeg switched over to SDL2. 
