#include <iostream>
#include <Eigen/Dense>
#include <cmath>

using namespace std;
using namespace Eigen;

double cubicPoint(int i, double xi, VectorXd x, VectorXd y, VectorXd k) {
    double t = (xi-x(i-1)) / (x(i)-x(i-1));
    double a = k(i-1)*(x(i)-x(i-1)) - (y(i)-y(i-1));
    double b = -1.0*k(i)*(x(i)-x(i-1)) +(y(i)-y(i-1));
    return (1-t)*y(i-1) + t*y(i) + t*(1-t)*(a*(1-t)+b*t);
}

VectorXd splineDerivative(int d, VectorXd x, VectorXd y) {
    //solve a[][]k[] = b[] to find frst derivatives
    VectorXd k(d);
    MatrixXd a(d, d); a.setZero(d, d);
    VectorXd b(d);

    //first row
    a(0, 0) = 2.0/(x(1)-x(0));
    a(0, 1) = 1.0/(x(1)-x(0));
    b(0) = 3.0* (y(1)-y(0)) / pow((x(1)-x(0)),2);

    //middle rows
    for (int i = 1; i<d-1; i++) {
        a(i, i-1) = 1.0/(x(i)-x(i-1));
        a(i, i) = 2.0* (1/(x(i)-x(i-1)) + 1/(x(i+1)-x(i)));
        a(i, i+1) = 1.0/(x(i+1)-x(i));
        b(i) = 3.0* ( ((y(i)-y(i-1)) / pow((x(i)-x(i-1)),2)) + ((y(i+1)-y(i)) / pow((x(i+1)-x(i)),2)));

    }

    //last row
    a(d-1, d-1) = 1.0/(x(d-1)-x(d-2));
    a(d-1, d-2) = 2.0/(x(d-1)-x(d-2));
    b(d-1) = 3.0* (y(d-1) - y(d-2)) / pow((x(d-1)-x(d-2)),2);

    k = a.colPivHouseholderQr().solve(b);
    return k;
}


int main() {
    //initialize known x and y points
    int d = 6;
    VectorXd x(d);
    VectorXd y(d);
    x << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0;
    y << 0.0, 1.0, 0.0, -1.0, 0.0, 1.0;

    //initialize qx and qy for extraction
    int points = 500;
    VectorXd qx(points);
    VectorXd qy(points);

    qx(0) = x(0);
    qy(0) = y(0);

    for (int i = 1; i < points; i++) {
        qx(i) = qx(i - 1) + 1.0*(d-1) / points;
    }

    //obtain derivatives
    VectorXd k(points);
    k = splineDerivative(d, x, y);

    for (int j = 1; j < points; j++) {
        double t = (x(d - 1) - x(0)) / points;
        double time = t * j;
        int i = 1.0 * time / (x(1) - x(0));
        qy(j) = cubicPoint(i + 1, qx(j), x, y, k);
    }
    cout<<qx<<endl;
    cout<<qy<<endl;

    return 0;
}