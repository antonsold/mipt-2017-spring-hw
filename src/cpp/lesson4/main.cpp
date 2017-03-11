#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
    int x;
    Matrix a = Matrix::eye(4);
    a.set(1, 2, -5);
    a.set(2, 2, 2);
    cout << Matrix::eye(4) * 2 * a + Matrix::eye(4);
    return 0;
}