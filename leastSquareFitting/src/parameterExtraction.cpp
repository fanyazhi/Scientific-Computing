//
//  parameterExtraction.cpp
//  Least Square Fitting
//
//  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/3/18.
//  Copyright © 2018 Yazhi and Yijia. All rights reserved.
//

#include "parameterExtraction.h"
#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

const double x[] = {1.0, 4.5, 9.0, 20, 74, 181 };
const double y[] = {3.0, 49.4, 245, 1808, 2.2E4, 7.3E4};
double p = 0.0001; //perturbation


double V(double a, double m){
    double v = 0;
    for (int i = 0; i<6; i++){
        v += pow(log(a)+m*log(x[i])-log(y[i]),2);
    }
    return v;
}

double dVdx1(double a, double m){
    double sum = 0;
    for (int i = 0; i<6; i++){
        sum += 2*log(x[i])*(log(a)+m*log(x[i])-log(y[i]));
    }

    return sum;
}

double dVdx2(double a, double m){
    double sum = 0;
    for (int i = 0; i<6; i++){
        sum += 2*(log(a)+m*log(x[i])-log(y[i]));
        //sum += ((log(a)+(1+p)*m*log(x[i])-log(y[i]))-(log(a)+m*log(x[i])-log(y[i])))/(p*m);
    }
    return sum;
}

double delta1(double x1, double x2){
    double J12 = 0, J21 = 0, J11 = 0, J22 = 0;
    for (int i = 0; i<6; i++){
        J11 += (V(x1*(1+p)*(1+p),x2)-2*V(x1*(1+p), x2)+V(x1, x2))/(p*x1*p*x1);
        J12 += (V(x1*(1+p),x2*(1+p))-2*V(x1, x2*(1+p))+V(x1, x2))/(p*x1*p*x2);
        J21 += (V(x1*(1+p),x2*(1+p))-2*V(x1*(1+p), x2)+V(x1, x2))/(p*x1*p*x2);
        J22 += (V(x1,x2*(1+p)*(1+p))-2*V(x1, x2*(1+p))+V(x1, x2))/(p*x2*p*x2);
    }
    return (-1.0/(J11*J22-J12*J21))*(J22*dVdx1(x1, x2)-J12*dVdx2(x1, x2));
}
double delta2(double x1, double x2){
    double J12 = 0, J21 = 0, J11 = 0, J22 = 0;
    for (int i = 0; i<6; i++){
        J11 += (V(x1*(1+p)*(1+p),x2)-2*V(x1*(1+p), x2)+V(x1, x2))/(p*x1*p*x1);
        J12 += (V(x1*(1+p),x2*(1+p))-2*V(x1, x2*(1+p))+V(x1, x2))/(p*x1*p*x2);
        J21 += (V(x1*(1+p),x2*(1+p))-2*V(x1*(1+p), x2)+V(x1, x2))/(p*x1*p*x2);
        J22 += (V(x1,x2*(1+p)*(1+p))-2*V(x1, x2*(1+p))+V(x1, x2))/(p*x2*p*x2);
    }
    return (-1.0/(J11*J22-J12*J21))*(-J21*dVdx1(x1, x2)+J11*dVdx2(x1, x2));
}

double norm(double a, double b){
    return sqrt(pow(a,2)+pow(b, 2));
}

int main(){
    double x1 = 2; double x2 = 1;
    int count1= 0;
    double t = 0.5;
    double threshold = 1E-7;
    cout<<"when xi(0) = (0,0): "<<endl;
    while(norm(delta1(x1, x2), delta2(x1, x2)) > threshold && V(x1+t*delta1(x1, x2), x2+t*delta2(x1, x2))<=V(x1, x2)+1E-5 || V(x1, x2) >0.5){
        cout<<"x1: "<<x1<<" x2: "<<x2<<" delta(x) norm: "<<norm(delta1(x1, x2), delta2(x1, x2))<<" V: "<<V(x1, x2)<<" t: "<<t<<endl;
        x1 += t*delta1(x1, x2);
        x2 += t*delta2(x1, x2);
        count1++;
    }


    cout<<"when xi(0) = (0,0), converges after "<<count1<<" iterations"<<endl;
    cout<<x1<<" "<<x2<<" "<<V(x1, x2)<<endl;


    cout<<"test"<<endl;
    for (int i = 0; i<6; i++){
        cout<<x1*pow(x[i],x2)-y[i]<<endl;
    }
    return 0;
}
