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

double myRand(){
	return 1.0*(rand()%100 +1)/100;
}
double distribute(double lambda, list<double>& Fv){
	double u = myRand();
	Fv.push_back(u);
	return (-1/lambda)*log(1-u);
	
}
int main(){
	double lambda = 0.2;
	list<double> v;
	list<double> Pv;
	list<double> Fv;
	for (int i = 0; i<1000; i++){
		v.push_back(distribute(lambda, Fv));
	}
	v.sort();
	Fv.sort();
	for (auto v : v){
		if (v>=0) Pv.push_back(lambda*exp(-lambda*v));
		else Pv.push_back(0);
	}
	cout<<"v"<<endl;
	for (auto v : v)
	cout << v << "\n";
	
	cout<<"P(v)"<<endl;
	for (auto v : Pv)
	cout << v << "\n";
	
	cout<<"F(v)"<<endl;
	for (auto v : Fv)
	cout << v << "\n";
}