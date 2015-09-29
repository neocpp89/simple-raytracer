#include "color.hpp"
#include "color.h"

color::color()
{	rgb = new rgb_t;
	hsv = new hsv_t;
	return;
}

color::~color()
{	delete rgb;
	delete hsv;
	return;
}

hsv_t *color::gethsv()
{	return hsv;
}

rgb_t *color::getrgb()
{	return rgb;
}

void color::sethsv(int h, int s, int v)
{	if (h > 360 || s > 100 || v > 255) {
		return;
	}

	double ns, nv; //normalized saturation and value
	double f, p, q, t;
	int i;

	if (s == 0 || v == 0) {
		//a gray color or black if v is 0
		rgb->red = v;
		rgb->green = v;
		rgb->blue = v;
	} else {
		ns = s / 100.0;
		nv = v / 255.0;
		i = ((h) / 60) % 6;
		f = (((h) / 60.0) - i);
		p = ((nv) * (1 - ns));
		q = ((nv) * (1 - (f * ns)));
		t = ((nv) * (1 - ((1 - f) * ns)));

		nv *= 255.0;
		t *= 255.0;
		q *= 255.0;
		p *= 255.0;

		switch (i) {
			case 0: {
				rgb->red = (int)nv;
				rgb->green = (int)t;
				rgb->blue = (int)p;
			} break;
			case 1: {
				rgb->red = (int)q;
				rgb->green = (int)nv;
				rgb->blue = (int)p;
			} break;
			case 2: {
				rgb->red = (int)p;
				rgb->green = (int)nv;
				rgb->blue = (int)t;
			} break;
			case 3: {
				rgb->red = (int)p;
				rgb->green = (int)q;
				rgb->blue = (int)nv;
			} break;
			case 4: {
				rgb->red = (int)t;
				rgb->green = (int)p;
				rgb->blue = (int)nv;
			} break;
			case 5: {
				rgb->red = (int)nv;
				rgb->green = (int)p;
				rgb->blue = (int)q;
			} break;
		}
	}

	hsv->hue = h;
	hsv->saturation = s;
	hsv->value = v;

	return;
}

void color::setrgb(int r, int g, int b)
{	if (r > 255 || g > 255 || b > 255) {
		return;
	}

	int min = 0;
	int max = 0;
	int delta = 0;
	double t = 0;

	hsv->hue = max = ((max = (r>g)?(r):(g))>b)?(max):(b);
	min = ((min = (r<g)?(r):(g))<b)?(min):(b);
	delta = max - min;

	if (max == min) {
		t = 0;
	} else if (hsv->hue == r) {
		t = (g - b) / ((double)delta);
	} else if (hsv->hue == g) {
		t = (b - r) / ((double)delta);
		t += 2;
	} else { //hsv->hue == b
		t = (r - g) / ((double)delta);
		t += 4;
	}
	t *= 60.0;

	if (t < 0) {
		t += 360;
	}

	hsv->hue = (int)t;
	hsv->saturation = (int)(100.0 * (((double)delta) / max));
	hsv->value = max;
	rgb->red = r;
	rgb->green = g;
	rgb->blue = b;

	return;
}
