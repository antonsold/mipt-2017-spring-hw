#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <cstdlib>
#include <iosfwd>

typedef int matrix_cell;

class Matrix{
private:
    size_t row_count;
    size_t col_count;
    matrix_cell** values;
public:
    Matrix(const Matrix&);
    Matrix(size_t, size_t);
    ~Matrix();
    matrix_cell get(size_t, size_t);
    void set(size_t, size_t, matrix_cell);
    Matrix& operator=(const Matrix&);
    friend std::ostream& operator<<(std::ostream&, const Matrix&);
    friend std::istream& operator>>(std::istream&, Matrix&);
    Matrix operator+(const Matrix&);
    Matrix operator*(int k);
    Matrix operator*(const Matrix&);
    static Matrix eye(size_t n);
};
#endif //MATRIX_MATRIX_H
