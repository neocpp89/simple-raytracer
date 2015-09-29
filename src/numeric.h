#ifndef __NUMERIC_H__
#define __NUMERIC_H__

int find_min_root(double *root, double (*fn2)(double x), double a, double b, double tol);
double find_min(double *at, double (*fn)(double x), double a, double b, double tol);

#endif