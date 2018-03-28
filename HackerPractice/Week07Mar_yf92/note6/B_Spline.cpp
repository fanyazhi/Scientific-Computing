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


int main(){
	int d = 6;
	double x[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
	double y[] = {0.0, 1.0, 0.0, -1.0, 0.0, 1.0};
	
	double k[d];
	k[0] = 1;
	k[d-1] = 1;
	for (int i = 0; i<d-2; i++){
		k[i+1] = 3*((x[i+1]-x[i])/(x[i]-x[i-1])*(y[i]-y[i-1])+(x[i]-x[i-1])/(x[i+1]-x[i])*(y[i+1]-y[i]))
		-(x[i+1]-x[i])*k[i-1]-2*k[i]*(x[i+1]-x[i-1]);
	}
	for (int i = 0; i<d; i++){
		cout<<k[i]<<endl;
	}
}