#include "matrix.h"
#include <cstdlib>
#include <iostream>



Matrix::Matrix() //Inicializa linhas e colunas com zero
{
    this->rows = 0;
    this->cols = 0;
}

Matrix::Matrix(int row, int col)//Inicializa a Matriz com as linhas e colunas determinadas
{
    this->init(row, col);
}


Matrix::Matrix(const Matrix & otherMatrix)//Cria uma cópia da Matriz
{
    this->init(otherMatrix.rows, otherMatrix.cols);
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            this->Mat[i][j] = otherMatrix.Mat[i][j];
}

Matrix::~Matrix()//Destrutor da Classe Matriz
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

void Matrix::init(int row, int col)//Aloca o espaço de memória para a Matriz e inicializa com 0
{
    this->Mat = (float**)calloc(col,(row)*sizeof(float*)); //Cria as linhas
    for (int i = 0; i < row; i++)
        this->Mat[i] = (float*)calloc(row,(col)*sizeof(float)); //Cria as colunas
    this->rows = row;
    this->cols = col;

}

void Matrix::init(string value)//Inicializa a Matriz com uma cadeia de strings como entrada
{
    int posComma, posSemiComma, col = 1, row = 1;
    string temp;

    while (!value.empty())
    {
        posSemiComma = value.find(";");
        if (posSemiComma != -1)
            temp = value.substr(0,posSemiComma);
        else
        {
            temp = value;
            posSemiComma = value.length();
        }
        while (!temp.empty())
        {
            posComma = temp.find(",");
            if( posComma == -1)
                posComma = temp.length();

            string temp2 = temp.substr(0, posComma);
            float num = atof(temp2.c_str());
            this->add(row, col, num);
            temp.erase(0, posComma+1);
            col++;
        }
        value.erase(0,posSemiComma+1);
        col = 1;
        row++;
    }
}

void Matrix::add(int row, int col, float number)//Adiciona valores a matriz, se tiver valores maiores as dimensões coloca na posição indicada completando com 0
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

