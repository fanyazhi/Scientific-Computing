#include <iostream>
#include <cmath>
#include <array>
#include <iomanip>
using namespace std;

double f(double t){
	return pow(M_E, -t);
}
double forwardEuler(double t, double delta){
	if (t < 0) return 0;
	if (t == 0) return 1;
	return (1-delta)*forwardEuler(t-delta, delta);
}
double backwardEuler(double t, double delta){
	if (t == 0) return 1;
	return 1/(1+delta)*backwardEuler(t-delta, delta);
}

int main()
{
    array<double,3> delta = {0.5, 1.0, 2.0};
	for (unsigned int i = 0; i <= 2; i++)
	{
		cout<<"delta = "<<delta[i]<<endl;
		for (double t=0; t<20; t= t+2.0)
		{
			double fa = f(t);
			double forwards = forwardEuler(t, delta[i]);
			double backward = backwardEuler(t, delta[i]);
			cout<<left<<setw(15)<<fa<<left<<setw(15)<<forwards<<left<<setw(15)<<backward<<endl;
		}
	}
	return 0;
}



