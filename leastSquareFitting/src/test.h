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


#endif //LEASTSQUAREFITTING_VALIDATION_H
