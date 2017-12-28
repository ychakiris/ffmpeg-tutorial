// tutorial01.c
// Code based on a tutorial by Martin Bohme (boehme@inb.uni-luebeckREMOVETHIS.de)
// Tested on Gentoo, CVS version 5/01/07 compiled with GCC 4.1.1

// A small sample program that shows how to use libavformat and libavcodec to
// read video from a file.
//
// Use
//
// gcc -o tutorial01 tutorial01.c -lavformat -lavcodec -lz
//
// to build (assuming libavformat and libavcodec are correctly installed
// your system).
//
// Run using
//
// tutorial01 myvideofile.mpg
//
// to write the first five frames from "myvideofile.mpg" to disk in PPM
// format.

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
#include <stdio.h>


void hexDump (char *desc, void *addr, int len) {
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    // Output description if given.
    if (desc != NULL)
        printf ("%s:\n", desc);

    if (len == 0) {
        printf("  ZERO LENGTH\n");
        return;
    }
    if (len < 0) {
        printf("  NEGATIVE LENGTH: %i\n",len);
        return;
    }

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf ("  %s\n", buff);

            // Output the offset.
            printf ("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf (" %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf ("   ");
        i++;
    }

    // And print the final ASCII bit.
    printf ("  %s\n", buff);
}




void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame) {
    FILE *pFile;
    char szFilename[32];
    int  y;

    // Open file
    sprintf(szFilename, "frame%d.ppm", iFrame);
    pFile=fopen(szFilename, "wb");
    if(pFile==NULL)
        return;

    // Write header
    fprintf(pFile, "P6\n%d %d\n255\n", width, height);

    // Write pixel data
    for(y=0; y<height; y++)
        fwrite(pFrame->data[0]+y*pFrame->linesize[0], 1, width*3, pFile);

    // Close file
    fclose(pFile);
}

#pragma mark - Main function
int main(int argc, char *argv[]) {
    AVFormatContext    *pFormatCtx;
    int                i, videoStreamIdx;
    AVCodecContext     *pCodecCtx;
    AVCodecParameters  *pCodecPar;
    AVCodec            *pCodec;
    AVFrame            *pFrame;
    AVFrame            *pFrameRGB;
    AVPacket           packet;
    int                frameFinished;
    int                numBytes;
    uint8_t            *buffer;
    static struct SwsContext *img_convert_ctx;

    if(argc < 2) {
        printf("Please provide a movie file\n");
        return -1;
    }
    // Register all formats and codecs
    av_register_all();
    pFormatCtx = avformat_alloc_context();
    if (!pFormatCtx) {
        return -1;
    }

    /// Open video file
    //if(av_open_input_file(&pFormatCtx, argv[1], NULL, 0, NULL)!=0) // Deprecated
    if(avformat_open_input(&pFormatCtx, argv[1], NULL, NULL) != 0)
        return -1; // Couldn't open file

    /// Retrieve stream information
    //if(av_find_stream_info(pFormatCtx)<0) // Deprecated
    if(avformat_find_stream_info(pFormatCtx, NULL) < 0)
        return -1; // Couldn't find stream information


    /// Dump information about file onto standard error
    av_dump_format(pFormatCtx, 0, argv[1], 0);


    /// Find the first video stream
    videoStreamIdx=-1;
    for(i=0; i<pFormatCtx->nb_streams; i++)
        if(pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) { //CODEC_TYPE_VIDEO
            videoStreamIdx=i;
            break;
        }
    if(videoStreamIdx==-1)
        return -1; // Didn't find a video stream


    /// Get a pointer to the codec context for the video stream
    // pCodecCtx = pFormatCtx->streams[videoStreamIdx]->codec; //deprecated
    pCodecPar = pFormatCtx->streams[videoStreamIdx]->codecpar;

    /// Find the decoder for the video stream
    //  pCodec = avcodec_find_decoder( pCodecCtx->codec_id); // deprecated
    pCodec = avcodec_find_decoder(pCodecPar->codec_id);
    if(pCodec==NULL) {
        fprintf(stderr, "Unsupported codec!\n");
        return -1; // Codec not found
    }

    pCodecCtx = avcodec_alloc_context3(pCodec);
    if (!pCodecCtx) {
      fprintf(stderr, "Unable to allocate a AVCodecContext");
      return -1; 
    }

    if (avcodec_parameters_to_context(pCodecCtx, pCodecPar) < 0) {
      fprintf(stderr, "Unable to copy parameters from AVCodecParameters to AVCodecContext");
      return -1;
    }

    /// Open codec
    //if( avcodec_open(pCodecCtx, pCodec) < 0 ) -- Deprecated
    if( avcodec_open2(pCodecCtx, pCodec, NULL) < 0 )
        return -1; // Could not open codec

    /// Allocate video frame
    pFrame = av_frame_alloc();


    /// Allocate an AVFrame structure
    pFrameRGB = av_frame_alloc();
    if(pFrameRGB==NULL)
        return -1;


    /// Determine required buffer size and allocate buffer  // deprecated
    // numBytes = avpicture_get_size(AV_PIX_FMT_RGB24,
    //                              pCodecCtx->width,
    //                              pCodecCtx->height);

    // Determine required buffer size and allocate buffer
    // the deprecated function simply calls this one with a 1

    numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24,
                                        pCodecCtx->width,
                                        pCodecCtx->height, 1);

    buffer = (uint8_t *) av_malloc(numBytes*sizeof(uint8_t));


    /// Assign appropriate parts of buffer to image planes in pFrameRGB
    // Note that pFrameRGB is an AVFrame, but AVFrame is a superset
    // of AVPicture
    avpicture_fill((AVPicture *)pFrameRGB, buffer, AV_PIX_FMT_RGB24,
                   pCodecCtx->width, pCodecCtx->height);


    int w = pCodecCtx->width;
    int h = pCodecCtx->height;
    img_convert_ctx = sws_getContext(w, h, pCodecCtx->pix_fmt,
                                     w, h, AV_PIX_FMT_RGB24,
                                     SWS_BICUBIC, NULL, NULL, NULL);
    // Read frames and save first five frames to disk
    i=0;
    while((av_read_frame(pFormatCtx, &packet)>=0) && (i<5)) {
        // Is this a packet from the video stream?
        if(packet.stream_index==videoStreamIdx) {

            /// Decode video frame
            //avcodec_decode_video(pCodecCtx, pFrame, &frameFinished,packet.data, packet.size);
            avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

            // Did we get a video frame?
            if(frameFinished) {
                i++;
                sws_scale(img_convert_ctx, (const uint8_t * const *)pFrame->data,
                          pFrame->linesize, 0, pCodecCtx->height,
                          pFrameRGB->data, pFrameRGB->linesize);
                SaveFrame(pFrameRGB, pCodecCtx->width, pCodecCtx->height, i);
            }
        }

        // Free the packet that was allocated by av_read_frame
        av_free_packet(&packet);
    }


    // Free the RGB image
    av_free(buffer);
    av_free(pFrameRGB);

    // Free the YUV frame
    av_free(pFrame);

    // Close the codec
    avcodec_close(pCodecCtx);

    // Close the video file
    avformat_close_input(&pFormatCtx);

//*/
    return 0;
}
