#ifndef SRT_BITMAP_HPP_
#define SRT_BITMAP_HPP_
#include <stdexcept>
#include <string>
#include <vector>

#include "bitmap.h"
#include "Color.hpp"

namespace simple_raytracer {

/*
    Class for managing simple 24-bit bitmaps.

    Allows you to set pixel data as well as write it to a file.
*/
class Bitmap
{
    public:
        Bitmap(int x, int y);

        int width() const { return width_; }
        int height() const { return height_; }

        /*
            Access bitmap data in cartesian coordinates x, y.
        */
        void SetPixel(int x, int y, const RGBColor &c);
        RGBColor GetPixel(int x, int y) const;

        /*
            Access bitmap data in image coordinates i,j
            increasing to the right and down from the top-left corner.

            These will throw if you give them bad coordinates.
        */
        void SetPixelImageCoordinates(int i, int j, const RGBColor &c);
        RGBColor GetPixelImageCoordinates(int i, int j) const;

        /*
           Be careful with this, it actually will fail if we don't run this on a
           little-endian machine, since BMP format uses little endian.

           The only way you'll know is that the bitmap won't have the magic header
           'BM' at the beginning of the file.

           I haven't thought of a good way to fix this yet.
         */
        void WriteFile(const std::string &file) const;

    private:
        const int width_;
        const int height_;

        std::vector<b24bitpixel_t> data_;

        bfheader_t bf_;
        biheader_t bi_;
        int datasize_;
        int filesize_;

        /*
            These are helper functions that throw a std::out_of_range exception
            if the coordinates are out of range, otherwise they do nothing.
        */
        void CheckImageCoordinates(int i, int j) const;
        void CheckCoordinates(int x, int y) const;
};

} // namespace simple_raytracer

#endif //SRT_BITMAP_HPP_
