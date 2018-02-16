#include "defs.h"
#include "gradualUnderflow.h"
#include "floatOperations.h"
using namespace std;

double subUnderflow() {
	double x, y;
	double xx = 1.21;
	int i = 1;

	// The normalized number is above 4.9407*10^(-324)
	for (i = 1; i<20; i++) {
		x = xx*pow(10, -322);
		y = 1.01*pow(10, -322);
		xx -= 0.01;

		cout << ' ' << x << " - " << y << " = " << x - y << " x==y?" << (x == y) << endl;
	}
	cout << "The above operations are within 4.9407*10^-324." << endl;
	cout << "The next operation shows the difference of the smallest" << endl;
	cout << "valid x and y above divided by two, which results in underflow." << endl;

	cout << ' ' << x / 2 << " - " << y / 2 << " = " << (x - y) / 2 << " x==y?" << (x == y) << endl;
	return 0;
}

double divUnderflow() {
	double x = 1.234567890123456;
	int i = 1;

	// The normalized number is above 4.9407*10^(-324)
	x *= pow(10, -307);
	double y = 10;
	// Decrease the normalized number to the range of denormals
	for (i = 1; i<20; i++) {
		x /= y;
		cout << x << endl;
	}
	return 0;
}

double sinUnderflow(){
	for(int i =1000; i<INFINITY; i=i*i){
		double x = 1 / i;
		double y;
		y = sin(1.23456789012345*x) / x;
		cout << y << endl;
	}
	return 0;
}
