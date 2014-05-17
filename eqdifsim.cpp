#include "eqdifsim.h"

StateSpace::StateSpace()
{

}

StateSpace::StateSpace(Matrix AdIn, Matrix BdIn, Matrix CdIn, Matrix DdIn, float Time)
{
    this->Ad = AdIn;
    this->Bd = BdIn;
    this->Cd = CdIn;
    this->Dd = DdIn;
    this->SampleTime = Time;
}

StateSpace::StateSpace(Matrix AIn, Matrix BIn, Matrix CIn, Matrix DIn)
{
    this->A = AIn;
    this->B = BIn;
    this->C = CIn;
    this->D = DIn;
    this->typeModel = "SSContinuous";
}

StateSpace::StateSpace(Matrix NumdIn, Matrix DendIn, float Time)
{
    this->Numd = NumdIn;
    this->Dend = DendIn;
    this->SampleTime = Time;
    this->typeModel = "TFDiscrete";
}

StateSpace::StateSpace(Matrix NumIn, Matrix DenIn)
{
    this->Num = NumIn;
    this->Den = DenIn;
    this->typeModel = "TFContinuous";
}

void StateSpace::c2d(float Time)
{
    this->SampleTime = Time;
    this->Ad.zeros(this->A.getRows(), this->A.getCols());
    for(int i = 0; i < 4; i++)
        this->Ad = this->Ad + (1/factorial(i))*(this->A^i)*(pow(this->SampleTime, i));
    this->Bd = this->A.inv()*(this->Ad - (this->Ad^0))*this->B;
    this->Cd = this->C;
    this->Dd = this->D;
    this->typeModel = "SSDiscrete";

}

void StateSpace::printSS()
{

    if (this->typeModel == "SSDiscrete")
    {
        cout<<endl<<"Ad = "<<endl;
        this->Ad.print();
        cout<<endl<<endl<<"Bd = "<<endl;
        this->Bd.print();
        cout<<endl<<"Cd = "<<endl;
        this->Cd.print();
        cout<<endl<<"Dd = "<<endl;
        this->Dd.print();
        cout<<endl<<endl;
    }
    else
    {
        cout<<endl<<"A = "<<endl;
        this->A.print();
        cout<<endl<<"B = "<<endl;
        this->B.print();
        cout<<endl<<"C = "<<endl;
        this->C.print();
        cout<<endl<<"D = "<<endl;
        this->D.print();
        cout<<endl;
    }

}

void StateSpace::tf2ss()
{
    Matrix I, ZeroVector, tempDen( 1, this->Den.getCols()-1);

    I.eye(this->Den.getCols()-2);
    ZeroVector.zeros( this->Den.getCols()-2, 1);
    for (int i = 2; i <= this->Den.getCols(); i++)
        tempDen.add( 1, i-1, -(this->Den.getMat( 1, i)));

    this->A = tempDen||(I|ZeroVector);
    this->B.zeros(this->A.getRows(), 1);
    this->B.add( 1, 1, 1);

    if (this->Num.getCols() == 1)
    {
        this->C.add( 1, this->B.getRows(), this->Num.getMat( 1, 1));
        this->D.add( 1, 1, 0);
    }
    else if (this->Num.getCols() < this->Den.getCols())
    {
        for (int i = this->B.getRows(); i > 1; i--)
            this->C.add( 1, i, this->Num.getMat( 1, this->Num.getCols() -( this->B.getRows() - i )));
        this->D.add( 1, 1, 0);
    }

    else if (this->Num.getCols() == this->Den.getCols())
    {
        float B0 = this->Num.getMat( 1, 1);

        for (int i = 1; i <= this->B.getRows(); i++)
         {
            C.add( 1, i, this->Num.getMat( 1, i+1)- this->Den.getMat( 1, i+1)*B0);
         }
        this->D.add( 1, 1,  B0);
    }







}

float StateSpace::factorial(float n)
{
    float retval = 1;

    for (int i = n; i > 1; --i)
        retval *= i;

    return retval;
}
