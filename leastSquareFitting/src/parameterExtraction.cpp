//
//  parameterExtraction.cpp
//  Least Square Fitting
//
//  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/3/18.
//  Copyright © 2018 Yazhi and Yijia. All rights reserved.
//

#include "parameterExtraction.h"
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// ----------------------------------------------------------------------------------------

/*
   Some constants are used throughout parameterExtraction.cpp.
   They are declared and explained here for convenience
*/
double p = 0.0001;          //the perturbation used in finite difference derivative approximation
double t = 1;               //weight on the increament delta x during each iteration
double threshold = 1E-5;    //threshold on delta x norm to confirm convergence
double maxIteration = 1E6;  //max number of iterations allowed to observe convergenc

// ----------------------------------------------------------------------------------------

double V(vector<double> a, MatrixXd x, T f){
    double v = 0;
    //take the sum of all the squared differences for all measurement
    for (int i = 0; i < x.cols(); i++){
        v += f(a, x.col(i));
    }
    return v;
}

double partialDerivative(vector<double> a, int d, MatrixXd x, T f){
    //d determines which parameters in a to take the derivative with
    vector<double> b = a;
    b[d] = a[d]*(1+p);

    //taking partial derivative with a[d], use derivation from backward difference
    return (V(b, x, f) - V(a, x, f)) / (a[d]*p);
}

double doubleDerivative(vector<double> a, int d1, int d2, MatrixXd x, T f) {
    //d1 and d2 determine which parameters in a to take the derivative with
    vector<double> b = a;
    b[d1] = a[d1] * (1 + p);
    vector<double> c = b;
    c[d2] = a[d2] * (1 + p);

    //taking partial derivative twice with a[d1] and a[d2], use derivation from backward difference
    return 6* (V(c, x, f) - 2*V(b, x, f) + V(a, x, f)) / (a[d1]*p*a[d2]*p);
}

double secantDerivative(vector<double> a, vector<double> aPrevious, int d, MatrixXd x, T f){
    //d determines which parameters in a to take the derivative with
    return (V(a, x, f) - V(aPrevious, x, f)) / (a[d] - aPrevious[d]);
}

vector<double> getDelta(vector<double> a, MatrixXd x, T f){
    //find the Hessian Matrix
    MatrixXd H (a.size(), a.size());
    for (int i = 0; i < a.size(); i++){
        for (int j = 0; j < a.size(); j++){
            H(i, j) = doubleDerivative(a, i, j, x, f);
        }
    }

    //find the inverse of the Hessian matrix
    MatrixXd Hi (a.size(), a.size());
    Hi = H.inverse();

    //find the divergence of V
    VectorXd dV(a.size());
    for (int i = 0; i < a.size(); i++){
        dV(i) = partialDerivative(a, i, x, f);
    }

    //delta x is the negative inverse of H multiplied by divergence of V
    vector<double> delta(a.size());
    for (int i = 0; i < a.size(); i++){
        for (int j = 0; j < a.size(); j++)
        delta[i] += -1.0* (Hi(j,i)*dV(j));
    }
    return delta;
}

vector<double> getDelta_Secant(vector<double> aPrevious, vector<double> a, MatrixXd x, T f){
    //find the Jacobbian Matrix
    MatrixXd J = MatrixXd::Zero(a.size(), a.size());
    for (int i = 0; i < a.size(); i++){
        //use the secant method to evaluate matrix J
        J(i, i) = (V(a, x, f) - V(aPrevious, x, f)) / (a[i] - aPrevious[i]);
    }

    //find the inverse of J
    MatrixXd Ji (a.size(), a.size());
    Ji = J.inverse();

    //find the divergence of V
    VectorXd dV(a.size());
    for (int i = 0; i < a.size(); i++){
        dV(i) = partialDerivative(a, i, x, f);
    }

    //delta x is the negative inverse of J multiplied by divergence of V
    vector<double> delta(a.size());
    for (int i = 0; i < a.size(); i++){
        for (int j = 0; j < a.size(); j++)
            delta[i] += -1.0* (Ji(j,i)*dV(j));
    }
    return delta;
}

double norm(vector<double> a){
    double sum = 0;
    for (int i = 0; i < a.size(); i++){
        sum += pow(a[i], 2);
    }
    return sqrt(sum);
}

vector<double> parameterExtraction(vector<double> a, MatrixXd x, T f){
    int count= 0;
    while(count<maxIteration){

        vector<double> delta = getDelta(a, x, f);
        for (int i = 0; i < a.size(); i++){
            cout<<"a["<<i<<"]: "<<a[i]<<" ";
        }
        cout<<" delta(x) norm: "<<norm(delta)<<" V: "<<V(a, x, f)<<" t: "<<t<<endl;
        vector<double> temp = a;

        for (int i = 0; i < a.size(); i++) temp[i] = a[i] + t* delta[i];
        if (norm(delta) < threshold ) {
            cout<<"norm of delta x converged to threshold"<<endl;
            break;
        }

        for (int i = 0; i < a.size(); i++) a[i] = temp[i];
        count++;

    }

    if (count>maxIteration){
        cout<<"Too many iterations. Result is not converging."
              " Initial guess may not be in the basin of attraction. "<<endl;
    }

    //print the result parameters
    for (int i = 0; i < a.size(); i++) {
        cout<<"parameter a["<<i<<"] = "<<a[i]<<" ";
        cout<<endl;
    }
    cout<<"V = "<<V(a, x, f)<<endl;

    return a;
}

vector<double> parameterExtraction_Secant(vector<double> aPrevious, vector<double> a, MatrixXd x, T f){
    int count= 0;
    while(count<maxIteration){

        vector<double> delta = getDelta_Secant(aPrevious, a, x, f);
        for (int i = 0; i < a.size(); i++){
            cout<<"a[ "<<i<<" ]: "<<a[i]<<" ";
        }
        cout<<" delta(x) norm: "<<norm(delta)<<" V: "<<V(a, x, f)<<" t: "<<t<<endl;
        vector<double> temp = a;

        for (int i = 0; i < a.size(); i++) temp[i] = a[i] + t* delta[i];
        if (norm(delta) < threshold ) {
            cout<<"norm of delta x converged to threshold"<<endl;
            break;
        }

        //update both a(k) and a(k-1) for the next iteration
        for (int i = 0; i < a.size(); i++) {
            aPrevious[i] = a[i];
            a[i] = temp[i];
        }
        count++;
    }

    if (count>=maxIteration){
        cout<<"Too many iterations. Result is not converging."
              " Initial guess may not be in the basin of attraction. "<<endl;
    }

    //print the result parameters
    for (int i = 0; i < a.size(); i++) {
        cout<<"parameter a["<<i<<"] = "<<a[i]<<" ";
        cout<<endl;
    }
    cout<<"V = "<<V(a, x, f)<<endl;

    return a;
}