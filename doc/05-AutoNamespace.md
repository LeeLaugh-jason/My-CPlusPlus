# 作用域、命名空间和auto

### 作用域

啥是作用域？作用域是指变量或函数能被访问的范围。我们之前在内存管理中讲到过，
当我们在定义函数和变量的时候（不是静态或者全局）时候，代码会在栈区为每一个函数分配一个帧栈。
在函数内定义的变量会在随着函数的结束，帧栈的释放一同释放

因此对于这一类函数，在其中定义的变量就只存在于被调用的函数中。

这种在函数内定义，随函数销毁而销毁的变量的作用域，叫做 __局部作用域__

在我们写代码的时候常常用到for，while等循环：

```
for(i=1;i<0;i++){
    int j=0;
    
}
```

这些循环语句内部的内容通常用一个花括号括起来。

我们在花括号内定义的内容无法在花括号外调用：

```
void Func1(){
    int i = 0;
    for(i=0; i<10; i++){
        int j = i * 2;
    }
    printf("j=%d\n", j); // 错误，j的作用域仅在for循环内
}
```

<img width="1408" height="178" alt="image" src="https://github.com/user-attachments/assets/b9800257-3170-4350-93cc-2e3e8f53b861" />

报错说j没有定义在这个范围。这种用花括号{}括起来的变量，作用域在花括号内，叫做 **块作用域**

如果我们在花括号内外都定义了同一个变量呢？

```
int x = 100; // 全局变量

void Func2(){
    int x = 10;
{
    int x = 50; // 块作用域变量
    std::cout << "块作用域变量x: " << x << std::endl; // 输出50
    std::cout << "局部变量x: " << ::x << std::endl; // 输出100
    std::cout << "全局变量x: " << ::x << std::endl; // 输出100
}
    std::cout << "局部变量x: " << x << std::endl; // 输出10
    std::cout << "全局变量x: " << ::x << std::endl; // 输出100
}
```

<img width="978" height="204" alt="image" src="https://github.com/user-attachments/assets/7799ffb4-a14b-484c-ae7c-dc6f92b3b6a8" />

从运行结果看出：花括号更里面的变量可以隐藏比它外层的同名变量。但是使用`::`可以在各个块中打印全局变量。

如果想要在块中打印局部变量呢？可以尝试使用引用变量。

```
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
```

<img width="960" height="208" alt="image" src="https://github.com/user-attachments/assets/3c2aa2d8-d861-4605-aa44-256fe5c21343" />

通过引用让变量以别名进入根深的块中。

定义在函数外的变量作用域是 **全局作用域**，定义在类中的变量在 **类作用域**

在底层内存中，作用域是如何运行的呢？

首先，作用域不是在运行时才被排列出来的，而是在编译时就被确定下来了。

在编译时，编译器会维护一个 **符号表**，这个表用于记录：

* 每个变量的名字；
* 它所在的作用域层级；
* 它在内存（栈）中的偏移位置；
* 类型信息等。

当编译器遇到一个新的作用域就会：

* 创建一个新的符号表
* 作用域结束时这个表就会销毁
* 编译器会根据此计算变量的栈偏移

而在运行时，当程序运行到一个函数中，会创建这个函数的帧栈，在函数中定义的变量会顺序排列，当函数返回后帧栈整体弹出。

像上述代码中出现同名变量时，隐藏机制是在底层是如何运行的？

```
int x = 100; // 全局变量

void Func3(){
    int x = 10;
    {
        int x = 50;
        std::cout << x << std::endl; // 使用最内层的 x
    }
}
```

编译器的符号表如下：

<img width="608" height="173" alt="image" src="https://github.com/user-attachments/assets/81a50f56-9172-41a7-bd20-6eb2c943a645" />

编译器根据“就近作用域”原则，先查找当前块中有无对应变量，有就不再往外查。

块作用域结束时，编译器不会真的“释放”那几字节空间，
而是仅仅停止在符号表中追踪那个名字。
因此从语法层面它“消失”，但从物理内存层面，它还在。

**符号表**是编译器在语法分析阶段维护的数据结构，用于记录程序中出现的所有“名字”（标识符：变量名、函数名、类名、命名空间等）的所有信息。

### 命名空间

命名空间是C++中用来给名字分组的机制，避免命名冲突。

C++在全局范围内，所有标识符都共享一个“全局符号表”，当不同文件或其他情况下，在全局空间下定义了同一个名词的标识符，会产生冲突而报错：

