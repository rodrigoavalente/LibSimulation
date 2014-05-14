#ifndef LSIM_H
#define LSIM_H

#include "matrix.h"

class lsim
{
private:
    Matrix output, input, A, X, SimulatedOut;
    string Model;

public:
    lsim();
    void addIO(Matrix in, Matrix out);
//    void addIO(string FileName, int nIn, int nOut);
    void AddModelCoef(Matrix Coef);
    bool VefMat(Matrix Mat1);

    void polyModel(int grau);
    void SimPoly(int grau);
    void PolyCoefFind(int grau);
};

#endif // LSIM_H
