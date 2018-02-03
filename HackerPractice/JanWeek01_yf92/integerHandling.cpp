#include <iostream>

using namespace std;

int main()
{
    long i = 1; int intFactorial = 1;

    for (i=2;i<20;i++){
        intFactorial *= i;
        cout<<intFactorial<<endl;
    }
    for (i=20;i>20;i--){
        intFactorial /= i;
        cout<<intFactorial<<endl;
    }
    return 0;
}
