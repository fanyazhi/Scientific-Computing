/*
 *  test.h
 *  ODESolver
 *  This file contains a test ODE function
 *
 *  Created by Yijia Chen (yc2366) and Yazhi Fan (yf92) on 4/18/18.
 *  Copyright © 2018 Yijia and Yazhi. All rights reserved.
 *
 */

#ifndef ODESOLVER_TEST_H
#define ODESOLVER_TEST_H

#include <iostream>
#include <Eigen/Dense>
#include <cmath>
#include "RK34.h"
#include "forwardEuler.h"

using namespace std;
using namespace Eigen;

// ----------------------------------------------------------------------------------------

/* Test ODE with single variable
        Parameters:
                t: time
                x: variable
        Return:
                dV/dx
*/
VectorXd testODE (double t, VectorXd x);

// ----------------------------------------------------------------------------------------

/* Test function which is the known solution to test ODE
        Parameters:
                t: time
        Return:
                ground truth x values
*/
VectorXd testFunction (double t0, double tn, double h);

// ----------------------------------------------------------------------------------------

/* Percent error calculation
        Parameters:
                a: first value
                b: second value
        Return:
                percent error between a and b
*/
double percentError (double a, double b);

#endif //ODESOLVER_TEST_H
