#include "color.hpp"
#include "color.h"

namespace {

template <typename T>
T max_of_three(T a, T b, T c)
{
    if (a > b && a > c) {
        return a;
    } else if (b > a && b > c) {
        return b;
    } else /* (c > a && c > b) */ {
        return c;
    }
}

template <typename T>
T min_of_three(T a, T b, T c)
{
    if (a < b && a < c) {
        return a;
    } else if (b < a && b < c) {
        return b;
    } else /* (c < a && c < b) */ {
        return c;
    }
}

} // anonymous namespace

namespace SimpleRaytracer {

void RGBColor::clamp_values()
{
    if (r_ < 0) {
        r_ = 0;
    }
    if (r_ > 255) {
        r_ = 255;
    }
    if (g_ < 0) {
        g_ = 0;
    }
    if (g_ > 255) {
        g_ = 255;
    }
    if (b_ < 0) {
        b_ = 0;
    }
    if (b_ > 255) {
        b_ = 255;
    }
    return;
}

HSVColor RGBColor::toHSV() const
{
    const int max = max_of_three(r_, g_, b_);
    const int min = min_of_three(r_, g_, b_);
    const int delta = max - min;
    int h = max;

    double t = 0;
    if (max == min) {
        t = 0;
    } else if (h == r_) {
        t = (g_ - b_) / static_cast<double>(delta);
    } else if (h == g_) {
        t = (b_ - r_) / static_cast<double>(delta);
        t += 2;
    } else { //h == b
        t = (r_ - g_) / static_cast<double>(delta);
        t += 4;
    }
    t *= 60.0;

    if (t < 0) {
        t += 360;
    }

    h = static_cast<int>(t);
    int s = static_cast<int>(100.0 * (static_cast<double>(delta) / max));
    int v = max;

    HSVColor hsv(h, s, v);
    hsv.clamp_values();
    return hsv;
}

void HSVColor::clamp_values()
{
    while (h_ < 0) {
        h_ += 360;
    }
    while (h_ > 360) {
        h_ -= 360;
    }
    if (s_ < 0) {
        s_ = 0;
    }
    if (s_ > 100) {
        s_ = 100;
    }
    if (v_ < 0) {
        v_ = 0;
    }
    if (v_ > 255) {
        v_ = 255;
    }
}

RGBColor HSVColor::toRGB() const
{
    int r = 0;
    int g = 0;
    int b = 0;

    if (s_ == 0 || v_ == 0) {
        //a gray color or black if v is 0
        r = v_;
        g = v_;
        b = v_;
    } else {
        // Normalized saturation and value
        double ns = s_ / 100.0;
        double nv = v_ / 255.0;

        int i = ((h_) / 60) % 6;
        double f = (((h_) / 60.0) - i);
        double p = ((nv) * (1 - ns));
        double q = ((nv) * (1 - (f * ns)));
        double t = ((nv) * (1 - ((1 - f) * ns)));

        nv *= 255.0;
        t *= 255.0;
        q *= 255.0;
        p *= 255.0;

        /*
            Somewhat ugly, but this is how HSV goes to RGB.
        */
        switch (i) {
            case 0: {
                r = (int)nv;
                g = (int)t;
                b = (int)p;
            } break;
            case 1: {
                r = (int)q;
                g = (int)nv;
                b = (int)p;
            } break;
            case 2: {
                r = (int)p;
                g = (int)nv;
                b = (int)t;
            } break;
            case 3: {
                r = (int)p;
                g = (int)q;
                b = (int)nv;
            } break;
            case 4: {
                r = (int)t;
                g = (int)p;
                b = (int)nv;
            } break;
            case 5: {
                r = (int)nv;
                g = (int)p;
                b = (int)q;
            } break;
        }
    }

    RGBColor rgb(r, g, b);
    rgb.clamp_values();
    return rgb;
}


color::color()
{   rgb = new rgb_t;
    hsv = new hsv_t;
    return;
}

color::~color()
{   delete rgb;
    delete hsv;
    return;
}

hsv_t *color::gethsv()
{   return hsv;
}

rgb_t *color::getrgb()
{   return rgb;
}

void color::sethsv(int h, int s, int v)
{
    HSVColor chsv(h, s, v);
    RGBColor crgb = chsv.toRGB();
    hsv->hue = chsv.h();
    hsv->saturation = chsv.s();
    hsv->value = chsv.v();
    rgb->red = crgb.r();
    rgb->green = crgb.g();
    rgb->blue = crgb.b();
    return;
}

void color::setrgb(int r, int g, int b)
{
    RGBColor crgb(r, g, b);
    HSVColor chsv = crgb.toHSV();
    hsv->hue = chsv.h();
    hsv->saturation = chsv.s();
    hsv->value = chsv.v();
    rgb->red = crgb.r();
    rgb->green = crgb.g();
    rgb->blue = crgb.b();
    return;
}

} // namespace SimpleRaytracer
