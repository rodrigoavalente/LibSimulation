#ifndef LSIM_H
#define LSIM_H

#include "matrix.h"
#include "fstream"

class Lsim
{
    public:
        Matrix y,u,A,X,b, PeriodicTime;//Saídas,Entradas,Matriz montada a partir dos dados, coeficientes, Saída simulada
        string Model;

    public:
        Lsim();
        void addIO(Matrix in, Matrix out);
        void addIO(const char *namefile);
        void modelCoef(Matrix coef);
    //Modelos polinomiais
        void polyModel(int grau);
        void simPoly(int grau);
        void polyCoef(int grau);
    //Modelos ARX (Auto Recursive with eXogenous output)
        void arxModel(int ny, int nu);
        void simArx(int ny, int nu);
        void arxCoef(int ny, int nu);
    //Modelos de equações diferenciais
        void eqdifModel(float h);
        void eqdifCoef(float h);

};

#endif // LSIM_H
