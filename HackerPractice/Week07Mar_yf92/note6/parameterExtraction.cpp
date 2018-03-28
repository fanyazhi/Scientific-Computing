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
const double x[] = {1.0, 4.5, 9.0, 20, 74, 181 };
const double y[] = {3.0, 49.4, 245, 1808, 2.2E4, 7.3E4};


double f(double a, double m){
	double v = 0;
	for (int i = 0; i<6; i++){
		v += a*pow(x[i], m)-y[i];
	}
	return v;
}

double delta1(double x1, double x2){
	//cout<<"delta"<<(-1/((f(1.0001*x1,x2)-f(x1, x2))/(0.0001*x1)))*f(x1, x2)<<endl;
	return (-1*(0.0001*x1)/(f(1.0001*x1,x2)-f(x1, x2)))*f(x1, x2);
}

double delta2(double x1, double x2){
	return (-1*(0.0001*x2)/(f(x1,1.0001*x2)-f(x1, x2)))*f(x1, x2);
}

double norm(double delta1, double delta2){
	return sqrt(pow(delta1,2)+pow(delta2, 2));
}

int main(){
	double x1 = 2; double x2 = 1;
	int count1 = 0;
	cout<<"when xi(0) = (0,0): "<<endl;
	while(norm(delta1(x1, x2), delta2(x1, x2))>10E-7){
		cout<<"x norm: "<<norm(x1, x2)<<" delta(x) norm: "<<norm(delta1(x1, x2), delta2(x1, x2))<<" V: "<<f(x1, x2)<<endl;
		double temp = x1;
		x1 += 0.001*delta1(x1, x2);
		x2 += 0.001*delta2(x1, x2);
		count1++;
	}
	
	cout<<"when xi(0) = (0,0), converges after "<<count1<<" iterations"<<endl;

	return 0;
}