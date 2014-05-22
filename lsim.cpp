#include "lsim.h"

Lsim::Lsim()
{

}

void Lsim::addIO(Matrix in, Matrix out)
{
    this->u = in;
    this->y = out;
}

void Lsim::addIO(const char *namefile)
{
    ifstream myfile(namefile);
    string data;

    try
    {
        if (!myfile.is_open())
            throw "Nao foi possivel abrir o arquivo";
        else
        {
            int posBar;
            string input = "", output = "", time = "";


            while(!myfile.eof())
            {
                getline( myfile, data);
                posBar = data.find("-");
                input = input + data.substr( 0, posBar) + ";";
                data.erase( 0, posBar+1);
                posBar = data.find("-");
                output = output + data.substr(0, posBar) + ";";
                data.erase( 0, posBar+1);
                time = time + data + ";";
            }
            myfile.close();
            this->u = input;
            this->y = output;
            this->PeriodicTime = time;
            this->u.print();
            this->y.print();
            this->PeriodicTime.print();

        }

    }
    catch(const char* msg)
    {
        cerr<<msg<<endl;
    }
}


void Lsim::modelCoef(Matrix coef)
{
    this->X = coef;
}
void Lsim::polyModel(int grau)
{
    this->Model = "polinomial";
    this->u.print();
    this->A.ones(this->u.getRows(),1);
    for(int i = 1; i <= grau; i++)
        this->A = this->A|(this->u>i);
}

void Lsim::simPoly(int grau)
{
    this->polyModel(grau);
    this->b = this->A*this->X;
}

void Lsim::polyCoef(int grau)
{
    this->polyModel(grau);
    this->X = ((~this->A*this->A)^-1)*(~this->A)*this->y;
}

//Modelos ARX (Auto Recursive with eXogenous output)

void Lsim::arxModel(int ny, int nu)
{
    int maxNuNy,minRowInOut;
    this->Model = "ARX";

    if(ny>nu)
        maxNuNy = ny;
    else
        maxNuNy = nu;

    if(this->y.getRows() > this->u.getRows())
        minRowInOut = this->u.getRows();
    else
        minRowInOut = this->y.getRows();

    for(int i = maxNuNy; i < minRowInOut; i++)
    {
        this->b.add(i-maxNuNy+1,1,this->y.getMat( i, 1));
        for(int j = 0; j < nu+ny; j++)
        {
            if(j<ny)
                this->A.add(i-maxNuNy+1,j+1,-this->y.getMat( i-ny+j,1));
            else
                this->A.add(i-maxNuNy+1,j+1,this->u.getMat( i-nu-ny+j, 1));
        }
    }

}


void Lsim::simArx(int ny, int nu)
{
    this->arxModel(ny,nu);
    this->b = this->A*this->X;
}

void Lsim::arxCoef(int ny, int nu)
{
    this->arxModel(ny,nu);
    this->X = ((~this->A*this->A)^-1)*(~this->A)*this->b;
}

void Lsim::eqdifModel(float h)
{
    Matrix dy, d2y;
    dy = diff(this->y,h);
    d2y = diff(dy,h);

    for(int i = 0; i < d2y.getRows(); i++)
    {
        this->A.add(i+1,1,-this->y.getMat( i, 1));
        this->A.add(i+1,2,-dy.getMat( i, 1));
        this->A.add(i+1,3,this->u.getMat( i, 1));
    }
    this->b = d2y;
}

void Lsim::eqdifCoef(float h)
{
    this->eqdifModel(h);
    this->X = ((~this->A*this->A)^-1)*(~this->A)*this->b;
}
