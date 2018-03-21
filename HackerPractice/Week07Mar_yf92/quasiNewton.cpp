#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cfloat>
#include <fstream>
#include <limits>
#include <list>
#include <iostream>
#include <iterator>

using namespace std;

double f(double x){
	return exp(100*x)-1;
}

double df(double x){
	return 100*exp(100*x);
}

double delta(double x){
	return -1/((f(1.0001*x)-f(x))/(0.0001*x))*f(x);
}
int main(){
	double x = 1;
	int count1 = 0;
	cout<<"when x(0) = 1: "<<endl;
	while(f(x)>10E-7){
		cout<<"x: "<<x<<" delta(x): "<<delta(x)<<" f(x): "<<f(x)<<endl;
		x += delta(x);
		count1++;
	}
	
	cout<<"when x0 = 1, converges after "<<count1<<" iterations"<<endl;

	return 0;
}