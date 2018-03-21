#include <iostream>
#include <vector>
#include <cstream>
using namespace std;
class matrix3
{
	int input;
	vector<int> value;
	vector<int> rowPtr;
	vector<int> colInd; 
	vector<int> rowLength;
	public :
		void values();
		int rowPermute();
		int rowScaling();
		int productAx();
};
void matrix3::values()
{
	cout << "Enter the values, enter 0 when finished   ";
	while ((cin >> input) && (input!=0)){
		value.push_back(input);
	}
	cout << "Enter the row pointer, enter 0 when finished   "; 
	while ((cin >> input) && (input!=0)){
		rowPtr.push_back(input);
	}
	cout << "Enter the column indicies\n\n";
	while ((cin >> input) && (input!=0)){
		colInd.push_back(input);
	}
}
void matrix3::rowPermute()
{
	cout << "switch row[i] and row[j] for matrix A and vector x\n";
	/*for (i=0;i<sizeof(rowPtr)-1;i++){
		rowLength.push_back(rowPtr[i+1]-rowPtr[i]);
	}
	
	swap(rowPtr[i],rowPtr[j]);*/
	for (int a=0;a<=rowPtr[i+1]-1-rowPtr[i];a++){
		iter_swap(value+rowPtr[i]+a,value+rowPtr[j]+a);  
		iter_swap(colInd.begin()+rowPtr[i]+a,colInd.begin()+rowPtr[j]+a); 
	}
	int row = 0;
	for(int i=0; i < colInd.size(); i++){
		if (colInd[i]==1) {
			rowPtr[row]=i;row++;
		}
	}
	//print out results
	for (it=value.begin(); it<value.end(); it++)
		std::cout << ' ' << *it;
    std::cout << '\n';
	for (it=colInd.begin(); it<colInd.end(); it++)
		std::cout << ' ' << *it;
    std::cout << '\n';
	for (it=rowPtr.begin(); it<rowPtr.end(); it++)
		std::cout << ' ' << *it;
    std::cout << '\n';

}
void matrix3::rowScaling()
{
	cout << "row scaling of the matrix is\n";

  
}
void matrix3::productAx()
{
	cout << "product of the matrix and vector is\n";
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
			m.rowScale(k,l,q);
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
