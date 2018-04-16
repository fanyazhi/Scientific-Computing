//
//  Note6_hp5.cpp
//  Week13
//
//  Created by Yijia Chen and Yazhi Fan on 4/15/18.
//  Copyright © 2018 Yijia Chen and Yazhi Fan. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <list>
#include <sstream>

#define tol pow(10,-7)
#define ER pow(10,-6)
#define EA pow(10,-7)

using namespace std;


double dx(double t, double x){
    return 4*exp(0.8*t) - 0.5*x;
}

void RK34(double x[], double (*f)(double,double)){
    double xRK34[5]={2};//x(0)=2
    double xRK3[5]={2};
    double E[5]={0};
    double h[5]={1};
    double k1,k2,k3,k4;
    int t;
    for(t = 0; t<4; t++){            //construct x[i+1] E[i+1] h[i+1]
        k1 = f(t,xRK34[t]);
        k2 = f(t+1.0/2,xRK34[t]+k1*1.0/2);
        k3 = f(t+3*1.0/4,xRK34[t]+3*k2*1.0/4);
        k4 = f(t+1.0,xRK34[t]+k3*1.0);
        xRK3[t+1] = xRK34[t] + 1.0/9*(2*k1+3*k2+4*k3)*1; //RK3
        xRK34[t+1] = xRK34[t] + 1.0/24*(7*k1+6*k2+8*k3+3*k4)*1;  //RK4
        E[t+1] = E[t] + 1.0/72*(-5*k1+6*k2+8*k3+(-9)*k4)*1; //error estimator
        h[t+1] = 1*pow(ER/(abs(E[t+1])/abs(xRK34[t+1])+EA),1.0/3);
        
    }
    for(int i = 0; i < 5; i++){         //print out result
        cout<<xRK34[i]
        <<"    epsilon: "<<abs(xRK34[i]-x[i])/x[i]*100<<"% "
        <<" estimate error: "<<E[i]
        <<" Feasible time step: "<<h[i]<<endl;
    }
}


int main(){
    double xTrue[]={2.0000,6.1946,14.843,33.677,75.339};
    RK34(xTrue,dx);
    return 0;
}
