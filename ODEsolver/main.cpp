/*
 *  main.cpp
 *  ODESolver
 *
 *
 *  Created by Yijia Chen (yc2366) and Yazhi Fan (yf92) on 4/18/18.
 *  Copyright © 2018 Yijia and Yazhi. All rights reserved.
 *
 */

#include <iostream>
#include <Eigen/Dense>
#include "forwardEuler.h"
#include "RK34.h"
#include "circuit.h"
#include "test.h"

using namespace std;
using namespace Eigen;

int main() {
    MatrixXd result;
    VectorXd x (2);
    x << 2.5, 2.5;
    //result = RK34_adaptiveH(f, 2, 0, 5, 1);
    //result = forwardEuler(f, x, 0, 5, 1);

    result = RK34_adaptiveH(CSamplifier, x, 0, 100E-9, 0.2E-9);
    //result = forwardEuler(CSamplifier, x, 0, 100E-9, 0.2E-9);

    for (int i = 0; i<result.cols(); i++) {
        cout << result(1, i) << endl;
    }

    return 0;

}