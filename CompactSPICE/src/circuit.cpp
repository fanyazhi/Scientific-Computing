/*
 *  circuit.cpp
 *  ODESolver
 *  This file contains functions for RC circuit and CS amplifier
 *
 *  Created by Yijia Chen (yc2366) and Yazhi Fan (yf92) on 4/18/18.
 *  Copyright © 2018 Yijia and Yazhi. All rights reserved.
 *
 */

#include "circuit.h"

using namespace std;
using namespace Eigen;

// ----------------------------------------------------------------------------------------

VectorXd RCcircuit(double t, VectorXd X) {
    double C1 = 1E-12, C2 = 1E-12;              //F
    double R1 = 10E3, R2 = 10E3, R3 = 10E3;     //ohms

    Matrix2d M;
    M(0, 0) = (-1.0) * ((1/C1/R1) + (1/C1/R2));
    M(0, 1) = 1/C1/R2;
    M(1, 0) = 1/C2/R2;
    M(1, 1) = (-1.0) * ((1/C2/R2) + (1/C2/R3));

    Vector2d B;
    B(0) = currentSource(t)/C1;
    B(1) = 0;

    Vector2d f;
    f = M*X+B;

    return f;
}

VectorXd CSamplifier(double t, VectorXd x) {
    double IS = 5E-6;       //A
    double k = 0.7;
    double VTH = 1.0;       //V
    double VT = 26E-3;      //V

    //get ID,EKV
    double ID = EKV (x(0), x(1), IS, k, VTH, VT);

    double VDD = 5;                 //V
    double RG = 10E3, RL = 10E3;    //ohms
    double C1 = 1E-12, C2 = 1E-12;  //F

    Vector2d f;
    f(0) = (-1.0/RG/C1) * x(0) + (currentSource(t)/C1);
    f(1) = (-1.0*ID/C2) - ((1/RL/C2)*x(1)) + (VDD/RL/C2);

    return f;
}

double currentSource (double t) {
    double T = 20;      //s
    if (fmod(t*1E9, T) < 1) return 1E5 * fmod(t, T/1E9);
    else if (fmod(t*1E9, T) < 10) return 1E-4;
    else if (fmod(t*1E9, T) < 11) return (-1.0)*1E5*fmod(t, T/1E9) + 11E-4;
    else return 0;
}

double EKV (double VGS, double VDS, double IS, double k, double VTH, double VT) {
    double IF = IS*pow( log(1+exp( (k*(VGS - VTH)) / (2*VT) )) , 2);
    double IR = IS*pow( log(1+exp( (k*(VGS - VTH)-VDS) / (2*VT) )) , 2);
    double ID = IF - IR;
    return ID;
}