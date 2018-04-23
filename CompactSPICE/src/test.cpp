/*
 *  test.cpp
 *  ODESolver
 *  This file contains a test ODE function
 *
 *  Created by Yijia Chen (yc2366) and Yazhi Fan (yf92) on 4/18/18.
 *  Copyright © 2018 Yijia and Yazhi. All rights reserved.
 *
 */

#include "test.h"

using namespace std;
using namespace Eigen;

VectorXd testODE (double t, VectorXd x) {
    VectorXd result (x.size());
    result(0) = 4 * exp(0.8 * t) - 0.5 * x(0);
    return result;
}

VectorXd testFunction (VectorXd t) {
    VectorXd result (t.size());
    for (int i = 0; i<t.size(); i++){
        result(i) = (4/1.3)*(exp(0.8*t(i))-exp(-0.5*t(i)))+2*exp(-0.5*t(i));
    }
    return result;
}

double percentError (double a, double b) {
    return (a-b)/a;
}

