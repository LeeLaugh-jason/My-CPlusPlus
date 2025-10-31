#include <iostream>
using namespace std;

int g = 10;          // 全局区
const char* msg = "Hello"; // 常量区

void func() {   // 内存分布演示
    int a = 5;        // 栈区
    int* p = new int(20); // 堆区
    static int s = 30;    // 静态区

    cout << "局部变量a地址: " << &a << endl;
    cout << "堆变量*p地址: " << p << endl;
    cout << "静态变量s地址: " << &s << endl;
    cout << "全局变量g地址: " << &g << endl;
    cout << "字符串msg地址: " << (void*)msg << endl;
    delete p;
}

void test() {   // 内存分布演示
    static int count = 0; // 作用域仅在 test() 内，但生命周期贯穿整个程序
    int local = 0;        // 作用域与生命周期都仅在 test()
    count++;
    local++;
    cout << "count=" << count << ", local=" << local << endl;
}

struct Demo {
    string name;
    Demo(string n) : name(n) { cout << name << " 构造\n"; }
    ~Demo() { cout << name << " 析构\n"; }
};

//Demo h("全局变量");

void func2() {
    Demo local("局部变量");
    static Demo s("静态变量");
    Demo* heap = new Demo("堆变量");
    delete heap;
}

void func3() {
    int* p = new int[5]; // 分配数组
    for (int i = 0; i < 5; i++) p[i] = i * 10;
    cout << "数组内容: ";
    for (int i = 0; i < 5; i++) cout << p[i] << " ";
    cout << endl;
    delete[] p; // 释放数组
}

void func4() {
    int* p = new int(10);

    cout << "p 的地址（在栈上）: " << &p << endl;
    cout << "p 指向的地址（在堆上）: " << p << endl;
    cout << "堆中存的值: " << *p << endl;

    delete p; // 释放单个整数
}

int main() {
    //func();
    //for (int i = 0; i < 3; i++) test();
    //func2();
    //cout << "main结束\n";
    //func3();
    func4();
    return 0;
}
