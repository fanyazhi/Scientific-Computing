#pragma once
#include<iostream>
#include<cmath>
#include <limits>
#include <cfloat>
#include <fstream>
#include <cstdio>


/*************************** Function Definitions ****************************/

/**
Creat the expection of Integer overflows 

return the result of integer overflows

varify overflow occurs
*/

int IntegerOverflows();

int fib(int n);

bool isIntOverflow();

/**
Create the expection of Integer divided by 0;

@return the result of integer divided by 0

varify overflow occurs
*/

double integerDividedByZero();


/**
Creat the expection of Integer overflows

@return the result of float point overflows
*/

double floatOverflows();

double fibf(int n);

bool isFloatOverflow();










