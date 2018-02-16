#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>
using namespace std;

void addBig(double x, double y){//x and y must have 16 percisions
	int sum [617] = { }; //DBL_MAX 1.7976931348623158e+308
	int ex, ey; //exponent of x and y
	double manx, many; //mantissa of x and y 
	double result1, result2; //results are 16 percisions
	//first find exponent of x
	if (x==0){
		ex = 0;
	}else{
		ex = (int)(log10(fabs(x)));
	}
	//then find mantissa of x
	manx = x*pow(10,-1*ex);
	//find exponent of y
	if (y==0){
		ey = 0;
	}else{
		ey = (int)(log10(fabs(y)));
	}
	//find mantissa of y
	many = y*pow(10,-1*ey);
	//add x and y components into array
	for (int i= ex; i>ex-16; i--){
		sum[309+i]=sum[309+i]+(int)manx;
		manx= (manx-(int)manx)*10.0;
	}
		
	for (int i= ey; i>ey-16; i--){
		sum[309+i]=sum[309+i]+(int)many;
		many= (many-(int)many)*10;
	}
	//Now the result is stored in sum[]
	//Then we have to output it into two 16 digits double
	int counter = 1;
	for (int i= 617; i>0; i--){
		if (sum[i]!=0){//first non zero
			if (counter<16){ //add first 16 digits to result1
				result1 = result1+sum[i]*pow(10,i-309);
			}
			else if (counter<32){ //add rest of the digits to result2
				result2 = result2+sum[i]*pow(10,i-309);
			}
			counter++;
		}
	}

	
	//exception handling
	//if one is infinity and the other is larger than zero, result is infinity
	if ((x==INFINITY && y>=0) || (y==INFINITY && x>=0) ){
		result1 = INFINITY; result2 = INFINITY;
	}
	//if one is negative infinity and the other is smaller than zero, result is negative infinity
	if ((x==-1*INFINITY && y<=0) || (y==-1*INFINITY && x<=0)){
		result1 = -1*INFINITY; result2 = -1*INFINITY;
	}
	//if one is NAN, both results are NAN
	if (x==NAN || y==NAN){
		result1 = NAN; result2 = NAN;
	}
	//if larger (exponent) result is infinity, both result will be infinity
	if (result1 == INFINITY){
		result1 = INFINITY; result2 = INFINITY;
	}
	//if larger (exponent) result is negative infinity, both result will be infinity
	if (result1 == -1*INFINITY){
		result1 = -1*INFINITY; result2 = -1*INFINITY;
	}
	cout<<"sum of "<<x<<" and "<<y<<" is:"<<endl;
	cout<<result1<<" and "<<result2<<endl;
		
}

int main(){
	addBig(1.234567890123456e10, 6.7890123456789012e-50);
	return 0;
}
