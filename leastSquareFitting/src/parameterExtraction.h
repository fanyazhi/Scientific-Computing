//
//  parameterExtraction.h
//  Least Square Fitting
//
//  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/3/18.
//  Copyright © 2018 Yazhi and Yijia. All rights reserved.
//

#ifndef LEASTSQUAREFITTING_PARAMETEREXTRACTION_H
#define LEASTSQUAREFITTING_PARAMETEREXTRACTION_H

#include <vector>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

typedef double (*T)(vector<double>, VectorXd);

// ----------------------------------------------------------------------------------------

/* (Smodel - Smeasure)^2
   the squared difference of each measured independent variables
        Parameters:
                a: set of meaningful parameters
                xi: the measured set of an independent variable

        Return:
                the squared difference between Smodel and Smeasure for a single measurement
*/
double f(vector<double> a, VectorXd xi);

// ----------------------------------------------------------------------------------------

/* sum[(Smodel - Smeasure)^2]
   the sum of squared differences of all measured independent variables
        Parameters:
                a: set of meaningful parameters
                x: the measured independent variables contained in a matrix
                   number of rows = number of independent variables
                   number of columns = number of measurements for a variable
        Return:
                the sum of squared difference between Smodel and Smeasure for all measurements
*/
double V(vector<double> a, MatrixXd x, T f);

// ----------------------------------------------------------------------------------------

/* parameter extraction with quansi-Newton method
        Parameters:
                a: initial guess of the parameters
                x: the measured independent variables contained in a matrix
                   number of rows = number of independent variables
                   number of columns = number of measurements for a variable
        Return:
                resulted parameters after least squared fitting
*/
vector<double> parameterExtraction(vector<double> a, MatrixXd x, T f);

// ----------------------------------------------------------------------------------------

/* parameter extraction with secant method
        Parameters:
                aPrevious: initial guess of the first set of parameters
                a: initial guess of the second set of parameters
                x: the measured independent variables contained in a matrix
                   number of rows = number of independent variables
                   number of columns = number of measurements for a variable
        Return:
                resulted parameters after least squared fitting
*/
vector<double> parameterExtraction_Secant(vector<double> aPrevious, vector<double> a, MatrixXd x, T f);

// ----------------------------------------------------------------------------------------

/* delta x[] = -[H(x)]^(-1) * divergence[V(x)]
   computes the delta x used in Newton method for searching the optimal value of V
        Parameters:
                a: set of meaningful parameters
                x: the measured independent variables contained in a matrix
                   number of rows = number of independent variables
                   number of columns = number of measurements for a variable
        Return:
                delta x for the next iteration
*/
vector<double> getDelta(vector<double> a, MatrixXd x, T f);

// ----------------------------------------------------------------------------------------

/* delta x[] = -[J(x)]^(-1) * divergence[V(x)]
   computes the delta x used in secant method for searching the optimal value of V
        Parameters:
                aPrevious: initial guess of the first set of parameters
                a: initial guess of the second set of parameters
                x: the measured independent variables contained in a matrix
                   number of rows = number of independent variables
                   number of columns = number of measurements for a variable
        Return:
                delta x for the next iteration
*/
vector<double> getDelta_Secant(vector<double> aPrevious, vector<double> a, MatrixXd x, T f);

// ----------------------------------------------------------------------------------------

/* takes the partial derivative of f with respect to a[d] using finite difference
        Parameters:
                a: set of meaningful parameters
                d: index for the parameter to take derivative with respect to
                x: the measured independent variables contained in a matrix
                   number of rows = number of independent variables
                   number of columns = number of measurements for a variable
        Return:
                numerical partial derivative
*/
double partialDerivative(vector<double> a, int d, MatrixXd x, T f);

// ----------------------------------------------------------------------------------------

/* takes the double derivative of f with respect to a[d1] and a[d2] using finite difference
        Parameters:
                a: set of meaningful parameters
                d1: index for the parameter to take derivative with respect to
                d2: index for the parameter to take derivative with respect to
                x: the measured independent variables contained in a matrix
                   number of rows = number of independent variables
                   number of columns = number of measurements for a variable
        Return:
                numerical double derivative
*/
double doubleDerivative(vector<double> a, int d1, int d2, MatrixXd x, T f);

// ----------------------------------------------------------------------------------------

/* computes the norm of a set of values by taking the square root of the sum squared
        Parameters:
                a: set of values
        Return:
                norm of a[]
*/
double norm(vector<double> a);


#endif //LEASTSQUAREFITTING_PARAMETEREXTRACTION_H
