#ifndef SRT_COLOR_HPP_ 
#define SRT_COLOR_HPP_

#include "color.h"

namespace SimpleRaytracer {

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
