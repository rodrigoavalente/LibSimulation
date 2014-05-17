#ifndef EQDIFSIM_H
#define EQDIFSIM_H

#include "lsim.h"

class StateSpace
{
private:
    float SampleTime, TimeSimulation;
    Matrix A, B, C, D, Num, Den, Ad, Bd, Cd, Dd, Numd, Dend;
    string typeModel;

public:
    StateSpace();
    StateSpace(Matrix AIn, Matrix BIn, Matrix CIn, Matrix DIn);
    StateSpace(Matrix AdIn, Matrix BdIn, Matrix CdIn, Matrix DdIn, float Time);
    StateSpace(Matrix NumIn, Matrix DenIn);
    StateSpace(Matrix NumdIn, Matrix DendIn, float Time);

//    void ss2tf();
    void tf2ss();
    void printSS();
    void printTF();
    void c2d(float Time);

    float factorial(float n);
};

#endif // EQDIFSIM_H
