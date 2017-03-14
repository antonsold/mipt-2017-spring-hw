#include "BigInt.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <stdexcept>

int NumberLen(long long n){
    if (n == 0)
        return 1;
    int count = 0;
    while (n != 0){
        n /= 10;
        count++;
    }
    return count;
}

int StrLen(const char* c){
    int count = 0, i = 0;
    while((c[i] == '0' || i == 0 && c[0] == '-') && c[i] != 0){
        count++;
        i++;
    }
    return count == strlen(c) ? 1 : strlen(c) - count;
}
BigInt::BigInt(){
    this->sign = 1;
    this->capacity = 1;
    this->values = new short [1];
    this->values[0] = 0;
}

BigInt::BigInt(const char* c){
    int len = strlen(c);
    this->capacity = StrLen(c);
    this->values = new short[this->capacity];
    if (c[0] == '-')
        this->sign = -1;
    else
        this->sign = 1;
    for (int i = 0; i < this->capacity; i++)
        this->values[i] = c[i + len - this->capacity] - '0';
}

BigInt::BigInt(long long number){
    if (number == 0) {
        this->capacity = 1;
        this->values = new short[1];
        this->values[0] = 0;
    }
    else{
        this->capacity = NumberLen(number);
        this->values = new short[this->capacity];
        if (number >= 0)
            this->sign = 1;
        else
            this->sign = -1;
        number = llabs(number);
        int i = 0;
        while (number > 0){
            this->values[this->capacity - i - 1] = (short)(number % 10);
            number /= 10;
            i++;
        }
    }
}

BigInt::BigInt(const BigInt &a){
    this->capacity = a.capacity;
    this->sign = a.sign;
    this->values = new short [this->capacity];
    for (int i = 0; i < this->capacity; i++)
        this->values[i] = a.values[i];
}

BigInt::BigInt(int len, short sign){
    this->capacity = len;
    this->sign = sign;
    this->values = new short [len];
}

bool BigInt::IsZero() const{
    bool flag = true;
    for (int i = 0; i < this->capacity; i++)
        if (this->values[i] != 0)
            flag = false;
    return flag;
}

BigInt::~BigInt(){
    delete[] this->values;
}

int BigInt::length() const {
    if (this->IsZero())
        return 0;
    int count = 0, i = 0;
    while(this->values[i] == 0){
        count++;
        i++;
    }
    return this->capacity - count;
}

std::ostream &operator<<(std::ostream &os, const BigInt& a){
    if (a.IsZero())
        os << '0';
    else {
        if (a.sign == -1)
            os << '-';
        int zeros = a.capacity - a.length();
        for (int i = zeros; i < a.capacity; i++)
            os << a.values[i];
    }
    return os;
}

BigInt& BigInt::operator=(const BigInt &a) {
    this->capacity = a.capacity;
    this->sign = a.sign;
    short* tmp = new short[this->capacity];
    for (int i = 0; i < this->capacity; i++){
        tmp[i] = a.values[i];
    }
    delete[] this->values;
    this->values = tmp;
    return *this;
}

BigInt BigInt::operator+(const BigInt& a) const{
    if (this->sign == a.sign) { //складываем только числа с одинаковыми знаками
        int len1 = this->length(), len2 = a.length(), cap1 = this->capacity, cap2 = a.capacity;
        int cap = std::max(len1, len2) + 1; //длина числа увеличивается не более, чем на 1
        short nxt = 0; //перенос старшего разряда
        if (len1 >= len2) {
            BigInt res(cap, this->sign);
            res.values[0] = 0;
            for (int i = 1; i <= len1 - len2; i++)
                res.values[i] = this->values[cap1 - len1 + i - 1];  //копируем первые цифры
            for (int i = 1; i <= len2; i++) {
                short sum = this->values[cap1 - i] + a.values[cap2 - i] + nxt; //остальные складываем
                res.values[cap - i] = sum % (short) 10;
                nxt = sum / (short) 10;
            }
            res.values[cap - len2 - 1] += nxt;
            return res;
        } else {
            return (a + *this); //если второе длиннее первого, меняем местами
        }
    }
    else
        return -(-*this - a); //если знаки разные, используем вычитание
}

bool BigInt::operator>(const BigInt& a) const{
    int cap1 = this->capacity, cap2 = a.capacity, len1 = this->length(), len2 = a.length();
    if (this->sign > a.sign)
        return true;
    if (a.sign > this->sign)
        return false;
    if (len1 > len2)
        return (bool) (this->sign + 1);
    if (len2 > len1)
        return (bool) (this->sign - 1);
    //простые проверки знаков и длины
    int i = 0;
    while (this->values[cap1 - len1 + i] == a.values[cap2 - len2 + i] && i < len1) //если знаки и длины равны, идем по разрядам
        i++;
    if (i - len1 == cap1) //дошли до конца
        return false;
    return (bool) (this->values[cap1 - len1 + i] > a.values[cap2 - len2 + i] ? this->sign + 1 : this->sign - 1); //встретили неравенство
}

