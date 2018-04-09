#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <list>
#include <sstream>

#define tol pow(10,-7)
using namespace std;


double dx(double t, double x){
    return 4*exp(0.8*t) - 0.5*x;
}

void  forwardEuler(double x[]){
    double xForward[5]={2};//x(0)=2
    for(int t = 0; t < 4; t++)//h=1
        xForward[t+1] = xForward[t] + dx(t,xForward[t]);
    cout<<"forward Eular:"<<endl;
    for(int i = 0; i < 5; i++){
        cout<<xForward[i]<<"    epsilon: "
        <<abs(xForward[i]-x[i])/x[i]*100<<"%"<<endl;
    }
}

void huneOne(double x[]){
    double xHuneOne[5]={2};
    for(int t = 0; t < 4; t++){
        xHuneOne[t+1] = xHuneOne[t] + dx(t,xHuneOne[t]);
        xHuneOne[t+1] = xHuneOne[t] +
                        (dx(t+1,xHuneOne[t+1])+dx(t,xHuneOne[t]))/2;
    }
    cout<<"Hune one step:"<<endl;
    for(int i = 0; i < 5; i++){
        cout<<xHuneOne[i]<<"    epsilon: "
        <<abs(xHuneOne[i]-x[i])/x[i]*100<<"%"<<endl;
    }
}

double epcilon(double x2, double x1){
    return abs((x2-x1)/x2);
}

void huneIterator(double x[]){
    double xHuneItr[5]={2};
    double temp;
    for(int t = 0; t < 4; t++){
        xHuneItr[t+1] = xHuneItr[t] + dx(t,xHuneItr[t]);//predictor,j=0
        temp = xHuneItr[t+1];
        xHuneItr[t+1] = xHuneItr[t] +                   //corrector
        (dx(t+1,xHuneItr[t+1])+dx(t,xHuneItr[t]))/2;
        while(epcilon(xHuneItr[t+1], temp) >= tol){     //iteration
            temp = xHuneItr[t+1];
            xHuneItr[t+1] = xHuneItr[t] +
            (dx(t+1,xHuneItr[t+1])+dx(t,xHuneItr[t]))/2;
        }
    }
    cout<<"Hune Iterator:"<<endl;
    for(int i = 0; i < 5; i++){
        cout<<xHuneItr[i]<<"    epsilon: "
        <<abs(xHuneItr[i]-x[i])/x[i]*100<<"%"<<endl;
    }
}


int main(){
    double xTrue[]={2.0000,6.1946,14.843,33.677,75.339};
    forwardEuler(xTrue);
    huneOne(xTrue);
    huneIterator(xTrue);
    return 0;
}





