#include "defs.h"
using namespace std;

 /* Helper function: getD
 * get the diagonal matrix D, also takes the inverse of the diagonal elements
 */
void getD(double *Dvalue[], int &DvalueSize, int DrowPtr[], int DrowPtrSize, int *DcolInd[], int &DcolIndSize){
	int totalRow = DrowPtrSize-1;
	int totalCol = colNum(*DcolInd, DcolIndSize); 
	for (int i = 0; i<totalRow; i++){
		for (int j = 0; j<totalCol; j++){
			if (i != j){
				deleteValue(Dvalue, DvalueSize, DrowPtr, DrowPtrSize, DcolInd, DcolIndSize, i, j);
			}else{
				inverse(*Dvalue, DrowPtr, *DcolInd, i, j);
			}
		}
	}
}

 /* Helper function: getL
 * get the lower triangular matrix L
 */
void getL(double *Lvalue[], int &LvalueSize, int LrowPtr[], int LrowPtrSize, int *LcolInd[], int &LcolIndSize){
	int totalRow = LrowPtrSize-1;
	int totalCol = colNum(*LcolInd, LcolIndSize); 
	for (int i = 0; i<totalRow; i++){
		for (int j = 0; j<totalCol; j++){
			if (i <= j){
				deleteValue(Lvalue, LvalueSize, LrowPtr, LrowPtrSize, LcolInd, LcolIndSize, i, j);
			}else{
				negative(*Lvalue, LrowPtr, *LcolInd, i, j);
			}
		}
	}
}

 /* Helper function: getU
 * get the upper triangular matrix U
 */
void getU(double *Uvalue[], int &UvalueSize, int UrowPtr[], int UrowPtrSize, int *UcolInd[], int &UcolIndSize){
	int totalRow = UrowPtrSize-1;
	int totalCol = colNum(*UcolInd, UcolIndSize); 
	for (int i = 0; i<totalRow; i++){
		for (int j = 0; j<totalCol; j++){
			if (i >= j){
				deleteValue(Uvalue, UvalueSize, UrowPtr, UrowPtrSize, UcolInd, UcolIndSize, i, j);
			}else{
				negative(*Uvalue, UrowPtr, *UcolInd, i, j);
			}
		}
	}
}

 /* Helper function: inverseD
 * take the inverse of a diagonal matrix D
 */
void inverseD(double Dvalue[], int DvalueSize, int DrowPtr[], int DrowPtrSize, int DcolInd[], int DcolIndSize){
	int totalRow = DrowPtrSize-1;
	int totalCol = colNum(DcolInd, DcolIndSize); 
	for (int i = 0; i<totalRow; i++){
		for (int j = 0; j<totalCol; j++){
			if (i == j){
				inverse(Dvalue, DrowPtr, DcolInd, i, j);
			}
		}
	}
}

 /* Helper function: LplusU
 * take the sum of the lower and upper triangular matrices, store in LUValue[]
 */
void LplusU(double *LUvalue[], int &LUvalueSize, int LUrowPtr[], int LUrowPtrSize, int *LUcolInd[], int &LUcolIndSize){
	int totalRow = LUrowPtrSize-1;
	int totalCol = colNum(*LUcolInd, LUcolIndSize); 
	for (int i = 0; i<totalRow; i++){
		for (int j = 0; j<totalCol; j++){
			if (i == j){
				deleteValue(LUvalue, LUvalueSize, LUrowPtr, LUrowPtrSize, LUcolInd, LUcolIndSize, i, j);
			}else{
				negative(*LUvalue, LUrowPtr, *LUcolInd, i, j);
			}
		}
	}
}

 /* Helper function: iteration
 * take D^-1 * (L+U), store in DLU
 */
void iteration(double Dvalue[], double LUvalue[], int LUvalueSize, int LUrowPtr[], int LUrowPtrSize, int LUcolInd[], int LUcolIndSize, double DLUvalue[]){
	int totalRow = LUrowPtrSize-1;
	int totalCol = colNum(LUcolInd, LUcolIndSize); 
	for (int i = 0; i<totalRow; i++){
		for (int j = 0; j<totalCol; j++){
			for (int n = LUrowPtr[i]; n<LUrowPtr[i]+rowSize(LUrowPtr, i); n++){
				if (LUcolInd[n] == j){
						DLUvalue[n] = Dvalue[i]*retrieve(LUvalue, LUrowPtr, LUcolInd, i, j);
					}
			}
		}
	}
}

 /* Helper function: product
 * take the product of A*x, store in product[]
 */
void product(double value[], int valueSize, int rowPtr[], int rowPtrSize, int colInd[], int colIndSize, double x[], double product[]){
	int totalRow = rowPtrSize-1;
	int totalCol = colNum(colInd, colIndSize); 
	for (int i = 0; i<totalRow; i++){
		for (int j = 0; j<totalCol; j++){
			product[i] += x[j]*retrieve(value, rowPtr, colInd, i, j);
		}
	}
}

 /* Helper function: product
 * take the sum of two vectors a and b, store in c
 */
