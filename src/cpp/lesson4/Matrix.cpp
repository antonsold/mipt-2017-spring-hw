//
// Created by 123 on 28.02.2017.
//
#include "Matrix.h"
#include <cstring>
#include <iostream>
#include <stdexcept>

Matrix::Matrix(const Matrix &m) {
    this->row_count = m.row_count;
    this->col_count = m.col_count;
    this->values = new matrix_cell*[this->row_count];
    for (int i = 0; i < row_count; i++){
        this->values[i] = new matrix_cell[this->col_count];
        std::memcpy(this->values[i], m.values[i], col_count * sizeof(matrix_cell));
    }
}

Matrix::Matrix(size_t row_count = 2, size_t col_count = 2):row_count(row_count), col_count(col_count) {
    this->values = new matrix_cell*[this->row_count];
    for (int i = 0; i < row_count; i++){
        this->values[i] = new matrix_cell[this->col_count];
    }
    for (int row = 0; row < this->row_count; row++)
        for (int col = 0; col < this->col_count; col++)
            this->values[row][col] = 0;
}

Matrix::~Matrix(){
    for (int i = 0; i < this->row_count; i++){
        delete[] this->values[i];
    }
    delete[] this->values;
}

matrix_cell Matrix::get(size_t row, size_t col){
    return this->values[row][col];
}

void Matrix::set(size_t row, size_t col, matrix_cell value){
    this->values[row][col] = value;
}

Matrix& Matrix::operator=(const Matrix &m) {
    if (this->row_count != m.row_count || this->col_count != m.col_count)
        std::runtime_error("Unequal dimensions!");
    else{
        for (int row = 0; row <= this->row_count; row++)
            for (int col = 0; col <= this->col_count; col++)
                this->values[row][col] = m.values[row][col];
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    for (int row = 0; row < matrix.row_count; ++row){
        for (int col = 0; col < matrix.col_count; ++col){
            os << matrix.values[row][col] << ' ';
        }
        os << '\n';
    }
    return os;
}

std::istream &operator>>(std::istream &is, Matrix &matrix){
    for (int row = 0; row < matrix.row_count; ++row){
        for (int col = 0; col < matrix.col_count; ++col) {
            is >> matrix.values[row][col];
        }
    }
    return is;
}

Matrix Matrix::operator+(const Matrix &m2) {
    if (this->row_count != m2.row_count || this->col_count != m2.col_count)
        std::runtime_error("Unequal dimensions!");
    else{
        size_t col = this->col_count;
        size_t row = this->row_count;
        Matrix m(row, col);
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                m.values[i][j] = this->values[i][j] + m2.values[i][j];
            }
        }
        return m;
    }
}

Matrix Matrix::operator*(int k){
    Matrix res(this->row_count, this->col_count);
    for (int i = 0; i < this->row_count; i++)
        for (int j = 0; j < this->col_count; j++)
            res.values[i][j] = this->values[i][j] * k;
    return res;
}

Matrix Matrix::operator*(const Matrix &m) {
    if (this->col_count != m.row_count)
        std::runtime_error("Wrong dimensions!");
    else {
        Matrix res(this->row_count, m.col_count);
        for (int row = 0; row < res.row_count; row++)
            for (int col = 0; col < res.col_count; col++)
                for (int i = 0; i < this->col_count; i++)
                    res.values[row][col] += this->values[row][i] * m.values[i][col];
        return res;
    }
}

Matrix Matrix::eye(size_t n) {
    Matrix res(n, n);
    for (int i = 0; i < n; i++)
        res.values[i][i] = 1;
    return res;
}