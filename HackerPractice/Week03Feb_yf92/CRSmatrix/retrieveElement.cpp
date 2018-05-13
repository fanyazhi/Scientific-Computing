#include <iostream>
#include <vector>

using namespace std;

struct CRSmatrix {
    vector<double> value;
    vector<int> rowPtr;
    vector<int> colInd;

    //constructor
    CRSmatrix(vector<double> v, vector<int> r, vector<int> c)
    {
        value = v;
        rowPtr = r;
        colInd = c;
    }

    //return value at [i][j]
    double retrieveElement (int i, int j) {
        int pos = rowPtr[i];
        bool found = 0;
        for (int n = rowPtr[i]; n<rowPtr[i]+ (rowPtr[i+1] - rowPtr[i]); n++){
            if (colInd[n] == j){
                pos = n;
                found = 1;
            }
        }
        if (found) return value[pos];
        return 0.0;
    }
} ;

int main() {
    vector<double> value {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    vector<int> rowPtr {0, 3, 6, 9, 10, 12};
    vector<int> colInd {0, 1, 4, 0, 1, 2, 1, 2, 4, 3, 0, 4};

    CRSmatrix A (value, rowPtr, colInd);

    double x = A.retrieveElement(4,4);
    cout<<x<<endl;

    return 0;
}

