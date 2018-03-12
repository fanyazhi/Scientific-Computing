#include "defs.h"
using namespace std;

 /* Helper function: rowPermute
 * Switch row[i] and row[j]
 * Note: index of the first row is 0
 */
void rowPermute(double value[], int valueSize, int rowPtr[], int colInd[], int colIndSize, int i, int j){
	//cout<<rowPtr[i]<<" "<<rowPtr[i+1]<<" "<<rowPtr[j]<<" "<<rowPtr[j+1]<<endl;
	arrSwap(value, valueSize, rowPtr[i], rowPtr[i+1], rowPtr[j], rowPtr[j+1]);
	arrSwapInt(colInd, colIndSize, rowPtr[i], rowPtr[i+1], rowPtr[j], rowPtr[j+1]);
	if (rowSize(rowPtr, i) != rowSize(rowPtr, j)){
		int diff = rowSize(rowPtr, j)-rowSize(rowPtr, i);
		for (int a = i+1; a<=j; a++){
			rowPtr[a] += diff;
		}
	}
}
 /* Helper function: rowScale
 * add a*row[i] to row [j]
 * Note: index of the first row is 0
 */
void rowScale(double *value[], int &valueSize, int rowPtr[], int rowPtrSize, int *colInd[], int &colIndSize, double a, int i, int j){
	//find the lengths of row i and j
	int iColInd = rowPtr[i];
	int jColInd = rowPtr[j];
	int maxRow = rowPtr[i]+rowSize(rowPtr, i);
	while (iColInd<maxRow){
		if ((*colInd)[iColInd] ==(*colInd)[jColInd]){
			//cout<<"same :"<<"colInd["<<iColInd<<"] = "<<(*colInd)[iColInd]<<" "<<"colInd["<<jColInd<<"] = "<<(*colInd)[jColInd]<<endl;
			//if the addition results in 0, delete value[jColInd] and colInd[jColInd]
			if (abs((*value)[jColInd] + (*value)[iColInd]*a) < DBL_MIN){
				arrRemove(value, valueSize, jColInd);
				arrRemoveInt(colInd, colIndSize, jColInd);
				for (int n = j+1; n<rowPtrSize; n++) rowPtr[n]--;
				(i>j)? iColInd--:iColInd;
				(i>j)? maxRow--: maxRow;
			}else{
				(*value)[jColInd] += (*value)[iColInd]*a;
			}
			iColInd++; 
			//for (int i = 0; i < valueSize; i++) cout <<" "<<(*value)[i];cout<<endl;
		}else if ((*colInd)[iColInd] <(*colInd)[jColInd]){
			//cout<<"insert to empty j :"<<"colInd["<<iColInd<<"] = "<<(*colInd)[iColInd]<<" "<<"colInd["<<jColInd<<"] = "<<(*colInd)[jColInd]<<endl;
			//insert new element to row j, for value[] and colInd[]
			arrInsert(value, valueSize, jColInd, (*value)[iColInd]*a);
			arrInsertInt(colInd, colIndSize, jColInd, (*colInd)[iColInd]);
			//add 1 to all elements in rowPtr from row j
			for (int n = j+1; n<rowPtrSize; n++) rowPtr[n]++;
			(i>j)? iColInd+=2: iColInd ++; 
			(i>j)? maxRow++: maxRow;
			jColInd ++;//only because a new element is inserted to colInd[]
			//for (int i = 0; i < valueSize; i++) cout <<" "<<(*value)[i];cout<<endl;
		}else{
			//cout<<"skip this j : "<<"colInd["<<iColInd<<"] = "<<(*colInd)[iColInd]<<" "<<"colInd["<<jColInd<<"] = "<<(*colInd)[jColInd]<<endl;
			jColInd++;
		}
	}
//		for (int i = 0; i < valueSize; i++) 
//		cout <<"value"<<(*value)[i]<<endl;
//		for (int i = 0; i < colIndSize; i++) 
//		cout <<"col"<<(*colInd)[i]<<endl;
//		for (int i = 0; i < rowPtrSize; i++) 
//		cout <<"row"<<rowPtr[i]<<endl;
}

 /* Helper function: retrieve
 * return value[i][j], ith row and jth column
 */
double retrieve(double value[], int rowPtr[], int colInd[], int i, int j){
	int pos = rowPtr[i];
	bool found = 0;
	for (int n = rowPtr[i]; n<rowPtr[i]+rowSize(rowPtr, i); n++){
		if (colInd[n] == j){
			pos = n;
			found = 1;
		}
	}
	if (found) return value[pos];
	return 0.0;
}

 /* Helper function: deleteValue
 * delete value[i][j], ith row and jth column
 * also delete colInd[i][j], and change rowPtr accordingly
 */
