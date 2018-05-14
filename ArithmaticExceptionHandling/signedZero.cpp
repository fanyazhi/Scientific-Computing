#include "defs.h"
#include"floatOperations.h"

using namespace std;

/*log(x) when x is limited to positive zero*/
double logPZ() {
	double i;
	for (i=1000; i<numeric_limits<double>::infinity(); i*=i)
	cout<< log(1/i) << endl;
	return log(1/i);
}

/*log(x) when x is limited to negative zero*/
double logNZ() {
	double i;
	for (i=1000; i<numeric_limits<double>::infinity(); i*=i)
	cout<< log(-1/i) << endl;
	return log(-1/i);
}

/*sinc(x) when x is limited to positive zero*/
double sincPZ() {
	double i;
	for (i=1000; i<numeric_limits<double>::infinity(); i*=i)
	cout<< sin(1/i)/(1/i) << endl;
	return sincPZ();
}

/*sinc(x) when x is limited to negative zero*/
double sincNZ() {
	double i;
	for (i=1000; i<numeric_limits<double>::infinity(); i*=i)
	cout<< sin(-1/i)/(-1/i) << endl;
	return sin(-1/i)/(-1/i);
}

/*sin(x)/|x| when x is limited to negative zero*/
double sincNZA() {
	double i;
	for (i=1000; i<numeric_limits<double>::infinity(); i*=i)
	cout<< sin(-1/i)/abs(-1/i) << endl;
	return sincNZA();
}
