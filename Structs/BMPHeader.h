#ifndef BMPHEADER_H
#define BMPHEADER_H

#pragma pack(push, 1)
struct BMPHeader {
    char signature[2];
    int fileSize;
    int reserved;
    int dataOffset;
    int headerSize;
    int width;
    int height;
    short planes;
    short bitsPerPixel;
    int compression;
    int dataSize;
    int horizontalResolution;
    int verticalResolution;
    int colors;
    int importantColors;
};

#endif