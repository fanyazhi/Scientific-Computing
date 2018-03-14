#include "defs.h"
using namespace std;

/* Note: Helper functions in list.cpp are in pairs:
 * one version operates on double typed array, and another version operates on integer typed array
 */
 
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
void arrToListInt(int arr[], int arrSize, list<int>& mylist){
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
void listToArrInt(int arr[], list<int> mylist){
	int k = 0;
	for (int const &i: mylist) {
		arr[k++] = i;
		}
}

/* Helper function: arrSwap
 * swap the [i1:i2) and [j1:j2) elements of a double array
 */
void arrSwap(double arr[], int arrSize, int i1, int i2, int j1, int j2){
	list<double> mylist;
	list<double> templist;
	arrToList(arr, arrSize, mylist);
	templist.assign (mylist.begin(),mylist.end());
	//initiate iterators
	list<double>::iterator i1It = templist.begin(); advance(i1It, i1);
	list<double>::iterator i2It = templist.begin(); advance(i2It, i2-1);
	list<double>::iterator j1It = templist.begin(); advance(j1It, j1);
	list<double>::iterator j2It = templist.begin(); advance(j2It, j2-1);
	list<double>::iterator firstPos = templist.begin(); advance(firstPos, i2);
	list<double>::iterator secondPos = templist.begin(); advance(secondPos, j2);
	//cout<<*i1It<<*i2It<<*j1It<<*j2It<<*firstPos<<*secondPos<<endl;
	if (j1It != firstPos) templist.splice(firstPos, templist, j1It, secondPos);
//	for (auto v : templist)
//	cout << v << "\n";
	templist.splice(secondPos, templist, i1It, j1It);
	listToArr(arr, templist);

}
void arrSwapInt(int arr[], int arrSize, int i1, int i2, int j1, int j2){
	list<int> mylist;
	list<int> templist;
	arrToListInt(arr, arrSize, mylist);
	templist.assign (mylist.begin(),mylist.end());
	//initiate iterators
	list<int>::iterator i1It = templist.begin(); advance(i1It, i1);
	list<int>::iterator i2It = templist.begin(); advance(i2It, i2-1);
	list<int>::iterator j1It = templist.begin(); advance(j1It, j1);
	list<int>::iterator j2It = templist.begin(); advance(j2It, j2-1);
	list<int>::iterator firstPos = templist.begin(); advance(firstPos, i2);
	list<int>::iterator secondPos = templist.begin(); advance(secondPos, j2);
//	cout<<*i1It<<*i2It<<*j1It<<*j2It<<*firstPos<<*secondPos<<endl;
	if (j1It != firstPos) templist.splice(firstPos, templist, j1It, secondPos);
//	for (auto v : templist)
//	cout << v << "\n";
	templist.splice(secondPos, templist, i1It, j1It);
	listToArrInt(arr, templist);
}

/* Helper function: arrInsert
 * insert value a to an array at position pos
 */
 void arrInsert(double *arr[], int&arrSize, int pos, double a){
	 list<double> mylist;
	 arrToList(*arr, arrSize, mylist);
	 list<double>::iterator it = mylist.begin(); advance(it, pos);
	 mylist.insert(it, a);
	 arrSize++;
	 *arr = new double[arrSize];
	 listToArr(*arr, mylist);
 }
 void arrInsertInt(int *arr[], int&arrSize, int pos, int a){
	 list<int> mylist;
	 arrToListInt(*arr, arrSize, mylist);
	 list<int>::iterator it = mylist.begin(); advance(it, pos);
	 mylist.insert(it, a);
	 arrSize++;
	 *arr = new int[arrSize];
	 listToArrInt(*arr, mylist);
	 
 }
 /* Helper function: arrRemove
 * remove element of an array at position pos
 */
void arrRemove(double *arr[], int&arrSize, int pos){
	list<double> mylist;
	arrToList(*arr, arrSize, mylist);
	list<double>::iterator it = mylist.begin(); advance(it, pos);
	mylist.erase(it);
	arrSize--;
	*arr = new double[arrSize];
	listToArr(*arr, mylist);
}
void arrRemoveInt(int *arr[], int&arrSize, int pos){
	list<int> mylist;
	arrToListInt(*arr, arrSize, mylist);
	list<int>::iterator it = mylist.begin(); advance(it, pos);
	mylist.erase(it);
	arrSize--;
	*arr = new int[arrSize];
	listToArrInt(*arr, mylist);
}

/* Helper function: compareArr
 * compare if all elements in first list and second list have less than e difference (double only)
 * int firstSize: size of the first array
 * int secondSize: size of the second array
 * double e: epilson value (double only)
 */
bool compareArr(double first[], int firstSize, double second[], int secondSize, double e){
	for (int i = 0; i < firstSize; i++){
		if (abs(first[i] - second[i]) > e)
			return false;
	}
	return firstSize == secondSize;
}
bool compareArrInt(int first[], int firstSize, int second[], int secondSize){
	for (int i = 0; i < firstSize; i++){
		if (first[i] != second[i])
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
	cout << "Test arrSwap case 1: no error"<<endl:cout << "Test arrSwap case 1: error"<<endl;
	
	double arr3[] = {1.1,2.2,3.3,4.4,5.5,6.6,7.7};
	int arr3Size = sizeof(arr3)/sizeof(arr3[0]);
	arrSwap(arr3, arr3Size, 0, 3, 3, 6);
	double arrTest3[] = {4.4,5.5,6.6,1.1,2.2,3.3,7.7};//what the array should look like after swap
	compareArr(arr3, sizeof(arr3)/sizeof(arr3), arrTest3, sizeof(arrTest3)/sizeof(arrTest3), 0.0001)? 
	cout << "Test arrSwap case 2: no error"<<endl:cout << "Test arrSwap case 2: error"<<endl; 
	
	double arr4[] = {1.1,2.2,3.3,4.4,5.5,6.6,7.7};
	int arr4Size = sizeof(arr4)/sizeof(arr4[0]);
	arrSwap(arr4, arr4Size, 0, 1, 6, 7);
	double arrTest4[] = {7.7,2.2,3.3,4.4,5.5,6.6,1.1};//what the array should look like after swap
	compareArr(arr4, sizeof(arr4)/sizeof(arr4), arrTest4, sizeof(arrTest4)/sizeof(arrTest4), 0.0001)? 
	cout << "Test arrSwap case 3: no error"<<endl:cout << "Test arrSwap case 3: error"<<endl; 

}