```
// a.cpp
void init() {}

// b.cpp
void init() {}
```

编译时会报错

```
multiple definition of `init()`
```

为了解决这种问题，命名空间出现了

#### 命名空间基本语法

创建命名空间：

```
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
```

使用命名空间需要用到`::` **作用域解析运算符**，表示在命名空间中寻找符号

```
int main() {
    A::print(); // 输出 A::x = 10
    B::print(); // 输出 B::x = 20
    return 0;
}
```

命名空间可以嵌套使用：

```
namespace Outer {
    int a = 1;

    namespace Inner {
        int b = 2;
    }
}

int main() {
    std::cout << Outer::a << std::endl;        // 1
    std::cout << Outer::Inner::b << std::endl; // 2
    return 0;
}
```

也可以对命名空间取别名：

```
namespace OI = Outer::Inner;  // 给命名空间起别名
std::cout << OI::b << std::endl;
```

命名空间可以拆开来写，编译器会自动合并空间：

```
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
```

<img width="958" height="92" alt="image" src="https://github.com/user-attachments/assets/21f1a2ba-d576-42a7-8efc-12d14a3b0e81" />

命名空间可以使用匿名的方式定义，这样的命名空间只会在当前文件中被访问：

```
namespace {
    int secret = 42;
    void helper() {
        std::cout << "Hidden function\n";
    }
}

int main() {
    std::cout << secret << std::endl; // ✅ 可用
    helper(); // ✅ 可用
}
```

<img width="950" height="108" alt="image" src="https://github.com/user-attachments/assets/02e9c360-f1b4-4883-92b9-81ee04464a6a" />

我们可以用`using`引入命名空间：

```
using namespace std;

int main() {
    cout << "Hello" << endl;  // 不需要写 std::
}
```

也可以引入某个符号：

```
using std::cout;
using std::endl;

int main() {
    cout << "Hello" << endl;
}
```

命名空间不会被分配内存空间，而是仅仅在编译的时候创建在符号表中：

```
//编译前
namespace A { void f(){} }
namespace B { void f(){} }
//编译后
_ZN1A1fEv   // A::f()
_ZN1B1fEv   // B::f()
```

这个过程`_ZN1A1fEv`叫做**符号修饰**，用于防止命名冲突。

### Auto

Auto是自动类型推导关键字，它告诉编译器：请你根据右边表达式的类型自动推断出变量的类型。

```
auto x = 10;       // 编译器推断 x 是 int
auto y = 3.14;     // 推断 y 是 double
auto s = "hello";  // 推断 s 是 const char*
```

为什么需要auto来推断变量而不是手写呢？

这可能是手写出的内容：

```
std::vector<std::pair<std::string, int>> vec;
for (std::vector<std::pair<std::string, int>>::iterator it = vec.begin(); it != vec.end(); ++it) {
    ...
}
```

太长了，对人眼很不友好，而用了auto后：

```
for (auto it = vec.begin(); it != vec.end(); ++it) {
    ...
}
```

一下子就清晰了。

Auto的推导类型如下：

<img width="1194" height="774" alt="image" src="https://github.com/user-attachments/assets/e0eee738-908a-414e-b848-31d1678e599f" />

在其中出现了左值右值的概念：

左值就是在内存中可以找到具体地址的有名字变量，如定义的int x, double l，而右值是无法在内存中查找到对应地址的常量、中间值（3、x+1等），没有名字

我们看到图片中auto推导类型很复杂，但其实只是四种类型的组合：
* 普通值推导
* 常量值推导
* 指针推导
* 引用推导

其中引用推导又被分为：左值推导、右值推导、左值引用折叠三部分。

左值推导的情况，`auto& 变量 = 普通值变量` ，这个变量是左值引用普通值变量的别名。

右值推导的情况，`auto&& 变量 = 普通值`，这个变量是右值引用的普通值的别名。

左值引用推导，`auto&& 变量 = 普通值变量`，这个变量和左值推导的情况相同

在出现`auto&&`的情况中，只要出现左值引用，那么变量的引用规则就是左值引用

#### auto的常用方式

遍历容器

```
int Func6(){
    std::vector<int> v = {1, 2, 3};
    for (auto x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}
```

简化迭代器声明：

```
std::map<std::string, int> dict;
for (auto it = dict.begin(); it != dict.end(); ++it) {
    std::cout << it->first << ": " << it->second << std::endl;
}
```

容器和迭代器的具体概念我们在讲到STL的时候再来深究，现在可以把它们简单理解为数组和指针。
