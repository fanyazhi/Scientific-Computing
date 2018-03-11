#include "defs.h"
using namespace std;

/* Helper function: infinityNorm
 * return the infinity norm of a row compressed matrix
 */
double infinityNorm(double value[], int rowPtr[], int rowPtrSize){
	int totalR = rowPtrSize-1; //totalR: number of rows
	double* infinitySum = new double[totalR]; //infinitySum: array that stores the sum of each row
	for (int r = 0; r<totalR; r++){
		infinitySum[r] = add1Row(value, rowPtr, r);
	}
	double in = 0; //in: infinity norm
	for (int i = 0; i < totalR; i++) { //find the max number in infinitySum ->infinity norm
		if (infinitySum[i]>in) in = infinitySum[i];
	}
	delete [] infinitySum;
	return in;
	
}

/* Helper function: firstNorm
 * return the first norm of a row compressed matrix
 */
double firstNorm(double value[], int colInd[], int colIndSize){
	int col = colNum(colInd, colIndSize); //col: number of columns
	double* firstSum = new double[col]; //firstSum: array that stores the sum of each column
	
	int totalC = colNum(colInd, colIndSize);
	for (int c = 0; c<totalC; c++){
		firstSum[c] = add1Col(value, c, colInd, colIndSize);
	}
	double fn = 0; //fn: first norm
	for (int i = 0; i < col; i++) { //find the max number in firstSum ->first norm
		if (firstSum[i]>fn) fn = firstSum[i];
	}
	delete [] firstSum;
	return fn;
}

/* Helper function: colNum
 * input: column index array, column index array size
 * return the total number of columns
 */
int colNum(int colInd[], int colIndSize){
	int col = 0;
	for (int i = 0; i <= colIndSize; i++) {
		if (colInd[i]>col) col = colInd[i];
	}
	return col+1;
}

/* Helper function: add1Col
 * input: value array, rowPtr array, row number
 * return the sum of the elements in row r
 */
double add1Col(double value[], int c, int colInd[], int colIndSize){
	double sum = 0;
	for (int i = 0; i<colIndSize; i++){
		if (colInd[i] == c) sum += value[i];
	}
	return sum;
}

/* Helper function: add1Row
 * input: value array, rowPtr array, row number
 * return the sum of the elements in row r
 */
double add1Row(double value[], int rowPtr[], int r){
	double sum = 0;
	int rBegin = rowPtr[r];
	int rStop = rowPtr[r+1];
	for (int i = rBegin; i<rStop; i++){
		sum += value[i];
	}
	return sum;
}

bool compareDouble(double first, double second, double e){
	return abs(first - second) <e;
}

void testUpper(){
	double value[] = {1,2,3,4,5,6,7,8,9,10,11,12};
	int rowPtr[] = {0,3,6,9,10,12};
	int colInd[] = {0,1,4,0,1,2,1,2,4,3,0,4};
	
	//int valueSize = sizeof(value)/sizeof(*value);
	int rowPtrSize = sizeof(rowPtr)/sizeof(*rowPtr);
	int colIndSize = sizeof(colInd)/sizeof(*colInd);
	
	compareDouble(infinityNorm(value, rowPtr, rowPtrSize), 24.0, 0.0001)? 
	
	cout << "Test infinityNorm: no error"<<endl:cout << "Test infinityNorm: error"<<endl;
	
	compareDouble(firstNorm(value, colInd, colIndSize), 24.0, 0.0001)? 
	cout << "Test firstNorm: no error"<<endl:cout << "Test firstNorm: error"<<endl;
}



