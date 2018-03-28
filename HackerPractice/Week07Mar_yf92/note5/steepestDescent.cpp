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

double f(double x1, double x2){
	return pow((3*pow(x1,2)+x2-4),2)+pow((pow(x1,2)-3*x2+2),2);
}

double delta1(double x1, double x2){
	//cout<<"delta"<<-1*f(x1+(0.0001*x1), x2)/(0.0001*x1)<<endl;
	return -1*f(x1+(0.1*x1), x2)/(0.1*x1);
}

double delta2(double x1, double x2){
	return -1*f(x1, x2+(0.1*x2))/(0.1*x2);
}

double norm(double delta1, double delta2){
	return sqrt(pow(delta1,2)+pow(delta2, 2));
}

int main(){
	double x1 = 0.01; double x2 = 0.01;
	int count1 = 0;
	cout<<"when xi(0) = (0,0): "<<endl;
	while(1E-6*norm(delta1(x1, x2), delta2(x1, x2))>10E-6){
		cout<<"x norm: "<<norm(x1, x2)<<" delta(x) norm: "<<norm(delta1(x1, x2), delta2(x1, x2))<<" V: "<<f(x1, x2)<<endl;
		double temp = x1;
		x1 += 1E-6*delta1(x1, x2);
		x2 += 1E-6*delta2(x1, x2);
		count1++;
	}
	
	cout<<"when xi(0) = (0,0), converges after "<<count1<<" iterations"<<endl;

	return 0;
}