void Matrix::eye(int num)//Gera uma Matriz Identidade, entrando como parâmetro a dimensão quadrada da Matriz
{
    this->init(num,num);
    for(int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            if (i == j)
                this->Mat[i][j] = 1;

}

void Matrix::zeros(int row, int col)
{
    this->init(row, col);
}

void Matrix::print()//Imprime a Matriz na Tela
{
    cout<<"\n";
    for (int i = 0; i< this->rows; i++)
    {
        for (int j = 0; j< this->cols; j++)
            cout<<this->Mat[i][j]<<" ";
        cout<<endl;
    }
}

Matrix Matrix::operator +(Matrix Mat1)//Operador de soma Matriz Matriz
{
    Matrix Ret(this->rows, this->cols);

    for(int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            Ret.Mat[i][j] = this->Mat[i][j] + Mat1.Mat[i][j];

    return Ret;
}

Matrix Matrix::operator +(float a)//Operador de soma Escalar Matriz
{
    Matrix Ret(this->rows, this->cols);

    for(int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            Ret.Mat[i][j] = this->Mat[i][j] + a;

    return Ret;
}

Matrix operator+(float a, Matrix Mat1)//Operador de soma Matriz Escalar
{
    return Mat1+a;
}

Matrix Matrix::operator -(Matrix Mat1)//Operador de subtração Matriz Matriz
{
    Matrix Ret(this->rows, this->cols);

    for(int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            Ret.Mat[i][j] = this->Mat[i][j] - Mat1.Mat[i][j];

    return Ret;
}

Matrix Matrix::operator -(float a)//Operador de subtração Escalar Matriz
{
    Matrix Ret(this->rows, this->cols);

    for(int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            Ret.Mat[i][j] = this->Mat[i][j] - a;

    return Ret;
}

Matrix operator-(float a, Matrix Mat1)//Operador de subtração Matriz Escalar
{
    return Mat1-a;
}

void Matrix::operator =(Matrix Mat1)//Operador de Igualdade entre Matrizes
{
   this->init(Mat1.rows, Mat1.cols);

   for(int i = 0; i < this->rows; i++)
       for (int j = 0; j < this->cols; j++)
           this->Mat[i][j] = Mat1.Mat[i][j];
}

void Matrix::operator=(string value)//Operador para a entrada de uma String
{
    this->init(value);
}

Matrix Matrix::operator *(Matrix Mat1)//Operador de Multiplicação Matriz Matriz
{

    float temp = 0;
    Matrix Ret(this->rows, Mat1.cols);

    try
    {
        if (this->cols != Mat1.rows)
        {
            throw "As dimensoes das matrizes nao batem, a multiplicacao nao e possivel";
            Ret.zeros(this->rows, Mat1.cols);
        }
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

Matrix Matrix::operator *(float a)//Operador de multiplicação Escalar Matriz
{
    Matrix Ret(this->rows, this->cols);

    for(int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            Ret.Mat[i][j] = a*this->Mat[i][j];

    return Ret;
}

Matrix operator*(float a, Matrix Mat1)//Operador de multiplicação Matriz Escalar
{
    return Mat1*a;
}

Matrix Matrix::operator|(Matrix Mat1)//Concatenção de Matrizes a Esquerda
{
    Matrix temp(this->rows,this->cols+Mat1.cols);

    for(int i = 0; i < temp.rows; i++)
        for (int j = 0; j < temp.cols; j++)
            if(j<this->cols)
                temp.add(i+1,j+1,this->Mat[i][j]);
            else
                temp.add(i+1,j+1,Mat1.Mat[i][j-this->cols]);

    return temp;

}

Matrix Matrix::operator||(Matrix Mat1)//Concatenação de Matrizes Abaixo
{
    Matrix temp(this->rows+Mat1.rows,this->cols);

    for(int j = 0; j < temp.cols; j++)
        for (int i = 0; i < temp.rows; i++)
            if(i<this->rows)
                temp.add(i+1,j+1,this->Mat[i][j]);
            else
                temp.add(i+1,j+1,Mat1.Mat[i-this->rows][j]);

    return temp;

}

Matrix Matrix::operator~()//Faz a transporta da Matriz
{
    Matrix temp = *this, Ret (this->rows, this->cols);
    for(int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
                Ret.Mat[i][j] = temp.Mat[j][i];

    return Ret;
}

Matrix Matrix::operator^(float exp)
{
    Matrix Ret, temp = *this;
    int sinal;

    if(exp < 0)
    {   sinal = -1;
        exp = exp*(-1);
    }
    else
        sinal = 1;

    Ret.eye(this->rows);

    for(float i = 0; i < exp; i++)
    {
        if(sinal > 0)
            Ret = Ret*temp;
        else
            Ret = temp.inv()*Ret;
    }

    return Ret;
}


void Matrix::cholesky()
{
    Matrix L(this->rows, this->cols);
    float temp;


   for(int i = 0; i < this->rows; i++)
   {
        for(int j = 0; j < this->cols; j++)
        {
            temp = 0;
            if(i == j)
            {
                for(int k = 0; k < j; k++)
                {
                    temp+=((L.Mat[j][k])*(L.Mat[j][k]));
                }

               L.Mat[i][j]=sqrt((double)(this->Mat[i][j]-temp));
            }

            if(i > j)
            {
                for(int k = 1; k < j; k++)
                    {
                        temp+=((L.Mat[i][k]*L.Mat[j][k]));
                    }
                L.Mat[i][j]=(1/(L.Mat[j][j]))*((this->Mat[i][j])-temp);
            }

            if(i < j)
            {
                L.Mat[i][j] = 0;
            }
        }
   }
   L.print();
   (~L).print();
   (L*(~L)).print();
 }

Matrix Matrix::inv()
{
    Matrix Ret =*this, Id;
    Id.eye(this->rows);

    for(int i = 0; i < this->rows; i++ )
        for(int j = i+1; j<this->rows; j++)
        {
            float m = Ret.Mat[j][i]/Ret.Mat[i][i];
            for(int k = 0; k <this->cols; k++)
            {
                Ret.Mat[j][k] = Ret.Mat[j][k]-m*Ret.Mat[i][k];
                Id.Mat[j][k] = Id.Mat[j][k]-m*Id.Mat[i][k];
            }
        }


    for(int i = this->rows-1; i >=0 ; i-- )
        for(int j = i-1; j>=0; j--)
        {
            float m = Ret.Mat[j][i]/Ret.Mat[i][i];
            for(int k = 0; k <this->cols; k++)
            {
                Ret.Mat[j][k] = Ret.Mat[j][k]-m*Ret.Mat[i][k];
                Id.Mat[j][k] = Id.Mat[j][k]-m*Id.Mat[i][k];
            }
        }

    for(int i=0; i< this->rows; i++)
    {
        float m = 1/Ret.Mat[i][i];
        for(int j=0; j<this->rows; j++)
        {
             Ret.Mat[i][j] = m*Ret.Mat[i][j];
             Id.Mat[i][j] = m*Id.Mat[i][j];
        }

    }

    return Id;
}
