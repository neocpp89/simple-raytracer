#include "numeric.h"
#include <cmath>
#include <cstdio>

using namespace std;

double resphi = (3 - sqrt(5.0)) / 2.0;
double find_min_helper(double (*fn)(double x), double a, double c, double b, double tol);

#define MAXIT 100

float rtsafe(void (*funcd)(float, float *, float *), float x1, float x2,
    float xacc)
{
/*	void perror(char error_text[]);*/
    int j;
    float df,dx,dxold,f,fh,fl;
    float temp,xh,xl,rts;

    (*funcd)(x1,&fl,&df);
    (*funcd)(x2,&fh,&df);
    if ((fl > 0.0 && fh > 0.0) || (fl < 0.0 && fh < 0.0))
        perror("Root must be bracketed in rtsafe");
    if (fl == 0.0) return x1;
    if (fh == 0.0) return x2;
    if (fl < 0.0) {
        xl=x1;
        xh=x2;
    } else {
        xh=x1;
        xl=x2;
    }
    rts=0.5*(x1+x2);
    dxold=fabs(x2-x1);
    dx=dxold;
    (*funcd)(rts,&f,&df);
    for (j=1;j<=MAXIT;j++) {
        if ((((rts-xh)*df-f)*((rts-xl)*df-f) > 0.0)
            || (fabs(2.0*f) > fabs(dxold*df))) {
            dxold=dx;
            dx=0.5*(xh-xl);
            rts=xl+dx;
            if (xl == rts) return rts;
        } else {
            dxold=dx;
            dx=f/df;
            temp=rts;
            rts -= dx;
            if (temp == rts) return rts;
        }
        if (fabs(dx) < xacc) return rts;
        (*funcd)(rts,&f,&df);
        if (f < 0.0)
            xl=rts;
        else
            xh=rts;
    }
    perror("Maximum number of iterations exceeded in rtsafe");
    return 0.0;
}
#undef MAXIT

int find_min_root(double *root, double (*fn2)(double x), double a, double b, double tol)
{
	double at;
	double val;
	double pat;
	double pval;

	double bprime;
	/*
		fn2 is the function squared (so global min at 0->zero in fn).
	*/
	val = find_min(&at, fn2, a, b, tol);
	do {
		pval = val;
		pat = at;
		bprime = at - tol;
		val = find_min(&at, fn2, a, bprime, tol);
	} while (abs(val) < tol && abs(bprime - a) < tol);

	if (abs(pval) < tol) {
		*root = pat;
		return 1;
	}

	return 0;
}

double find_min(double *at, double (*fn)(double x), double a, double b, double tol)
{
	*at = find_min_helper(fn, a, a + resphi * (b - a), b, tol);
	return fn(*at);
}

double find_min_helper(double (*fn)(double x), double a, double c, double b, double tol)
{
	double d = c + resphi * (b - c);

	if (abs(b - a) < tol * (abs(c) + abs(d))) {
		return ((b + a) / 2);
	}

	if (fn(d) < fn(c)) {
		return find_min_helper(fn, c, d, b, tol);
	} else {
		return find_min_helper(fn, d, b, a, tol);
	}
}
