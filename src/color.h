#ifndef __COLOR_H__
#define __COLOR_H__

//color header file for raytracer.
//Created By Sachith Dunatunga at 20:33:54 on 17.12.07.
//This code is GPL'ed. See the files in ./gpl/ for details.

//possible defines

//---Includes-----//
//----------------//

//---Defines------//
//----------------//

//----------------------------------------------------------------------------//
typedef struct rgb_s {
	int red;	//0-255
	int green;	//0-255
	int blue;	//0-255
} rgb_t;

typedef struct hsv_s {
	int hue;	//0-360
	int saturation;	//0-100
	int value;	//0-255
} hsv_t;
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//

#endif

