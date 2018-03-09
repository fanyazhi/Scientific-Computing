#include "defs.h"
using namespace std;

//Note: index of the first row is 0
void rowPermute(double value[], int valueSize, int rowPtr[], int colInd[], int colIndSize, int i, int j){
	arrSwap(value, valueSize, rowPtr[i], rowPtr[i+1], rowPtr[j], rowPtr[j+1]);
	arrSwapInt(colInd, colIndSize, rowPtr[i], rowPtr[i+1], rowPtr[j], rowPtr[j+1]);
}


void testCrsOperations(){
	double value[] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0};
	int rowPtr[] = {0,3,6,9,10,12};
	int colInd[] = {0,1,4,0,1,2,1,2,4,3,0,4};
	
	int valueSize = sizeof(value)/sizeof(*value);
	int rowPtrSize = sizeof(rowPtr)/sizeof(*rowPtr);
	int colIndSize = sizeof(colInd)/sizeof(*colInd);
	int i = 0; int j = 1;
	
	double valTest[] = {4.0,5.0,6.0,1.0,2.0,3.0,7.0,8.0,9.0,10.0,11.0,12.0};
	int colTest[] = {0,1,2,0,1,4,1,2,4,3,0,4};
	rowPermute(value, valueSize, rowPtr, colInd, colIndSize, i, j);
//	for (int i = 0; i < sizeof(value)/sizeof(value[0]); i++) 
//	cout <<sizeof(value)/sizeof(value[0])<<endl;
//	for (int i = 0; i < sizeof(valTest)/sizeof(valTest[0]); i++) 
//	cout <<sizeof(valTest)/sizeof(valTest)<<endl;
	compareArr(value, sizeof(value)/sizeof(value[0]), valTest, sizeof(valTest)/sizeof(valTest[0]), 0.0001)
	&& compareArrInt(colInd, sizeof(colInd)/sizeof(colInd[0]), colTest, sizeof(colTest)/sizeof(colTest[0]))? 
	cout << "Test rowPermute case 1: no error"<<endl:cout << "Test rowPermute case 1: error"<<endl; 

}