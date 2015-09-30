#ifndef SRT_BITMAP_HPP_
#define SRT_BITMAP_HPP_
#include <vector>
#include "bitmap.h"
#include "Color.hpp"

namespace SimpleRaytracer {

class Bitmap
{	public:
		Bitmap(int x, int y);

		const int width() const { return width_; }
		const int height() const { return height_; }

		void set_pixel(int x, int y, const RGBColor &c);
		RGBColor get_pixel(int x, int y) const;

        /*
            Be careful with this, it actually will fail if we don't run this on a
            little-endian machine, since BMP format uses little endian.

            The only way you'll know is that the bitmap won't have the magic header
            'BM' at the beginning of the file.

            I haven't thought of a good way to fix this yet.
        */
		void write_file(const char *file) const;

	private:
        const int width_;
        const int height_;

		std::vector<b24bitpixel_t> data_;

		bfheader_t bf_;
		biheader_t bi_;
		int datasize_;
		int filesize_;
};

} // namespace SimpleRaytracer

#endif //SRT_BITMAP_HPP_
