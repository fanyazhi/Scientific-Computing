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
	return exp(50*x)-1;
}

double df(double x){
	return 50*exp(50*x);
}

double delta(double x){
	return -1*pow(df(x),-1)*f(x);
}
int main(){
	double result = 10;
	double deltax = 10;
	double best = 1;
	double t;
	int count1 = 0;
	cout<<"when x(0) = 1: "<<endl;
	for (t=1; t>0.2; t=t*0.5){
		cout<<"when t = "<<t<<endl;
		double x = 10;
		while(f(x)>10E-7){
			cout<<"x: "<<x<<" delta(x): "<<delta(x)<<" f(x): "<<f(x)<<endl;
			x += t*delta(x);
			count1++;
		}
		if (delta(x)<deltax){
			best = t;
			result = x;
			deltax = delta(x);
		}
	}

	cout<<"when x0 = 10, converges after "<<count1<<" iterations"<<endl;
	return 0;
}