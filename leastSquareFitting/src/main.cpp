//
//  parameterExtraction.h
//  Least Square Fitting
//
//  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/3/18.
//  Copyright © 2018 Yazhi and Yijia. All rights reserved.
//

#include "parameterExtraction.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// ----------------------------------------------------------------------------------------

int main()
{


//read in x1{}, x2{}, and Smeasured{}

    MatrixXd x (2, 6);
    x << 1.0, 4.5, 9.0, 20, 74, 181,
            3.0, 49.4, 245, 1808, 2.2E4, 7.3E4;

    //Declare initial guesses
    vector<double> a{2.8, 1.8};

    vector<double> result = parameterExtraction(a, x);

    return 0;
}