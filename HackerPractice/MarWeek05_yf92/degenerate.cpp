#include <iostream>
#include <cmath>
#include <limits>
#include <cfloat>
#include <fstream>
#include <cstdio>
#include <iomanip>

using namespace std;

double det(double e){
	return abs(100*(98.01-e)-99*99);
}

int main(){
	int i;
	double e;
	double x[8],y[8],secNorm[8];
	
	ofstream myfile;
	myfile.open("HP1.txt"); 
	
	for(i=0;i<8;i++){
		e = pow(10,-2-i);
		x[i] = ((98.01-e)*199-99*97)/det(e);
		y[i] = (-99*199+197*100)/det(e);
		myfile<<"x: "<<x[i]<<"  y: "<<y[i]<<endl; 
		secNorm[i] = sqrt(pow(100*x[i] + 99*y[i] - 199,2) + pow(99*x[i]+(98.01-e)*y[i],2)); 
		myfile<<"second norm: "<<secNorm[i]<< endl;
	}
	myfile.close();
}
