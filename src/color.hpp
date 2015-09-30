#ifndef SRT_COLOR_HPP_ 
#define SRT_COLOR_HPP_

#include "color.h"

namespace SimpleRaytracer {

/*
    Forward declare these since they return each other as objects in conversion.
*/
class RGBColor;
class HSVColor;

class RGBColor
{
    public:
        RGBColor(int r, int g, int b) : r_(r), g_(g), b_(b) {}
        inline int r() const { return r_; }
        inline int g() const { return g_; }
        inline int b() const { return b_; }
        inline void set_r(const int r) { r_ = r; }
        inline void set_g(const int g) { g_ = g; }
        inline void set_b(const int b) { b_ = b; }
        void clamp_values();
        HSVColor toHSV() const;

    private:
        int r_;
        int g_;
        int b_;
};

class HSVColor
{
    public:
        HSVColor(int h, int s, int v) : h_(h), s_(s), v_(v) {}
        inline int h() const { return h_; }
        inline int s() const { return s_; }
        inline int v() const { return v_; }
        inline void set_h(const int h) { h_ = h; }
        inline void set_s(const int s) { s_ = s; }
        inline void set_v(const int v) { v_ = v; }
        void clamp_values();
        RGBColor toRGB() const;

    private:
        int h_;
        int s_;
        int v_;
};

class color
{	public:
		color();
		~color();

		hsv_t *gethsv();
		rgb_t *getrgb();
		void sethsv(int h, int s, int v);
		void setrgb(int r, int g, int b);

	private:
		rgb_t *rgb;
		hsv_t *hsv;
};

} // namespace SimpleRaytracer

#endif //SRT_COLOR_HPP_
