#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdio>

using namespace std;

double f(double t){
    return exp(-t);
}

void backwardEuler(double delta, double init){
    int n = 20/delta;
        cout<<"back ward Euler delta = " <<delta<<endl;
        double *arr = new double[n];
        arr[0] = init;
        for(int j = 0; j < 20/delta-1; j++){
            arr[j+1] = arr[j]/(1+delta);
            cout<<arr[j+1]<<endl;
        }
}

void trapezoidalEuler(double delta, double init){
    int n = 20/delta;
    cout<<"trapezoidal Euler delta = " << delta<<endl;
    double *arr = new double[n];
    arr[0] = init;
    for(int j = 0; j < 20/delta-1; j++){
        arr[j+1] = (2-delta)/(2+delta)*arr[j];
        cout<<arr[j+1]<<endl;
    }
}

int main(){
    double t;
    double delta[]={0.5, 0.1};
    for(int i = 0; i < sizeof(delta)/sizeof(delta[0]); i++){
        cout<<"groud truth delta = "<<delta[i]<<endl;
        for(t=0; t<=20; t+=delta[i]){  //calculate the ground truth
            cout<<f(t)<<endl;
        }
        backwardEuler(delta[i],1);  //backwardEuler
        trapezoidalEuler(delta[i],1); // trapezoidal Euler
    }
    
    return 0;
}












