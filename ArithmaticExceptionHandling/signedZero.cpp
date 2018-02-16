#include "defs.h"
#include"floatOperations.h"

/*log(x) when x is limited to positive zero*/
double logPZ() {
	double i;
	for (i=1000; i<INIFINTY; i*=i)
	cout<< log(1/i) << endl;
}

/*log(x) when x is limited to negative zero*/
double logNZ() {
	double i;
	for (i=1000; i<INIFINTY; i*=i)
	cout<< log(-1/i) << endl;
}

/*sinc(x) when x is limited to positive zero*/
double sincPZ() {
	double i;
	for (i=1000; i<INIFINTY; i*=i)
	cout<< sin(1/i)/(1/i) << endl;
	
}

/*sinc(x) when x is limited to negative zero*/
double sincNZ() {
	double i;
	for (i=1000; i<INIFINTY; i*=i)
	cout<< sin(-1/i)/(-1/i) << endl;
}
/*sin(x)/|x| when x is limited to negative zero*/
double sincNZA() {
	double i;
	for (i=1000; i<INIFINTY; i*=i)
	cout<< sin(-1/i)/abs(-1/i) << endl;
}
