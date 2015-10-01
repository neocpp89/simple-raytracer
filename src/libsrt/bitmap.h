#ifndef SRT_BITMAP_H_
#define SRT_BITMAP_H_
#include <stdint.h>

namespace simple_raytracer {

/*
    Bitmap header information and structure defintion.
    These structures are aligned correctly in memory and can be written
    out directly.
*/
#pragma pack(push, 1)
typedef struct bfheader_s {
    uint16_t type;        // must be set to 19778
    uint32_t size;        // size in bytes
    uint16_t reserved1;   // must be 0
    uint16_t reserved2;   // must be 0
    uint32_t offset;      // offset to where bitmap starts
} bfheader_t;

typedef struct biheader_s {
    uint32_t size;            // size of structure in bytes
    uint32_t width;           // width of image
    uint32_t height;          // height of image
    uint16_t planes;          // planes on device
    uint16_t bpp;             // bits per pixel
    uint32_t compression;     // compression type (0 = no compression)
    uint32_t datasize;        // inflated data size (if compressed)
    uint32_t xppm;            // horizontal pixels per meter
    uint32_t yppm;            // vertical pixels per meter
    uint32_t clrused;         // number of colors used in bitmap
    uint32_t clrimportant;    // number of imporant colors in bitmap (0 = all important)
} biheader_t;

typedef struct brgbquad_s {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t reserved;   // must be 0
} brgbquad_t;

typedef struct b24bitpixel_s {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} b24bitpixel_t;
#pragma pack(pop)

} // namespace simple_raytracer

#endif //SRT_BITMAP_H_

