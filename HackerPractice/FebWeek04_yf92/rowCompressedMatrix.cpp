#include <iostream>
#include <vector>

using namespace std;
class matrix3
{
	int input, i, j;
	vector<int> value;
	vector<int> rowPtr;
	vector<int> colInd; 
	vector<int> rowLength;
	vector<int> xVector;
	vector<int> product;
	double a;
	public :
		void values();
		void rowPermute(int i, int j);
		void rowScaling(int i, int j, double a);
		void productAx();
};
void matrix3::values()
{
	//input row compressed matrix
	cout << "Enter the values, enter 0 when finished   ";
	while ((cin >> input) && (input!=0)){
		value.push_back(input);
	}
	cout << "Enter the row pointer, enter 999 when finished   "; 
	while ((input!=999) && (cin >> input)){
		rowPtr.push_back(input);
	}
	cout << "Enter the column indicies, enter 0 when finished  \n\n";
	while ((cin >> input) && (input!=0)){
		colInd.push_back(input);
	}
	//input vector x if needed
	cout << "Enter the vector x, enter 0 if not needed or is finished   "; 
	while ((cin >> input) && (input!=0)){
		xVector.push_back(input);
	}

}
void matrix3::rowPermute(int i, int j)
{
	cout << "switch row[i] and row[j] for matrix A and vector x\n";
	for (int i=0;i<sizeof(rowPtr)-1;i++){
		rowLength.push_back(rowPtr[i+1]-rowPtr[i]);
	}
	
	swap(rowPtr[i],rowPtr[j]);
	//print out results
	vector<int>::iterator it;
	it = value.begin();
	for (it=value.begin(); it<value.end(); it++)
		std::cout << ' ' << *it;
    std::cout << '\n';
	it = colInd.begin();
	for (it=colInd.begin(); it<colInd.end(); it++)
		std::cout << ' ' << *it;
    std::cout << '\n';
	it = rowPtr.begin();
	for (it=rowPtr.begin(); it<rowPtr.end(); it++)
		std::cout << ' ' << *it;
    std::cout << '\n';

}
void matrix3::rowScaling(int i, int j, double a)
{
	cout << "row scaling of the matrix is\n";
	int k,l,c;
	vector<int> des;
	vector<int> fac;
	//extract destination row
	for(k = rowPtr[i-1]; k < rowPtr[i]; k++){
		if(k-rowPtr[i-1]+1 == colInd[i])
			des[k-rowPtr[i-1]+1] = value[k];
		else des[k-rowPtr[i-1]+1] = 0;
    }
    //extract factor row
    for(l=rowPtr[j-1]; l<rowPtr[j]; l++){
    	if((l-rowPtr[j-1]+1) == colInd[l])
    		fac[l-rowPtr[j-1]+1] = value[l];
    	else fac[l-rowPtr[j-1]+1] = 0;
	}
	
	//calculate the result after *a and addition
	c = *max_element(colInd.begin(),colInd.end());
	for(k=1; k<=c; k++){
		des[k] += a*fac[k];
		value[rowPtr[i-1]] = des[k];
	}    

  
}
void matrix3::productAx()
{
	cout << "switch row[i] and row[j] for matrix A and vector x\n";
		for (i=1;i<=sizeof(rowPtr);i++){
		for (j=rowPtr[i];j<=rowPtr[i+1]-1;j++){
		product[i]=product[i]+value[j]*xVector[colInd[j]];
		}
	}
}
int main()
{
int input,k,l;
	double q;
	char ch;    
	matrix3 m;
	m.values();
	do
	 {
	cout << "Enter your choice\n";
	cout << " 1. Row permute\n" << " 2. Row scaling\n" << " 3. Vector product\n";
	cin >> input;
	switch (input)
	{
		case 1:
			cout << "Enter two row indecs,Switch row[k] and row[l] for matrix A\n";
			cin >> k;
			cin >> l;
			m.rowPermute(k, l);
			break;

		case 2:
			cout << "Add q*row[k] to row[l],order:k,l,q\n";
			cin >> k;
			cin >> l;
			cin >> q;
			m.rowScaling(k,l,q);
			break;

		case 3:
			cout << "Return the product of Ax\n";
			m.productAx();
			break;
	}
	cout << "\nDo another y/n?";
	cin >> ch;
	}
	while (ch!= 'n');
	cout << "\n";
	system ("pause");
return 0;
}
