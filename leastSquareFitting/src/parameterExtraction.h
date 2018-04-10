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

// ----------------------------------------------------------------------------------------

/*
   Some constants are used throughout parameter extraction.
   They are declared and explained here for convenience
*/
const double p = 0.0001;          //the perturbation used in finite difference derivative approximation

const double quadTol = 0.2;       //tolerance for quadratic convergence check

const double threshold = 1E-7;   //Stop condition: threshold on delta x norm to confirm convergence

const double maxIteration = 1E7;  //Stop condition: max number of iterations allowed to prevent infinite iterations

const double acceptableV = 0.1;   /* Stop condition: when delta x threshold is difficult to find,
                                    V has stopped decreasing, and ||V||2 has reached acceptableV, assume convergence occurred
                                    Note that acceptable V is only a safe check
                                    ||V||2 can can go beyond this value as long as it is still converging
                                 */

// ----------------------------------------------------------------------------------------

//alias type name for a model function
typedef double (*T)(vector<double>, VectorXd);

// ----------------------------------------------------------------------------------------

/* parameter extraction with quasi-Newton method
        Parameters:
                a: initial guess of the parameters
                x: the measured independent variables contained in a matrix
                   number of rows = number of independent variables
                   number of columns = number of measurements for a variable
                f: model function
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
                f: model function
        Return:
                resulted parameters after least squared fitting
*/
vector<double> parameterExtraction_Secant(vector<double> aPrevious, vector<double> a, MatrixXd x, T f);

// ----------------------------------------------------------------------------------------

/* sum[(Smodel - Smeasure)^2]
   the sum of squared differences of all measured independent variables
        Parameters:
                a: set of meaningful parameters
                x: the measured independent variables contained in a matrix
                   number of rows = number of independent variables
                   number of columns = number of measurements for a variable
                f: model function
        Return:
                the sum of squared difference between Smodel and Smeasure for all measurements
*/
double V(vector<double> a, MatrixXd x, T f);

// ----------------------------------------------------------------------------------------

/* delta x[] = -[H(x)]^(-1) * divergence[V(x)]
   computes the delta x used in Newton method for searching the optimal value of V
        Parameters:
                a: set of meaningful parameters
                x: the measured independent variables contained in a matrix
                   number of rows = number of independent variables
                   number of columns = number of measurements for a variable
                f: model function
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
                f: model function
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
                f: model function
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
                f: model function
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
