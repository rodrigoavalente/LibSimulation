#include "statespace.h"

StateSpace::StateSpace()
{

}

StateSpace::StateSpace(Matrix AdIn, Matrix BdIn, Matrix CdIn, Matrix DdIn, float Time)
{
    this->Ad = AdIn;
    this->Bd = BdIn;
    this->Cd = CdIn;
    this->Dd = DdIn;
}

StateSpace::StateSpace(Matrix AIn, Matrix BIn, Matrix CIn, Matrix DIn)
{
    this->A = AIn;
    this->B = BIn;
    this->C = CIn;
    this->D = DIn;
}

StateSpace::StateSpace(Matrix NumdIn, Matrix DendIn, float Time)
{
    this->Numd = NumdIn;
    this->Dend = DendIn;
}

StateSpace::StateSpace(Matrix NumIn, Matrix DenIn)
{
    this->Num = NumIn;
    this->Den = DenIn;
}

void StateSpace::c2d()
{
    for(int i = 0; i < 4; i++)
        this->Ad = this->Ad + (1/factorial(i))*(this->A^i)*(pow(this->SampleTime, i));
    this->Bd = this->A.inv()*(this->Ad - this->Ad^0)*this->B;
    this->Cd = this->C;
    this->Dd = this->D;
    this->typeModel = "SSDiscrete";

}

void StateSpace::printSS()
{

    if (this->typeModel == "SSDiscrete")
    {
        cout<<"Ad = "<<endl;
        this->Ad.print();
        cout<<"Bd = "<<endl;
        this->Bd.print();
        cout<<"Cd = "<<endl;
        this->Cd.print();
        cout<<"Dd = "<<endl;
        this->Dd.print();
    }

}

float StateSpace::factorial(float n)
{
    float retval = 1;

    for (int i = n; i > 1; --i)
        retval *= i;

    return retval;
}
