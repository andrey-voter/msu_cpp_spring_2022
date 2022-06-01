#include <iostream>
#include <string>
#include "my_matrix.hpp"

Matrix::ProxyRow::ProxyRow(size_t n = 1)
{
    data_ = new int32_t[n];
    this->size = n;
}

Matrix::Matrix(size_t m, size_t n)
{
    if (m == 0 || n == 0)
        throw std::invalid_argument("");
    this->m = m;
    this->n = n;
    rows_ = new ProxyRow [m];
    for (size_t i = 0; i < m; i++)
    {
        rows_[i] = ProxyRow(n);
    }
}

Matrix::~Matrix()
{
    if (rows_ != nullptr)
    {
        delete [] rows_;
        rows_ = nullptr;
    }
}


Matrix::Matrix(Matrix & other)
{
    *this = other;
}


int32_t& Matrix::ProxyRow::operator[](size_t j)
{
    if (j >= size)
        throw std::out_of_range("");
    return data_[j];
}


Matrix::ProxyRow& Matrix::operator[](size_t i)
{
    if (i >= m)
        throw std::out_of_range("");
    return rows_[i];
}
void Matrix::operator *= (size_t k)
{
    for(size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
        {
            rows_[i][j] *= k;
        }
}
bool Matrix::operator == (Matrix& other) const
{   
    if (this->m != other.getRows()) 
        return false;
    if (this->n != other.getColumns()) 
        return false;
    for(size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++) 
            if (rows_[i][j] != other[i][j])
                return false;
    return true;    
}
bool Matrix::operator != (Matrix& other) const
{
    return !(*this == other);
}

Matrix& Matrix::operator = (Matrix& other)
{
    this->rows_ = new ProxyRow [m]; 
    for(size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
            rows_[i][j] = other[i][j];
    return *this;
}

Matrix Matrix::operator + (Matrix & other) const
{
    if (this->m != other.getRows()) 
        throw std::logic_error("");
    if (this->n != other.getColumns()) 
        throw std::logic_error("");
    Matrix tmp(m, n);
    for(size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
        {
            tmp[i][j] = rows_[i][j] + other[i][j];
        }
    return tmp;
}
size_t Matrix::getRows() const
{
    return this->m;
}

size_t Matrix::getColumns() const
{
    return this->n;
}

std::ostream & operator << (std::ostream &os, Matrix & matrix) 
{
    for(size_t i = 0; i < matrix.getRows(); i++)
    {
        for (size_t j = 0; j < matrix.getColumns(); j++)
            os  <<  matrix[i][j]<< " ";
        os << std::endl;
    }
    os << std::endl;
    return os;
}