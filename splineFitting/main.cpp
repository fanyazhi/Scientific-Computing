#include <iostream>
#include <vector>
#include "cubicSpline.h"
#include "CRSmatrix.h"

using namespace std;

int main() {
    //initialize known x and y points
    int d = 5;
    vector<double> x(d);
    vector<double> y(d);
    x = {3, 1, 2.5, 3, 3.5, 5, 3};
    y = {1, 4, 4.5, 3, 4.5, 4, 1};

    //initialize qx and qy for extraction
    int points = 500;
    vector<double> qx(points);
    vector<double> qy(points);

    //call cubic spline
    cubicSpline(x, y, qx, qy);

    for (int i = 0; i<qy.size(); i++){
        cout<<qx[i]<<endl;
    }
    cout<<"__________"<<endl;
    for (int i = 0; i<qy.size(); i++){
        cout<<qy[i]<<endl;
    }
    return 0;
}