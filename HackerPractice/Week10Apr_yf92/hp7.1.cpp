//
//  main.cpp
//  Week13
//
//  Created by Yijia Chen and Yazhi Fan on 4/15/18.
//  Copyright © 2018 Yijia Chen and Yazhi Fan. All rights reserved.
//

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

int main()
{
    Matrix4f A;
    Vector4f b;
    A << -2,1,0,0,  1,-2,1,0,  0,1,-2,1, 0,0,1,-2;
    b << 0.2*0.2, 0, 0, 0;
    cout << "Here is the matrix A:\n" << A << endl;
    cout << "Here is the vector b:\n" << b << endl;
    Vector4f x = A.colPivHouseholderQr().solve(b);
    cout << "The solution is:\n" << x << endl;

    Matrix4f A2;
    Vector4f b2;
    A2 << -2,1,0,0,  1,-2,1,0,  0,1,-2,1, 0,0,1,-1;
    b2 << 0.2*0.2, 0, 0, 0;
    cout << "Here is the matrix A2:\n" << A2 << endl;
    cout << "Here is the vector b2:\n" << b2 << endl;
    Vector4f x2 = A2.colPivHouseholderQr().solve(b2);
    cout << "The solution is:\n" << x2 << endl;
}


