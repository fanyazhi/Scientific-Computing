#include <iostream>
#include <cmath>
#include <limits>
#include <cfloat>
#include <fstream>
#include <cstdio>
#include <iomanip>

using namespace std;

class HP2{
	public:
		/*find the sparsity of every row*/
		int maxSparsity(int A[][5], int size){
			int s[size] = {0};
			int i,j;
			for(i=0;i<size;i++){
				for(j=0;j<size;j++){
					if(A[i][j]==0) s[i]++;
				}	
		    }  
			int idx = 0; int m=s[0];
			for(i=0;i<(size-1);i++)
				if(m<s[i+1]){
					idx = i+1;
					m = s[i+1];
				}
		    return idx;	 //return 3, which is the index of the row with bigest sparsity
		}
		/*sort the sparsity descending*/
		
		void rowPermute(int A[5][5], int i, int j){
			int tempA[5][5] = {0};
			for (int a=0; a<5; a++){
				for (int b=0; b<5; b++){
					tempA[a][b] = A[a][b];
				}
			} 
			for (int c=0; c<5; c++){
				A[i][c] = tempA[j][c];
				A[j][c] = tempA[i][c];
			}
		}// swap row(maybe in main func)
		
		void rowScale(int A[5][5], double x, int i, int j){
			for (int c=0; c<5; c++){
				A[j][c] = A[j][c]*x - A[i][c];
			}
		}
		
		void removeFirst(int A[5][5], int B[4][5]){
			for (int a=0; a<4; a++){
				for (int b=0; b<5; b++){
					B[a][b] = A [a+1][b];
				}
			}
		}
		void pivot(int A[5][5], int rowIdx){
			int j;
			for(j=0;j<5;j++){
				if(A[rowIdx][j]!=0){
					cancel(A,rowIdx,j);
				}
			}			
		}
		
		void cancel(int A[5][5],int i, int j){
			
		} 		
};




 int main(){
 	HP2 HP2;
 	int A[5][5] = {{1,2,0,0,3},{4,5,6,0,0},{0,7,8,0,9},{0,0,0,10,0},{11,0,0,0,12}};
 	
 	int maxS = HP2.maxSparsity(A, 5);
	HP2.rowPermute(A, 1, maxS);
	for (int i = 0; i<5; i++){
		if (A[i][maxS] !=0) HP2.rowScale(A, A[0][maxS], 0, i);
	}	
	
 	return 0;
 } 
 
 
