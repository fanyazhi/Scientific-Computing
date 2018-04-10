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

vector<double> parameterExtraction(vector<double> a, MatrixXd x, T f){
    int count= 0;
    cout<<"------------------------------------"<<endl;
    cout<<"PARAMETER SEARCH RESULT"<<endl;
    while(count<maxIteration){
        //get delta x
        vector<double> delta = getDelta(a, x, f);

        //compute ||V||2 and ||delta||2
        double V2 = V(a, x, f);
        double D2 = 0;
        for (int i = 0; i < a.size(); i++){
            D2 += pow(delta[i],2) / pow(a[i],2);
        }

        //Print a[], ||delta(x)||2, ||V||2, and ||D||2
        for (int i = 0; i < a.size(); i++){
            cout<<"a["<<i<<"]: "<<a[i]<<" ";
        }
        cout<<" ||delta(x)||2: "<<norm(delta)<<" ||V||2: "<<V2<<" ||D||2: "<<D2;

        //add delta to a and store in temp
        vector<double> temp = a;
        for (int i = 0; i < a.size(); i++) temp[i] = a[i] + delta[i];

        //check for quadratic convergence
        bool quadConvergence = true;
        if (! ((1-quadTol)*sqrt(V(a, x, f))< V(temp, x, f) && V(temp, x, f)  < (1+quadTol)*sqrt(V(a, x, f))) ) {
            quadConvergence = false;
        }
        cout << " Quadratic: " << quadConvergence << endl;

        //check if convergence threshold is met
        if (norm(delta) < threshold ) {
            cout<<"norm of delta x converged to threshold after "<<count<<" iterations"<<endl;
            break;
        }

        //check if result is diverging
        if (V(temp, x, f)>= V(a, x, f) && V(a, x, f) > acceptableV ){
            cout<<"PARAMETER SEARCH FAILED"<<endl
                <<"Result is diverging."
                  " Initial guess may not be in the basin of attraction. "<<endl;
            break;
        }

        //check if result has converged even if specified threshold is not met
        if (V(temp, x, f)>= V(a, x, f) && V(a, x, f) < acceptableV ){
            cout<<"norm of delta x converged after "<<count<<" iterations"<<endl;
            break;
        }

        //update a[i] for next iteration
        for (int i = 0; i < a.size(); i++) a[i] = temp[i];
        count++;
    }

    if (count>=maxIteration){
        cout<<"PARAMETER SEARCH FAILED"<<endl
            <<"Max number of iterations has been reached. Result is not converging."
              " Initial guess may not be in the basin of attraction. "<<endl;
    }

    //print the result parameters
    for (int i = 0; i < a.size(); i++) {
        cout<<"parameter a["<<i<<"] = "<<a[i]<<" ";
        cout<<endl;
    }
    cout<<"||V||2 = "<<V(a, x, f)<<endl;
    cout<<"||delta x||2 = "<<norm(getDelta(a, x, f))<<endl;

    return a;
}

vector<double> parameterExtraction_Secant(vector<double> aPrevious, vector<double> a, MatrixXd x, T f){
    int count= 0;
    cout<<"------------------------------------"<<endl;
    cout<<"PARAMETER SEARCH RESULT"<<endl;
    while(count<maxIteration){
        //get delta
        vector<double> delta = getDelta_Secant(aPrevious, a, x, f);

        //compute ||V||2 and ||delta||2
        double V2 = V(a, x, f);
        double D2 = 0;
        for (int i = 0; i < a.size(); i++){
            D2 += pow(delta[i],2) / pow(a[i],2);
        }

        //Print a[], ||delta(x)||2, ||V||2, and ||D||2
        for (int i = 0; i < a.size(); i++){
            cout<<"a["<<i<<"]: "<<a[i]<<" ";
        }
        cout<<" ||delta(x)||2: "<<norm(delta)<<" ||V||2: "<<V2<<" ||D||2: "<<D2;

        //add delta to a and store in temp
        vector<double> temp = a;
        for (int i = 0; i < a.size(); i++) temp[i] = a[i] + delta[i];

        //check for quadratic convergence
        bool quadConvergence = true;
        if (! ((1-quadTol)*V(a, x, f)< V(temp, x, f) && V(temp, x, f)  < (1+quadTol)*V(a, x, f)) ) {
            quadConvergence = false;
        }
        cout << " Quadratic converge: " << quadConvergence << endl;

        //check if convergence threshold is met
        if (norm(delta) < threshold ) {
            cout<<"norm of delta x converged to threshold after "<<count<<" iterations"<<endl;
            break;
        }

        //check if result is diverging
        if (V(temp, x, f)>= V(a, x, f) && V(a, x, f) > acceptableV ){
            cout<<"PARAMETER SEARCH FAILED"<<endl
                <<"Result is diverging."
                  " Initial guess may not be in the basin of attraction. "<<endl;
            break;
        }

        //check if result is NAN
        if (V(a, x, f) != V(a, x, f)){
            cout<<"PARAMETER SEARCH FAILED"<<endl
                <<"Result is NAN."
                  " Initial guess may not be in the basin of attraction. "<<endl;
            break;
        }

        //check if result has converged even if specified threshold is not met
        if (V(temp, x, f)>= V(a, x, f) && V(a, x, f) < acceptableV ){
            cout<<"norm of delta x converged after "<<count<<" iterations"<<endl;
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
        cout<<"PARAMETER SEARCH FAILED"<<endl
            <<"Max number of iterations has been reached. Result is not converging."
              " Initial guess may not be in the basin of attraction. "<<endl;
    }

    //print the result parameters
    for (int i = 0; i < a.size(); i++) {
        cout<<"parameter a["<<i<<"] = "<<a[i]<<" ";
        cout<<endl;
    }
    cout<<"||V||2 = "<<V(a, x, f)<<endl;
    cout<<"||delta x||2 = "<<norm(getDelta(a, x, f))<<endl;

    return a;
}

double V(vector<double> a, MatrixXd x, T f){
    double v = 0;
    //take the sum of all measurements
    for (int i = 0; i < x.cols(); i++){
        v += f(a, x.col(i));
    }
    return v;
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
    //initiate a matrix of zeros, fill the diagonal elements with dV/dx with secant method
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

double norm(vector<double> a){
    double sum = 0;
    for (int i = 0; i < a.size(); i++){
        sum += pow(a[i], 2);
    }
    return sqrt(sum);
}