void deleteValue(double *value[], int &valueSize, int rowPtr[], int rowPtrSize, int *colInd[], int &colIndSize, int i, int j){
	int pos = rowPtr[i];
	for (int n = rowPtr[i]; n<rowPtr[i]+rowSize(rowPtr, i); n++){
		if ((*colInd)[n] == j){
			pos = n;
			arrRemove(value, valueSize, pos);
			arrRemoveInt(colInd, colIndSize, pos);
			for (int m = i+1; m<rowPtrSize; m++) rowPtr[m]--;
		}
	}
}

 /* Helper function: negative
  * make value[i][j] = -1* value[i][j]
 */
void negative(double value[], int rowPtr[], int colInd[], int i, int j){
	int pos = rowPtr[i];
	for (int n = rowPtr[i]; n<rowPtr[i]+rowSize(rowPtr, i); n++){
		if (colInd[n] == j){
			pos = n;
			value[pos] *= -1.0;
		}
	}
}

 /* Helper function: inverse
  * make value[i][j] = value^-1[i][j]
 */
void inverse(double value[], int rowPtr[], int colInd[], int i, int j){
	int pos = rowPtr[i];
	for (int n = rowPtr[i]; n<rowPtr[i]+rowSize(rowPtr, i); n++){
		if (colInd[n] == j){
			pos = n;
			value[pos] = 1/value[pos];
		}
	}
}

 /* Helper function: rowSize
 * return the number of elements in row r
 * Note: index of the first row is 0
 */
int rowSize(int rowPtr[], int r){
	return rowPtr[r+1] - rowPtr[r];
}

 /* Helper function: printA
 * print the matrix with cout
 */
void printA(double value[], int colInd[], int colIndSize, int rowPtr[], int rowPtrSize){
	int totalCol = colNum(colInd, colIndSize);
	int totalRow = rowPtrSize-1;
	for (int valI = 0; valI<totalRow; valI++){
		for (int valJ = 0; valJ<totalCol; valJ++){
			cout<<" "<<retrieve(value, rowPtr, colInd, valI, valJ);
		}
		cout<<endl;
	}
}


