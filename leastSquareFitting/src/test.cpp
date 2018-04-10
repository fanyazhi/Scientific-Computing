//
//  test.cpp
//  Least Square Fitting
//
//  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/7/18.
//  Copyright © 2018 Yazhi and Yijia. All rights reserved.
//

#include "test.h"
#include "EKV.h"
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

void asymptoticCheck (vector<double> a, vector<double> VGS, vector<double> VDS) {
    double allowedError = 0.5; //max ||error|| allowed
    vector<double> zeroVDS (VGS.size());
    double expError = 0; //sum of relative error during exponential region
    double quadError = 0; //sum of relative error during quadratic region
    double insensitivityError = 0; //sum of errors in insensitivity to VDS

    //loop through all value points
    for (int i = 0; i < VGS.size(); i++){
        //calculate VDsat
        double VDsat = a[1]*(VGS[i] - threshold) - VSB;

        //when VGS < Vth, ID should be an exponential function of VGS and insensitive to VDS
        if (VGS[i] < a[2]){
            //add relative error to error sum. Checks the condition if denominator is 0.
            if (EKVmodel_getID(a, VGS, VDS)[i] != 0) {
                expError += pow((IDexp(a, VGS[i], VDS[i]) - EKVmodel_getID(a, VGS, VDS)[i]), 2) /
                            EKVmodel_getID(a, VGS, VDS)[i];
                insensitivityError += pow((EKVmodel_getID(a, VGS, zeroVDS)[i] - EKVmodel_getID(a, VGS, VDS)[i]), 2) /
                            EKVmodel_getID(a, VGS, VDS)[i];
            }else {
                expError += pow((IDexp(a, VGS[i], VDS[i]) - EKVmodel_getID(a, VGS, VDS)[i]), 2);
                insensitivityError += pow((EKVmodel_getID(a, VGS, zeroVDS)[i] - EKVmodel_getID(a, VGS, VDS)[i]), 2);
            }

        }
        //When VGS > Vth and VDS > VDsat, ID should be a quadratic function to VGS and insensitive to VDS
        else if (VDS[i] > VDsat){
            if (EKVmodel_getID(a, VGS, VDS)[i] != 0) {
                quadError += pow((IDquad(a, VGS[i], VDS[i]) - EKVmodel_getID(a, VGS, VDS)[i]), 2) /
                             EKVmodel_getID(a, VGS, VDS)[i];
                insensitivityError += pow((EKVmodel_getID(a, VGS, zeroVDS)[i] - EKVmodel_getID(a, VGS, VDS)[i]), 2) /
                                      EKVmodel_getID(a, VGS, VDS)[i];
            }else {
                quadError += pow((IDquad(a, VGS[i], VDS[i]) - EKVmodel_getID(a, VGS, VDS)[i]), 2);
                insensitivityError += pow((EKVmodel_getID(a, VGS, zeroVDS)[i] - EKVmodel_getID(a, VGS, VDS)[i]), 2);
            }
        }
        //When VGS > Vth and VDS < VDsat, ID should be a quadratic function
        else {
            if (EKVmodel_getID(a, VGS, VDS)[i] != 0) {
                quadError += pow((IDquad(a, VGS[i], VDS[i]) - EKVmodel_getID(a, VGS, VDS)[i]), 2) /
                             EKVmodel_getID(a, VGS, VDS)[i];
            }else {
                quadError += pow((IDquad(a, VGS[i], VDS[i]) - EKVmodel_getID(a, VGS, VDS)[i]), 2);
            }
        };
    }

    //compare relative error to allowed error and print out result
    cout<<"------------------------------------"<<endl;
    cout<<"ASYMPTOTIC VALIDATION RESULT"<<endl;
    if (expError/VGS.size() < allowedError){
        cout<<"VGS < Vth: ID behaves as an exponential function of VGS with ||error|| = "
              <<expError/VGS.size()<<endl;
    }else{
        cout<<"VGS < Vth: ID DOES NOT behave as an exponential function of VGS with ||error|| = "
              <<expError/VGS.size()<<endl;
    }

    if (quadError/VGS.size() < allowedError) {
        cout << "VGS > Vth: ID behaves as an quadratic function to VGS with ||error|| = "
                <<quadError/VGS.size()<<endl;
    }else{
        cout<<"VGS > Vth: ID DOES NOT behave as a quadratic function to VGS with ||error|| = "
              <<quadError/VGS.size()<<endl;
    }

    if (insensitivityError/VGS.size() < allowedError) {
        cout<<"VGS < Vth or VDS > VDsat : ID is insensitive to VDS with ||error|| = "
            <<expError/VGS.size()<<endl;
    }else{
        cout<<"VGS < Vth or VDS > VDsat : ID is NOT insensitive to VDS with ||error|| = "
            <<expError/VGS.size()<<endl;
    }
}

double IDexp(vector<double> a, double VGS, double VDS){
    //IDexp = Is*exp( (k*(VGS - Vth)) / VT) - Is*exp( (k*(VGS - Vth) - VDS) / VT);
    return a[0]*exp( (a[1]*(VGS - a[2])) / VT) - a[0]*exp( (a[1]*(VGS - a[2]) - VDS) / VT);

}

double IDquad(vector<double> a, double VGS, double VDS){
    //IDquad = Is*pow( (k*(VGS - Vth)) / (2*VT) , 2) - Is*pow( (k*(VGS - Vth) - VDS) / (2*VT) , 2);
    return a[0]*pow( (a[1]*(VGS - a[2])) / (2*VT) , 2) - a[0]*pow( (a[1]*(VGS - a[2]) - VDS) / (2*VT) , 2);
}