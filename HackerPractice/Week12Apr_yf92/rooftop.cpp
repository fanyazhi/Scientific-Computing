#include <iostream>
#include <math.h>

const double PI = 3.141592653589793;

using namespace std;

double f(double x){
    return sin(x);
}

double vk1(double xk0, double xk, double xk1, double x){
    if (x < xk && x >= xk0)
        return (x - xk0) / (xk - xk0);
    else if (x >= xk && x < xk1)
        return (xk1 - x) / (xk1 - xk);
    else
        return 0;
}

double vk2(double basepoint[], int size, int i, double x){
    // i-th rooftop line. Eg, in this practice, 1<=i<=7
    if (i > 0 && i < size - 1) {
        double xk = basepoint[i];
        double xk1 = basepoint[i + 1];
        double xk0 = basepoint[i - 1];
        if (x < xk && x >= xk0)
            return (x - xk0) / (xk - xk0);
        else if (x >= xk && x < xk1)
            return (xk1 - x) / (xk1 - xk);
        else
            return 0;
    }
    else return -1;//input a wrong format parameter
}

double cal_ak(double xk0, double xk, double xk1) {
    double temp = vk1(xk0, xk, xk1, xk);
    double ak = f(xk) / temp;
    return ak;
}

double* cal_ak(double basepoint[],int size) {
    double *ak = new double [size-1];
    for(int i = 1; i<size-1; i++) {
        double temp = vk2(basepoint,size,i,basepoint[i]);
        ak[i] = f(basepoint[i]) / temp;
    }
    return ak;
}

double rooftop(double xk[],int sizex, double ak[], int sizea, double x) {
    int l = sizex - 1;
    //l=8 in test example
    double result = 0;
    //over the range we do the approximation
    if(x>PI/2 || x<0) {
        return -1;
    }

    //first line
    if (x>=xk[0] && x<=xk[1]) {
        result = vk1(xk[0], xk[1],xk[2], x) * ak[1];
        return result;
    }
        //last line
    else if (x>=xk[l-1] && x<=xk[l]) {
        result = vk1(xk[l-2], xk[l-1],xk[l], x) * ak[l-1];
        return result;
    }
        //middle lines
    else {
        for (int i = 1; i<l-1;i++) {
            if (x>=xk[i] && x<=xk[i+1]) {
                double temp1 = vk1(xk[i-1], xk[i],xk[i+1], x) * ak[i];
                double temp2 = vk1(xk[i], xk[i+1],xk[i+2], x) * ak[i+1];
                result = temp1 + temp2;
                return result;
            }
        }
    }
    return result;
}



int main() {
    // TODO Auto-generated method stub
    int N = 8;
    double delta = PI / (2 * N);

    double* basepoint = new double[N + 1];
    basepoint[0] = 0;

    for (int i = 1; i < N + 1; i++) {
        basepoint[i] = basepoint[i - 1] + delta;
    }

    double* ak = new double[N];
//		for (int i = 1; i<N; i++) {
//			ak[i] = cal_ak(x[i-1],x[i],x[i+1]);
//		}
    ak = cal_ak(basepoint,N+1);

    //Use 100 points by the ground truth and approximated roof top function
    //to find the percentage error in the area estimate
    double* x = new double[100];
    double* error = new double[100];
    x[0] = 0;
    double dx = PI/200;
    for (int i = 1; i < 90; i++) {
        x[i] = x[i-1] + dx;
        double gt = f(x[i]);
        double apx = rooftop(basepoint,N+1, ak,N, x[i]);

        error[i] = abs((gt-apx)/gt);
        cout<<error[i]<<endl;
    }

    return 0;
}


