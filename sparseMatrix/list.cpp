#include "defs.h"
using namespace std;

/* Helper function: arrToList
 * converts an array to a linked list
 * double arr[]: array to be converted 
 * int arrSize: size of the array to be converted
 * list<double>& mylist: pointer to the list to be converted into
 */
void arrToList(double arr[], int arrSize, list<double>& mylist){
	for (int i=0; i<arrSize; i++){
		mylist.push_back(arr[i]);
	}
}
/* Helper function: listToArr
 * converts a list to an array
 * double arr[]: array to be converted into
 * list<double>& mylist: pointer to the list to be converted 
 */
void listToArr(double arr[], list<double> mylist){
	int k = 0;
	for (double const &i: mylist) {
		arr[k++] = i;
		}
}

/* Helper function: arrSwap
 * swap the [i1:i2) and [j1:j2) elements of an array
 */
void arrSwap(double arr[], int arrSize, int i1, int i2, int j1, int j2){
	list<double> mylist;
	list<double> templist;
	arrToList(arr, arrSize, mylist);
	templist.assign (mylist.begin(),mylist.end());
	//initiate iterators
	list<double>::iterator i1It = templist.begin(); advance(i1It, i1);
	list<double>::iterator i2It = templist.begin(); advance(i2It, i2);
	list<double>::iterator j1It = templist.begin(); advance(j1It, j1);
	list<double>::iterator j2It = templist.begin(); advance(j2It, j2);
	templist.splice(i1It, templist, j1It, j2It);
	templist.splice(j2It, templist, i1It, i2It);
	listToArr(arr, templist);
}

/* Helper function: compareArr
 * compare if all elements in first list and second list have less than e difference
 * int firstSize: size of the first array
 * int secondSize: size of the second array
 * double e: epilson value
 */
bool compareArr(double first[], int firstSize, double second[], int secondSize, double e){
	for (int i = 0; i < firstSize; i++){
		if (abs(first[i] - second[i]) > e)
			return false;
	}
	return firstSize == secondSize;
}


void testList(){
	/* Test arrToList and listToArr at the same time
	 * This test first converts an array to a list 
	 * and then convert the list back to a new array
	 */
	double arr[3] = {23.1,78.2,35.3};
	int arrSize = sizeof(arr)/sizeof(arr[0]);
	list<double> mylist;
	arrToList(arr, arrSize, mylist);
	double newarr[mylist.size()];
	listToArr(newarr, mylist);

	compareArr(arr, sizeof(arr)/sizeof(arr), newarr, sizeof(newarr)/sizeof(newarr), 0.0001)? 
	cout << "Test arrToList: no error"<<endl:cout << "Test arrToList: error"<<endl;
	
	
	/* Test arrSwap
	 */
	double arr2[] = {1.1,2.2,3.3,4.4,5.5,6.6};
	int arr2Size = sizeof(arr2)/sizeof(arr2[0]);
	arrSwap(arr2, arr2Size, 0, 2, 3, 6);
	double arrTest[] = {4.4,5.5,6.6,3.3,1.1,2.2};//what the array should look like after swap
	
	compareArr(arr2, sizeof(arr2)/sizeof(arr2), arrTest, sizeof(arrTest)/sizeof(arrTest), 0.0001)? 
	cout << "Test arrSwap: no error"<<endl:cout << "Test arrSwap: error"<<endl;
}