#include <iostream>
#include <Eigen/Dense>
#include "forwardEuler.h"
#include "RK34.h"
#include "circuit.h"

using namespace std;
using namespace Eigen;

VectorXd f(double t, VectorXd x) {
    VectorXd result (x.size());
    result(0) = 4 * exp(0.8 * t) - 0.5 * x(0);
    return result;
}



int main() {
    MatrixXd result;
    VectorXd x (2);
    x << 1, 2;
    //result = RK34_adaptiveH(f, 2, 0, 5, 1);
    //result = forwardEuler(f, x, 0, 5, 1);

    f(1, x);
    result = RK34_adaptiveH(RCcircuit, x, 0, 100E-9, 0.2E-9);
    //result = forwardEuler(RCcircuit, x, 0, 100E-9, 0.2E-9);


    return 0;

}