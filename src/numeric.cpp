#include "numeric.h"
#include <cmath>
#include <cstdio>

constexpr double resphi = (3 - sqrt(5.0)) / 2.0;
double find_min_helper(double (*fn)(double x), double a, double c, double b, double tol);

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
	} while (std::abs(val) < tol && std::abs(bprime - a) < tol);

	if (std::abs(pval) < tol) {
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

	if (std::abs(b - a) < tol * (std::abs(c) + std::abs(d))) {
		return ((b + a) / 2);
	}

	if (fn(d) < fn(c)) {
		return find_min_helper(fn, c, d, b, tol);
	} else {
		return find_min_helper(fn, d, b, a, tol);
	}
}
