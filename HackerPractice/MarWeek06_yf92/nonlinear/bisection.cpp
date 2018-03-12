//

//  main.cpp

//  Week6

//

//  Created by YJ C and YZ F on 3/4/18.

//  Copyright © 2018 YJ C. All rights reserved.

//



#include <iostream>

#include <cmath>

using namespace std;



double f(double x){

    return exp(x)-1;

}



int main() {

    double i=-5, j=10, temp=(i+j)/2;

    cout<<temp<<endl;

    while(abs(f(temp))>10e-7){

        if(f(temp)*f(i)>=0)

            i = temp;

        else j = temp;

        temp = (i+j)/2;

    }

    cout << temp <<endl;

    cout << f(5.96046e-07) <<endl;

    cout << f(1)<<endl;

    return 0;

}

