#include <iostream>

class ShallowCopyExample {
public:
    int* ptr;  // 指向动态分配的整数

    // 构造函数：分配内存
    ShallowCopyExample(int value) {
        ptr = new int(value);
        std::cout << "构造函数: 分配内存，地址 = " << ptr << ", 值 = " << *ptr << "\n";
    }

    // 默认拷贝构造函数（编译器生成）→ 执行浅拷贝
    // 相当于：
    // ShallowCopyExample(const ShallowCopyExample& other) {
    //     ptr = other.ptr;  // 只复制指针值，不复制指向的内容
    // }

    // 析构函数：释放内存
    ~ShallowCopyExample() {
        std::cout << "析构函数: 释放内存，地址 = " << ptr << "\n";
        delete ptr;  // ⚠️ 如果多个对象共享 ptr，这里会 double-delete！
    }
};

int main() {
    ShallowCopyExample obj1(42);
    ShallowCopyExample obj2 = obj1;  // 调用默认拷贝构造 → 浅拷贝！

    std::cout << "obj1.ptr = " << obj1.ptr << ", *obj1.ptr = " << *obj1.ptr << "\n";
    std::cout << "obj2.ptr = " << obj2.ptr << ", *obj2.ptr = " << *obj2.ptr << "\n";

    // 程序结束时，obj2 和 obj1 依次析构
    // 两者 ptr 指向同一地址 → delete 同一块内存两次 → 未定义行为（通常崩溃）
    return 0;
}