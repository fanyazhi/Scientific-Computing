#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

int main()
{
    double a= pow(10,-20);
    double b= pow(10,3);
    double c= pow(10,3);
    double a1= (-b+sqrt(pow(b,2)-4*a*c))/(2*a);
    double a2= (-b-sqrt(pow(b,2)-4*a*c))/(2*a);

    double b1= (2*c)/(-b+sqrt(pow(b,2)-4*a*c));
    double b2= (2*c)/(-b-sqrt(pow(b,2)-4*a*c));

    double x1= 0;
    double x2= 0;
    if (a1-b1 < 1E-9 || a2-b2 < 1E-9 ){
        x1=-c/b;
        x2=-b/a+c/b;
    }else{
        x1=a1;
        x2=a2;
    }


    cout << a1 << endl;
    cout << a2 << endl;
    cout << b1 << endl;
    cout << b2 << endl;
    cout << x1 << endl;
    cout << x2 << endl;
    return 0;

    //0,23,inf,-1,-1,23
}
