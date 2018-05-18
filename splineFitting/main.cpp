#include <iostream>
#include <vector>
#include "cubicSpline.h"
#include "CRSmatrix.h"

using namespace std;

int main() {

    //initialize known x and y points
    vector<double> x;
    vector<double> y;
    x = constructVariables("/Users/Jane_Fan/Desktop/xcircle.csv");
    y = constructVariables("/Users/Jane_Fan/Desktop/ycircle.csv");

    //initialize qx and qy for extraction
    int points = 500;
    vector<double> qx(points);
    vector<double> qy(points);

    //call cubic spline
    cubicSpline(x, y, qx, qy);

    for (int i = 0; i<qx.size(); i++){
        cout<<qx[i]<<endl;
    }
    cout<<"__________"<<endl;
    for (int i = 0; i<qy.size(); i++){
        cout<<qy[i]<<endl;
    }

    return 0;
}