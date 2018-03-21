#include <iostream>
#include <cmath>
#include <limits>
#include <cfloat>
#include <fstream>
#include <cstdio>
#include <iomanip>

using namespace std;
class HP3{
	public:
		int firstNormF(int mtx[5][5]){
		int i,j,m,n;
		m = 5;
		n = 5;
		int l[5]={0};
		for(i=0; i<n; i++){
			for(j=0;j<m;j++){
				l[i]+=abs(mtx[j][i]);
			
			}
		}
		
		return maxElem(l);
	} 
	
	int maxElem(int x[5]){
		int i,m=0;
		for(i=0;i<5;i++){
			m = max(m,abs(x[i]));
		}
		return m;
	}
	
	int infNormF(int mtx[5][5]){
		int i,j,m,n;
		m = 5;
		n = sizeof mtx[0]/sizeof mtx[0][0];
		int l[5];
		
		for(i=0; i<m; i++){
			l[i] = 0;
			for(j=0;j<n;j++){
				l[i]+=abs(mtx[i][j]);
			}
		}
		return maxElem(l);
	} 
	
};

int main(){
	int mtx[5][5]={{1,2,0,0,3},{4,5,6,0,0},{0,7,8,0,9},{0,0,0,10,0},{11,0,0,0,12}};
	HP3 HP3;
	cout<< HP3.firstNormF(mtx) <<endl;
	cout<< HP3.infNormF(mtx) << endl;
	return 0;
}