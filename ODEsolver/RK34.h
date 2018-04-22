/*
 *  RK34.h
 *  ODESolver
 *  This file contains declarations for RK34 method with and without time adaptation
 *
 *  Created by Yijia Chen (yc2366) and Yazhi Fan (yf92) on 4/18/18.
 *  Copyright © 2018 Yijia and Yazhi. All rights reserved.
 *
 */

#ifndef ODESOLVER_RK34_H
#define ODESOLVER_RK34_H

#include <vector>
#include <iostream>
#include <cmath>
#include "forwardEuler.h"
#include <Eigen/Dense>

using namespace std;

// ----------------------------------------------------------------------------------------

/* RK3 ODE solver
        Parameters:
                f: ODE function
                x0: initial condition
                t0: start time
                tn: end time
                h: step size
        Return:
                solution of ODE at all time steps
*/
MatrixXd RK3 (T f, VectorXd x0, double t0, double tn, double h);

// ----------------------------------------------------------------------------------------

/* RK4 ODE solver
        Parameters:
                f: ODE function
                x0: initial condition
                t0: start time
                tn: end time
                h: step size
        Return:
                solution of ODE at all time steps
*/
MatrixXd RK4 (T f, VectorXd x0, double t0, double tn, double h);

// ----------------------------------------------------------------------------------------

/* RK34 time adaptive ODE solver
        Parameters:
                f: ODE function
                x0: initial condition
                t0: start time
                tn: end time
                h0: initial step size
        Return:
                solution of ODE at all time steps
*/
MatrixXd RK34_adaptiveH (T f, VectorXd x0, double t0, double tn, double h0);

// ----------------------------------------------------------------------------------------

/* slope function for RK34
        Parameters:
                f: ODE function
                ti: time
                h: step size
                xi: previous x
        Return:
                K1, K2, K3, k4 for all variables
*/
MatrixXd slopeFunction (T f, double ti, double h, VectorXd xi);

#endif //ODESOLVER_RK34_H
