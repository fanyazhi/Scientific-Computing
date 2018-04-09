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
#include <cmath>
#include <vector>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// ----------------------------------------------------------------------------------------


int main()
{
    //Declare initial guesses
    //IS, k, Vth
    vector<double> a{1.6E-06 , 0.6 , 0.25 };
    vector<double> a2{1.58e-06 , 0.58 , 0.253 };
    //vector<double> a{1.58029e-06 , 0.571274 , 0.2533 };
    //vector<double> a{8.81137e-07, 0.429298, 1.35112};
    MatrixXd x = constructVariables ();
    vector<double> result = parameterExtraction_Secant(a, a2, x, normalizedEKVmodel);



    return 0;
}




//    IOFormat HeavyFmt(FullPrecision, 0, ", ", ";\n", "[", "]", "[", "]");
//    cout << x.format(HeavyFmt) <<endl;

//vector<double> result = parameterExtraction_Secant(aPrevious, a, x);