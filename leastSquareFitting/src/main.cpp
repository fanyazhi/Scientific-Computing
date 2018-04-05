#include "fullMatrix.h"
#include "parameterExtraction.h"
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<double> value = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0};
    Matrix m = constructMatrix(3, value);
    printMatrix(m);
    vector<double> x = {1.0, 1.0, 1.0};
    vector<double> b = productAx(m, x);
    return 0;
}