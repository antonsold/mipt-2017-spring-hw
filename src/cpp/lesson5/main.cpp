#include <iostream>
#include "BigInt.h"

int main() {
    BigInt b1("5"), b2("52");
    std::cin >> b1;
    b1 = b1 * b1;
    std::cout << b1;
    return 0;
}
