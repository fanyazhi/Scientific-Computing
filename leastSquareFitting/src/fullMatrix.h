//
//  fullMatrix.h
//  Least Square Fitting
//
//  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/3/18.
//  Copyright © 2018 Yazhi and Yijia. All rights reserved.
//

#ifndef fullMatrix_h
#define fullMatrix_h

#include <vector>
using namespace std;


/* full square matrix
        Contents:
                size: dimension of the square matrix
                value: values in the matrix from first to last row and column
*/
struct Matrix
{
	int size;
	vector<double> value;
};


/* Creates the full square matrix
        Parameters:
                size: dimension of the square matrix
                value: values in the matrix from first to last row and column
        Return:
                a Matrix
*/
Matrix constructMatrix(int size, vector<double> x);

/* Prints the full square matrix for debugging purposes
        Parameters:
                matrix: matrix to be printed
        Return:
                none
*/
void printMatrix(Matrix matrix);

/* Multiplies Matrix A by vector x and returns the product
        Parameters:
                A: the pointer to the sparse matrix
                x: the pointer to vector x to multiply with A
        Return:
                a vector that contains the product of Ax
*/
vector<double> productAx(Matrix A, vector<double> x);


#endif