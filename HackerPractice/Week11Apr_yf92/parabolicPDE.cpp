//
//  parabolicPDE.cpp
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
double delta = 1;
double D = 1;
double f = 0;

int main() {
    MatrixXd n (5, 1);
    n << 0, 0, 10, 0, 0;

    MatrixXd A (5, 5);
    MatrixXd B (5, 5);

    for (int t = 1; t<7; t++){
        cout<<"t = "<<t-1<<endl;
        for (int i = 0; i<5; i++){
            A(i, i) = (1.0/delta)+(2.0*D/h/h);
            B(i, i) = (1.0/delta);
        }
        for (int i = 0; i<4; i++){
            A(i+1, i) = -1.0*D/h/h;
        }
        for (int i = 0; i<5; i++){
            cout<<n(i);
        }

        cout<<endl;

        n = B * A.inverse() * n;
    }

    return 0;
}