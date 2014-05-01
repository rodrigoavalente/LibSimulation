#include "matrix.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Matrix::Matrix() //Inicializa linhas e colunas com zero
{
    this->rows = 0;
    this->cols = 0;
}

Matrix::Matrix(int row, int col)
{
    this->init(row, col);
}

Matrix::Matrix(const Matrix & otherMatrix)
{
    this->init(otherMatrix.rows, otherMatrix.cols);
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            this->Mat[i][j] = otherMatrix.Mat[i][j];
}

Matrix::~Matrix()
{
    for (int i = 0; i < this->rows; i++)
    {
        free(this->Mat[i]);
        this->Mat[i] = NULL;
    }
    free(this->Mat);
    this->rows = 0;
    this->cols = 0;
    this->Mat = NULL;
}

void Matrix::init(int row, int col)//Aloca o espaço de memória para a Matriz
{
    this->Mat = (float**)malloc((row)*sizeof(float*)); //Cria as linhas
    for (int i = 0; i < row; i++)
        this->Mat[i] = (float*)malloc((col)*sizeof(float)); //Cria as colunas
    this->rows = row;
    this->cols = col;

}

void Matrix::add(int row, int col, float number)
{
    //Matrix Temp(row, col);
    this->Mat[row-1][col-1] = number;
}

void Matrix::print()
{
    cout<<"\n";
    for (int i = 0; i< this->rows; i++)
    {
        for (int j = 0; j< this->cols; j++)
            cout<<this->Mat[i][j]<<" ";
        cout<<endl;
    }
}

Matrix Matrix::operator +(Matrix Mat1)
{
    Matrix Ret(this->rows, this->cols);

    for(int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            Ret.Mat[i][j] = this->Mat[i][j] + Mat1.Mat[i][j];

    return Ret;
}

Matrix Matrix::operator -(Matrix Mat1)
{
    Matrix Ret(this->rows, this->cols);

    for(int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            Ret.Mat[i][j] = this->Mat[i][j] - Mat1.Mat[i][j];

    return Ret;
}

void Matrix::operator =(Matrix Mat1)
{
   this->init(Mat1.rows, Mat1.cols);

   for(int i = 0; i < this->rows; i++)
       for (int j = 0; j < this->cols; j++)
           this->Mat[i][j] = Mat1.Mat[i][j];
}

Matrix Matrix::operator *(Matrix Mat1)
{

    float temp = 0;
    Matrix Ret(this->rows, this->cols);

    for(int i = 0; i < this->rows; i++)
    {
        for (int col = 0; col < this->cols; col++)
        {
            temp = 0;
            for (int j = 0; j < this->cols; j++)
                  temp += this->Mat[i][j]*Mat1.Mat[j][col];
            Ret.Mat[i][col] = temp;
        }


    }
    return Ret;
}

Matrix Matrix::operator *(float a)
{
    Matrix Ret(this->rows, this->cols);

    for(int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            Ret.Mat[i][j] = a*this->Mat[i][j];

    return Ret;
}

Matrix operator*(float a, Matrix Mat1)
{
    return Mat1*a;
}
