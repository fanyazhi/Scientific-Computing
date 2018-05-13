//
// Created by Jane Fan on 5/13/18.
//

#include "CRSmatrix.h"
#include "cubicSpline.h"

using namespace std;


CRSmatrix::CRSmatrix(vector<double> v, vector<int> r, vector<int> c)
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

CRSmatrix::CRSmatrix(int r, int c)
{
    rowNum = r;
    colNum = c;
}

double CRSmatrix::retrieveElement (int i, int j) {
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

void CRSmatrix::changeValue (double x, int i, int j) {
    bool found = 0;
    if (value.empty()){
        value.push_back(x);
        colInd.push_back(j);
        rowPtr.push_back(0);
        rowPtr.push_back(1);
    } else {
        value.push_back(x);
        colInd.push_back(j);
        if (rowPtr.size() <= i+1) rowPtr.push_back(value.size());
        else rowPtr[rowPtr.size()-1] = rowPtr[rowPtr.size()-1]+1;
    }
}

vector<double> CRSmatrix:: productAx(vector<double> x){
    vector<double> product(x.size());
    for (int i = 0; i<rowNum; i++){
        for (int j = 0; j<colNum; j++){
            product[i] += x[j]*retrieveElement(i, j);
            //cout<<"x["<<i<<"]" <<x[j]<<" * "<<retrieveElement(i, j)<<endl;
        }
    }
    return product;
}

void CRSmatrix::deleteValue(int i, int j){
    for (int n = rowPtr[i]; n<rowPtr[i]+ (rowPtr[i+1] - rowPtr[i]); n++){
        if (colInd[n] == j){
            value.erase(value.begin()+n);
            colInd.erase(colInd.begin()+n);
            for (int m = i+1; m<rowPtr.size(); m++) rowPtr[m]--;
        }
    }
}

void CRSmatrix::printA(){
    for (int valI = 0; valI<rowNum; valI++){
        for (int valJ = 0; valJ<colNum; valJ++){
            cout<<" "<<retrieveElement(valI, valJ);
        }
        cout<<endl;
    }
}

double vectorNorm(vector<double> x) {
    double sum = 0.0;
    for (int i = 0; i<x.size(); i++){
        sum += pow(x[i], 2);
    }
    return sqrt(sum);
}

//solve Ax = b
vector<double> Jacobi(CRSmatrix A, vector<double> b) {
    //first find the inverse of the diagonal matrix
    CRSmatrix Di = A;
    for (int i = 0; i<Di.rowNum; i++){
        for (int j = 0; j<Di.colNum; j++){
            //remove all elements other than the diagonal
            if (i != j){
                Di.deleteValue(i, j);
            }else{
                //take the inverse of the diagonal
                int pos;
                for (int n = Di.rowPtr[i]; n<Di.rowPtr[i]+(Di.rowPtr[i+1] - Di.rowPtr[i]); n++){
                    if (Di.colInd[n] == j){
                        pos = n;
                        Di.value[pos] = 1/Di.value[pos];
                    }
                }
            }
        }
    }

    //find L+U
    CRSmatrix LU = A;
    for (int i = 0; i<LU.rowNum; i++) {
        for (int j = 0; j < LU.colNum; j++) {
            if (i == j) {
                LU.deleteValue(i, j);
            }else {
                //take the inverse of the diagonal
                int pos;
                for (int n = LU.rowPtr[i]; n < LU.rowPtr[i] + (LU.rowPtr[i + 1] - LU.rowPtr[i]); n++) {
                    if (LU.colInd[n] == j) {
                        pos = n;
                        LU.value[pos] = -1.0 * LU.value[pos];
                    }
                }
            }
        }
    }


    //take D^-1 * (L+U), store in DLU
    CRSmatrix DLU = LU;
    for (int i = 0; i<DLU.rowNum; i++){
        for (int j = 0; j<DLU.colNum; j++){
            for (int n = DLU.rowPtr[i]; n<DLU.rowPtr[i]+(DLU.rowPtr[i+1] - DLU.rowPtr[i]); n++){
                if (DLU.colInd[n] == j){
                    DLU.value[n] = Di.value[i]*LU.retrieveElement(i, j);
                }
            }
        }
    }
    //Di.printA();
    //LU.printA();
    //DLU.printA();


    //find intercept D^-1 * b
    vector<double> cep(b.size());
    cep = Di.productAx(b);

    //initial guess is the same as the intercept
    vector<double> x = cep;

    //find vetor norm ||b-Ax|| of initial guess
    vector<double> normTemp(x.size());
    normTemp = A.productAx(x);
    for (int i = 0; i < b.size(); i++) {
        normTemp[i] = -1*normTemp[i];
        normTemp[i] = b[i] + normTemp[i];
    }
    int count=0;

    //start Jacobi iteration
    vector<double> xTemp(b.size());
    vector<double> prod (b.size());
    while (vectorNorm(normTemp) > 10E-7){
        count++;

        //x(k-1)
        for (int i = 0; i < b.size(); i++) {
            xTemp[i] = x[i];
        }

        //find product of D^-1(L+U)*x
        prod = DLU.productAx(xTemp);

        //add D^-1(L+U)*x to D^-1 * b, store in x
        for (int i = 0; i<x.size(); i++){
            x[i] = prod[i] + cep[i];
        }

        //cout<<"x(k-1) "<<xTemp[0]<<" x(k) "<<x[0]<<" "<<x[1]<<" "<<x[2]<<" "<<x[3]<<" "<<x[4]<<" "<<endl;
        //cout<<"DLU*x(k-1) "<<prod[0] << endl;

        //find new vetor norm ||x(k-1)-x||
        for (int i = 0; i < b.size(); i++) {
            normTemp[i] = -1.0*x[i];
            normTemp[i] = xTemp[i] + normTemp[i];
        }

        //cout<<"iteration #"<< count<<": "<<vectorNorm(normTemp)<<" "<<prod[1]<<endl;
    }
    return x;
}




