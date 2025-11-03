#include <iostream>



void Func1(){
    int i = 0;
    for(i=0; i<10; i++){
        int j = i * 2;
    }
    //printf("j=%d\n", j); // 错误，j的作用域仅在for循环内
}

int x = 100; // 全局变量

void Func2(){
    int x = 10;
    int& ref = x;
{
    int x = 50; // 块作用域变量
    std::cout << "块作用域变量x: " << x << std::endl; // 输出50
    std::cout << "局部变量x: " << ref << std::endl; // 输出10
    std::cout << "全局变量x: " << ::x << std::endl; // 输出100
}
    std::cout << "局部变量x: " << x << std::endl; // 输出10
    std::cout << "全局变量x: " << ::x << std::endl; // 输出100
}

void Func3(){
    int x = 10;
    {
        int x = 50;
        std::cout << x << std::endl; // 使用最内层的 x
    }
}

namespace A {
    int x = 10;
    void print() {
        std::cout << "A::x = " << x << std::endl;
    }
}

namespace B {
    int x = 20;
    void print() {
        std::cout << "B::x = " << x << std::endl;
    }
}

int main() {
    A::print(); // 输出 A::x = 10
    B::print(); // 输出 B::x = 20
    return 0;
}