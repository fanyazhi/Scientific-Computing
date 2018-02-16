#pragma once;

/**
Generate INF 
*/
double geneINF();

/**
Generate NINF 
*/
double geneNINF();

/**
Generate NAN 
*/
double geneNaN();

/*INF test
return true if is the infinity, false otherwise
*/
bool isINF(double x);


/*NINF test
return true if is the negative infinity, false otherwise
*/
bool isNINF(double x);


/*NAN test
return true if is the Not a Number, false otherwise
*/
bool isNaN(double x);

/*Observe behavior in certain function
*/
void testFunction(double x);

/*Observe behavior in propagation and interaction
*/
void multiplyZero(double x);

/*Test interaction of infinity, negative infinty and NAN*/
void testInteraction();

/*Sum of all the test above*/
int floatingPointOperations();
