//
//  fullMatrix.cpp
//  Least Square Fitting
//
//  Created by Yazhi Fan (yf92) and Yijia Chen (yc2366) on 4/3/18.
//  Copyright © 2018 Yazhi and Yijia. All rights reserved.
//

#include "fullMatrix.h"
#include <iostream>
#include <vector>
#include "cmath"
#include <cstdio>
using namespace std;


Matrix constructMatrix(int size, vector<double> x) {
    //initiate variables of a matrix
    Matrix myMatrix;
    myMatrix.size = size;
    myMatrix.value = x;
    return myMatrix;
}

void printMatrix(Matrix matrix){
    // Loop through rows and columns to display all values
    for (int row = 0; row < matrix.size; row++) {
        for (int col = 0; col < matrix.size; col++) {
            cout <<matrix.value[col+row*matrix.size] << " ";
        }
        cout << endl;
    }
}

vector<double> productAx(Matrix A, vector<double> x){
    //initialize empty vector b
    vector<double> b;
    //multiply A and x and push result to b
    for (int row = 0; row < A.size; row++) {
        double sum = 0;
        for (int col = 0; col < A.size; col++) {
            sum +=A.value[col + row * A.size] * x[col];
        }
        b.push_back(sum);
    }
    return b;
}

