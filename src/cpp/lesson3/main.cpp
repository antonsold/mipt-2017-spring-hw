#include <iostream>
#include "String.h"

using namespace std;

int main(){
    String s1 = "1234";
    s1.append('s');
    String s2 = s1.substring(0, 2);
    cout << int(s2) << endl;
    cout << s1 + 'e';
    s2 = "wpoqqx13d3";
    cout << s2;
    String s3 = s2 + 'b' + s1 + "qwerty";
    cout << s3;
    return 0;
}