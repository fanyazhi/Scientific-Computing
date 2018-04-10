//
//  test.h
//  Least Square Fitting
//
//  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/7/18.
//  Copyright © 2018 Yazhi and Yijia. All rights reserved.
//

#ifndef LEASTSQUAREFITTING_VALIDATION_H
#define LEASTSQUAREFITTING_VALIDATION_H

#include <vector>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

/* test file contains validations for parameter extraction and EKV model.
   There are two major tests: validation for power law model and asymptotic testing for EKV model.

   Validation for power law y = c0*x^a (task 2)
   a set of x and y are generated with known parameter a and m
   and parameter extraction method is called to find a and m with the generated x and y
   result from parameter extraction is compared with ground truth

   asymptotic testing for EKV (task 7)
   checks if result from IDmodel conforms with the expected regional behavior:
   1. when VGS < Vth, ID should be an exponential function of VGS and insensitive to VDS
   2. When VGS > Vth and VDS > VDsat, ID should be a quadratic function to VGS and insensitive to VDS
   3. When VGS > Vth and VDS < VDsat, ID should be a quadratic function
*/

// ----------------------------------------------------------------------------------------

/* Validation of the parameter extraction method for power law y = c0*x^a
        Parameters:
                none
        Return:
                none
*/
void powerLawValidation();

// ----------------------------------------------------------------------------------------

/* power law function y = c0*x^a in linearized form used in powerLawValidation
        Parameters:
                a: set of meaningful parameters
                xi: one measured set of all independent variables

        Return:
                the squared difference between Smodel and Smeasure for a single measurement
*/
double powerFunc (vector<double> a, VectorXd xi);

// ----------------------------------------------------------------------------------------

/* random number generator
        Parameters:
                fMin: minimum possible random number
                fMax: maxmum possible random number

        Return:
                a random double valued between fMin and fMax
*/
double fRand(double fMin, double fMax);

// ----------------------------------------------------------------------------------------

/* checks if result from IDmodel conforms with the expected regional behavior
        Parameters:
                VGS: VGS values in vector
                VDS: VDS values in vector
                a: IS, k, Vth  in a vector
        Return:
                none
*/
void asymptoticCheck (vector<double> a, vector<double> VGS, vector<double> VDS);

// ----------------------------------------------------------------------------------------

/* helper function for asymptoticCheck, calculates ID in exponential form
        Parameters:
                VGS: VGS value
                VDS: VDS value
                a: IS, k, Vth  in a vector
        Return:
                none
*/
double IDexp(vector<double> a, double VGS, double VDS);

// ----------------------------------------------------------------------------------------

/* helper function for asymptoticCheck, calculates ID in quadratic form
        Parameters:
                VGS: VGS value
                VDS: VDS value
                a: IS, k, Vth  in a vector
        Return:
                none
*/
double IDquad(vector<double> a, double VGS, double VDS);

#endif //LEASTSQUAREFITTING_VALIDATION_H
