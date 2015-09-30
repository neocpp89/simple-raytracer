#ifndef SRT_BITMAP_HPP_
#define SRT_BITMAP_HPP_
#include <vector>
#include "bitmap.h"
#include "color.hpp"

namespace SimpleRaytracer {

class Bitmap
{	public:
		Bitmap(int x, int y);
		~Bitmap();

		void setpixel(int x, int y, color *c);
		color *getpixel(int x, int y) const;
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

} // namespace SimpleRaytracer

#endif //SRT_BITMAP_HPP_
