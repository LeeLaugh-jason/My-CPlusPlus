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

