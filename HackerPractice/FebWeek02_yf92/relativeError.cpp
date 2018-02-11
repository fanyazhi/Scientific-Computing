#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
double f(double x, double c)
{
    return pow(x,2)+pow(c,10);
}
double fDerivative(double x, double h, double c)
{
    double fder = (f(x+h,c)-f(x,c))/h;
    return fder;
}
double fDerivative2(double x, double h, double c)
{
	double fder = (f(x+h,c)-f(x-h,c))/(2*h);
    return fder;
}
int main()
{
	for (double h = 0.1; h > pow(10,-18); h = h*0.1)
    {
		double x = 1;
		double c = 0;
		double fder11 = fDerivative(x, h, c);
		double fder12 = fDerivative2(x, h, c);
		double c2 = 10;
		double fder21 = fDerivative(x, h, c2);
		double fder22 = fDerivative2(x, h, c2);
		
		double error11 = 2-fder11;
		double error12 = 2-fder12;
		double error21 = 2-fder21;
		double error22 = 2-fder22;
        cout<<left<<setw(15)<<error11<<left<<setw(15)<<error12<<left<<setw(15)<<error21<<left<<setw(15)<<error22<<endl;
	}
	return 0;
}

