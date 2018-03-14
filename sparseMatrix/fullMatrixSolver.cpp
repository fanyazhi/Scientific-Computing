#include "defs.h"
using namespace std;

/*A full matrix direct solver was written to test the sparse matrix solver using the Wilkison Principle
 * This full matrix solver can only solve small and simple matrices
 */
 void fullSolve(double A[5][5], double x[], double b[], int r, int c){
	 for (int ci = 0; ci<c-1; ci++){
	 for (int p = ci; p<r-1; p++){
	 for (int ri = p+1; ri<c; ri++){
		 //cout<<"ci "<<ci<< " p "<<p<< " ri "<<ri<<endl;
		 if (abs((A[ri][ci]-A[p][ci]))>0.0000001) {
			 double a = (-1*(A[ri][ci]/A[p][ci]));
			 b[ri] += a*b[p];
			 fullRowScale(A, p, ri, c, a);
			 //for (int i = 0; i<3; i++) cout<<b[i]<<" ";cout<<endl;
		 }
	 }}}
	 
	 for (int ci = c-1; ci>0; ci--){
	 for (int p = ci; p>0; p--){
	 for (int ri = p-1; ri>=0; ri--){
		 //cout<<"ci "<<ci<< " p "<<p<< " ri "<<ri<<endl;
		 if (abs((A[ri][ci]-A[p][ci]))>0.0000001) {
			 double a = (-1*(A[ri][ci]/A[p][ci]));
			 //cout<<"b[ri] "<<b[ri]<< " a*b[p] "<<a*b[p]<<endl;
			 b[ri] += a*b[p];
			 fullRowScale(A, p, ri, c, a);
			 //for (int i = 0; i<3; i++) cout<<b[i]<<" ";cout<<endl;
		 }
	 }}}
	 for (int i = 0; i<r; i++) x[i] = b[i]/A[i][i];
 }
 
 void fullRowScale(double A[5][5], int i, int j, int c, double a){
	 for (int n = 0; n<c; n++){
		 //cout<<"added"<<A[i][n]*a<<endl;
		 A[j][n] += A[i][n]*a;
	 }
 }
 
 void testFullMatrixSolver(){
	const int r = 5; const int c = 5;
	double A[r][c] = {{-4,1,0,0,1},{4,-4,1,0,0},{0,1,-4,1,0},{0,0,1,-4,1},{1,0,0,1,-4}};
	
	double b[] = {1,2,3,4,5};
	double x[] = {0};
	
	fullSolve(A, x, b, r, c);
	cout<<"Test FullMatrixSolver: no error"<<endl;
 }

