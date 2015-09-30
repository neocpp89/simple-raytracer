#include "color.hpp"
#include "Bitmap.hpp"
#include "bitmap.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>

namespace SimpleRaytracer {

Bitmap::Bitmap(int x, int y)
{
	data = new b24bitpixel_t[x * y];

	bf.type = 19778;
	bf.size = 3 * x * y + sizeof(bfheader_t) + sizeof(biheader_t); //assume 24bpp
	bf.reserved1 = 0;
	bf.reserved2 = 0;
	bf.offset = sizeof(bfheader_t) + sizeof(biheader_t);

	bi.size = sizeof(biheader_t);
	bi.width = x;
	bi.height = y;
	bi.planes = 1;
	bi.bpp = 24;
	bi.compression = 0;
	bi.datasize = 0;
	bi.xppm = 3780;
	bi.yppm = 3780;
	bi.clrused = 0;
	bi.clrimportant = 0;

	datasize = bi.width * bi.height * sizeof(b24bitpixel_t);
	filesize = 4 * (int)(ceil((24 * x) / 32.0)) * y + 54;	//24bpp

	return;
}

Bitmap::~Bitmap()
{
	delete[] data;
	return;
}

void Bitmap::setpixel(int x, int y, color *c)
{
	if (x > bi.width || y > bi.height || x < 0 || y < 0) {
		return;
	}
	rgb_t *r = c->getrgb();
	data[(bi.height - y - 1) * bi.width + x].red = r->red;
	data[(bi.height - y - 1) * bi.width + x].green = r->green;
	data[(bi.height - y - 1) * bi.width + x].blue = r->blue;
	return;
}

color *Bitmap::getpixel(int x, int y) const
{
	color *r = new color;
	if (x > bi.width || y > bi.height || x < 0 || y < 0) {
		return r;
	}
	r->setrgb(	data[(bi.height - y - 1) * bi.width + x].red,
				data[(bi.height - y - 1) * bi.width + x].green,
				data[(bi.height - y - 1) * bi.width + x].blue);
	return r;
}

void Bitmap::writefile(const char *filename)
{
	std::ofstream file;
	int8_t *raw;
	int len, i;
	int x, y, c;

	len = 0;
	raw = new int8_t[filesize + 1];

	memcpy(raw, &bf, sizeof(bfheader_t));
	len += sizeof(bfheader_t);
	memcpy((void *)(raw + len), &bi, sizeof(biheader_t));
	len += sizeof(biheader_t);

	for (y = 0; y < bi.height; y++) {
		c = 0;
		for (x = 0; x < bi.width; x++) {
			memcpy((void *)(raw + len), &data[y * bi.width + x], sizeof(b24bitpixel_t));
			c += sizeof(b24bitpixel_t);
			len += sizeof(b24bitpixel_t);
		}
		if (c % 4 != 0) {
			memset((void *)(raw + len), 0xFF, 4 - (c % 4));
			len += (4 - (c % 4));
		}
	}

	raw[len] = '\0';

	file.open(filename, std::ios::out | std::ios::binary);

	for (i = 0; i < filesize; i++) {
		file << raw[i];
	}

	delete[] raw;

	file.close();
	return;
}

int Bitmap::getwidth()
{	return bi.width;
}

int Bitmap::getheight()
{	return bi.height;
}

} // namesapce SimpleRaytracer
