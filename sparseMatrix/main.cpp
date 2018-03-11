#include "defs.h"
using namespace std;

int main(){
	testUpper();
	testList();
	testCrsOperations();


	ifstream file("rowPtr.txt");
    if(file.is_open())
    {
		cout<<"open"<<endl;
        string myArray[5001];

        for(int i = 0; i < 5001; ++i)
        {
            file >> myArray[i];
        }
    }
//		for (int i = 0; i < 5001; i++) 
//		cout <<"row"<<myArray[i]<<endl;
}
