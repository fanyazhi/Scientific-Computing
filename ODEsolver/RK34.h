/*
 *  RK34.h
 *  ODESolver
 *  This this is header file for RK34 method with and without time adaptation
 *
 *  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/18/18.
 *  Copyright © 2018 Yazhi and Yijia. All rights reserved.
 *
 */

#ifndef ODESOLVER_RK34_H
#define ODESOLVER_RK34_H

#include <vector>
#include <iostream>
#include <cmath>
#include "forwardEuler.h"

using namespace std;

vector<double> RK3 (T f, double x0, double t0, double tn, double h);

vector<double> RK4 (T f, double x0, double t0, double tn, double h);

vector<double> RK34_adaptiveH (T f, double x0, double t0, double tn, double h);

vector<double> slopeFunction (T f, double ti, double h, double xi);

double RK34ErrorEstimator (vector<double> k, double h);

double adaptiveH (double hi, double eR, double eA, double E, double x);

#endif //ODESOLVER_RK34_H
