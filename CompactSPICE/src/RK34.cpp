/*
 *  RK34.cpp
 *  ODESolver
 *  This file contains RK34 method with and without time adaptation
 *
 *  Created by Yijia Chen (yc2366) and Yazhi Fan (yf92) on 4/18/18.
 *  Copyright © 2018 Yijia and Yazhi. All rights reserved.
 *
 */

#include "RK34.h"

using namespace std;
using namespace Eigen;

MatrixXd RK3 (T f, VectorXd x0, double t0, double tn, double h) {
    int stepNum = ((int) ((tn - t0) / h) + 1);
    MatrixXd result(x0.size(), stepNum);

    // store the initial guess, vector x0
    for (int i = 0; i < x0.size(); i++) {
        result(i, 0) = x0[i];
    }

    //loop through t, generate x[]
    for (int j = 1; j < stepNum; j++) {
        MatrixXd k(x0.size(), 4);
        k = slopeFunction(f, t0 + ((j - 1) * h), h, result.col(j - 1));
        result.col(j) = result.col(j - 1) + ((1.0 / 9.0) * (2.0 * k.col(0) + 3.0 * k.col(1) + 4.0 * k.col(2)) * h);
    }

    return result;
}

MatrixXd RK4 (T f, VectorXd x0, double t0, double tn, double h) {
    int stepNum = ((int) ((tn - t0) / h) + 1);
    MatrixXd result(x0.size(), stepNum);

    // store the initial guess, vector x0
    for (int i = 0; i < x0.size(); i++) {
        result(i, 0) = x0[i];
    }

    //loop through t, generate x[]
    for (int j = 1; j < stepNum; j++) {
        MatrixXd k(x0.size(), 4);
        k = slopeFunction(f, t0 + ((j - 1) * h), h, result.col(j - 1));
        result.col(j) = result.col(j-1) + ((1.0/24.0) * (7.0*k.col(0) + 6.0*k.col(1) + 8.0*k.col(2) + 3*k.col(3)) * h);
    }

    return result;
}


MatrixXd RK34_adaptiveH (T f, VectorXd x0, double t0, double tn, double h0) {
    MatrixXd x (x0.size(), 1); x = x0;          //stores result of RK34 time adaptive
    MatrixXd xRK4 (x0.size(), 1); x = x0;        //stores RK4 x
    VectorXd h (1); h(0) = h0;                  //stores time steps
    int stepNum = ((int)( (tn-t0) / h0) + 1);
    MatrixXd result (x0.size(), stepNum); result.col(0) = x0; //stores result of RK34 at desired time steps

    double eR = 1E-7;   //epsilon R used for Error calculation
    double eA = 1E-9;   //epsilon A used for Error calculation

    double totalTime = 0;   //records total time
    double point = 1;       //records number of points in result
    int i = 1;              //records number of points in RK34 x

    while(totalTime < tn-t0){

        //calculate RK4 xi+1 with current hi
        MatrixXd k(x0.size(), 4);
        k = slopeFunction(f, t0+(totalTime), h(i-1), x.col(i-1));
        xRK4.conservativeResize(NoChange, xRK4.cols()+1);
        xRK4.col(i) =  x.col(i-1) + ((1.0/24.0) * (7*k.col(0) + 6.0*k.col(1) + 8.0*k.col(2) + 3*k.col(3)) * h(i-1) );

        //calculate error estimator
        VectorXd E (x0.size());
        E = (1.0/72.0) * (-5*k.col(0) + 6*k.col(1) + 8*k.col(2) - 9*k.col(3)) * h(i-1);

        //get hi+1 with adaptive h formula
        double adaptH = h(i-1) * pow( (eR / E.norm()) / ( (xRK4.col(i)).norm()+eA ), 1.0/3.0 );
        h.conservativeResize(h.size()+1);
        h(i) = adaptH;

        //calculate xi+1 with hi+1
        k = slopeFunction(f, t0+(totalTime), h(i), x.col(i-1));
        x.conservativeResize(NoChange, x.cols()+1);
        x.col(i) =  x.col(i-1) + ((1.0/24.0) * (7*k.col(0) + 6.0*k.col(1) + 8.0*k.col(2) + 3*k.col(3)) * h(i)) ;

        //increment time
        totalTime += adaptH;
        //add this point to result if it is at a desired time step
        if (totalTime > h0*point && point <stepNum){
            result.col(point) = x.col(i);
            point++;
        }

        i++;
    }

    return result;
}

MatrixXd slopeFunction (T f, double ti, double h, VectorXd xi) {
    //return vector k1, k2, k3, k4
    MatrixXd k (xi.size(), 4);
    k.col(0) = f(ti, xi);
    k.col(1) = f(ti+h/2, xi+k.col(0)*h/2);
    k.col(2) = f(ti+3*h/4, xi+3*k.col(1)*h/4);
    k.col(3) = f(ti+h, xi+k.col(2)*h);
    return k;
}



