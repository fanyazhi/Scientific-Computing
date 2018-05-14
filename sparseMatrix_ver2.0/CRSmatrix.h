//
// Created by Jane Fan on 5/13/18.
//

#ifndef SPLINEFITTING_CRSMATRIX_H
#define SPLINEFITTING_CRSMATRIX_H

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct CRSmatrix {
    vector<double> value;
    vector<int> rowPtr;
    vector<int> colInd;
    int rowNum;
    int colNum;

    //CRSmatrix constructor with known elements
    CRSmatrix(vector<double> v, vector<int> r, vector<int> c);

    //CRSmatrix constructor with known dimensions
    CRSmatrix(int r, int c);

    //return value at [i][j]
    double retrieveElement (int i, int j);

    //insert value x at position [i][j]
    void changeValue (double x, int i, int j);

    //multiply matrix with a vector x
    vector<double> productAx(vector<double> x);

    //delete value at position [i][j]
    void deleteValue(int i, int j);

    //print CRSmatrix
    void printA();
} ;

vector<double> Jacobi(CRSmatrix A, vector<double> b);

#endif //SPLINEFITTING_CRSMATRIX_H
