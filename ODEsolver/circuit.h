//
// Created by Jane Fan on 4/20/18.
//

#ifndef ODESOLVER_CIRCUIT_H
#define ODESOLVER_CIRCUIT_H

#include <vector>
#include <iostream>
#include <cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

VectorXd RCcircuit(double t, VectorXd x);

double currentSource (double t);

#endif //ODESOLVER_CIRCUIT_H
