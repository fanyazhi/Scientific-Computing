#include "defs.h"
using namespace std;

/*A full matrix direct solver was written to test the sparse matrix solver using the Wilkison Principle
 * This full matrix solver can only solve small and simple matrices
 */
 void fullSolve(double A[5][5], double x[], double b[], int r, int c){
	 for (int ci = 0; ci<c-1; ci++){
	 for (int p = ci; p<r-1; p++){
	 for (int ri = p+1; ri<c; ri++){
		 if (abs((A[ri][ci]-A[p][ci]))>0.0000001) {
			 double a = (-1*(A[ri][ci]/A[p][ci]));
			 b[ri] += a*b[p];
			 fullRowScale(A, p, ri, c, a);
		 }
	 }}}
	 
	 for (int ci = c-1; ci>0; ci--){
	 for (int p = ci; p>0; p--){
	 for (int ri = p-1; ri>=0; ri--){
		 if (abs((A[ri][ci]-A[p][ci]))>0.0000001) {
			 double a = (-1*(A[ri][ci]/A[p][ci]));
			 b[ri] += a*b[p];
			 fullRowScale(A, p, ri, c, a);
		 }
	 }}}
	 for (int i = 0; i<r; i++) x[i] = b[i]/A[i][i];
 }

 
 void fullRowScale(double A[5][5], int i, int j, int c, double a){
	 for (int n = 0; n<c; n++){
		 A[j][n] += A[i][n]*a;
	 }
 }
 
 void testFullMatrixSolver(){
	 //first use full matrix solver to solve
	const int r = 5; const int c = 5;
	double A[r][c] = {{-4,1,0,0,1},{4,-4,1,0,0},{0,1,-4,1,0},{0,0,1,-4,1},{1,0,0,1,-4}};
	
	double b[] = {1,0,0,0,0};
	double x[] = {0};
	
	fullSolve(A, x, b, r, c);
	
	for (int i = 0; i < 5; i++) 
	cout <<x[i]<<endl;
	//then use jacobi method to solve 
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
	
	int bSize = colNum(colInd, colIndSize);
	double* b2 = new double[bSize];
	for (int i = 0; i < bSize; i++) b2[i] = 0;
	b2[0] = 1;
	
	//initiate x to save the result
	double * x2 = new double[bSize];
	for (int i = 0; i < bSize; i++) x2[i] = 0;
	jacobi(value, valueSize, rowPtr, rowPtrSize, colInd, colIndSize, b2, bSize, x2);
	
	compareArr(x, 5, x2, 5, 1E-2)? cout<<"compare result from Jacobi method and full matrix solver: no error"<<endl: 
	cout<<"compare result from Jacobi method and full matrix solver: error"<<endl;
 }
