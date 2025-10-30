#include <iostream>
using namespace std;

int print(int a) {return a;}
double print(int a) {return (double)a;}

int main() {
    print(10);
    return 0;
}
