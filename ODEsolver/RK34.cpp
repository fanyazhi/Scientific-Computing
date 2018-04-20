/*
 *  RK34.cpp
 *  ODESolver
 *  This file contains RK34 method with and without time adaptation
 *
 *  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/18/18.
 *  Copyright © 2018 Yazhi and Yijia. All rights reserved.
 *
 */

#include "RK34.h"

using namespace std;

vector<double> RK3 (T f, double x0, double t0, double tn, double h) {
    vector<double> x ((int)( (tn-t0) / h) + 1);
    x[0] = x0;

    for (int i = 1; i < (int)( (tn-t0) / h) + 1; i++){
        vector<double> k(4);    //get slope function
        k = slopeFunction(f, t0+((i-1)*h), h, x[i-1]);
        x[i] = x[i-1] + ((1.0/9.0) * (2.0*k[0] + 3.0*k[1] + 4.0*k[2]) * h);
    }

    return x;
}

vector<double> RK4 (T f, double x0, double t0, double tn, double h) {
    vector<double> x ((int)( (tn-t0) / h) + 1);
    x[0] = x0;

    for (int i = 1; i < (int)( (tn-t0) / h) + 1; i++){
        vector<double> k(4);    //get slope function
        k = slopeFunction(f, t0+((i-1)*h), h, x[i-1]);
        x[i] = x[i-1] + ((1.0/24.0) * (7*k[0] + 6.0*k[1] + 8.0*k[2] + 3*k[3]) * h);
    }

    return x;
}

vector<double> RK34_adaptiveH (T f, double x0, double t0, double tn, double h0) {
    vector<double> x {0};       //stores result of RK34 time adaptive
    vector<double> xRK4 {0};    //stores RK4 x
    vector<double> h{h0};

    double eR = 1E-5;
    double eA = 1E-5;

    double totalTime = 0;
    int i = 1;

    while(totalTime < tn-t0){
        //calculate RK4 xi+1 with current hi
        vector<double> k(4);
        k = slopeFunction(f, t0+(totalTime+h[i-1]), h[i-1], x[i-1]);
        xRK4.push_back( x[i-1] + ((1.0/24.0) * (7*k[0] + 6.0*k[1] + 8.0*k[2] + 3*k[3]) * h[i-1]) );

        //calculate error estimator
        double E = (1.0/72.0) * (-5*k[0] + 6*k[1] + 8*k[2] - 9*k[3]) * h[i-1];

        //get hi+1 with adaptive h formula
        double adaptH = adaptiveH (h[i-1], eR, eA, E, xRK4[i]);
        h.push_back(adaptH);

        //calculate xi+1 with hi+1
        k = slopeFunction(f, t0+(totalTime+h[1]), h[i], x[i-1]);
        x.push_back( x[i-1] + ((1.0/24.0) * (7*k[0] + 6.0*k[1] + 8.0*k[2] + 3*k[3]) * h[i]) );

        cout<<totalTime<<" "<<x[i]<<endl;
        i++;
        totalTime += adaptH;
    }
    return x;
}

//return k1, k2, k3, k4
vector<double> slopeFunction (T f, double ti, double h, double xi) {
    vector<double> k(4);
    k[0] = f(ti, xi);
    k[1] = f(ti+h/2, xi+k[0]*h/2);
    k[2] = f(ti+3*h/4, xi+3*k[1]*h/4);
    k[3] = f(ti+h, xi+k[2]*h);
    return k;
}


double adaptiveH (double hi, double eR, double eA, double E, double x) {
    return hi * sqrt(eR / (abs(E) / (abs(x)+eA) ));
    
}