bool BigInt::operator<(const BigInt& a) const{
    return (a > *this);
}

bool BigInt::operator==(const BigInt& a) const{
    if (this->sign != a.sign || this->length() != a.length())
        return false;
    int cap1 = this->capacity, cap2 = a.capacity, len1 = this->length(), len2 = a.length();
    for (int i = 0; i < len1; i++){
        if (this->values[cap1 - len1 + i] != a.values[cap2 - len2 + i])
            return false;
    }
    return true;
}

bool BigInt::operator>=(const BigInt& a) const{
    return *this > a || *this == a;
}

bool BigInt::operator<=(const BigInt& a) const{
    return *this < a || *this == a;
}

BigInt BigInt::operator-() const{
    BigInt res(*this);
    res.sign *= -1;
    return res;
}

BigInt BigInt::abs() const{
    BigInt res(*this);
    res.sign = 1;
    return res;
}

BigInt BigInt::operator-(const BigInt &a) const{
    if (this->sign != a.sign){
        return *this + (-a);
    }
    else{
        int nxt = 0;
        if (this->abs() >= a.abs()){
            int len1 = this->length(), len2 = a.length(), cap1 = this->capacity, cap2 = a.capacity;
            BigInt res(len1, this->sign);
            for (int i = 0; i < len1 - len2; i++) //аналогично сложению
                res.values[i] = this->values[cap1 - len1 + i];
            for (int i = 1; i <= len2; i++){
                int diff = this->values[cap1 - i] - a.values[cap2 - i] + nxt;
                if (diff < 0){
                    diff += 10;
                    nxt = -1;
                }
                else
                    nxt = 0;
                res.values[len1 - i] = (short)diff;
            }
            if (len1 > len2)
                res.values[len1 - len2 - 1] += nxt;
            return res;
        }
        else //если второе больше по модулю, меняем местами
            return -(a - *this);
    }
}

BigInt BigInt::x10n(int n) const { //копируем поразрядно и дописываем нули
    if (-n >= this->length()){
        BigInt res("0");
        return res;
    }
    else {
        BigInt res(this->length() + n, this->sign);
        for (int i = 0; i < this->length(); i++)
            res.values[i] = this->values[this->capacity - this->length() + i];
        for (int i = 0; i < n; i++)
            res.values[this->length() + i] = 0;
        return res;
    }
}

BigInt BigInt::operator*(const BigInt &a) const{
    int cap1 = this->capacity, cap2 = a.capacity, len1 = this->length(),  len2 = a.length();
    BigInt res("0");
    for (int i = 0; i < len2; i++){ //умножаем первое число на каждую цифру второго
        BigInt part(len1 + 1, 1); //результат умножения
        short add = 0; //переход старшего разряда
        for (int j = 1; j <= len1; j++){ //само умножение
            short pr = this->values[cap1 - j] * a.values[cap2 - i - 1] + add;
            part.values[len1 + 1 - j] = pr % (short)10;
            add = pr / (short)10;
        }
        part.values[0] = add;
        res = res + part.x10n(i); //прибавляем как в "столбике"
        res.sign = this->sign * a.sign; //определяемся со знаком
    }
    return res;
}

BigInt BigInt::operator/(const BigInt &a) const{
    if (a.IsZero())
        throw std::runtime_error("Division by zero!");
    if (this->abs() < a.abs()){
        BigInt res("0");
        return res;
    }
    else{
        int len1 = this->length(), len2 = a.length(), cap = len1 - len2 + 1;
        BigInt res(cap, this->sign * a.sign);
        BigInt dividend = this->abs();
        BigInt divisor = a.abs();
        for (int i = 0; i < cap; i++){
            short k = 0;
            BigInt div = divisor.x10n(len1 - len2 - i);
            while (dividend >= div){
                dividend = dividend - div;
                k += 1;
            }
            res.values[i] = k;
        }
        return res;
    }
}

std::istream &operator>>(std::istream &is, BigInt& a){
    BigInt temp("0");
    int c = is.get();
    if (c == '-') {
        temp.sign = -1;
        c = is.get();
    }
    while (c - '0' <= 9 && c - '0' >= 0){
        BigInt tmp(c - '0');
        temp = temp.x10n(1) + tmp;
        c = is.get();
    };
    a = temp;
    return is;
}
