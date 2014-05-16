#ifndef MATRIX_H
#define MATRIX_H
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>

using namespace std;

class Matrix
{
private:
    int rows, cols;
    float **Mat;

    //#####Verificação de Matriz Quadrada#####//
    bool sqr(Matrix Mat1);
    //#######################################//

    //#####Verficação se é uma Matriz Idenditade#####//
    bool ind(Matrix Mat1);
    //##############################################//

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

    //#######Criação do Operador de Soma#########//
    Matrix operator+(Matrix Mat1);//Soma Matriz Matriz
    Matrix operator+(float a);//Soma Escalar Matriz
    friend Matrix operator+(float a, Matrix Mat1);//Soma Matriz Escalar
    //##########################################//

    //#####Criação do Operador de Subtração#####//
    Matrix operator-(Matrix Mat1);//Subtração Matriz Matriz
    Matrix operator-(float a);//Subtração Escalar Matriz
    friend Matrix operator-(float a, Matrix Mat1);//Subtração Matriz Escalar
    //##########################################//

    //#####Criação do Operador de Atribuição#####//
    void operator=(Matrix Mat1);//Igualando Matriz Matriz
    void operator=(string value);//Atribuindo String a Entrada da Matriz
    //#########################//

    //#####Criação do Operador de Multiplicação####//
    Matrix operator*(Matrix Mat1);//Multiplicação Matriz Matriz
    Matrix operator*(float a);//Multiplicação Escalar Matriz
    friend Matrix operator*(float a, Matrix Mat1);//Multiplicação Matriz Escalar
    //##########################################//

    //#####Criação Operadores de Concatenação Matrizes#####//
    Matrix operator| (Matrix Mat1);//Concatena Matrizes a Esquerda
    Matrix operator|| (Matrix Mat1);//Concatena Matrizes Abaixo
    //#############################//

    //#####Criação do Operador de Matriz Transposta#####//
    Matrix operator~();
    //##################################################//

    //#####Criação do Operador de Potência de Matrizes#####//
    Matrix operator^(float exp);
    //####################################################//

    //#####Método reservado para futuros testes#####//
    void testemetods();
    //#############################################//

    //#####Inversa de uma Matriz#####//
    Matrix inv();
    //##############################//

    //#####Cálculo do Traço#####//
    float trace();
    //#########################//

    //#####Encontrando o Polinômio Característico de uma Matriz#####//
    Matrix pol();
    //#############################################################//

    //#####Método QR para encontrar os Autovalres#####//
    Matrix eigenvalues();
    //###############################################//

    //#####Determinando da Matriz#####//
    float det();
    //###############################//

    //#####Recebendo informações das linhas e colunas das Matrizes#####//
    int getCols();
	int getRows();
    //#######################################################//

    //#####Recebendo um elemento especifíco da Matriz#####//
    float getMat(int row, int col);
    //###################################################//

};



#endif // MATRIX_H
