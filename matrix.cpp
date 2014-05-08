#ifndef MATRIX_H
#define MATRIX_H
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

class Matrix
{
private:
    int rows, cols;
    float **Mat;

    //#####VerificaÃ§Ã£o de Matriz Quadrada#####//
    bool sqr(Matrix Mat1);
    //#######################################//

public:
    Matrix(); //Construtor
    Matrix(int row, int col);
    Matrix(const Matrix & otherMatrix);
    ~Matrix();

    void init(int row, int col); //Inicializador da Matriz
    void init(string value);
    void add(int rol, int col, float number);
    void print();
    void eye(int num);

    void zeros(int row, int col);

    //#######CriaÃ§Ã£o do Operador de Soma#########//
    Matrix operator+(Matrix Mat1);//Soma Matriz Matriz
    Matrix operator+(float a);//Soma Escalar Matriz
    friend Matrix operator+(float a, Matrix Mat1);//Soma Matriz Escalar
    //##########################################//

    //#####CriaÃ§Ã£o do Operador de SubtraÃ§Ã£o#####//
    Matrix operator-(Matrix Mat1);//SubtraÃ§Ã£o Matriz Matriz
    Matrix operator-(float a);//SubtraÃ§Ã£o Escalar Matriz
    friend Matrix operator-(float a, Matrix Mat1);//SubtraÃ§Ã£o Matriz Escalar
    //##########################################//

    //#####CriaÃ§Ã£o do Operador de AtribuiÃ§Ã£o#####//
    void operator=(Matrix Mat1);//Igualando Matriz Matriz
    void operator=(string value);//Atribuindo String a Entrada da Matriz
    //#########################//

    //#####CriaÃ§Ã£o do Operador de MultiplicaÃ§Ã£o####//
    Matrix operator*(Matrix Mat1);//MultiplicaÃ§Ã£o Matriz Matriz
    Matrix operator*(float a);//MultiplicaÃ§Ã£o Escalar Matriz
    friend Matrix operator*(float a, Matrix Mat1);//MultiplicaÃ§Ã£o Matriz Escalar
    //##########################################//

    //#####CriaÃ§Ã£o Operadores de ConcatenaÃ§Ã£o Matrizes#####//
    Matrix operator| (Matrix Mat1);//Concatena Matrizes a Esquerda
    Matrix operator|| (Matrix Mat1);//Concatena Matrizes Abaixo
    //#############################//

    //#####CriaÃ§Ã£o do Operador de Matriz Transposta#####//
    Matrix operator~();
    //##################################################//

    //#####CriaÃ§Ã£o do Operador de PotÃªncia de Matrizes#####//
    Matrix operator^(float exp);
    //####################################################//

    //SeparaÃ§Ã£o de Cholesky//
    void cholesky();
    //Matrix choleskytrans ();

    //#####Inversa de uma Matriz#####//
    Matrix inv();
    //##############################//

    //#####CÃ¡lculo do TraÃ§o#####//
    float trace();
    //#########################//

    //#####Encontrando o PolinÃ´mio CaracterÃ­stico de uma Matriz#####//
    void pol();
    //#############################################################//

    //#####RotaÃ§Ã£o de Jacobi#####///
    void jacobi();
};



#endif // MATRIX_H
