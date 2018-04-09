//
//  parameterExtraction.h
//  Least Square Fitting
//
//  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/3/18.
//  Copyright © 2018 Yazhi and Yijia. All rights reserved.
//

#include "EKV.h"
#include "parameterExtraction.h"
#include "validation.h"
#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// ----------------------------------------------------------------------------------------

//double f(vector<double> a, VectorXd xi){
//    return pow(log(a[0])+a[1]*log(xi(0))-log(xi(1)),2);
//}


//Smodel = ID(VGS, VDS; IS, k, Vth)

int main()
{
    //Declare initial guesses
    //IS, k, Vth
    vector<double> a{10E-7, 0.902, 1};

    MatrixXd x = constructVariables ();

    vector<double> result = parameterExtraction(a, x, EKVmodel);


    return 0;
}


//    MatrixXd x (2, 6);
//    x << 1.0, 4.5, 9.0, 20, 74, 181,
//            3.0, 49.4, 245, 1808, 2.2E4, 7.3E4;


//    IOFormat HeavyFmt(FullPrecision, 0, ", ", ";\n", "[", "]", "[", "]");
//    cout << x.format(HeavyFmt) <<endl;

//vector<double> result = parameterExtraction_Secant(aPrevious, a, x);