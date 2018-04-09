//
//  test.cpp
//  Least Square Fitting
//
//  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/7/18.
//  Copyright © 2018 Yazhi and Yijia. All rights reserved.
//

#include "test.h"
#include "parameterExtraction.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// ----------------------------------------------------------------------------------------

/*
   Validation for power law y = c0*x^a (task 2)
   a set of x and y are generated with known parameter a and m
   and parameter extraction method is called to find a and m with the generated x and y
   result from parameter extraction is compared with ground truth
*/

void powerLawValidation(){
    //Ground truth
    vector<double> aKnown = {10, -0.5};

    //Generate 10 samples of Smeasured with random noise within 10%
    int paraNum = 2;        //number of parameters
    int sampleNum = 10;     //number of samples
    MatrixXd x (paraNum, sampleNum);

    VectorXd x0 (10);
    //x must cover a good range of values, so we did not generate x randomly
    x0 << 1.0, 2.5, 4.5, 9.0, 20, 30, 53, 74, 181, 200;
    x.row(0) = x0;
    for (int i = 0; i < 10; i++){
        //generate y = c0*x^m based on x with random noise from -0.10 to 0.10
        x(1,i) =  (fRand(-0.1,0.1)+1) * (aKnown[0]*pow(x(0,i), aKnown[1]));
    }

    //make initial guess
    vector<double> a = {12.0, -0.6};
    //test parameter extraction method with the above values
    vector<double> result = parameterExtraction(a, x, powerFunc);

    //compare to ground truth
    vector<double> error(a.size());
    for (int i = 0; i < a.size(); i++){
        //calculate percent error
        error[i] = abs((aKnown[i] - result[i])) / aKnown[i];
    }

    cout<<"Power Law Validation Result: "<<endl;
    cout<<"||error||2 = "<<norm(error)<<endl;
}

double powerFunc (vector<double> a, VectorXd xi){
    return pow(log(a[0])+a[1]*log(xi(0))-log(xi(1)),2);
}

double fRand(double fMin, double fMax){
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

// ----------------------------------------------------------------------------------------

/*
   asymptotic testing for EKV (task 7)

*/