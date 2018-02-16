#include "defs.h"
/*Outputs a floating point overflow using Fibonacci Series
*/
using namespace std;

/*INF, NINF, and NAN generation
*/
double geneINF() {
	float x = 0.0;
	float y = 1 / x;
	return y;
}

double geneNINF() {
	float x = -0.0;
	float y = 1 / x;
	return y;
}

double geneNaN() {
	float x = -1;
	return log(x);
}

bool isINF(double x) {
	return (x == INFINITY);
}

bool isNINF(double x) {
	return (x == -INFINITY);
}

bool isNaN(double x) {
	return (x != x);
}


void testFunction(double x)
{
	cout << "one divided by " << x << " result: " << 1 / x << endl;
	cout << "sin(" << x << ") result: " << sin(x) << endl;
	cout << "exp(" << x << ") result: " << exp(x) << endl;
}

void multiplyZero(double x)
{
	cout << "zero multiply " << x << " result: " << 0 * x << endl;
}

void testInteraction()
{
	/*infinity plus negative infinity result*/
	cout << INFINITY + (-INFINITY) << endl;

	/*infinity minus negative infinity result*/
	cout << INFINITY - (-INFINITY) << endl;

	/*infinity multiply negative infinity result*/
	cout << INFINITY*(-INFINITY) << endl;

	/*infinity divide negative infinity result*/
	cout << INFINITY / (-INFINITY) << endl;

	/*not a number plus infinity result*/
	cout << NAN + INFINITY << endl;

	/*not a number plus negative infinity result*/
	cout << NAN + (-INFINITY) << endl;
}

int floatingPointOperations(){
	/*Behavior of INF and NINF in 1/x, exp(x), and sin(x)*/
	testFunction(INFINITY);

	testFunction(-INFINITY);

	/*Propagation and interaction of INF, NINF, and NAN*/
	multiplyZero(INFINITY);

	multiplyZero(-INFINITY);

	multiplyZero(NAN);

	/*interaction of NAN INF and NINF*/
	testInteraction();

	return 0;
}