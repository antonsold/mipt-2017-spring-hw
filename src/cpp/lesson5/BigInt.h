#include <iostream>
#ifndef MIPT_2017_SPRING_HW_BIGINT_H
#define MIPT_2017_SPRING_HW_BIGINT_H


class BigInt {
private:
    int capacity;
    short* values;
    short sign;
    int length() const; //число цифр без начальных нулей
    bool IsZero() const; //является ли нулем
    BigInt x10n(int n) const; //умножение на 10^n
public:
    BigInt(); //пустой
    BigInt(long long); //из числа
    BigInt(const char*); //из строки
    BigInt(const BigInt &a); //копирования
    BigInt(int, short); //по длине числа и знаку, второй аргумент чтобы не путать с BigInt(long long)
    ~BigInt();
    bool operator>(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator==(const BigInt&) const;
    bool operator>=(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    BigInt abs() const;
    BigInt operator-() const;
    BigInt& operator=(const BigInt&);
    BigInt operator+(const BigInt&) const;
    BigInt operator-(const BigInt&) const;
    BigInt operator*(const BigInt&) const;
    BigInt operator/(const BigInt&) const;
    friend std::ostream &operator<<(std::ostream &, const BigInt&);
    friend std::istream &operator>>(std::istream &, BigInt&);
};


#endif //MIPT_2017_SPRING_HW_BIGINT_H
