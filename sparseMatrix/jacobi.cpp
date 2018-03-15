#include "defs.h"
using namespace std;

	
void jacobi(double value[], int valueSize, int rowPtr[], int rowPtrSize, int colInd[], int colIndSize){	
	cout<<"1"<<endl;
	/****Jacobi Method*****/
		//test getD
	int DvalueSize = valueSize;
	int DrowPtrSize = rowPtrSize;
	int DcolIndSize = colIndSize;
	double * Dvalue = new double[DvalueSize];
	for (int i = 0; i < DvalueSize; i++) Dvalue[i] = value[i];
	
	int * DrowPtr = new int[DrowPtrSize];
	for (int i = 0; i < DrowPtrSize; i++) DrowPtr[i] = rowPtr[i];
	
	int * DcolInd = new int[DcolIndSize];
	for (int i = 0; i < DcolIndSize; i++) DcolInd[i] = colInd[i];
	
	getD(&Dvalue, DvalueSize, DrowPtr, DrowPtrSize, &DcolInd, DcolIndSize);
	//cout<<"D= "<<endl;
	//printA(Dvalue, DcolInd, DcolIndSize, DrowPtr, DrowPtrSize);
	cout<<"aftergetD"<<endl;
	
	//cout<<"D^-1= "<<endl;
	//printA(Dvalue, DcolInd, DcolIndSize, DrowPtr, DrowPtrSize);
	
	//test L+U
	int LUvalueSize = 15;
	int LUrowPtrSize = 6;
	int LUcolIndSize = 15;
	double * LUvalue = new double[LUvalueSize];
	for (int i = 0; i < LUvalueSize; i++) LUvalue[i] = value[i];
	
	int * LUrowPtr = new int[LUrowPtrSize];
	for (int i = 0; i < LUrowPtrSize; i++) LUrowPtr[i] = rowPtr[i];
	
	int * LUcolInd = new int[LUcolIndSize];
	for (int i = 0; i < LUcolIndSize; i++) LUcolInd[i] = colInd[i];
	
	LplusU(&LUvalue, LUvalueSize, LUrowPtr, LUrowPtrSize, &LUcolInd, LUcolIndSize);
	//cout<<"L + U = "<<endl;
	//printA(LUvalue, LUcolInd, LUcolIndSize, LUrowPtr, LUrowPtrSize);

	//test iteration
	int DLUvalueSize = LUvalueSize;
	int DLUrowPtrSize = LUrowPtrSize;
	int DLUcolIndSize = LUcolIndSize;
	double * DLUvalue = new double[DLUvalueSize];
	for (int i = 0; i < DLUvalueSize; i++) DLUvalue[i] = LUvalue[i];
	
	int * DLUrowPtr = new int[DLUrowPtrSize];
	for (int i = 0; i < DLUrowPtrSize; i++) DLUrowPtr[i] = LUrowPtr[i];
	
	int * DLUcolInd = new int[DLUcolIndSize];
	for (int i = 0; i < DLUcolIndSize; i++) DLUcolInd[i] = LUcolInd[i];
	iteration(Dvalue, LUvalue, LUvalueSize, LUrowPtr, LUrowPtrSize, LUcolInd, LUcolIndSize, DLUvalue);
	//cout<<"D^-1 * (L+U) = "<<endl;
	//printA(DLUvalue, DLUcolInd, DLUcolIndSize, DLUrowPtr, DLUrowPtrSize);
	
	//test product
	//get intercept
	//intialize the b vector
	int bSize = colNum(colInd, colIndSize);
	double* b = new double[bSize];
	b[0] = 1;
	for (int i = 1; i < bSize; i++) b[i] = 0;
	
	int cepSize = bSize;
	double * cep = new double[cepSize];
	for (int i = 0; i < cepSize; i++) cep[i] = 0.0;
	
	product(Dvalue, DvalueSize, DrowPtr, DrowPtrSize, DcolInd, DcolIndSize, b, cep);
//		for (int i = 0; i < cepSize; i++) 
//		cout <<"cep"<<cep[i]<<endl;

	//Start of Jacobi Iterative Method
	int xSize = cepSize;
	double * x = new double[xSize];
	for (int i = 0; i < cepSize; i++) x[i] = cep[i];
	int count = 0;
	double * xTemp = new double[xSize];
	for (int i = 0; i < xSize; i++) xTemp[i] = 0;
	
	double * normTemp = new double[xSize];
	for (int i = 0; i < xSize; i++) normTemp[i] = 0;
	
	add(x, xTemp, xSize, normTemp);
	while (vectorNorm(normTemp, xSize) > 10E-7){
		for (int i = 0; i < xSize; i++) xTemp[i] = x[i];
		count++;
		double* prod = new double[xSize];
		product(DLUvalue, DLUvalueSize, DLUrowPtr, DLUrowPtrSize, DLUcolInd, DLUcolIndSize, x, prod);
		add(prod, cep, cepSize, x);
		for (int i = 0; i < xSize; i++) xTemp[i] = -1*xTemp[i];
		add(x, xTemp, xSize, normTemp);
	}
	
//	cout<<"x: "<<endl;
//	for (int i = 0; i < xSize; i++) 
//	cout <<x[i]<<endl;
//	cout<<"number of iterations: "<<count<<endl;
	
	double * check = new double[xSize]; for (int i = 0; i < xSize; i++) check[i] = 0;
	product(value, valueSize, rowPtr, rowPtrSize, colInd, colIndSize, x, check);
	cout<<"checking the evolution of the residual vector"<<endl;
	for (int i = 0; i < xSize; i++) check[i] = -1*check[i];
	double * check2 = new double[xSize]; for (int i = 0; i < xSize; i++) check2[i] = 0;
	add(check, b, bSize, check2);
	
	
//	for (int i = 0; i < xSize; i++) 
//	cout <<check2[i]<<endl;
	cout <<"residual vector norm: "<<vectorNorm(check2, bSize)<<endl;

}