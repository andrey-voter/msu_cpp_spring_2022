#pragma once

#include <iostream>
#include <string>
#include <vector>

class Matrix
{
    class ProxyRow
    {
    private:
        int32_t *data_;
        size_t size;
    public:
        ProxyRow(size_t);       
        int32_t& operator[](size_t j);
    };

public:
    Matrix(size_t m = 1, size_t n = 1);
    Matrix(Matrix &);
    ProxyRow& operator[](size_t i);
    void operator *= (size_t k);
    bool operator == (Matrix & other);
    bool operator != (Matrix & other);
    Matrix operator + (Matrix & other);
    Matrix& operator = (Matrix& other);
    size_t getRows();
    size_t getColumns();

private:
    ProxyRow *rows_;
    size_t m;
    size_t n;
};

std::ostream & operator << (std::ostream &os, Matrix& matrix);