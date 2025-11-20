# STL容器

容器在C++中表示存储数据的工具，STL是C++中的标准模板库，它有很多可以泛用的组件，主要用于处理数据结构和算法。经典的STL主要包含6大组件：

1. 容器Container
2. 算法Algorithms
3. 迭代器Lterators
4. 函数对象Functions
5. 适配器Adapter
6. 分配器Allocators

今天我们就来看看其中的容器如何使用。

### 容器

STL容器是一组类模板，主要包含三大类：序列式容器、关联式容器、无需关联式容器。

#### 序列式容器

1. std::vector
   
这是一个动态数组，可以定义这个数组存储的数据类型，尾部和头部删除和添加很快（O(1)），而在中间添加和删除较慢（O(n)）。说到快慢，就要说到代码的时间复杂度了。

我们先简单地说O(1)是个常数时间，它的操作耗时几乎不随变量个数耳边。

而O(n)是一个线性时间，它的操作时间随变量的大小而线性增加。

为什么在vector中插入数据和尾部插入数据有不同的变化呢？vector看作一个一维向量，其中的数据和位置是有对应关系的，当我们在向量的尾部添加或删除数据时，
也就只是将尾部数据向前或者向后插入，**中间数据状态不变**。而如果在向量中间插入一个数字，会导致原本的数据被分为两部分，**必然有一部分的数据会整体偏移**。

这是由于在代码中，vector内存分布的数据是连续的，如果在头部或者中间添加的话，会导致后面的数据需要整体做地址偏移。

我们可以在定义vector时提前定义容量`reserve`，这样可以直接分配对应容量的数组，不过vector的容量可以动态管理，当vector中容量不足时，就可以发生**扩容**。

扩容由于会在地址空间中重新分布一块连续内存，所以在程序中比较耗时，时间复杂度也是O(n)。

对于vector来说，主要的成员函数有：访问元素`at(i) operator[]`、获取大小`size()`、容量`capacity()`、是否为空`empty()`、
首/尾元素`front() back()`、插入`push_back(x)`、删除`pop_back()`、清空`clear()`、重设大小`resize(n) resize(n, val)`、
预留空间`reserve(n)`、释放多于内存`shrink_to_fit()`。

```
#include <iostream>
#include <vector>

int main(){
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    std::cout << "Vector size: " << numbers.size() << std::endl;
    std::cout << "Vector capacity: " << numbers.capacity() << std::endl;

    int ret = numbers.empty();
    if(ret){
        std::cout << "Vector is empty" << std::endl;
    } else {
        std::cout << "Vector is not empty" << std::endl;
    }

    std::cout << "first element: " << numbers.front() << std::endl;
    std::cout << "last element: " << numbers.back() << std::endl;

    std::cout << "push_back: ";
    numbers.push_back(6);
    for(const auto& num : numbers){
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "pop_back: ";
    numbers.pop_back();
    for(const auto& num : numbers){
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "clear vector" << std::endl;
    numbers.clear();
    std::cout << "Vector size after clear: " << numbers.size() << std::endl;

    numbers.resize(10);
    std::cout << "Vector size after resize to 10: " << numbers.size() << std::endl;

    numbers.shrink_to_fit();
    std::cout << "Vector size after shrink_to_fit: " << numbers.size() << std::endl;

    return 0;
}
```

我们在代码中看到了熟悉的内容：

```
for(const auto& num : numbers){
        std::cout << num << " ";
}
```

我们在Auto的那一章的末尾讲到了这个概念，这个可以看作是循环遍历容器每个元素，并且输出的简化版代码，像这样依次访问某个序列中的每个元素并作出行动的方法，
叫做**迭代**。

我们这里写到的代码其实是简化版的代码，实际上这段代码会被编译器编译为如下内容：

```
{
    auto&& __range = numbers;    //引用折叠
    auto __begin = __range.begin();
    auto __end   = __range.end();
    for (; __begin != __end; ++__begin) {
        const auto& num = *__begin;  // 不拷贝数据！
        std::cout << num << "\n";
    }
}
```

auto&&是一个通用引用，左值右值可以随numbers而定，不用手动确定。

我们观察简化版的代码，其实就是取得了numbers的头部元素和尾部元素之后的位置的指针，通过头部指针不断遍历，获得vector中的数据并解引用`*__begin`，
然后将这个指针不断指向每一个元素，直到指向末尾元素之后一个位置后，结束迭代。

其中`__begin`实现了遍历容器所有元素地址，解引用获取元素，可以自增地址的能力，我们把在迭代中具有这样功能的指针叫做**迭代器**。

此时我们回到这段代码：

```
for(const auto& num : numbers){
        std::cout << num << " ";
}
```

在for的判断条件中，我们使用一个简化的代码替换了较为复杂的代码部分，并且能实现原来的功能。像这样的语法，
由于它让我们的代码变得更加易读易写，而且底层逻辑不变的语法，我们叫做**语法糖**。

2. std::deque

这是双端队列，它在内存中的分布与一整块连续的vector不同。它在内存中由两个逻辑部分组成：中央控制数组(map)、多个固定大小的缓冲块(buffer)。缓冲块就是内存块，只是我们不是主动去管理而是自动管理的内存块，而是程序自动分配的内存。但是注意，vector、deque都是使用的堆区的内存。

其中中央控制数组存储着指向每个buffer缓冲块的首地址。当调用deque时，中央控制数组首先初始化，在第一次插入数据的时候，首先分配一个空的缓冲块。由于数据是由map管理的，在deque的前后分配内存都会很方便，不需要改动中间的部分。

双向队列的主要成员函数有：元素访问`dp[0]（不检查边界） dp.at()检查边界 dp.front() dp.back()`、容量管理`dp.empty()（是否为空） dp.size() dp.max_size()（最大可能大小）`、元素修改`push_front() push_back()（插入） pop_front() pop_back()（删除） insert() 插入 erase()删除 clear()` 

其中max_size()表示这个容器在当前系统中理论上能容纳的最多元素。不需要过多关注这个函数其实很少用到。

```
int main(){
    std::deque<int> dq = {1, 2, 3, 4, 5};

    for(const auto& elem : dq){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::cout << "Element at index 2: " << dq[2] << std::endl;
    std::cout << "Element at index 3: " << dq.at(3) << std::endl;
    std::cout << "Front element: " << dq.front() << std::endl;
    std::cout << "Back element: " << dq.back() << std::endl;
    std::cout << "Deque size: " << dq.size() << std::endl;
    std::cout << "Is deque empty? " << (dq.empty() ? "Yes" : "No") << std::endl;
    std::cout << "Max size of deque: " << dq.max_size() << std::endl;

    dq.push_back(6);
    dq.push_front(0);
    std::cout << "Deque after push_back and push_front: ";
    for(const auto& elem : dq){
        std::cout << elem << " ";   
    }
    std::cout << std::endl;
    dq.pop_back();
    dq.pop_front();
    std::cout << "Deque after pop_back and pop_front: ";
    for(const auto& elem : dq){
        std::cout << elem << " ";   
    }
    std::cout << std::endl;

    dq.insert(dq.begin() + 2, 10);
    std::cout << "Deque after insert 10 at index 2: ";
    for(const auto& elem : dq){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    dq.erase(dq.begin() + 2);
    std::cout << "Deque after erase element at index 2: ";
    for(const auto& elem : dq){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    dq.clear();
    std::cout << "Deque size after clear: " << dq.size() << std::endl;

    return 0;
}
```

