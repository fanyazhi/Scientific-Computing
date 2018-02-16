#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>
using namespace std;

double factorial(int n){
	double f = 1;
	for(int i = 1; i <=n; ++i)
    {
        f = f*i;
    }
	return f;
}
double pDigits(int k){
	//double d = (1/pow(16,k))*(4/(8*k+1)-2/(8*k+4)-1/(8*k+5)-1/(8*k+6))-3;
	//double p = (log(pow(640320,3)+744)/sqrt(163))*pow(10,n);
	double d=(k*pow(2.0,k)*pow(factorial(k),2.0))/factorial(2*k);
	cout << d << endl;
	return d;
}


int main(){
	double p = -3.0;
	for(double k = 1; k <50; k=k+1)
	{
		//p=((k*pow(2.0,k)*pow(factorial(k),2.0))/factorial(2*k));
		cout<<setprecision(10)<<p<<endl;
		//p.append(to_string(pDigits(i)));
	}
	
}