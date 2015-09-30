#ifndef SRT_BITMAP_HPP_
#define SRT_BITMAP_HPP_
#include <vector>
#include "bitmap.h"
#include "color.hpp"

namespace SimpleRaytracer {

class Bitmap
{	public:
		Bitmap(int x, int y);

		void set_pixel(int x, int y, color *c);
		color *get_pixel(int x, int y) const;
		void write_file(const char *file) const;
		const int get_width() const;
		const int get_height() const;

	private:
        int width_;
        int height_;

		std::vector<b24bitpixel_t> data_;

		bfheader_t bf;
		biheader_t bi;
		int datasize;
		int filesize;
};

} // namespace SimpleRaytracer

#endif //SRT_BITMAP_HPP_
