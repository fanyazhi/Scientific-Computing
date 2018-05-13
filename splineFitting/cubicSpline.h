//
// Created by Jane Fan on 5/9/18.
//

#ifndef SPLINEFITTING_CUBICSPLINE_H
#define SPLINEFITTING_CUBICSPLINE_H

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double cubicPoint(int i, double xi, vector<double> x, vector<double> y, vector<double> k);
vector<double> splineDerivative(int d, vector<double> x, vector<double> y);
void cubicSpline(vector<double> x, vector<double> y, vector<double> &qx, vector<double> &qy);

#endif //SPLINEFITTING_CUBICSPLINE_H
