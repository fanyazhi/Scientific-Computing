/*
 *  forwardEuler.h
 *  ODESolver
 *  This file contains forward Euler method with and without time adaptation
 *
 *  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/18/18.
 *  Copyright © 2018 Yazhi and Yijia. All rights reserved.
 *
 */

#include "forwardEuler.h"

using namespace std;

vector<double> forwardEuler (T f, double x0, double t0, double tn, double h){
    vector<double> x ((int)( (tn-t0) / h) + 1);
    x[0] = x0;

    for (int i = 1; i < (int)( (tn-t0) / h) + 1; i++){
        x[i] = x[i-1] + f(t0+((i-1)*h), x[i-1]);
    }
    return x;
}

