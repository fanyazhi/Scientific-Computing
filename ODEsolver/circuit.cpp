/*
 *  forwardEuler.h
 *  ODESolver
 *  This file contains forward Euler method with and without time adaptation
 *
 *  Created by Yijia Chen (yc2366) and Yazhi Fan (yf92) on 4/18/18.
 *  Copyright © 2018 Yijia and Yazhi. All rights reserved.
 *
 */
#include "circuit.h"

using namespace std;
using namespace Eigen;

//f[] = M[][]*X[]+B[]
VectorXd RCcircuit(double t, VectorXd x) {
    double C1 = 1E-12, C2 = 1E-12; //F; //F
    double R1 = 10E3, R2 = 10E3, R3 = 10E3; //omega

    Matrix2d M;
    M(0, 0) = (-1.0) * ((1/C1/R1) + (1/C1/R2));
    M(0, 1) = 1/C1/R2;
    M(1, 0) = 1/C2/R2;
    M(1, 1) = (-1.0) * ((1/C2/R2) + (1/C2/R3));

    Vector2d X;
    for (int i = 0; i<x.size(); i++) {
        X(i) = x[i];
    }

    Vector2d B;
    B(0) = currentSource(t)/C1;
    B(1) = 0;

    Vector2d f;
    f = M*X+B;

    return f;
}

double currentSource (double t) {
    double T = 20E-9; //s
    if (remainder(t, T) < 1E-9) return 1E5 * t;
    else if (remainder(t, T) < 10E-9) return 1E-4;
    else if (remainder(t, T) < 11E-9) return (-1.0)*1E5*t + 11E-4;
    else return 0;
}
