#pragma once
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cfloat>
#include <fstream>
#include <limits>
#include <list>
#include <iostream>
#include <iterator>

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
various helper functions in upperBoundSparse.cpp
*/
double infinityNorm(double value[], int rowPtr[], int rowPtrSize);
double firstNorm(double value[], int colInd[], int colIndSize);
int colNum(int colInd[], int colIndSize);
double add1Col(double value[], int c, int colInd[], int colIndSize);
double add1Row(double value[], int rowPtr[], int r);
bool compareDouble(double first, double second, double e);
void testUpper();

/**
functions in crsOperations.cpp, include basic operations such row permute, row scaling, and vector product
*/
void rowPermute(double value[], int valueSize, int rowPtr[], int colInd[], int colIndSize, int i, int j);
void rowScale(double *value[], int &valueSize, int rowPtr[], int rowPtrSize, int *colInd[], int &colIndSize, double a, int i, int j);
double retrieve(double value[], int rowPtr[], int colInd[], int i, int j);
int rowSize(int rowPtr[], int r);
void printA(double value[], int colInd[], int colIndSize, int rowPtr[], int rowPtrSize);


void testCrsOperations();