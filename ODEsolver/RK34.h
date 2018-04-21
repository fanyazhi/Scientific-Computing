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
#include <Eigen/Dense>

using namespace std;

MatrixXd RK3 (T f, VectorXd x0, double t0, double tn, double h);

MatrixXd RK4 (T f, VectorXd x0, double t0, double tn, double h);

MatrixXd RK34_adaptiveH (T f, VectorXd x0, double t0, double tn, double h0);

MatrixXd slopeFunction (T f, double ti, double h, VectorXd xi);

#endif //ODESOLVER_RK34_H
