#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double f(double x)
{
	return pow(x,3);
}
double fDerivative1(double x, double h)
{
	return (f(x+h)-f(x))/h;
}
double fDerivative2(double x, double h)
{
	return (-1/(2*h))*f(x+2*h)-(3/(2*h))*f(x)+(2/h)*f(x+h);
}

int main()
{
	double x = 1;
	cout<<"tabulate relative error"<<endl;
	cout<<"1st order derivative"<<"   2nd order derivative"<<endl;
	for (double h=pow(2,-4); h>=pow(2,-10); h=h*0.5)
	{
		//tabulate relative error
		double error1=3-fDerivative1(x, h);
		double error2=3-fDerivative2(x, h);
		cout<<left<<setw(15)<<error1<<left<<setw(15)<<error2<<endl;
	}
	cout<<"estimate eta"<<endl;
	cout<<"1st order derivative "<<"        2nd order derivative"<<endl;
	for (double h=pow(2,-4); h>=pow(2,-10); h=h*0.5){
		//estimate eta
		double etaE1=(3-fDerivative1(x, 2*h))/(3-fDerivative1(x, h));
		double etaA1=(fDerivative1(x, 4*h)-fDerivative1(x, 2*h))/(fDerivative1(x, 2*h)-fDerivative1(x, h));
		double etaE2=(3-fDerivative2(x, 2*h))/(3-fDerivative2(x, h));
		double etaA2=(fDerivative2(x, 4*h)-fDerivative2(x, 2*h))/(fDerivative2(x, 2*h)-fDerivative2(x, h));
		cout<<left<<setw(15)<<etaE1<<left<<setw(15)<<etaA1<<left<<setw(15)<<etaE2<<left<<setw(15)<<etaA2<<endl;
	}
	return 0;
}
