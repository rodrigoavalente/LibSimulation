#ifndef STATESPACE_H
#define STATESPACE_H

#include "lsim.h"

class StateSpace //Lembrando que essa classe não está representando somente uma representação de equações diferenciais  na
                //forma de espaço de estados, mas também na forma de função de transferência e ainda nas suas formas discretas
                //Portanto o nome da classe deveria ser mudado para que isso seja claro
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
//    void tf2ss();
    void printSS();
    void printTF();
    void c2d();

    float factorial(float n);
};

#endif // STATESPACE_H
