//
//  parameterExtraction.cpp
//  Least Square Fitting
//
//  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/3/18.
//  Copyright © 2018 Yazhi and Yijia. All rights reserved.
//

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
   Some global variables are used for conveniences.
   Their values and meanings are explained below.
*/
double p = 0.0001; //the perturbation used in finite difference derivative approximation


// ----------------------------------------------------------------------------------------

double f(vector<double> a, VectorXd xi){
    return pow(log(a[0])+a[1]*log(xi(0))-log(xi(1)),2);
}

double V(vector<double> a, MatrixXd x){
    double v = 0;
    //take the sum of all the squared differences for all measurement
    for (int i = 0; i < x.cols(); i++){
        v += f(a, x.col(i));
    }
    return v;
}

double partialDerivative(vector<double> a, int d, MatrixXd x){
    //d determines which parameters in a to take the derivative with
    vector<double> b = a;
    b[d] = a[d]*(1+p);

    double sum = 0;
    for (int i = 0; i < x.cols(); i++){
        sum += (f(b, x.col(i)) - f(a, x.col(i))) / (a[d]*p);
    }
    return sum;
}

double doubleDerivative(vector<double> a, int d1, int d2, MatrixXd x) {
    //d1 and d2 determine which parameters in a to take the derivative with
    vector<double> b = a;
    b[d1] = a[d1] * (1 + p);
    vector<double> c = b;
    c[d2] = a[d2] * (1 + p);

    //taking partial derivative twice with a[d1] and a[d2], use derivation from backward difference
    double sum = 0;
    for (int i = 0; i < x.cols(); i++) {
        sum += (f(c, x.col(i)) - 2*f(b, x.col(i)) + f(a, x.col(i))) / (a[d1]*p*a[d2]*p);
    }
    return 6*sum;

}

vector<double> getDelta(vector<double> a, MatrixXd x){
    //find the Hessian Matrix
    MatrixXd H (a.size(), a.size());
    for (int i = 0; i < a.size(); i++){
        for (int j = 0; j < a.size(); j++){
            H(i, j) = doubleDerivative(a, i, j, x);
        }
    }

    //find the inverse of the Hessian matrix
    MatrixXd Hi (a.size(), a.size());
    Hi = H.inverse();

    //find the divergence of V
    VectorXd dV(a.size());
    for (int i = 0; i < a.size(); i++){
        dV(i) = partialDerivative(a, i, x);
    }

    //delta x is the negative inverse of H multiplied by divergence of V
    vector<double> delta(a.size());
    for (int i = 0; i < a.size(); i++){
        for (int j = 0; j < a.size(); j++)
        delta[i] += -1.0* (Hi(j,i)*dV(j));
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

vector<double> parameterExtraction(vector<double> a, MatrixXd x){
    int count= 0;
    double t = 1;
    double threshold = 1E-7;
    double maxIteration = 100000;
    while(count<maxIteration){

        vector<double> delta = getDelta(a, x);
        cout<<"a: "<<a[0]<<" m: "<<a[1]<<" delta(x) norm: "<<norm(delta)<<" V: "<<V(a, x)<<" t: "<<t<<endl;
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
    cout<<"V = "<<V(a, x)<<endl;

    return a;
}