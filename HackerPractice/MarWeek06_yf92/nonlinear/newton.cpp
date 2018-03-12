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
	double x = 1;
	int count1 = 0;
	cout<<"when x(0) = 1: "<<endl;
	while(f(x)>10E-7){
		cout<<"x: "<<x<<" delta(x): "<<delta(x)<<" f(x): "<<f(x)<<endl;
		x += delta(x);
		count1++;
	}
	
	double x2 = 10;
	int count2 = 0;
	cout<<"when x(0) = 10: "<<endl;
	while(f(x2)>10E-7){
		cout<<"x: "<<x2<<" delta(x): "<<delta(x2)<<" f(x): "<<f(x2)<<endl;
		x2 += delta(x2);
		count2++;
	}
	
	cout<<"when x0 = 1, converges after "<<count1<<" iterations"<<endl;
	cout<<"when x0 = 10, converges after "<<count2<<" iterations"<<endl;
	return 0;
}

