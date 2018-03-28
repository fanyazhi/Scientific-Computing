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

	int count = 0;
	for (int N = 10; N<10E6; N*=10){
		double * x = new double[N];
		double * y = new double[N];

		for (int i = 1; i< N; i++){
			x[i] = 1.0*(rand()%100+1)/100;
			y[i] = 1.0*(rand()%100+1)/100;
			if ( x[i]*x[i] + y[i]*y[i] < 1 ) count++;
		}
		
		double pi = 4*count/(double)N;
		cout<<pi<<endl;
	}
	
}