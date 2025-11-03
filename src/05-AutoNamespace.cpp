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
    std::cout << "局部变量x: " << x << std::endl; // 输出10
    std::cout << "全局变量x: " << ::x << std::endl; // 输出100
}

int main() {
    //Func1();
    Func2();
    return 0;
}