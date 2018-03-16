#pragma once
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cfloat>
#include <ctime>
#include <fstream>
#include <limits>
#include <list>
#include <iostream>
#include <iterator>
#include <stdlib.h> 

using namespace std;
/*************************** Function Definitions ****************************/

/**
 * list and array helper functions in list.cpp
 * each function has two versions, one for double array and one for integer array
 * double array is used for value[], and integer array is used for colInd[] and rowPrt[]
*/
void arrToList(double arr[], int arrSize, list<double>& mylist);
void arrToListInt(int arr[], int arrSize, list<int>& mylist);
void listToArr(double arr[], list<double> mylist);
void listToArrInt(int arr[], list<int> mylist);
void arrSwap(double arr[], int arrSize, int i1, int i2, int j1, int j2);
void arrSwapInt(int arr[], int arrSize, int i1, int i2, int j1, int j2);
void arrInsert(double *arr[], int&arrSize, int pos, double a);
void arrInsertInt(int *arr[], int&arrSize, int pos, int a);
void arrRemove(double *arr[], int&arrSize, int pos);
void arrRemoveInt(int *arr[], int&arrSize, int pos);
bool compareArr(double first[], int firstSize, double second[], int secondSize, double e);
bool compareArrInt(int first[], int firstSize, int second[], int secondSize);
void testList();

/**
functions in fullMatrixSolver.cpp
*/
void fullRowScale(double A[5][5], int i, int j, int c, double a);
void fullSolve(double A[5][5], double x[], double b[], int r, int c);
void testFullMatrixSolver();

/**
various helper functions in norms.cpp
*/
double infinityNorm(double value[], int rowPtr[], int rowPtrSize);
double firstNorm(double value[], int colInd[], int colIndSize);
double vectorNorm(double b[], int bSize);
int colNum(int colInd[], int colIndSize);
double add1Col(double value[], int c, int colInd[], int colIndSize);
double add1Row(double value[], int rowPtr[], int r);
bool compareDouble(double first, double second, double e);
void testNorms();

/**
functions in crsOperations.cpp, include basic operations such row permute, row scaling, and vector product
*/
void rowPermute(double value[], int valueSize, int rowPtr[], int colInd[], int colIndSize, int i, int j);
void rowScale(double *value[], int &valueSize, int rowPtr[], int rowPtrSize, int *colInd[], int &colIndSize, double a, int i, int j);
void deleteValue(double *value[], int &valueSize, int rowPtr[], int rowPtrSize, int *colInd[], int &colIndSize, int i, int j);
void negative(double value[], int rowPtr[], int colInd[], int i, int j);
void inverse(double value[], int rowPtr[], int colInd[], int i, int j);
double retrieve(double value[], int rowPtr[], int colInd[], int i, int j);
int rowSize(int rowPtr[], int r);
void printA(double value[], int colInd[], int colIndSize, int rowPtr[], int rowPtrSize);
void testCrsOperations();


/**
functions in jacobiOperations.cpp
*/
void getD(double *Dvalue[], int &DvalueSize, int DrowPtr[], int DrowPtrSize, int *DcolInd[], int &DcolIndSize);
void getL(double *Lvalue[], int &LvalueSize, int LrowPtr[], int LrowPtrSize, int *LcolInd[], int &LcolIndSize);
void getU(double *Uvalue[], int &UvalueSize, int UrowPtr[], int UrowPtrSize, int *UcolInd[], int &UcolIndSize);
void inverseD(double Dvalue[], int DvalueSize, int DrowPtr[], int DrowPtrSize, int DcolInd[], int DcolIndSize);
void LplusU(double *LUvalue[], int &LUvalueSize, int LUrowPtr[], int LUrowPtrSize, int *LUcolInd[], int &LUcolIndSize);
void iteration(double Dvalue[], double LUvalue[], int LUvalueSize, int LUrowPtr[], int LUrowPtrSize, int LUcolInd[], int LUcolIndSize, double DLUvalue[]);
void product(double value[], int valueSize, int rowPtr[], int rowPtrSize, int colInd[], int colIndSize, double x[], double product[]);
void add(double a[], double b[], int size, double c[]);
void testJacobiOperations();


/**
functions in jacobi.cpp
*/
void jacobi(double value[], int valueSize, int rowPtr[], int rowPtrSize, int colInd[], int colIndSize, double b[], int bSize, double x[]);

/**
functions in modularTests
*/
void modularTests();