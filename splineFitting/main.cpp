#include <iostream>
#include <vector>
#include "cubicSpline.h"
#include "CRSmatrix.h"

using namespace std;

int main() {
    //initialize known x and y points
    int d = 6;
    vector<double> x(d);
    vector<double> y(d);
    x = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    y = {0.0, 1.0, 0.0, -1.0, 0.0, 1.0};

    //initialize qx and qy for extraction
    int points = 500;
    vector<double> qx(points);
    vector<double> qy(points);

    qx[0] = x[0];
    for (int i = 1; i < points; i++) {
        qx[i] = qx[i - 1] + 1.0*(d-1) / points;
    }

    //call cubic spline
    qy = cubicSpline(x, y, qx);
    for (int i = 0; i<qy.size(); i++){
        cout<<qy[i]<<endl;
    }
    return 0;
}