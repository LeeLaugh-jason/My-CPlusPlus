#include <iostream>
#include <vector>


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

namespace Outer {
    int a = 1;

    namespace Inner {
        int b = 2;
    }
}

namespace Log {
    void info() { std::cout << "info\n"; }
}

namespace Log {
    void error() { std::cout << "error\n"; }
}

int Func4() {
    Log::info();
    Log::error();
    return 0;
}

namespace {
    int secret = 42;
    void helper() {
        std::cout << "Hidden function\n";
    }
}

int Func5() {
    std::cout << secret << std::endl; // ✅ 可用
    helper(); // ✅ 可用
    return 0;
}

int Func6(){
    std::vector<int> v = {1, 2, 3};
    for (auto x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}


int main() {
    //A::print(); // 输出 A::x = 10
    //B::print(); // 输出 B::x = 20
    //std::cout << Outer::a << std::endl;        // 1
    //std::cout << Outer::Inner::b << std::endl; // 2
    //Func5();
    // auto x = 10;       // 编译器推断 x 是 int
    // auto y = 3.14;     // 推断 y 是 double
    // auto s = "hello";  // 推断 s 是 const char*
    Func6(); // 使用
    
    return 0;
}