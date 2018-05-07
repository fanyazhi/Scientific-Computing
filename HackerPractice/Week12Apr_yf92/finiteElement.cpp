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

typedef Matrix<double, 10, 10> Matrix10f;
typedef Matrix<double, 10, 1> Vector10f;

int main()
{
    double h = 0.1;
    Matrix10f A;
    Vector10f b;
    
    for(int i=0; i < 10; i++){
        A(i,i) = -2;
        b(i) = -1*h*2;
    }
    
    for(int j = 0; j < 9; j++){
        A(j+1,j) = 1;
        A(j,j+1) = 1;
    }
    
    Vector10f x = A.colPivHouseholderQr().solve(b);
    cout << "delta\n" << x << endl;


}


