//
//  EKV.cpp
//  Least Square Fitting
//
//  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/7/18.
//  Copyright © 2018 Yazhi and Yijia. All rights reserved.
//

#include "EKV.h"
#include <cmath>
#include <iomanip>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// ----------------------------------------------------------------------------------------

/*
   Some constants are used throughout EKV.cpp.
   They are declared and explained here for convenience
*/
double VSB = 0.0;       //S is shorted to B

double VT = 26E-3;      //VT in volts

// ----------------------------------------------------------------------------------------

double EKVmodel (vector<double> a, VectorXd xi) {
    //Smodel = ID(VGS, VDS; IS, k, Vth)
    //ID - IF + IR = 0
    //IF = IS*pow( log(1+exp( (k*(VGB - Vth)-VSB) / (2*VT) )) , 2);
    //IR = IS*pow( log(1+exp( (k*(VGB - Vth)-VDB) / (2*VT) )) , 2);

    double IF = a[0]*pow( log(1+exp( (a[1]*(xi[0] - a[2])-VSB) / (2*VT) )) , 2);
    double IR = a[0]*pow( log(1+exp( (a[1]*(xi[0] - a[2])-xi[1]) / (2*VT) )) , 2);
    return pow((xi[2] - IF +IR) , 2);
}

double normalizedEKVmodel (vector<double> a, VectorXd xi) {
    //Smodel = ID(VGS, VDS; IS, k, Vth) / IDmeasured

    double IF = a[0]*pow( log(1+exp( (a[1]*(xi[0] - a[2])-VSB) / (2*VT) )) , 2);
    double IR = a[0]*pow( log(1+exp( (a[1]*(xi[0] - a[2])-xi[1]) / (2*VT) )) , 2);
    double ID = (IF - IR)/xi[2];
    return pow((ID - IF +IR) , 2);
}

MatrixXd constructVariables () {
    //initiate vector x to store all elements in file
    vector<double> x;

    ifstream inValue;
    inValue.open("/Users/Jane_Fan/Desktop/leastSquareFitting/outputNMOS.txt");

    //check if file is open, if not exit code
    if(!inValue.is_open()) {
        cout << "error: file did not open" << endl;
        exit(1);
    }

    // Declare a variable to load the contents from the file
    string line = "";

    // Loading the value vector
    while (inValue >> line) {
        double value = stod(line);
        x.push_back(value);
    }

    //convert from array to matrix with known row and column numbers
    int rown = 3;
    int coln = 1010;
    MatrixXd X (rown, coln);
    for (int i = 0; i < x.size()/rown; i++){
        for (int j = 0; j < rown; j++) {
            X(j, i) = x[i*rown+j];
        }
    }
    return X;
}

