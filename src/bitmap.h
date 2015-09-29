#ifndef __BMP_H__
#define __BMP_H__

//bmpinfo -- prints bitmap header information.
//Created By Sachith Dunatunga at 20:33:54 on 17.12.07.
//This code is GPL'ed. See the files in ./gpl/ for details.

//possible defines

//---Includes-----//
#include <stdint.h>
//----------------//

//---Defines------//

//----------------//

//----------------------------------------------------------------------------//
#pragma pack(push, 1)
typedef struct bfheader_s {
	uint16_t bftype;	//must be set to 19778
	uint32_t bfsize;	//size in bytes
	uint16_t bfreserved1;	//must be 0
	uint16_t bfreserved2;	//must be 0
	uint32_t bfoffset;	//offset to where bitmap starts
} bfheader_t;

typedef struct biheader_s {
	uint32_t bisize;	//size of structure in bytes
	uint32_t biwidth;	//width of image
	uint32_t biheight;	//height of image
	uint16_t biplanes;	//planes on device
	uint16_t bibpp;	//bits per pixel
	uint32_t bicompression;	//compression type (0 = no compression)
	uint32_t bidatasize;	//inflated data size (if compressed)
	uint32_t bixppm;	//horizontal pixels per meter
	uint32_t biyppm;	//vertical pixels per meter
	uint32_t biclrused;	//number of colors used in bitmap
	uint32_t biclrimportant;	//number of imporant colors in bitmap (0 = all important)
} biheader_t;

typedef struct brgbquad_s {
	uint8_t blue;	//blue component
	uint8_t green;	//green component
	uint8_t red;	//red component
	uint8_t reserved;	//must be 0
} brgbquad_t;

typedef struct b24bitpixel_s {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
} b24bitpixel_t;
#pragma pack(pop)
//----------------------------------------------------------------------------//

#endif

