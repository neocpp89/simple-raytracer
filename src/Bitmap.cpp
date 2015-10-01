#include <fstream>
#include <vector>
#include <string>

#include <cstring>
#include <cmath>

#include "Color.hpp"
#include "Bitmap.hpp"
#include "bitmap.h"


namespace simple_raytracer {

Bitmap::Bitmap(int width, int height) : width_(width), height_(height), data_(width * height)
{
    bf_.type = 19778;   // magic header
    bf_.size = 3 * width * height + sizeof(bfheader_t) + sizeof(biheader_t); // 24bpp
    bf_.reserved1 = 0;
    bf_.reserved2 = 0;
    bf_.offset = sizeof(bfheader_t) + sizeof(biheader_t);

    bi_.size = sizeof(biheader_t);
    bi_.width = width;
    bi_.height = height;
    bi_.planes = 1;
    bi_.bpp = 24;
    bi_.compression = 0;
    bi_.datasize = 0;
    bi_.xppm = 3780;
    bi_.yppm = 3780;
    bi_.clrused = 0;
    bi_.clrimportant = 0;

    datasize_ = bi_.width * bi_.height * sizeof(b24bitpixel_t);
    filesize_ = 4 * static_cast<int>(ceil((24 * width) / 32.0)) * height + bf_.offset;  // 24bpp

    return;
}

void Bitmap::SetPixelImageCoordinates(int i, int j, const RGBColor &c)
{
    if (j >= width_ || i >= height_ || i < 0 || j < 0) {
        return;
    }
    const int image_coordinates_i = height_ - i - 1;
    data_[image_coordinates_i * width_ + j].red = c.r();
    data_[image_coordinates_i * width_ + j].green = c.g();
    data_[image_coordinates_i * width_ + j].blue = c.b();
    return;
}

void Bitmap::SetPixel(int x, int y, const RGBColor &c)
{
    if (x >= width_ || y >= height_ || x < 0 || y < 0) {
        return;
    }
    data_[y * bi_.width + x].red = c.r();
    data_[y * bi_.width + x].green = c.g();
    data_[y * bi_.width + x].blue = c.b();
    return;
}

RGBColor Bitmap::GetPixelImageCoordinates(int i, int j) const
{
    if (j >= width_ || i >= height_ || i < 0 || j < 0) {
        return RGBColor(0, 0, 0);
    }
    /*
        Bitmaps are actually weird and store image data
        in regular cartesian coordinates...

        Apparently this can be changed by setting the height
        to be negative, but this is easier for me.
    */
    const int image_coordinates_i = height_ - i - 1;
    const int r = data_[image_coordinates_i * width_ + j].red;
    const int g = data_[image_coordinates_i * width_ + j].green;
    const int b = data_[image_coordinates_i * width_ + j].blue;
    RGBColor rgb(r, g, b);
    return rgb;
}

RGBColor Bitmap::GetPixel(int x, int y) const
{
    if (x >= width_ || y >= height_ || x < 0 || y < 0) {
        return RGBColor(0, 0, 0);
    }
    const int r = data_[y * bi_.width + x].red;
    const int g = data_[y * bi_.width + x].green;
    const int b = data_[y * bi_.width + x].blue;
    RGBColor rgb(r, g, b);
    return rgb;
}

/*
    This function is actually somewhat wasteful since it
    allocates a large buffer for the bitmap and then writes that
    out a byte at a time. This can definintely be done better.
*/
void Bitmap::WriteFile(const std::string &filename) const
{
    std::vector<uint8_t> rawdata(filesize_);
    uint8_t *raw = &rawdata[0];

    int len = 0;
    memcpy(raw, &bf_, sizeof(bfheader_t));
    len += sizeof(bfheader_t);
    memcpy(raw + len, &bi_, sizeof(biheader_t));
    len += sizeof(biheader_t);

    for (int y = 0; y < height_; y++) {
        int c = 0;
        for (int x = 0; x < width_; x++) {
            memcpy(raw + len, &data_[y * bi_.width + x], sizeof(b24bitpixel_t));
            c += sizeof(b24bitpixel_t);
            len += sizeof(b24bitpixel_t);
        }
        if (c % 4 != 0) {
            memset(raw + len, 0xFF, 4 - (c % 4));
            len += (4 - (c % 4));
        }
    }

    // Actually write the huge buffer we made.
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    for (int i = 0; i < filesize_; i++) {
        file << raw[i];
    }
    file.close();
    return;
}

} // namesapce simple_raytracer
