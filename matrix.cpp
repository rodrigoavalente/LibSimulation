#include "matrix.h"
#include <cstdlib>
#include <iostream>



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
    this->Mat = (float**)calloc(col,(row)*sizeof(float*)); //Cria as linhas
    for (int i = 0; i < row; i++)
        this->Mat[i] = (float*)calloc(row,(col)*sizeof(float)); //Cria as colunas
    this->rows = row;
    this->cols = col;

}

void Matrix::init(string value)
{
    int posComma, posSemiComma, col = 1, row = 1;
    string temp;

    while (value.length() -1 != 0)
    {
        posComma = value.find(",");
        posSemiComma = value.find(";");

        if ((posComma == -1) && (posSemiComma == -1))
            break;

        if(posSemiComma == -1)
            posSemiComma = posComma+1;

        if(posComma == -1)
            posComma = posSemiComma+1;

        if (posComma < posSemiComma)
        {
            temp = value.substr(0, posComma);
            float num = atof(temp.c_str());
            this->add(row, col, num);
            value.erase(0, posComma+1);
            col++;
        }
        else if (posComma > posSemiComma)
        {

            temp = value.substr(0,posSemiComma);
            float num = atof(temp.c_str());
            this->add(row, col, num);
            value.erase(0, posSemiComma+1);
            col = 1;
            row++;
        }

        this->print();
    }
}

void Matrix::add(int row, int col, float number)
{
    int tempRow, tempCol;

    if(this->rows < row)
        tempRow = row;
    else
        tempRow = this->rows;
    if(this->cols < col)
        tempCol = col;
    else
        tempCol = this->cols;

    Matrix Temp(tempRow, tempCol);
    if((this->rows != 0) && (this->cols != 0))
    {
        for(int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                Temp.Mat[i][j] = this->Mat[i][j];
    }

    Temp.Mat[row-1][col-1] = number;
    this->init(tempRow, tempCol);

    for(int i = 0; i < Temp.rows; i++)
        for (int j = 0; j < Temp.cols; j++)
            this->Mat[i][j] = Temp.Mat[i][j];

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

Matrix Matrix::operator +(float a)
{
    Matrix Ret(this->rows, this->cols);

    for(int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            Ret.Mat[i][j] = this->Mat[i][j] + a;

    return Ret;
}

Matrix operator+(float a, Matrix Mat1)
{
    return Mat1+a;
}

Matrix Matrix::operator -(Matrix Mat1)
{
    Matrix Ret(this->rows, this->cols);

    for(int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            Ret.Mat[i][j] = this->Mat[i][j] - Mat1.Mat[i][j];

    return Ret;
}

Matrix Matrix::operator -(float a)
{
    Matrix Ret(this->rows, this->cols);

    for(int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            Ret.Mat[i][j] = this->Mat[i][j] - a;

    return Ret;
}

Matrix operator-(float a, Matrix Mat1)
{
    return Mat1-a;
}

void Matrix::operator =(Matrix Mat1)
{
   this->init(Mat1.rows, Mat1.cols);

   for(int i = 0; i < this->rows; i++)
       for (int j = 0; j < this->cols; j++)
           this->Mat[i][j] = Mat1.Mat[i][j];
}

void Matrix::operator=(string value)
{
    this->init(value);
}

Matrix Matrix::operator *(Matrix Mat1)
{

    float temp = 0;
    Matrix Ret(this->rows, Mat1.cols);

    try
    {
        if (this->cols != Mat1.rows)
            throw "As dimensoes das matrizes nao batem, a multiplicacao nao e possivel";
        else
        {
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
    }
    catch(const char* msg)
    {
        cerr<<endl<<msg<<endl;
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
