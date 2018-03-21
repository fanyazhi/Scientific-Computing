#include "defs.h"
using namespace std;

void infinityNorm(double value[], int rowPtr[], int rowPtrSize, double sum[]){
	int totalR = rowPtrSize-1;
	for (int r = 0; r<totalR; r++){
		int rBegin = rowPtr[r];
		int rStop = rowPtr[r+1];
		add1Row(value, r, rBegin, rStop, sum);
	
	}
}

void add1Row(double value[], int r, int rBegin, int rStop, double sum[]){
	for (int i = rBegin; i<rStop; i++){
		sum[r] += value[i];
	}
}

void firstNorm(double value[], int colInd[], int colIndSize, double sum[]){
	int totalC = colNum(colInd, colIndSize);
	for (int c = 0; c<totalC; c++){
		add1Col(value, c, colInd, colIndSize, sum);
	}
}

//find the number of columns
int colNum(int colInd[], int colIndSize){
	int col = 0;
	for (int i = 0; i <= colIndSize; i++) {
		if (colInd[i]>col) col = colInd[i];
	}
	return col+1;
}

//add values in column c
void add1Col(double value[], int c, int colInd[], int colIndSize, double sum[]){
	for (int i = 0; i<colIndSize; i++){
		if (colInd[i] == c) sum[c] += value[i];
	}
}
