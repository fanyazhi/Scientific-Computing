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
list and array helper functions in list.cpp
*/
void arrToList(double arr[], int arrSize, list<double>& mylist);
void listToArr(double arr[], list<double> mylist);
void arrSwap(double arr[], int arrSize, int i1, int i2, int j1, int j2);
bool compareArr(double first[], int firstSize, double second[], int secondSize, double e);
void testList();

/**
Create the expection of Integer divided by 0;
@return the result of integer divided by 0
varify overflow occurs
*/


/**
Creat the expection of Integer overflows
@return the result of float point overflows
*/
