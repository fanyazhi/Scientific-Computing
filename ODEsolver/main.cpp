#include <iostream>
#include <Eigen/Dense>
#include "forwardEuler.h"
#include "RK34.h"

using namespace std;

double f(double t, double x){
    return 4*exp(0.8*t) - 0.5*x;
}

int main() {
    vector<double> result;
    result = RK34_adaptiveH(f, 2, 0, 4, 1);
    result = RK4(f, 2, 0, 4, 1);

    cout<<"RK4"<<endl;
    for(int i = 0; i<result.size(); i++){
        cout<<result[i]<<endl;
    }
    return 0;
}