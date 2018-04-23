/*
 *  forwardEuler.h
 *  ODESolver
 *  This file contains declarations for the forward Euler method
 *
 *  Created by Yijia Chen (yc2366) and Yazhi Fan (yf92) on 4/18/18.
 *  Copyright © 2018 Yijia and Yazhi. All rights reserved.
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

/* forward Euler ODE solver
        Parameters:
                f: ODE function
                x0: initial condition
                t0: start time
                tn: end time
                h: step size
        Return:
                solution of ODE at all time steps
*/
MatrixXd forwardEuler (T f, VectorXd x0, double t0, double tn, double h);

#endif //ODESOLVER_FORWARDEULER_H


