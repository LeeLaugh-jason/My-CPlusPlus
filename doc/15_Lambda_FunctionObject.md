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

