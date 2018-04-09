//
//  EKV.h
//  Least Square Fitting
//
//  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/7/18.
//  Copyright © 2018 Yazhi and Yijia. All rights reserved.
//

#ifndef LEASTSQUAREFITTING_EKV_H
#define LEASTSQUAREFITTING_EKV_H

#include <vector>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

// ----------------------------------------------------------------------------------------

double EKVmodel (vector<double> a, VectorXd xi);

MatrixXd constructVariables ();

#endif //LEASTSQUAREFITTING_EKV_H