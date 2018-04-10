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

/*
   Some constants are used throughout the program.
   They are declared and explained here for convenience
*/
const double VSB = 0.0;       //S is shorted to B
const double VT = 26E-3;      //VT in volts

// ----------------------------------------------------------------------------------------

/* EKV function used to perform parameter extraction
   Smodel = ID(VGS, VDS; IS, k, Vth)
        Parameters:
                a: initial guess of the parameters IS, k, Vth
                xi: one measured set of all independent variables ID, VGS, VDS
        Return:
                the squared difference between EKVmodel and EKVmeasure for a single measurement
*/
double EKVmodel (vector<double> a, VectorXd xi);

// ----------------------------------------------------------------------------------------

/* EKV function with normalized ID used to perform parameter extraction
   Smodel = ID(VGS, VDS; IS, k, Vth) / IDmeasured
   similar to EKV model, but ID is calculated from VGS and VDS
        Parameters:
                a: initial guess of the parameters IS, k, Vth
                xi: one measured set of all independent variables VGS, VDS
        Return:
                the squared difference between EKVmodel and EKVmeasure for a single measurement
*/
double normalizedEKVmodel (vector<double> a, VectorXd xi);

// ----------------------------------------------------------------------------------------

/* get IDmodel from EKVmodel, can be used to validate result from EKV parameter extraction
        Parameters:
                VGS: VGS values in vector
                VDS: VDS values in vector
                a: IS, k, Vth  in a vector
        Return:
                the squared difference between EKVmodel and EKVmeasure for a single measurement
*/
vector <double> EKVmodel_getID (vector<double> a, vector<double> VGS, vector<double> VDS);

// ----------------------------------------------------------------------------------------

/* read text file and convert elements in file to a matrix
        Parameters:
                none
        Return:
                an Eigen::MatrixXd that contains all measured variables
                suppose there are n variables each with k measurements:
                [[x1(1) x1(2) ... x1(k)]
                 [x2(1) x2(2) ... x2(k)]
                 ......................
                 [xn(1) xn(2) ... xn(k)]]

*/
MatrixXd constructVariables ();

// ----------------------------------------------------------------------------------------

/* full grid for initial conditions, print out result from each search
        Parameters:
                initialIS: set of initial guess for IS
                initialk: set of initial guess for k
                initialVth: set of initial guess for Vth
        Return:
                none

*/
void fullGridSearch (vector<double> initialIS, vector<double> initialk, vector<double> initialVth );


#endif //LEASTSQUAREFITTING_EKV_H