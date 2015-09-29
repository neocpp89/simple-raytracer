#include "color.hpp"
#include "bitmap.hpp"
#include "bitmap.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

bitmap::bitmap(int x, int y)
{
	data = new b24bitpixel_t[x * y];

	bf.bftype = 19778;
	bf.bfsize = 3 * x * y + sizeof(bfheader_t) + sizeof(biheader_t); //assume 24bpp
	bf.bfreserved1 = 0;
	bf.bfreserved2 = 0;
	bf.bfoffset = sizeof(bfheader_t) + sizeof(biheader_t);

	bi.bisize = sizeof(biheader_t);
	bi.biwidth = x;
	bi.biheight = y;
	bi.biplanes = 1;
	bi.bibpp = 24;
	bi.bicompression = 0;
	bi.bidatasize = 0;
	bi.bixppm = 3780;
	bi.biyppm = 3780;
	bi.biclrused = 0;
	bi.biclrimportant = 0;

	datasize = bi.biwidth * bi.biheight * sizeof(b24bitpixel_t);
	filesize = 4 * (int)(ceil((24 * x) / 32.0)) * y + 54;	//24bpp

	return;
}

bitmap::~bitmap()
{
	delete[] data;
	return;
}

void bitmap::setpixel(int x, int y, color *c)
{
	if (x > bi.biwidth || y > bi.biheight || x < 0 || y < 0) {
		return;
	}
	rgb_t *r = c->getrgb();
	data[(bi.biheight - y - 1) * bi.biwidth + x].red = r->red;
	data[(bi.biheight - y - 1) * bi.biwidth + x].green = r->green;
	data[(bi.biheight - y - 1) * bi.biwidth + x].blue = r->blue;
	return;
}

color *bitmap::getpixel(int x, int y)
{
	color *r = new color;
	if (x > bi.biwidth || y > bi.biheight || x < 0 || y < 0) {
		return r;
	}
	r->setrgb(	data[(bi.biheight - y - 1) * bi.biwidth + x].red,
				data[(bi.biheight - y - 1) * bi.biwidth + x].green,
				data[(bi.biheight - y - 1) * bi.biwidth + x].blue);
	return r;
}

void bitmap::writefile(const char *filename)
{
	ofstream file;
	int8_t *raw;
	int len, i;
	int x, y, c;

	len = 0;
	raw = new int8_t[filesize + 1];

	memcpy(raw, &bf, sizeof(bfheader_t));
	len += sizeof(bfheader_t);
	memcpy((void *)(raw + len), &bi, sizeof(biheader_t));
	len += sizeof(biheader_t);

	for (y = 0; y < bi.biheight; y++) {
		c = 0;
		for (x = 0; x < bi.biwidth; x++) {
			memcpy((void *)(raw + len), &data[y * bi.biwidth + x], sizeof(b24bitpixel_t));
			c += sizeof(b24bitpixel_t);
			len += sizeof(b24bitpixel_t);
		}
		if (c % 4 != 0) {
			memset((void *)(raw + len), 0xFF, 4 - (c % 4));
			len += (4 - (c % 4));
		}
	}

	raw[len] = '\0';

	file.open(filename, ios::out | ios::binary);

	for (i = 0; i < filesize; i++) {
		file << raw[i];
	}

	delete[] raw;

	file.close();
	return;
}

int bitmap::getwidth()
{	return bi.biwidth;
}

int bitmap::getheight()
{	return bi.biheight;
}
