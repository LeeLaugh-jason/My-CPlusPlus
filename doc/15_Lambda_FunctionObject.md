# Lambda和函数对象

要解释Lambda，我们需要先从函数对象说起

### 函数对象

什么是函数对象？我们举个例子

```
struct Adder {
    int operator()(int a, int b) const {
        return a + b;
    }
};

Adder add;          // 创建函数对象
int result = add(3, 4);  // 像调用函数一样使用：结果为 7
```

我们使用struct定义了一个结构体Adder，在里面对`operator()`进行了重载。我们使用Adder创建了一个函数对象，可以像调用函数一样调用这个对象。

> 为什么我们可以在struct中定义一个函数？

> 注意！在C++中，结构体其实就是class类的一种。只不过struct和class默认继承方式不同：class默认为private继承，struct默认为public继承

也就是说，函数对象其实实际上就是一个对象，只不过我们通过重载`operator()`，使得这个对象可以被当成函数一样使用。

用专业一点的话说，**函数对象**(Function Object)（也被称为仿函数(Functor)），是指行为像函数的对象。
也是重载了函数调用运算符`operator()`的一个类的实例

它作为对象可以被放在栈区、堆区、全局区，而它其中定义的代码会被放在代码区。

如何定义函数对象？实际上就是重载operator()罢了。

如何使用函数对象呢？就像正常调用函数一样就好。

```
MyFunctor doubler(2);
int result = doubler(5);  // 调用 operator()(5)
std::cout << result;      // 输出: 10
```

函数对象可以用在比较器中：

```
#include <iostream>
#include <vector>
#include <algorithm>

struct Descending {
    bool operator()(int a, int b) const {
        std::cout << "Comparing " << a << " and " << b << "\n";
        return a > b;
    }
};

int main() {
    std::vector<int> v = {1, 3, 2};
    std::sort(v.begin(), v.end(), Descending{});
}
```

这样输出的内容会是：

```
Comparing 3 and 1
Comparing 2 and 3
Comparing 2 and 1
```

其中我们只提供了`Descending{}`，表示默认构造了这个临时对象，不过没有提供参数值。因为在sort中会自动调用这个比较器并且输入参数。

### Lambda表达式

Lambda是创建匿名函数对象的表达式。什么是匿名函数对象？

函数对象我们已经知道了，实际上就是类。而匿名函数对象表示我们创建这个类可以不用显式创建名字，而是由编译器自动生成。

当你写一个Lambda表达式：

```
auto f = [](int x) { return x * 2; };
```

编译器会自动整理为(伪代码)：

```
class __Lambda_Unique_Name_123 {
public:
    int operator()(int x) const {
        return x * 2;
    }
};

__Lambda_Unique_Name_123 f;  // 创建这个匿名类的对象
```

简单来说Lambda最基础的功能，实际上就是简化了匿名函数的写法。为什么要简化呢？

当我们想要用一个功能的时候，只会用在这里一次，而其它地方都不会用到。如果我们显示地定义一个函数对象，会十分冗余。

而如果我们只是使用Lambda表达式作为函数对象传递给其他需要调用函数指针的地方，就会十分对象

当然，匿名函数对象表达式还有更加突出的功能：捕获一般函数得不到的局部变量：

```
void process(int threshold) {
    std::vector<int> data = {1, 5, 10, 15};
    
    // 想过滤出 > threshold 的元素
    auto filtered = std::vector<int>{};
    std::copy_if(data.begin(), data.end(), std::back_inserter(filtered),
                 [threshold](int x) { return x > threshold; }); // 捕获 threshold！
}
```

捕获的意思其实就是把原本不会在调用lambda函数作用域的空间的值传递到这个空间中。

而在这个匿名函数对象中，不同捕获方式存在于函数对象的方式也不同。

1. 值捕获

形式如下：

```
auto lambda = [x]() {return x; }
```

在写lambda表达式时，可以在[]中写入`[=]`或者直接写要捕获的值`[x]`，就可以实现值捕获。相当于在函数对象中创建了成员变量，并将捕获到的成员变量的值拷贝到函数对象中。

在C++11开始写`[=]`，编译器会自动识别在函数对象中用到的变量，自动捕获实际使用的变量。

它的生命周期随函数对象的构造而生，随函数析构而灭。

把它与`()`括号中的元素相比较，`()`中的元素是传递给函数对象成员函数的临时变量，它的作用域只存在于函数调用的过程中。当函数调用完后它的内存就会被释放掉，而我们捕获的成员变量不会。只要这个成员函数还存在，它就不会被释放。

当然这个捕获不是无限制的，它只能捕获当前函数成员所在作用域内的局部变量。它无法捕获全局变量，

2. 引用捕获

形式如下：

```
int a = 10, b = 20;
auto f = [&a, &b]() {
    a++;      // 修改外部 a
    b += a;   // 修改外部 b
};
f();
std::cout << a << ", " << b; // 输出: 11, 31
```

我们已经知道了，函数对象的捕获就是将捕获到的值拷贝给函数对象的成员变量。引用捕获会在函数对象中生成一个引用类型的成员变量：

```
// 你写的：
int x = 5;
auto lambda = [&x]() { x = 10; };

// 编译器实际生成：
class __lambda {
    int& x;  // 成员是引用（底层通常实现为指针）
public:
    __lambda(int& x_) : x(x_) {}
    void operator()() const { x = 10; }
};

__lambda lambda(x); // 构造时绑定 x 的地址
```

它可以改变其引用的外部变量的值。注意引用捕获的作用域是引用变量本身的作用域，如果变量被delete或者离开了它所在的作用域，特别是作为函数返回值返回的时候，引用变量实际上已经结束了自己的生命周期。

```
auto dangerous() {
    int local = 100;
    return [&local]() { return local; }; // ❌ 引用局部变量
} // local 销毁！

int main() {
    auto f = dangerous();
    std::cout << f(); // ❌ 未定义行为！可能输出垃圾值或崩溃
}
```

主要还是由于，函数对象可能会跨越不同作用域，但是不同作用域自己的变量是不能的。

#### 用途？

学了这么多，我们可以用它来干什么呢？不能就只是看着方便吧？

当然不是，它可以用得十分方便。

尤其是在*STL*中。

我们知道，STL中的类都是已经封装好的，留出来的接口是固定的，我们没法通过改源代码来传入更多参数。因此Lambda函数对象就起作用了。

```
void filterData(std::vector<int>& v) {
    int threshold = 10;  // ← 局部变量

    // ✅ 必须捕获 threshold！
    v.erase(std::remove_if(v.begin(), v.end(), 
               [threshold](int n) { return n < threshold; }), 
            v.end());
}
```

这里的v对象是std::vector模板类创建的，其erase变量是它的一个成员函数。能提供给这个成员函数的参数的接口是固定的，它会带着这些接口进入到自己的作用域中，算是与外界分隔开。

这个时候我们可以将它与Lambda结合起来，用Lambda捕获其他的变量到STL封装好的函数中，这样就做到了**接口不变但是可以传入更多参数**的功能。
