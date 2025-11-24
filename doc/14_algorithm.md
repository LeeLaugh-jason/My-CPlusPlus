# 算法库<algorithm>

我们在容器那一节列举过，C++的STL库中的重要组成部分包含算法库。其中提供了大量通用、高效、可复用的算法，用于操作容器或其他序列。

这些算法有很多种不同的类别，我们按照不同类别来学习：

### 非修改型算法(Non-modifying)

只是读取序列中的数据，而不进行修改。

1. `std::find`查找元素

返回一个对应的迭代器，如果找不到数据就返回容器最后一个元素之后的位置，注意这个位置不能被解引用。

2. `std::count`统计出现次数

返回一个int类型的整数，代表出现的次数

3. `std::all_of / any_of / none_of`判断函数

它们用于对于一个范围内的数据（容器或数组）遍历判断

以all_of函数为例：

```
template< class InputIt, class UnaryPredicate >
bool all_of( InputIt first, InputIt last, UnaryPredicate p );
```

遍历`[first,last]`中的所有元素是否包含UnaryPredicate的p

### 修改型算法（Moditying）

1. `std::copy`复制范围内的数据

```
std::vector<int> src = {1,2,3}, dst(3);
std::copy(src.begin(), src.end(), dst.begin());
```

2. `std::fill`填充范围内的数据

```
std::fill(vec.begin(), vec.end(), 0);
```

3. `std::transform`对每个元素应用函数

```
std::transform(vec.begin(), vec.end(), vec.begin(), [](int x) { return x * x; });
```

4. `std::replace`替换值

```
std::replace(vec.begin(), vec.end(), 5, 99); // 把所有5换成99
```

### 排序与相关算法

1. `std::sort`排序，通常为快排/内省排序。这是sort中更高级的混合排序算法。

**快速排序**(QuickSort) 基本原理是使用递归的方式，先选择一个基准元素将数组分为两部分，小于基准的放左边，大于基准的放右边，递归地对左右两部分排序。好的情况下时间复杂度为O(n logn)，坏的情况下时间复杂度为O(n n)。

**内省排序**(Introsort = Intro + sort)

这是一种**混合排序算法**，结合了快速排序，堆排序、插入排序。

**堆排序**中使用堆这种数据结构，
**堆**是一个**完全二叉树**（从根节点开始，从上到下，从左到右的节点中，直到末尾之前都没有空缺），
它可以用数组高效储存。假设数组下标从0开始，对于任意节点i，父节点索引`(i - 1) / 2`，左孩子索引`2 * i + 1`，右孩子索引`2 * i + 2`。
因此，这使堆无需指针，仅用vector即可实现，节省内存且缓存友好。

堆排列的过程：首先建**最大堆**（父节点>子节点），再反复提取最大值（通过变量`heapSize`得到子数组大小，每次对其减一，进行子数组首尾元素交换，实现顺序排序）。堆这样排序的时间复杂度为O(n logn)

**插入排序**的当数组已升序的时候，时间复杂度是O(n)；数组随机排列时，时间复杂度为O(n n)；数组严格降序的时候，时间复杂度为O(n n)；

内省排序将三种排序方式组合在一起，主干用快速排序，监控递归的深度，若超过2*log2(n)可能会退化，此时切换到堆排序，保证O(n logn)的时间复杂度。当子数组长度小于一个阈值后，切换为插入排序，减少函数调用的开销。这种排序最坏的情况下，时间复杂度可以稳定保持再O(n logn)。

2. `std::stable_sort`稳定排序

相比于sort排序，稳定排序可以不改变相同元素的排列方式。打个比方，一组键值对中两个键值对的值相同，但是键不同，使用sort可能会改变两个键的位置，而使用stable_sort会保留原本键值对的排列顺序。

```
struct Student {
        std::string name;
        int score;
    };

    std::vector<Student> students = {
        {"Alice", 85},
        {"Bob", 90},
        {"Charlie", 85},
        {"David", 90}
    };

    // 按分数升序排序，但相同分数时保持输入顺序
    std::stable_sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return a.score < b.score;
        });

    std::cout << "Sorted students: ";
    for (const auto& s : students) {
        std::cout << s.name << ": " << s.score << "\n";
    }
    std::cout << std::endl;
```

```
Sorted students: Alice: 85
Charlie: 85
Bob: 90
David: 90
```

stable_sort的时间复杂度是O(n log^2(n))或者更好，额外占用的内存通常是O(n)；而sort时间复杂度平均为O(n logn)，二位内存通常是O(n logn)。

3. std::partial_sort 部分排序

可以传入一个容器，使用这个函数对容器中Top-K个数进行排序，并放在前面。而sort函数只是对于一个区间范围内进行全排序，与这个范围外的数据无关。

```
std::vector<int> v = {10, 4, 9, 1, 7, 3};
    std::partial_sort(v.begin(), v.begin() + 3, v.end());
    std::cout << "Partially sorted vector (first 3 elements): ";
    for (const auto& num : v) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
```

```
Partially sorted vector (first 3 elements): 1 3 4 10 9 7 
```

