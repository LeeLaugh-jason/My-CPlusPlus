# 函数重载与默认参数

### 函数重载
什么是函数重载？在同一个作用域中，函数名相同、但参数列表不同（类型、数量、顺序不同）的多个函数称为重载函数。

编译器会根据实时调用时传入的参数类型，自动选择调用哪一个版本的函数：

```
#include <iostream>
using namespace std;

void print(int x) {
    cout << "int: " << x << endl;
}

void print(double x) {
    cout << "double: " << x << endl;
}

void print(const char* s) {
    cout << "string: " << s << endl;
}

int main() {
    print(10);       // 调用 print(int)
    print(3.14);     // 调用 print(double)
    print("Hello");  // 调用 print(const char*)
}
```

输出内容是：

<img width="455" height="69" alt="image" src="https://github.com/user-attachments/assets/24df6fda-84d8-4578-a299-a6dd392c4d54" />

也就是说在C++中，我们可以定义名字相同但是内容逻辑不同的函数，通过给进的参数不同，调用的函数也不同。这便是函数重载。

函数重载的规则如下：
  1. 函数名相同
  2. 参数个数/参数类型/参数顺序 不同
  3. 返回值类型不参与重载的区分

可以看出只是复制一个函数改变返回值的类型不能算函数重载，编译器会觉得你定义了同一个函数，而不是两个重载版本，在编译的时候就会报错：

<img width="514" height="154" alt="image" src="https://github.com/user-attachments/assets/b3b2d254-c9fb-4151-8b75-98c5fc730cde" />

其中`ambiguating new declaration of ‘double print(int)’`点明了这一点，意思是 “新的声明与旧的声明产生歧义”。

### 默认参数

什么叫做默认参数，其实我之前在`python`中见到过，在函数的定义或者声明中，可以给某些参数提供默认值，这样在调用的时候可以省略这些参数。

```
void greet(string name = "Guest", int times = 1) {
    for (int i = 0; i < times; ++i)
        cout << "Hello, " << name << "!" << endl;
}

int main() {
    greet();              // 使用默认值 ("Guest", 1)
    greet("Alice");       // 覆盖第一个参数
    greet("Bob", 3);      // 覆盖全部参数
}

```

输出结果如下：

<img width="471" height="103" alt="image" src="https://github.com/user-attachments/assets/9a0f22dd-ebdc-4cac-86eb-cae5cf72d558" />

这个很好理解，不过如果把这个跟函数重载混用在一起呢？

我通过定义同一个函数名的函数，两个函数的第一个参数相同，一个没有第二个参数，另一个第二个参数为默认参数，会发生什么呢？

```
void test(int a);
void test(int a, int b = 0);

int main(){
    test(5);      
    return 0;
}
```

发现这个程序在编译的时候就报错：`call of overloaded ‘test(int)’ is ambiguous`（有歧义）

<img width="641" height="205" alt="image" src="https://github.com/user-attachments/assets/995f0220-55b6-4cdb-b0ab-073d3992cbf1" />

编译器在选择函数时会进行两件事情：1.找到所有叫test的函数，2.看看那些能用实参int调用。发现有两个函数都可以调用，编译器无法决定谁更合适，于是出现了报错。
