//
//  EKV.cpp
//  Least Square Fitting
//
//  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/7/18.
//  Copyright © 2018 Yazhi and Yijia. All rights reserved.
//

#include "EKV.h"
#include "parameterExtraction.h"
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

vector <double> EKVmodel_getID (vector<double> a, vector<double> VGS, vector<double> VDS) {
    //Smodel = ID(VGS, VDS; IS, k, Vth)
    //ID = IF - IR
    vector<double> ID (VGS.size()); //size of all vectors are equal

    for (int i = 0; i < VGS.size(); i++){
        double IF = a[0]*pow( log(1+exp( (a[1]*(VGS[i] - a[2])-VSB) / (2*VT) )) , 2);
        double IR = a[0]*pow( log(1+exp( (a[1]*(VGS[i] - a[2])-VDS[i]) / (2*VT) )) , 2);
        ID[i] = IF - IR;
    }
    return ID;
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

void fullGridSearch (vector<double> initialIS, vector<double> initialk, vector<double> initialVth ) {
    //get measured variables
    MatrixXd x = constructVariables ();

    //number of parameters
    int parameterNum = 3;

    //loop through full grid and perform EVK parameter extraction
    for (int i = 0; i < initialIS.size()-1; i++){
        for (int j = 0; j < initialk.size()-1; j++){
            for (int k = 0; k < initialVth.size()-1; k++){
                cout<<"--------------------------------------------------------------------------------"<<endl;
                cout<<"initialIS = "<<initialIS[i]<<" initialk = "<<initialk[j]<<" initialVth "<<initialVth[k]<<endl;
                vector<double> a(parameterNum);
                //second set of a for secant method which takes the averge between 2 consecutive guesses
                vector<double> a2(parameterNum);
                a[0] = initialIS[i];    a2[0] = (initialIS[i]+initialIS[i+1])/2;
                a[1] = initialk[j];     a2[1] = (initialk[i]+initialk[i+1])/2;
                a[2] = initialVth[k];   a2[2] = (initialIS[i]+initialIS[i+1])/2;
                vector<double> result = parameterExtraction(a, x, EKVmodel);
            }
        }
    }

}

