#include <iostream>

int main() {
    int a = 10;
    int& r = a;   
    
    std::cout << &a << std::endl; // 地址①
    std::cout << &r << std::endl; // 地址②
    return 0;
}