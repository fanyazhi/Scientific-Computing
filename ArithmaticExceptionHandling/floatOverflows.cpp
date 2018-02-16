/*/*Outputs a floating point overflow using Fibonacci Series
*/

#include "defs.h"

using namespace std;

double fibf(int n)
{
	double a = 0;
	double b = 1;
	while (n-- > 1) {
		double  t = a;
		a = b;
		b += t;
	}
	return b;
}

double floatOverflows()
{
	return fibf(187);
}

/*using Fibonocci to cause overflow
if previous element is greater or eqaul to the current element
then overflow occurs
*/
bool isFloatOverflow() {
	return(fib(187) <= fib(186));
}