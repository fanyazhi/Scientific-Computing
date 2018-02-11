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
    float fder = (f(x+h,c)-f(x,c))/h;
    return fder;
}

int main()
{
	for (double h = 0.1; h > pow(10,-18); h = h*0.1)
    {
		double x = 1;
		double c = 0;
		double fder = fDerivative(x, h, c);
		double c2 = 10;
		double fder2 = fDerivative(x, h, c2);
		
		double error = 2-fder;
		double error2 = 2-fder2;
        cout<<error<<" "<<error2<<endl;
	}
	return 0;
}

