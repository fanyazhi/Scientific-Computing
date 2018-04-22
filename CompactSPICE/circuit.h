/*
 *  circuit.h
 *  ODESolver
 *  This file contains declarations for RC circuit and CS amplifier
 *
 *  Created by Yijia Chen (yc2366) and Yazhi Fan (yf92) on 4/18/18.
 *  Copyright © 2018 Yijia and Yazhi. All rights reserved.
 *
 */

#ifndef ODESOLVER_CIRCUIT_H
#define ODESOLVER_CIRCUIT_H

#include <vector>
#include <iostream>
#include <cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// ----------------------------------------------------------------------------------------

/* RC circuit ODE
        Parameters:
                t: time
                x: V1 and V2
        Return:
                dV1/dt and dV2/dt
*/
VectorXd RCcircuit(double t, VectorXd x);

// ----------------------------------------------------------------------------------------

/* CS amplifier ODE
        Parameters:
                t: time
                x: V1(VGS) and V2(VDS)
        Return:
                dV1/dt and dV2/dt
*/
VectorXd CSamplifier(double t, VectorXd x);

// ----------------------------------------------------------------------------------------

/* current source i(t)
        Parameters:
                t: time
        Return:
                current at time t
*/
double currentSource (double t);

// ----------------------------------------------------------------------------------------

/* EKV equation
        Parameters:
                VGS, VDS, IS, k, VTH, VT
                all in SI units
        Return:
                ID,EKS
*/
double EKV (double VGS, double VDS, double IS, double k, double VTH, double VT);


#endif //ODESOLVER_CIRCUIT_H
