#ifndef __BITMAP_HPP_
#define __BITMAP_HPP_

#include "bitmap.h"
#include "color.hpp"

class bitmap
{	public:
		bitmap(int x, int y);
		~bitmap();

		void setpixel(int x, int y, color *c);
		color *getpixel(int x, int y);
		void writefile(const char *file);
		int getwidth();
		int getheight();

	private:
		b24bitpixel_t *data;
		bfheader_t bf;
		biheader_t bi;
		int datasize;

		int filesize;
};

#endif
