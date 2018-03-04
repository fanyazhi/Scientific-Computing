#include <iostream>
#include <vector>
#include <cstream>
#include <algorithm>
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

void matrix3::values_import(double a[], double b[], double c[]){
	value = a;
	rowInd = b;
	colInd = c;	
}

void matrix3::readtxt(){
	ifstream infile;   
  int num = 0; // num must start at 0
  infile.open("memplus.txt");// file containing numbers in 3 columns 
     if(infile.fail()) // checks to see if file opended 
    { 
      cout << "error" << endl; 
      return 1; // no point continuing if the file didn't open...
    } 
       while(!infile.eof()) // reads file to end of *file*, not line
      { 
         infile >> a[num]; // read first column number
         infile >> b[num]; // read second column number
         infile >> c[num]; // read third column number
         //cout<<exam1[num]<<" "<<exam2[num]<<" "<<exam3[num];
         ++num; // go to the next number

         // you can also do it on the same line like this:
         // infile >> exam1[num] >> exam2[num] >> exam3[num]; ++num;
      } 
  infile.close(); 
  return 0; // everything went right. 
}
void matrix3::rowPermute()
{
	cout << "switch row[i] and row[j] for matrix A and vector x\n";
	for (i=0;i<sizeof(rowPtr)-1;i++){
		rowLength.push_back(rowPtr[i+1]-rowPtr[i]);
	}
	
	swap(rowPtr[i],rowPtr[j]);
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
void matrix3::rowScaling(int i, int j, double a){
	int k,l,c;
	int des[], fac[];
	//extract destination row
	for(k = rowPtr[i-1]; k < rowPtr[i]; k++){
		if(k-rowPtr[i-1]+1 == colInd[i])
			des[k-rowPtr[i-1]+1] = value[k];
		else des[k-rowPtr[i-1]+1] = 0;
    }
    //extract factor row
    for(l=rowPtr[j-1]; l<rowPtr[j]; l++){
    	if(l-rowPtr[j-1]+) == colInd[l])
    		fac[l-rowPtr[j-1]+1] = value[l];
    	else fac[l-rowPtr[j-1]+1] = 0;
	}
	
	//calculate the result after *a and addition
	c = max_element(ColInd,ColInd+sizeof(ColInd));
	for(k=1; k<=c; k++){
		deski] += a*fac[k];
		value[rowPtr[i-1]+k] = des[k];
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
int main(){
	int input,k,l;
	double q;
	char ch;    
	matrix3 m;
	m.values_import();
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
