/*Outputs an integer overflow using Fibonacci Series
*/
#include "defs.h"
using namespace std;

int fib(int n)
{
	int a = 0;
	int b = 1;
	while (n-- > 1) {
		int t = a;
		a = b;
		b += t;
	}
	return b;
}

int IntegerOverflows()
{
	return fib(47);
}

/*using Fibonocci to cause overflow
  if previous element is greater or eqaul to the current element
  then overflow occurs
*/
bool isIntOverflow() {
	return(fib(47) <= fib(46));
}

