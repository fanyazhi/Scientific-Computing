#include <iostream>
#include <math.h>
#include <float.h>
using namespace std;
bool isNegativeZero(double x)
{
    return (1/x == -INFINITY);
}

bool isPositiveZero(double x)
{
    return (1/x == INFINITY);
}

bool isINF(double x)
{
    return (x == INFINITY);
}

bool isNINF(double x)
{
    return (x == -INFINITY);
}

bool isNAN(double x)
{
    return (x != x);
}

int main()
{
    double foo[9] = {1.0,-1.0,DBL_MAX,-1.0*DBL_MAX,+0,-1.0*0,INFINITY,-INFINITY,NAN};
    for (int i=0;i<9;i++)
    {
        bool a = isNegativeZero(foo[i]);
        bool b = isPositiveZero(foo[i]);
        bool c = isINF(foo[i]);
        bool d = isNINF(foo[i]);
        bool e = isNAN(foo[i]);
        cout<<foo[i]<<" is negative zero ("<<a<<"), a positive zero ("<<b<<"), infinity ("<<c<<"), negative infinity ("<<d<<"), or not a number ("<<e<<")"<< endl;
    }
    return 0;
}


