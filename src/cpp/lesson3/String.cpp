#include "string.h"
#include <cstring>
#include <iostream>

String::String(){
    this->capacity = 1;
    this->values = new char[1];
    this->values[0] = 0;
}

String::String(const char* a){
    int i = 0;
    while (a[i] != 0)
        i++;
    this->values = new char[i + 1];
    this->capacity = (size_t)i + 1;
    for (int j = 0; j < i; ++j)
        this->values[j] = a[j];
    this->values[i] = 0;
}

String::String(const String& s){
    this->capacity = s.capacity;
    this->values = new char[this->capacity];
    memcpy(this->values, s.values, s.length());
}

String::~String(){
    delete[] this->values;
}

String &String::append(const char * s) {
    int i = strlen(s);
    char* new_values = new char[this->capacity + i];
    memcpy(new_values, this->values, this->length());
    memcpy(new_values + this->length(), s, i);
    new_values[this->length() + i] = 0;
    delete[] this->values;
    this->values = new_values;
    this->capacity += i;
    return *this;
}

String &String::append(const char symbol){
    char* new_values = new char[this->capacity + 1];
    memcpy(new_values, this->values, this->length());
    new_values[this->length()] = symbol;
    new_values[this->length() + 1] = 0;
    this->capacity += 1;
    delete[] this->values;
    this->values = new_values;
    return *this;
}

String &String::append(const String &s){
    size_t i = s.length();
    char* new_values = new char[this->capacity + i];
    memcpy(new_values, this->values, this->length());
    memcpy(new_values + this->length(), s.values, i);
    new_values[this->length() + i] = 0;
    delete[] this->values;
    this->values = new_values;
    this->capacity += i;
    return *this;
}

String String::substring(int start, int finish) const{
    int f = (finish == -1)?(int)this->length() - 1:finish;
    char* str = new char[f - start + 2];
    for (int i = 0; i < f - start + 1; i++)
        str[i] = this->values[start + i];
    str[f - start + 1] = 0;
    String s(str);
    s.capacity = (size_t)(f - start + 2);
    return s;
}

String String::operator+(const char symbol) const{
    char* result = new char[this->capacity + 1];
    memcpy(result, this->values, this->length());
    result[this->length()] = symbol;
    result[this->length() + 1] = 0;
    String s(result);
    return s;
}

size_t String::length() const{
    size_t i = 0;
    while (this->values[i] != 0)
        i++;
    return i;
}

String String::operator+(const char* s) const{
    int i = strlen(s);
    char* result = new char [this->length() + i + 1];
    memcpy(result, this->values, this->length());
    for (int j = 0; j < i; j++){
        result[this->length() + j] = s[j];
    }
    result[this->length() + i] = 0;
    String str(result);
    return str;
}

String String::operator+(const String& s) const{
    char* result = new char [this->length() + s.length() + 1];
    memcpy(result, this->values, this->length());
    for (int j = 0; j < (int)s.length(); j++){
        result[this->length() + j] = s.values[j];
    }
    result[this->length() + s.length()] = 0;
    String str(result);
    return str;
}

int String::find(const char c){
    for (int i = 0; i < (int)this->length(); i++)
        if (this->values[i] == c)
            return c;
    return -1;
}

char &String::operator[](const int i) const{
    return (this->values[i]);
}

std::ostream &operator<<(std::ostream &os, const String &s) {
    os << s.values << '\n';
    return os;
}

String &String::operator=(const char *s){
    size_t i = strlen(s);
    char* new_values = new char[i + 1];
    memcpy(new_values, s, i);
    new_values[i] = 0;
    delete[] this->values;
    this->values = new_values;
    this->capacity = i + 1;
    return *this;
}

String &String::operator=(const char c){
    delete[] this->values;
    this->capacity = 2;
    this->values = new char[2];
    this->values[0] = c;
    this->values[1] = 0;
    return *this;
}

String::operator char *() const{
    return this->values;
}

String::operator int() const{
    return atoi(this->values);
}

String::operator double() const{
    return atof(this->values);
}