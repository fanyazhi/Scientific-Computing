/*
 *  forwardEuler.h
 *  ODESolver
 *  This this the header file for forward Euler method with and without time adaptation
 *
 *  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/18/18.
 *  Copyright © 2018 Yazhi and Yijia. All rights reserved.
 *
 */

#ifndef ODESOLVER_FORWARDEULER_H
#define ODESOLVER_FORWARDEULER_H

#include <vector>
#include <iostream>

using namespace std;

// ----------------------------------------------------------------------------------------

//alias type name for an ODE function
typedef double (*T)(double, double);

// ----------------------------------------------------------------------------------------



vector<double> forwardEuler (T f, double x0, double t0, double tn, double h);


#endif //ODESOLVER_FORWARDEULER_H


