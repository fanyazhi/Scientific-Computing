#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
double f(double x)
{
    return pow(x,2);
}
double fDerivative(double x, double h)
{
    float fder = (f(x+h)-f(x))/h;
    return fder;
}

int main()
{
	for (double h = 0.1; h > pow(10,-18); h = h*0.1)
    {
		double x = 1;
		double fder = fDerivative(x, h);
		
		double error = 2-fder;
        cout << setprecision (15) <<error<<endl;
	}
	return 0;
}

