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
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// ----------------------------------------------------------------------------------------

//alias type name for an ODE function
typedef VectorXd (*T)(double, VectorXd);


// ----------------------------------------------------------------------------------------



MatrixXd forwardEuler (T f, VectorXd x0, double t0, double tn, double h);


#endif //ODESOLVER_FORWARDEULER_H


