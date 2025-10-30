#include <iostream>

void reset(int* p) {
    if (p != nullptr) {
        *p = 0;
    }
}

int main(){
    int a = 5;
    reset(&a);    // 改成 0
    std::cout << "a = " << a << std::endl;
    reset(nullptr); // 不操作
    return 0;
}
