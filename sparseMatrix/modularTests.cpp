#include "defs.h"
using namespace std;

/*This file calls all the modular tests 
 */
 
 void modularTests(){
	cout<<"Method tests"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	testNorms();
	testList();
	testCrsOperations();
	cout<<endl;
	cout<<"Main method tests under Wilkinson Principle"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	testFullMatrixSolver();
 }