void add(double a[], double b[], int size, double c[]){
	for (int i = 0; i<size; i++){
		c[i] = a[i]+b[i];
	}
}

void testJacobiOperations(){
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
	
	//test getD
	int DvalueSize = 15;
	int DrowPtrSize = 6;
	int DcolIndSize = 15;
	double * Dvalue = new double[DvalueSize];
	for (int i = 0; i < DvalueSize; i++) Dvalue[i] = assignValue[i];
	
	int * DrowPtr = new int[DrowPtrSize];
	for (int i = 0; i < DrowPtrSize; i++) DrowPtr[i] = assignRowPtr[i];
	
	int * DcolInd = new int[DcolIndSize];
	for (int i = 0; i < DcolIndSize; i++) DcolInd[i] = assignColInd[i];
	
	getD(&Dvalue, DvalueSize, DrowPtr, DrowPtrSize, &DcolInd, DcolIndSize);
	
	//test getL
	int LvalueSize = 15;
	int LrowPtrSize = 6;
	int LcolIndSize = 15;
	double * Lvalue = new double[LvalueSize];
	for (int i = 0; i < LvalueSize; i++) Lvalue[i] = assignValue[i];
	
	int * LrowPtr = new int[LrowPtrSize];
	for (int i = 0; i < LrowPtrSize; i++) LrowPtr[i] = assignRowPtr[i];
	
	int * LcolInd = new int[LcolIndSize];
	for (int i = 0; i < LcolIndSize; i++) LcolInd[i] = assignColInd[i];
	
	getL(&Lvalue, LvalueSize, LrowPtr, LrowPtrSize, &LcolInd, LcolIndSize);
	
	//test getU
	int UvalueSize = 15;
	int UrowPtrSize = 6;
	int UcolIndSize = 15;
	double * Uvalue = new double[UvalueSize];
	for (int i = 0; i < UvalueSize; i++) Uvalue[i] = assignValue[i];
	
	int * UrowPtr = new int[UrowPtrSize];
	for (int i = 0; i < UrowPtrSize; i++) UrowPtr[i] = assignRowPtr[i];
	
	int * UcolInd = new int[UcolIndSize];
	for (int i = 0; i < UcolIndSize; i++) UcolInd[i] = assignColInd[i];
	
	getU(&Uvalue, UvalueSize, UrowPtr, UrowPtrSize, &UcolInd, UcolIndSize);
	

	
	//test L+U
	int LUvalueSize = 15;
	int LUrowPtrSize = 6;
	int LUcolIndSize = 15;
	double * LUvalue = new double[LUvalueSize];
	for (int i = 0; i < LUvalueSize; i++) LUvalue[i] = assignValue[i];
	
	int * LUrowPtr = new int[LUrowPtrSize];
	for (int i = 0; i < LUrowPtrSize; i++) LUrowPtr[i] = assignRowPtr[i];
	
	int * LUcolInd = new int[LUcolIndSize];
	for (int i = 0; i < LUcolIndSize; i++) LUcolInd[i] = assignColInd[i];
	LplusU(&LUvalue, LUvalueSize, LUrowPtr, LUrowPtrSize, &LUcolInd, LUcolIndSize);

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
	
	//test product
	//get intercept
	//intialize the b vector
	int bSize = 5;
	double* b = new double[bSize];
	double assignB[] = {1,0,0,0,0};
	for (int i = 0; i < bSize; i++) b[i] = assignB[i];
	
	int cepSize = bSize;
	double * cep = new double[cepSize];
	for (int i = 0; i < cepSize; i++) cep[i] = 0.0;
	
	product(Dvalue, DvalueSize, DrowPtr, DrowPtrSize, DcolInd, DcolIndSize, b, cep);

	//Start of Jacobi Iterative Method
	//Uncomment for hacker week 6 practice 1 
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
	
	cout<<"x: "<<endl;
	for (int i = 0; i < xSize; i++) 
	cout <<x[i]<<endl;
	cout<<"number of iterations: "<<count<<endl;
	
	double * check = new double[xSize]; for (int i = 0; i < xSize; i++) check[i] = 0;
	product(value, valueSize, rowPtr, rowPtrSize, colInd, colIndSize, x, check);
	cout<<"checking the evolution of the residual vector"<<endl;
	for (int i = 0; i < xSize; i++) check[i] = -1*check[i];
	double * check2 = new double[xSize]; for (int i = 0; i < xSize; i++) check2[i] = 0;
	add(check, b, bSize, check2);
	
	
	for (int i = 0; i < xSize; i++) 
	cout <<check2[i]<<endl;
	cout <<"residual vector norm: "<<vectorNorm(check2, bSize)<<endl;
	
}