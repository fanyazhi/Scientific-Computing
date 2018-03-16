//
//  Sparse Matrix Iterative Solver
//  
//	The main function reads three csv files, please change the 
// 	directories to your location of the files.
//
//  Created by Yazhi Fan(yf92) and Yijia Chen(yc2366) on 3/6/18.
//  Copyright © 2018 Yazhi and Yijia. All rights reserved.
//
#include "defs.h"
using namespace std;

int main(){
	//modularTests();

	/****read value.csv into a list****/
    list<double> myValueList;
    string myValue;
    ifstream inValue;
	inValue.open("/Users/Jane_Fan/Desktop/CodeLite/sparseMatrix/value.csv");
    if(!inValue.is_open()) cout<<"error: file open"<<endl;
	while(inValue.good()){
		getline(inValue,myValue,'\n');
		//convert string value to double value
		double myDoubleValue = atof(myValue.c_str());
        myValueList.push_back(myDoubleValue);
    }
	myValueList.pop_back();
	//convert value list into value array
	int valueSize = myValueList.size();
	double * value = new double[valueSize];
	listToArr(value, myValueList);
	inValue.close();
	
	/****read rowPtr.csv into a list****/
	list<int> myRowList;
    string myRow;
    ifstream inRow;
	inRow.open("/Users/Jane_Fan/Desktop/CodeLite/sparseMatrix/rowPtr.csv");
    if(!inRow.is_open()) cout<<"error: file open"<<endl;
	while(inRow.good()){
		getline(inRow,myRow,'\n');
		int myRowDoubleValue = atoi(myRow.c_str())-1;
        myRowList.push_back(myRowDoubleValue);
    }
	myRowList.pop_back();
	//convert value list into value array
	int rowPtrSize = myRowList.size();
	int *rowPtr  = new int[rowPtrSize];
	listToArrInt(rowPtr, myRowList);	
    inRow.close();
	
	/****read colInd.csv into a list****/
	list<int> myColList;
    string myCol;
    ifstream inCol;
	inCol.open("/Users/Jane_Fan/Desktop/CodeLite/sparseMatrix/colInd.csv");
    if(!inCol.is_open()) cout<<"error: file open"<<endl;
	while(inCol.good()){
		getline(inCol,myCol,'\n');
		int myColDoubleValue = atoi(myCol.c_str())-1;
        myColList.push_back(myColDoubleValue);
    }
	myColList.pop_back();
	
	//convert value list into value array
	int colIndSize = myColList.size();
	int *colInd  = new int[colIndSize];
	listToArrInt(colInd, myColList);
    inCol.close();
	
	cout<<"b=(1.0, 0, 0, …,0)^T: "<<endl;
	//initiate vector b
	int bSize = colNum(colInd, colIndSize);
	double* b = new double[bSize];
	for (int i = 0; i < bSize; i++) b[i] = 0;
	b[0] = 1;
	
	//initiate x to save the result
	double * x = new double[bSize];
	for (int i = 0; i < bSize; i++) x[i] = 0;
	jacobi(value, valueSize, rowPtr, rowPtrSize, colInd, colIndSize, b, bSize, x);
	
	cout<<endl;
	cout<<"b=(0, 0, 0, 0, 1.0, 0 …,0)^T: "<<endl;
	//initiate vector b
	int bSize2 = colNum(colInd, colIndSize);
	double* b2 = new double[bSize2];
	for (int i = 0; i < bSize2; i++) b2[i] = 0;
	b2[5] = 1;
	
	//initiate x to save the result
	double * x2 = new double[bSize2];
	for (int i = 0; i < bSize2; i++) x2[i] = 0;
	jacobi(value, valueSize, rowPtr, rowPtrSize, colInd, colIndSize, b2, bSize2, x2);
	
	cout<<endl;
	cout<<"b=(1.0, 1.0, 1.0, 1.0 …,1.0)^T: "<<endl;
	//initiate vector b
	int bSize3 = colNum(colInd, colIndSize);
	double* b3 = new double[bSize3];
	for (int i = 0; i < bSize3; i++) b3[i] = 1;
	
	//initiate x to save the result
	double * x3 = new double[bSize3];
	for (int i = 0; i < bSize3; i++) x3[i] = 0;
	jacobi(value, valueSize, rowPtr, rowPtrSize, colInd, colIndSize, b3, bSize3, x3);

	
    return 0;
}


