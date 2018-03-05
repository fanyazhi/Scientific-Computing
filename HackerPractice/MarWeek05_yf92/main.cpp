#include "defs.h"
using namespace std;

int main()
{
	//testList() for hacker practice 3;
	double value[] = {1,2,3,4,5,6,7,8,9,10,11,12};
	int rowPtr[] = {0,3,6,9,10,12};
	int colInd[] = {0,1,4,0,1,2,1,2,4,3,0,4};
	
	int valueSize = sizeof(value)/sizeof(*value);
	int rowPtrSize = sizeof(rowPtr)/sizeof(*rowPtr);
	int colIndSize = sizeof(colInd)/sizeof(*colInd);
	
	//finding the infinity
	double infinitySum[sizeof(rowPtr)/sizeof(*rowPtr)-1] = {};
	double in = 0;
	infinityNorm(value, rowPtr, rowPtrSize, infinitySum);
		for (int i = 0; i < sizeof(infinitySum)/sizeof(infinitySum[0]); i++) {
			if (infinitySum[i]>in) in = infinitySum[i];
	}
	cout<<"infinity norm is: "<<in<<endl;
	
	//finding the first norm
	int col = colNum(colInd, colIndSize);
	double* firstSum = new double[col];
	double fn = 0;
	firstNorm(value, colInd, colIndSize, firstSum);
	for (int i = 0; i < col; i++) {
		if (firstSum[i]>fn) fn = firstSum[i];
	}
	cout<<"first norm is: "<<fn<<endl;
	return 0;
}
