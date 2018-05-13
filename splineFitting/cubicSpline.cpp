//
// Created by Jane Fan on 5/9/18.
//

#include "cubicSpline.h"
#include "CRSmatrix.h"

using namespace std;

double cubicPoint(int i, double xi, vector<double> x, vector<double> y, vector<double> k) {
    double t = (xi-x[i-1]) / (x[i]-x[i-1]);
    double a = k[i-1]*(x[i]-x[i-1]) - (y[i]-y[i-1]);
    double b = -1.0*k[i]*(x[i]-x[i-1]) +(y[i]-y[i-1]);
    return (1-t)*y[i-1] + t*y[i] + t*(1-t)*(a*(1-t)+b*t);
}

vector<double> splineDerivative(int d, vector<double> x, vector<double> y) {
    //solve a[][]k[] = b[] to find frst derivatives
    vector<double> k(d);
    CRSmatrix a (d, d);
    vector<double> b(d);

    //first row
    a.changeValue(2.0/(x[1]-x[0]), 0, 0);
    a.changeValue(1.0/(x[1]-x[0]), 0, 1);
    b[0] = 3.0* (y[1]-y[0]) / pow((x[1]-x[0]),2);

    //middle rows
    for (int i = 1; i<d-1; i++) {
        a.changeValue(1.0/(x[i]-x[i-1]), i, i-1);
        a.changeValue(2.0* (1/(x[i]-x[i-1]) + 1/(x[i+1]-x[i])), i, i);
        a.changeValue(1.0/(x[i+1]-x[i]), i, i+1);
        b[i] = 3.0* ( ((y[i]-y[i-1]) / pow((x[i]-x[i-1]),2)) + ((y[i+1]-y[i]) / pow((x[i+1]-x[i]),2)));
    }

    //last row
    a.changeValue(1.0/(x[d-1]-x[d-2]), d-1, d-1);
    a.changeValue(2.0/(x[d-1]-x[d-2]), d-1, d-2);
    b[d-1] = 3.0* (y[d-1] - y[d-2]) / pow((x[d-1]-x[d-2]),2);

    k = Jacobi(a, b);
    return k;
}


vector<double> cubicSpline(vector<double> x, vector<double> y, vector<double> qx) {

    //initialize qx and qy for extraction
    vector<double> qy(qx.size());
    qy[0] = y[0];

    //obtain derivatives
    vector<double> k(qx.size());
    k = splineDerivative(x.size(), x, y);

    for (int j = 1; j < qx.size(); j++) {
        int i = 0;
        while (x[i]<qx[j] && i<x.size()){
            i++;
        }
        qy[j] = cubicPoint(i , qx[j], x, y, k);
    }

    return qy;
}