#include <iostream>
using namespace std;

void f(int x, int b = 10);


int main() {
    f('A');
}

void f(int x, int b = 10)    { cout << "f(int)" << endl; }
