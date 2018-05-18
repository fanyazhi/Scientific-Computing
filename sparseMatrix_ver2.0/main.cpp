#include <iostream>
#include <cmath>
#include <vector>
#include "CRSmatrix.h"

using namespace std;

int main() {
    //construct sparse matrix from file read
    CRSmatrix A;

    cout<<"b=(1.0, 0, 0, …,0)^T: "<<endl;
    //initiate vector b
    vector<double> b (A.colNum);
    for (int i = 0; i < b.size(); i++) b[i] = 0;
    b[0] = 1;

    //initiate vector x to save the result
    vector<double> x (b.size());
    x = Jacobi(A, b);
    
    return 0;
}