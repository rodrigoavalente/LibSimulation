#ifndef MATRIX_H
#define MATRIX_H
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>
#include <fstream>

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

    //#####Construtores e Destrutores da Classe#####//
    Matrix(); //Construtor
    Matrix(int row, int col);//Constroi a matriz de acordo com o número de linhas e colunas informados, respectivamente.
    Matrix(const Matrix & otherMatrix);//Faz uma cópia da Matriz
    ~Matrix();//Destrutor
    //#############################################//


    //#####Métodos de Inicialização da Matriz#####//
    void init(int row, int col); //Inicializador da Matriz de acordo com o número de linhas e colunas informados, respectivamente.
    void init(string value);//Adiciona os valores de uma string a matriz, serparando os elementos por "," e as linhas por ";".
    void add(int rol, int col, float number);//Adiciona elementos a matriz pelos índices i e j respectivamente. Obs.: i e j iniciam de 1 para este método.
    void eye(int num);//Cria uma matriz identidade de ordem num.
    void ones(int row, int col);//Inicia uma matriz com todos os índices iguais a 1, de acordo com o número de linhas e colunas respectivamente.
    void zeros(int row, int col);//Inicia uma matriz com todos os índices iguais a 0, de acordo com o número de linhas e colunas, respectivamente.
    //###########################################//

    //#####Método de Impressão da Matriz#####//
    void print();
    //######################################//

    //#####Operadores da Matriz#####//

    //-----Operadores de Soma-----//
    Matrix operator+(Matrix Mat1);//Soma Matriz Matriz
    Matrix operator+(float a);//Soma Escalar Matriz
    friend Matrix operator+(float a, Matrix Mat1);//Soma Matriz Escalar
    //--------------------------//

    //-----Operadores de Subtração-----//
    Matrix operator-(Matrix Mat1);//Subtração Matriz Matriz
    Matrix operator-(float a);//Subtração Escalar Matriz
    friend Matrix operator-(float a, Matrix Mat1);//Subtração Matriz Escalar
    //--------------------------------//

    //-----Operadores de Atribuição-----//
    void operator=(Matrix Mat1);//Igualando Matriz Matriz
    void operator=(string value);//Atribuindo String a Entrada da Matriz
    //---------------------------------//

    //-----Operadores de Multiplicação-----//
    Matrix operator*(Matrix Mat1);//Multiplicação Matriz Matriz
    Matrix operator*(float a);//Multiplicação Escalar Matriz
    friend Matrix operator*(float a, Matrix Mat1);//Multiplicação Matriz Escalar
    //------------------------------------//

    //-----Operadores de Concatenação Matrizes-----//
    Matrix operator| (Matrix Mat1);//Concatena Matrizes a Esquerda
    Matrix operator|| (Matrix Mat1);//Concatena Matrizes Abaixo
    //--------------------------------------------//

    //----Operador de Matriz Transposta-----//
    Matrix operator~();
    //-------------------------------------//

    //-----Operador de Potência de Matrizes-----//
    Matrix operator^(float exp);//Eleva a matriz a um determinado expoente.
    Matrix operator> (float num);//Eleva os elementos de uma matriz a um determinado expoente.
    //-----------------------------------------//

    //##########################################//

    //#####Álgebra Linear#####//
    float trace();//Cálculo do traço de uma matriz.
    Matrix inv();//Cálculo da matriz inversa da matriz.
    Matrix pol();//Cálculo dos índices do polinômio característico da matriz.
    Matrix eigenvalues();//Cálculo dos auto valores de uma matriz.
    float det();//Cálculo do determinante de uma matriz.
    friend Matrix diff(Matrix M, float h);//Cálcula a derivada de uma matriz.
    //##############################//



    //#####Retornando Informações da Matriz#####//
    int getRows();//Retorna o número de linhas da matriz.
    int getCols();//Retorna o número de colunas da matriz.
    float getMat(int row, int col);//Retorna o elemento no índice ij da matriz.
    //#######################################################//
};

#endif // MATRIX_H
