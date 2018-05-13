#include <iostream>
#include <vector>

using namespace std;

struct CRSmatrix {
    vector<double> value;
    vector<int> rowPtr;
    vector<int> colInd;
    int rowNum;
    int colNum;

    //CRSmatrix constructor
    CRSmatrix(vector<double> v, vector<int> r, vector<int> c)
    {
        value = v;
        rowPtr = r;
        colInd = c;

        //find total number of rows
        rowNum = rowPtr.size()-1;

        //find total number of columns
        colNum = 0;
        for (int i = 0; i <= colInd.size(); i++) {
            if (colInd[i]>colNum) colNum = colInd[i];
        }
        colNum++;
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

    //multiply matrix with a vector x
    vector<double> productAx(vector<double> x){
        vector<double> product(x.size());
        for (int i = 0; i<rowNum; i++){
            for (int j = 0; j<colNum; j++){
                product[i] += x[j]*retrieveElement(i, j);
            }
        }
        return product;
    }
} ;

int main() {
    vector<double> value {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    vector<int> rowPtr {0, 3, 6, 9, 10, 12};
    vector<int> colInd {0, 1, 4, 0, 1, 2, 1, 2, 4, 3, 0, 4};

    CRSmatrix A (value, rowPtr, colInd);
    vector<double> x {5, 4, 3, 2, 1};

    vector<double> b = A.productAx(x);
    for (int i = 0; i<b.size(); i++){
        cout<<b[i]<<endl;
    }

    return 0;
}