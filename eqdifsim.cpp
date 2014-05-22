#include "eqdifsim.h"

EqdifSim::EqdifSim()
{

}

EqdifSim::EqdifSim(Matrix AdIn, Matrix BdIn, Matrix CdIn, Matrix DdIn, float Time)
{
    this->Ad = AdIn;
    this->Bd = BdIn;
    this->Cd = CdIn;
    this->Dd = DdIn;
    ss2tfd();
    this->SampleTime = Time;
}

EqdifSim::EqdifSim(Matrix AIn, Matrix BIn, Matrix CIn, Matrix DIn)
{
    this->A = AIn;
    this->B = BIn;
    this->C = CIn;
    this->D = DIn;
    ss2tfc();
    this->typeModel = "SSContinuous";

}

EqdifSim::EqdifSim(Matrix NumdIn, Matrix DendIn, float Time)
{
    this->Numd = NumdIn;
    this->Dend = DendIn;
    this->SampleTime = Time;
    tf2ssd();
    this->typeModel = "TFDiscrete";
}

EqdifSim::EqdifSim(Matrix NumIn, Matrix DenIn)
{
    this->Num = NumIn;
    this->Den = DenIn;
    tf2ssc();
    this->typeModel = "TFContinuous";
}

void EqdifSim::c2d(float Time)
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

void EqdifSim::d2c()
{
    Matrix Mat, E, Temp, Root, I, ZeroVector;




    Mat = this->Ad.eigenvalues();

    for(int j = 1; j < 4; j++)//deixar a ordem flexivel
        E.add( 1, j+1, pow(this->SampleTime, j)/factorial(j));

    I.eye(E.getCols()-2);
    ZeroVector.zeros( E.getCols()-2, 1);

    for (int i = 0; i < Mat.getRows(); i++)
    {
        E.add(1, 1, 1 - Mat.getMat(1, i+1));
        Temp = E||(I|ZeroVector);
        Root = Temp.eigenvalues();

    }

}



void EqdifSim::printSS()
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

void EqdifSim::tf2ssc()
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
            this->C.add( 1, i, this->Num.getMat( 1, i+1)- this->Den.getMat( 1, i+1)*B0);
         }
        this->D.add( 1, 1,  B0);
    }
}

void EqdifSim::tf2ssd()
{
    Matrix I, ZeroVector, tempDen( 1, this->Dend.getCols()-1);

    I.eye(this->Dend.getCols()-2);
    ZeroVector.zeros( this->Dend.getCols()-2, 1);
    for (int i = 2; i <= this->Dend.getCols(); i++)
        tempDen.add( 1, i-1, -(this->Dend.getMat( 1, i)));

    this->Ad = tempDen||(I|ZeroVector);
    this->Bd.zeros(this->Ad.getRows(), 1);
    this->Bd.add( 1, 1, 1);

    if (this->Numd.getCols() == 1)
    {
        this->Cd.add( 1, this->Bd.getRows(), this->Numd.getMat( 1, 1));
        this->Dd.add( 1, 1, 0);
    }
    else if (this->Numd.getCols() < this->Dend.getCols())
    {
        for (int i = this->Bd.getRows(); i > 1; i--)
            this->Cd.add( 1, i, this->Numd.getMat( 1, this->Numd.getCols() -( this->Bd.getRows() - i )));
        this->Dd.add( 1, 1, 0);
    }

    else if (this->Numd.getCols() == this->Dend.getCols())
    {
        float B0 = this->Numd.getMat( 1, 1);

        for (int i = 1; i <= this->Bd.getRows(); i++)
         {
            this->Cd.add( 1, i, this->Numd.getMat( 1, i+1)- this->Dend.getMat( 1, i+1)*B0);
         }
        this->Dd.add( 1, 1,  B0);
    }
}

void EqdifSim::ss2tfc()
{
    Matrix Temp;

    Temp = this->A - (this->B*this->C);
    this->Num = Temp.pol();
    this->Den = this->A.pol();
}

void EqdifSim::ss2tfd()
{
    Matrix Temp;

    Temp = this->Ad - (this->Bd*this->Cd);
    this->Numd = Temp.pol();
    this->Dend = this->Ad.pol();
}

float EqdifSim::factorial(float n)
{
    float retval = 1;

    for (int i = n; i > 1; --i)
        retval *= i;

    return retval;
}
