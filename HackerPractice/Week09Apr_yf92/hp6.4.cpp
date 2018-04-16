
//
//  Note6_hp4.cpp
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

using namespace std;


double dx(double t, double x){
    return 4*exp(0.8*t) - 0.5*x;
}

/* default h=1 */
void RK4(double x[], double h, double (*f)(double,double)){
    double xRK4[5]={2};//x(0)=2
    double k1,k2,k3,k4;
    int t;
    for(t = 0; t<4; t++){            //construct x[i+1]
        k1 = f(t,xRK4[t]);
        k2 = f(t+h/2,xRK4[t]+k1*h/2);
        k3 = f(t+h/2,xRK4[t]+k2*h/2);
        k4 = f(t+h,xRK4[t]+k3*h);
        xRK4[t+1] = xRK4[t] + 1.0/6*(k1+2*k2+2*k3+k4)*h;
    }
    for(int i = 0; i < 5; i++){         //print out result
        t = i;
        k1 = f(t,xRK4[i]);
        k2 = f(t+h/2,xRK4[i]+k1*h/2);
        k3 = f(t+h/2,xRK4[i]+k2*h/2);
        k4 = f(t+h,xRK4[i]+k3*h);
        cout<<xRK4[i]<<" k1: "<<k1<<" k2: "<<k2<<" k3: "<<k4<<" k4: "<<k4
        <<"    epsilon: "
        <<abs(xRK4[i]-x[i])/x[i]*100<<"%"<<endl;
    }
}

int main(){
    double xTrue[]={2.0000,6.1946,14.843,33.677,75.339};
    RK4(xTrue,1,dx);
    return 0;
}


