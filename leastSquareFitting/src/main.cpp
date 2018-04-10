//
//  parameterExtraction.h
//  Least Square Fitting
//
//  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/3/18.
//  Copyright © 2018 Yazhi and Yijia. All rights reserved.
//

#include "EKV.h"
#include "parameterExtraction.h"
#include "test.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// ----------------------------------------------------------------------------------------
/* Below is an example use of some major functions in Least Square Fitting.
   The example performs quasi-Newton parameter extraction on an EKV model
   and does asymptotic validation on the result parameters.
*/

int main()
{
    //Declare initial guess {IS, k, Vth}
    vector<double> a{1E-6 , 1.0 , 1.0 };

    //read variable measurements
    MatrixXd x = constructVariables ();

    //perform parameter extraction
    vector<double> result = parameterExtraction(a, x, EKVmodel);

    //Get IDmodel from resulted parameters
    int points = 1010;                      //total data points wanted
    vector<double> IDmodel (points);

    //get VGS and VDS from x
    vector<double> VGS (points);
    vector<double> VDS (points);
    for (int i = 0; i < points; i++){
        VGS[i] = (x.row(0))[i];
        VDS[i] = (x.row(1))[i];
    }
    IDmodel = EKVmodel_getID (result, VGS, VDS);

    //asymptotic validation on IDmodel
    asymptoticCheck (result, VGS, VDS);

    return 0;
}