//tests for the various functions in crsOperations.cpp
void testCrsOperations(){
	int valueSize = 12;
	int rowPtrSize = 6;
	int colIndSize = 12;
	
	double* value = new double[valueSize];
	double assignValue[] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0};
	for (int i = 0; i < valueSize; i++) value[i] = assignValue[i];
		
	int* rowPtr = new int[rowPtrSize];
	int assignRowPtr[] = {0,3,6,9,10,12};
	for (int i = 0; i < rowPtrSize; i++) rowPtr[i] = assignRowPtr[i];
	
	int* colInd = new int[colIndSize];
	int assignColInd[] = {0,1,4,0,1,2,1,2,4,3,0,4};
	for (int i = 0; i < colIndSize; i++) colInd[i] = assignColInd[i];
	
	//rowPermute tests
	int i = 0; int j = 1;
	double valTest[] = {4.0,5.0,6.0,1.0,2.0,3.0,7.0,8.0,9.0,10.0,11.0,12.0};
	int colTest[] = {0,1,2,0,1,4,1,2,4,3,0,4};
	int rowTest[] = {0,3,6,9,10,12};
	rowPermute(value, valueSize, rowPtr, colInd, colIndSize, i, j);
	compareArr(value, valueSize, valTest, sizeof(valTest)/sizeof(valTest[0]), 0.0001)
	&& compareArrInt(colInd, colIndSize, colTest, sizeof(colTest)/sizeof(colTest[0]))
	&& compareArrInt(rowPtr, rowPtrSize, rowTest, sizeof(rowTest)/sizeof(rowTest[0]))? 
	cout << "Test rowPermute case 1: no error"<<endl:cout << "Test rowPermute case 1: error"<<endl; 
	
	int i1 = 3; int j1 = 4;
	double valTest1[] = {4.0,5.0,6.0,1.0,2.0,3.0,7.0,8.0,9.0,11.0,12.0,10.0};
	int colTest1[] = {0,1,2,0,1,4,1,2,4,0,4,3};
	int rowTest1[] = {0,3,6,9,11,12};
	rowPermute(value, valueSize, rowPtr, colInd, colIndSize, i1, j1);
	compareArr(value, valueSize, valTest1, sizeof(valTest1)/sizeof(valTest1[0]), 0.0001)
	&& compareArrInt(colInd, valueSize, colTest1, sizeof(colTest1)/sizeof(colTest1[0]))
	&& compareArrInt(rowPtr, rowPtrSize, rowTest1, sizeof(rowTest1)/sizeof(rowTest1[0]))? 
	cout << "Test rowPermute case 2: no error"<<endl:cout << "Test rowPermute case 2: error"<<endl; 
	
	int i2 = 0; int j2 = 4;
	double valTest2[] = {10.0,1.0,2.0,3.0,7.0,8.0,9.0,11.0,12.0,4.0,5.0,6.0};
	int colTest2[] = {3,0,1,4,1,2,4,0,4,0,1,2};
	int rowTest2[] = {0,1,4,7,9,12};
	rowPermute(value, valueSize, rowPtr, colInd, colIndSize, i2, j2);
	compareArr(value, valueSize, valTest2, sizeof(valTest2)/sizeof(valTest2[0]), 0.0001)
	&& compareArrInt(colInd, colIndSize, colTest2, sizeof(colTest2)/sizeof(colTest2[0]))
	&& compareArrInt(rowPtr, rowPtrSize, rowTest2, sizeof(rowTest2)/sizeof(rowTest2[0]))? 
	cout << "Test rowPermute case 3: no error"<<endl:cout << "Test rowPermute case 3: error"<<endl; 
	
	//rowScale tests
	double a = 2.0;
	int r1 = 1; int r2 = 2;
	double valTest3[] = {10.0,1.0,2.0,3.0,2.0,11.0,8.0,15.0,11.0,12.0,4.0,5.0,6.0};
	int colTest3[] = {3,0,1,4,0,1,2,4,0,4,0,1,2};
	int rowTest3[] = {0,1,4,8,10,13};
	rowScale(&value, valueSize, rowPtr, rowPtrSize, &colInd, colIndSize, a, r1, r2);
	compareArr(value, valueSize, valTest3, sizeof(valTest3)/sizeof(valTest3[0]), 0.0001)
	&& compareArrInt(colInd, colIndSize, colTest3, sizeof(colTest3)/sizeof(colTest3[0]))
	&& compareArrInt(rowPtr, rowPtrSize, rowTest3, sizeof(rowTest3)/sizeof(rowTest3[0]))?
	cout << "Test rowScale case 1: no error"<<endl:cout << "Test rowScale case 1: error"<<endl;
	
	double a2 = 2.0;
	int r3 = 4; int r4 = 0;
	double valTest4[] = {8.0,10.0,12.0,10.0,1.0,2.0,3.0,2.0,11.0,8.0,15.0,11.0,12.0,4.0,5.0,6.0};
	int colTest4[] = {0,1,2,3,0,1,4,0,1,2,4,0,4,0,1,2};
	int rowTest4[] = {0,4,7,11,13,16};
	rowScale(&value, valueSize, rowPtr, rowPtrSize, &colInd, colIndSize, a2, r3, r4);
	compareArr(value, valueSize, valTest4, sizeof(valTest4)/sizeof(valTest4[0]), 0.0001)
	&& compareArrInt(colInd, colIndSize, colTest4, sizeof(colTest4)/sizeof(colTest4[0]))
	&& compareArrInt(rowPtr, rowPtrSize, rowTest4, sizeof(rowTest4)/sizeof(rowTest4[0]))?
	cout << "Test rowScale case 2: no error"<<endl:cout << "Test rowScale case 2: error"<<endl;

	double a3 = -0.5;
	int r5 = 0; int r6 = 4;
	double valTest5[] = {8.0,10.0,12.0,10.0,1.0,2.0,3.0,2.0,11.0,8.0,15.0,11.0,12.0,-5.0};
	int colTest5[] = {0,1,2,3,0,1,4,0,1,2,4,0,4,3};
	int rowTest5[] = {0,4,7,11,13,14};
	rowScale(&value, valueSize, rowPtr, rowPtrSize, &colInd, colIndSize, a3, r5, r6);
	compareArr(value, valueSize, valTest5, sizeof(valTest5)/sizeof(valTest5[0]), 0.0001)
	&& compareArrInt(colInd, colIndSize, colTest5, sizeof(colTest5)/sizeof(colTest5[0]))
	&& compareArrInt(rowPtr, rowPtrSize, rowTest5, sizeof(rowTest5)/sizeof(rowTest5[0]))?
	cout << "Test rowScale case 3 with deletion: no error"<<endl:cout << "Test rowScale case 3 with deletion: error"<<endl;
}
