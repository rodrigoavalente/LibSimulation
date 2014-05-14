#include "lsim.h"

lsim::lsim()
{
}

void lsim::addIO(Matrix in, Matrix out)
{
    this->input = in;
    this->output = out;
}

bool lsim::VefMat(Matrix Mat1)
{
    bool vef;

    if((Mat1.getRows() != 0) && (Mat1.getCols() != 0))
        vef = true;
    else
        vef = false;

    return vef;
}

//void lsim::addIO(string FileName, int nIn, int nOut)
//{
//    FILE *pFile;
//    pFile = fopen(FileName, "r");
//    if (pFile != NULL)
//        for(int i = 0; i < nIn; i++)
//            for(int j = 0; j < nIn; j++)

//        for(int i = nIn +1; i < (nIn + nOut); i++)
//            for(int j = 0; j < (nIn + nOut); j++)
//}

void lsim::AddModelCoef(Matrix Coef)
{
    this->X = Coef;
}

void lsim::polyModel(int grau)
{
    try
    {
        if(!this->VefMat(this->input))
            throw "A entrada nao foi adicionada";
        else
            this->Model = "Polynomial";
            this->A.ones(this->input.getRows(), 1);
            for (int i = 1; i<= grau; i++)
                this->A = this->A|(this->input>i);
    }
    catch (const char* msg)
    {
        cerr<<msg<<endl;
    }

}

void lsim::SimPoly(int grau)
{
    try
    {
        if(!this->VefMat(this->X))
            throw "Os coeficientes nao foram adicionados";
        else
        {
            this->polyModel(grau);
            this->SimulatedOut = this->A*this->X;
        }
    }
    catch (const char* msg)
    {
        cerr<<msg<<endl;
    }

}

void lsim::PolyCoefFind(int grau)
{
    try
    {
        if (!this->VefMat(this->A))
        {
            this->polyModel(grau);
            this->PolyCoefFind(grau);
        }
        else if (!this->VefMat(this->output))
                throw "Nao parametros suficientes para calcular os coeficientes";
             else
                this->X = ((~this->A*this->A)^-1)*((~this->A)*this->output);
    }
    catch (const char* msg)
    {
        cerr<<msg<<endl;
    }
}


