/*
 *  forwardEuler.cpp
 *  ODESolver
 *  This file contains the forward Euler method
 *
 *  Created by Yijia Chen (yc2366) and Yazhi Fan (yf92) on 4/18/18.
 *  Copyright © 2018 Yijia and Yazhi. All rights reserved.
 *
 */

#include "forwardEuler.h"

using namespace std;
using namespace Eigen;

// ----------------------------------------------------------------------------------------

MatrixXd forwardEuler (T f, VectorXd x0, double t0, double tn, double h){
    int stepNum = ((int)( (tn-t0) / h) + 1);
    MatrixXd result (x0.size(), stepNum);

    // store the initial guess, vector x0
    for (int i = 0; i< x0.size(); i++){
        result(i, 0) = x0[i];
    }

    //loop through t, generate x[]
    for (int j = 1; j < stepNum; j++){
        result.col(j) = result.col(j-1) + f(t0 + (j-1)*h, result.col(j-1)) * h;
    }

    return result;
}

