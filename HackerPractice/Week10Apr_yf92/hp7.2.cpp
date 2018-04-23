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

typedef Matrix<double, 9, 9> Matrix9f;
typedef Matrix<double, 9, 1> Vector9f;

int main()
{
    double h = 10E-9;
    double Nd = 1E15;
    double Na = 1E17;
    double ni = 1.5E10;
    double epic = 1.03E-12;
    double Ld = 2.4E-3;
    double Vt = 2.6E-2;
    double phi[10]={0};
    Matrix9f A;
    Vector9f b;
    
    for(int i=0; i < 9; i++){
        A(i,i) = -4 - h*h*(exp(-phi[i])+exp(phi[i]));
    }
    A(1,0) = 1;
    A(0,1) = 0;
  
    h = h/Ld;
    
    b(0) = -4*phi[1] + phi[2] + phi[4] + h*h*Nd +2*phi[0];
    b(1) = phi[1] - 4*phi[2] + phi[3] + phi[5] + h*h*Nd;
    b(2) = phi[2] - 4*phi[3] + phi[6] - h*h*Na;
    b(3) = phi[1] - 4*phi[4] + phi[5] + phi[7] + h*h*Nd;
    b(4) = phi[2] + phi[4] -4*phi[5] + phi[6] + phi[8] - h*h*Na;
    b(5) = phi[3] + phi[5] -4*phi[6] + phi[9] - h*h*Na;
    b(6) = phi[4] - 4*phi[7] + phi[8] - h*h*Na;
    b(7) = phi[5] + phi[7] -4*phi[8] + phi[9] - h*h*Na;
    b(8) = phi[6] + phi[8] - 4*phi[9] -h*h*Na;
    
    Vector9f x = A.colPivHouseholderQr().solve(-b);
    cout << "delta\n" << x << endl;


}


