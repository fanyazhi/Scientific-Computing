/*
 *  main.cpp
 *  ODESolver
 *
 *  In this program, we implemented three ODE solving methods: forward Euler, RK4, and time adaptive RK34.
 *  The ODE solvers can take ODEs of any dimensions and any typed equations.
 *
 *  main.cpp provide three example uses of the ODE solver:
 *  1.  a single variable ODE with known solution, result from the three methods are compared with ground truth
 *      and error is reported
 *  2.  an AC circuit ODE, results from the three methods are compared
 *  3.  an CS amplifier ODE, results from the three methods are compared
 *
 *  Created by Yijia Chen (yc2366) and Yazhi Fan (yf92) on 4/18/18.
 *  Copyright © 2018 Yijia and Yazhi. All rights reserved.
 *
 */

#include <iostream>
#include <Eigen/Dense>
#include "forwardEuler.h"
#include "RK34.h"
#include "circuit.h"
#include "test.h"

using namespace std;
using namespace Eigen;

int main() {
    // Solving single variable ODE (Task 3)
    double singlet0 = 0, singletn = 5, singleh = 1; //start time, end time, and step size
    MatrixXd singleForwardResult, singleRK4Result, singleRK34Result, groundTruthResult;
    VectorXd singlex (1);
    singlex << 2;

    //get result from ODE solvers
    singleForwardResult = forwardEuler(testODE, singlex, singlet0, singletn, singleh);
    singleRK4Result = RK4(testODE, singlex, singlet0, singletn, singleh);
    singleRK34Result = RK34_adaptiveH(testODE, singlex, singlet0, singletn, singleh);

    //get result from ground truth
    groundTruthResult = testFunction(singlet0, singletn, singleh);

    //print result
    cout<<"Solving single variable ODE 4 * exp(0.8 * t) - 0.5 * x(0) (Task 3)"<<endl;
    cout<<"----------------------------------------------------------------------------------------"<<endl;
    for (int i = 0; i<singleForwardResult.size(); i++) {
        cout << "x("<<singlet0+singleh*i<<")"<<endl;
        cout << "ground truth: "<<groundTruthResult(i) <<" | ";
        cout << "forward Euler: "<<singleForwardResult(i) << "("<<
             percentError(groundTruthResult(i), singleForwardResult(i))<<"%)"<<" | ";
        cout << "RK4: "<<singleRK4Result(i) <<"("<<
             percentError(groundTruthResult(i), singleRK4Result(i))<<"%)"<<" | ";
        cout << "RK34: "<<singleRK34Result(i) <<"("<<
             percentError(groundTruthResult(i), singleRK34Result(i))<<"%)"<<" | "<<endl;
    }
    cout<<endl;



    //Solving RC circuit (Task 4)
    double RCt0 = 0, RCtn = 100E-9, RCh = 1E-9;
    MatrixXd RCForwardResult, RCRK4Result, RCRK34Result;
    VectorXd RCx (2);
    RCx << 0, 0;

    //get result from ODE solvers
    RCForwardResult = forwardEuler(RCcircuit, RCx, RCt0, RCtn, RCh);
    RCRK4Result = RK4(RCcircuit, RCx, RCt0, RCtn, RCh);
    RCRK34Result = RK34_adaptiveH(RCcircuit, RCx, RCt0, RCtn, RCh);

    //print result
    cout<<"Solving RC circuit (Task 4)"<<endl;
    cout<<"----------------------------------------------------------------------------------------"<<endl;
    for (int i = 0; i<RCRK4Result.cols(); i++) {
        cout << "x("<<RCt0+RCh*i<<")"<<endl;
        cout << "forward Euler: V1="<<RCForwardResult(0, i)<<" V2="<<RCForwardResult(1, i)<<" | ";
        cout << "RK4: V1="<<RCRK4Result(0, i)<<" V2="<<RCRK4Result(1, i)<<" | ";
        cout << "RK34: V1="<<RCRK34Result(0, i)<<" V2="<<RCRK34Result(1, i)<<" | "<<endl;
    }
    cout<<endl;



    //Solving CS amplifier (Task 5)
    double CSt0 = 0, CStn = 100E-9, CSh = 1E-9;
    MatrixXd CSForwardResult, CSRK4Result, CSRK34Result;
    VectorXd CSx (2);
    CSx << 2.5, 2.5;

    //get result from ODE solvers
    CSForwardResult = forwardEuler(CSamplifier, CSx, CSt0, CStn, CSh);
    CSRK4Result = RK4(CSamplifier, CSx, CSt0, CStn, CSh);
    CSRK34Result = RK34_adaptiveH(CSamplifier, CSx, CSt0, CStn, CSh);

    //print result
    cout<<"Solving CS amplifier (Task 5)"<<endl;
    cout<<"----------------------------------------------------------------------------------------"<<endl;
    for (int i = 0; i<CSRK4Result.cols(); i++) {
        cout << "x("<<CSt0+CSh*i<<")"<<endl;
        cout << "forward Euler: V1="<<CSForwardResult(0, i)<<" V2="<<CSForwardResult(1, i)<<" | ";
        cout << "RK4: V1="<<CSRK4Result(0, i)<<" V2="<<CSRK4Result(1, i)<<" | ";
        cout << "RK34: V1="<<CSRK34Result(0, i)<<" V2="<<CSRK34Result(1, i)<<" | "<<endl;
    }

    return 0;
}