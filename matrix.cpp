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

bool Matrix::sqr(Matrix Mat1)
{
    bool vef;

    if (Mat1.rows == Mat1.cols)
        vef = true;
    else
        vef = false;

    return vef;
}

bool Matrix::ind(Matrix Mat1)
{
    bool vef;
    int x = 0, a = 0, b = 0;

    for (int i = 0; i < Mat1.rows; i ++)
        for(int j = 0; j < Mat1.rows; j++)
            if ((i == j) && (Mat1.Mat[i][j]) == 1)
                x++;
    for(int i = 0; i < Mat1.rows; i++ )
        for(int j = i+1; j < Mat1.cols; j++)
        {
            if (Mat1.Mat[i][j] != 0)
            {
                i = Mat1.rows + 1;
                break;
            }
            else
                a++;
        }


    for(int i = 0; i < Mat1.rows; i++ )
        for(int j = i+1; j < Mat1.cols; j++)
        {
            if (Mat1.Mat[j][i] != 0)
            {
                i = Mat1.rows +1;
                break;
            }
            else
                b++;
        }

    if (x == (Mat1.rows) && (a != 0) && (b != 0))
        vef = true;
    else
        vef = false;

    return vef;
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
        if (!this->sqr(*this))
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

    Ret.eye(this->rows);

    if(exp < 0)
    {
        temp = this->inv();
        exp = exp*(-1);
    }


    Ret.eye(this->rows);

    for(float i = 0; i < exp; i++)
    {
            Ret = Ret*temp;
    }

    return Ret;
}


void Matrix::testemetods()
{
    try
    {
        if (!this->ind(*this))
            throw "A matriz nao identidade";
        else
            throw "A matriz e identidade";

    }
    catch (const char* msg)
    {
        cerr<<msg<<endl;
    }
}

Matrix Matrix::inv()
{
    Matrix Ret =*this, Id;


    try
    {
        if (!this->sqr(*this))
            throw "A matriz nao e quadrada";
        else
        {
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
        }

    }

    catch (const char* msg)
    {
        cerr<<msg<<endl;
    }



    return Id;
}

float Matrix::trace()
{
   float traco = 0;

   try
   {
        if(!this->sqr(*this))
            throw "A matrix nao e quadrada";
        else
            for(int i = 0; i < this->rows; i++ )
                for(int j = 0; j < this->cols; j++)
                    if( i == j)
                        traco = traco + this->Mat[i][j];
   }
   catch (const char* msg)
   {
        cerr<<msg<<endl;
   }

    return traco;
}

Matrix Matrix::pol()
{
    Matrix A = *this, B, I, C, ind(1, this->cols + 1);
    int sinal;

    try
    {
         if(!this->sqr(*this))
             throw "A matrix nao e quadrada";
         else
             I.eye(this->rows);
             C = A;
             sinal = pow(-1, this->rows);
             ind.Mat[0][0] = 1;
             for(int i = 1; i <= this->rows; i++ )
             {
                    ind.Mat[0][i] = (C.trace()/i);
                    B = C - ind.Mat[0][i]*I;
                    C = A*B;
                    ind.Mat[0][i] = -ind.Mat[0][i];

             }
             for (int i = 0; i < (ind.cols); i++)
                 ind.Mat[0][i] = ind.Mat[0][i]*sinal;

    }
    catch (const char* msg)
    {
         cerr<<msg<<endl;
    }

    cout<<"Os indices do polinomio sao: "<<endl;
    ind.print();

    return ind;

}

Matrix Matrix::eigenvalues()
{
    Matrix autovlr(1, this->rows);

    try
    {
       if (!this->sqr(*this))
           throw "A matrix não é quadrada";
       else
           if (!this->ind(*this))
       {
                   Matrix Q, temp, R, A = *this;
                   float max = 1000;

                   Q.eye(this->rows);
                   R.eye(this->rows);
                   while (max > 0.00001)
                   {
                       for(int i = 0; i < this->rows; i++ )
                           for(int j = i+1; j<this->rows; j++)
                               {
                                        temp.eye(this->rows);
                                        if (A.Mat[i][j] != 0)
                                        {
                                            temp.Mat[i][i] = (A.Mat[i][i])/sqrt(pow(A.Mat[i][i],2) + pow(A.Mat[i][j],2));
                                            temp.Mat[j][j] = temp.Mat[i][i];
                                            temp.Mat[i][j] = (A.Mat[i][j])/sqrt(pow(A.Mat[i][i],2) + pow(A.Mat[i][j],2));
                                            temp.Mat[j][i] = - temp.Mat[i][j];
                                        }
                                       R = temp*A;
                                       A = R*(~temp);
                           }
                       for(int i = 0; i < this->rows; i++ )
                           for(int j = i+1; j< this->rows; j++)
                           {
                               if ((A.Mat[i][j] > 0) && (A.Mat[i][j]) < max)
                                   max = A.Mat[i][j];
                               else if((A.Mat[i][j] < 0) && (-1*A.Mat[i][j]) < max)
                                   max = -1*(A.Mat[i][j]);
                           }
                    }
                   for(int i = 0; i < this->rows; i++ )
                       for(int j = 0; j< this->rows; j++)
                           if (i == j)
                                autovlr.Mat[0][i] = A.Mat[i][j];




       }
            else
               for(int i = 0; i < this->rows; i++ )
                   autovlr.Mat[0][i] = 1;

      }

    catch (const char* msg)
    {
        cerr<<msg<<endl;
    }

    return autovlr;
}

float Matrix::det()
{
    float x = 1;
    Matrix A;

    try
    {
        if (!this->sqr(*this))
            throw "A matrix não é quadrada";
        else if(!this->ind(*this))
             {
                A = this->eigenvalues();

                for (int i = 0; i < A.cols; i++)
                    x *= A.Mat[0][i];
             }
             else
                x = 1;
    }
    catch (const char* msg)
    {
        cerr<<msg<<endl;
    }

    return x;


}

int Matrix::getRows()
{
	return this->rows;
}

int Matrix::getCols()
{
	return this->cols;
}