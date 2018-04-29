//
//  advection.cpp
//
//  Created by Yijia Chen and Yazhi Fan on 4/29/18.
//  Copyright © 2018 Yijia Chen and Yazhi Fan. All rights reserved.
//
#include <iostream>
#include <cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

double h = 1;
double delta_x = 1;
double delta_t = 1;
double v = 1;
double D = 1;
double f = 0;

int main() {
    MatrixXd n (7, 1);
    n << 0, 0, 10, 0, 0, 0, 0;

    MatrixXd A (7, 7);
    MatrixXd B (7, 7);

    for (int t = 1; t<7; t++){
        cout<<"t = "<<t-1<<endl;
        for (int i = 0; i<7; i++){
            A(i, i) = (1.0/delta_t)+(2.0*D/delta_x);
            B(i, i) = (1.0/delta_t);
        }
        for (int i = 0; i<4; i++){
            A(i+1, i) = -1.0*D/delta_x;
        }
        for (int i = 0; i<7; i++){
            cout<<n(i);
        }

        cout<<endl;

        n = B * A.inverse() * n;
    }

    return 0;
}