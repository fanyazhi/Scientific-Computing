#include "defs.h"
using namespace std;

	
void jacobi(double value[], int valueSize, int rowPtr[], int rowPtrSize, int colInd[], int colIndSize, double b[], int bSize, double x[]){	
	/****Jacobi Method*****/
	//start timer
	int start_s=clock();
	//getD
	cout<<"computing diagonal matrix..."<<endl;
	int DvalueSize = rowPtrSize;
	int DrowPtrSize = rowPtrSize;
	int DcolIndSize = colNum(colInd, colIndSize);
	
	double * Dvalue = new double[DvalueSize];
	for (int i = 0; i < DvalueSize; i++) Dvalue[i] = 1/(retrieve(value, rowPtr, colInd, i, i));
	
	int * DrowPtr = new int[DrowPtrSize];
	for (int i = 0; i < DrowPtrSize; i++) DrowPtr[i] = i;
	
	int * DcolInd = new int[DcolIndSize];
	for (int i = 0; i < DcolIndSize; i++) DcolInd[i] = i;
	
	//LPlusU
	cout<<"computing sum of the left and right triangular matrices..."<<endl;
	int LUvalueSize = valueSize;
	int LUrowPtrSize = rowPtrSize;
	int LUcolIndSize = colIndSize;
	
	int * LUrowPtr = new int[LUrowPtrSize];
	for (int i = 0; i < LUrowPtrSize; i++) LUrowPtr[i] = rowPtr[i];
	
	list<double> myValueList;
	arrToList(value, valueSize, myValueList);
	list<int> myColList;
	arrToListInt(colInd, colIndSize, myColList);

	for (int i = 0; i<rowPtrSize-1; i++){
		//remove the value and colInd element at position [i][i]
		for (int n = rowPtr[i]; n<rowPtr[i]+rowSize(rowPtr, i); n++){
			if (colInd[n] == i){
				list<double>::iterator it = myValueList.begin(); advance(it, n-i);
				myValueList.erase(it);
				LUvalueSize--;
				list<int>::iterator it2 = myColList.begin(); advance(it2, n-i);
				myColList.erase(it2);
				LUcolIndSize--;
				for (int m = i+1; m<LUrowPtrSize; m++) LUrowPtr[m]--;
			}
		}
	}
	
	double * LUvalue = new double[LUvalueSize];
	int * LUcolInd = new int[LUcolIndSize];
	listToArr(LUvalue, myValueList);
	listToArrInt(LUcolInd, myColList);
	
	for (int i = 0; i< LUvalueSize; i++) LUvalue[i] = -1*LUvalue[i];

	//test iteration
	cout<<"performing iteration..."<<endl;
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
	
	//test product
	//get intercept
	//intialize the b vector
	
	int cepSize = bSize;
	double * cep = new double[cepSize];
	for (int i = 0; i < cepSize; i++) cep[i] = 0.0;
	
	product(Dvalue, DvalueSize, DrowPtr, DrowPtrSize, DcolInd, DcolIndSize, b, cep);

	//Start of Jacobi Iterative Method

	for (int i = 0; i < bSize; i++) x[i] = cep[i];
	int count = 0;
	double * xTemp = new double[bSize];
	for (int i = 0; i < bSize; i++) xTemp[i] = 0;
	
	double * normTemp = new double[bSize];
	for (int i = 0; i < bSize; i++) normTemp[i] = 0;
	
	add(x, xTemp, bSize, normTemp);
	while (vectorNorm(normTemp, bSize) > 10E-7){
		for (int i = 0; i < bSize; i++) xTemp[i] = x[i];
		count++;
		double* prod = new double[bSize];
		product(DLUvalue, DLUvalueSize, DLUrowPtr, DLUrowPtrSize, DLUcolInd, DLUcolIndSize, x, prod);
		add(prod, cep, cepSize, x);
		for (int i = 0; i < bSize; i++) xTemp[i] = -1*xTemp[i];
		add(x, xTemp, bSize, normTemp);
		cout<<"iteration #"<< count<<": "<<vectorNorm(normTemp, bSize)<<endl;
	}
	

	cout<<"total number of iterations: "<<count<<endl;
	int stop_s=clock();
	cout << "total run time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << "ms"<<endl;
	double * check = new double[bSize]; for (int i = 0; i < bSize; i++) check[i] = 0;
	product(value, valueSize, rowPtr, rowPtrSize, colInd, colIndSize, x, check);
	cout<<"checking the evolution of the residual vector..."<<endl;
	for (int i = 0; i < bSize; i++) check[i] = -1*check[i];
	double * check2 = new double[bSize]; for (int i = 0; i < bSize; i++) check2[i] = 0;
	add(check, b, bSize, check2);
	
	cout <<"residual vector norm: "<<vectorNorm(check2, bSize)<<endl;

}

void testJacobi(){
	//test the Jacobi method using a smaller matrix A
	int valueSize = 15;
	int rowPtrSize = 6;
	int colIndSize = 15;
	
	double* value = new double[valueSize];
	double assignValue[] = {-4,1,1, 4,-4,1, 1,-4,1, 1,-4,1, 1,1,-4};
	for (int i = 0; i < valueSize; i++) value[i] = assignValue[i];
		
	int* rowPtr = new int[rowPtrSize];
	int assignRowPtr[] = {0, 3, 6, 9, 12, 15};
	for (int i = 0; i < rowPtrSize; i++) rowPtr[i] = assignRowPtr[i];
	
	int* colInd = new int[colIndSize];
	int assignColInd[] = {0,1,4, 0,1,2, 1,2,3, 2,3,4, 0,3,4};
	for (int i = 0; i < colIndSize; i++) colInd[i] = assignColInd[i];

}