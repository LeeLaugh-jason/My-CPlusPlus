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

4. std::nth_element 选取容器中第k小的元素，将它放在序列中第k-1个位置。

其序列前面的数字都小于它，后面的元素都大于等于它，但它们不是有序的。**仅仅完成list[k-1]=num(k)**

时间按复杂度为O(1)

5. std::is_sorted 检查是否排序

函数输入一个序列的两端迭代器。输出一个bool变量

如果序列中元素已排序好，那函数输出1；反之输出0。

### 二分查找（要求已排序）

1. std::binary_search 是否存在某个值

输入：start迭代器、end迭代器、某个值

输出：1（其中有这个值），0（没有这个值）

2. std::lower_bound

输入：对象的首尾迭代器，输入一个数值（可以不存在于对象容器内部）

输出：第一个大于等于这个数的位置（迭代器）

如果容器是降序排列，不能使用默认的这个函数，而是要更换comp比较器，如`std::greater<>()`，更换比较规则。

3. std::upper_bound

这个函数与lower_bound比较像，要默认使用的话，默认排序顺序必须是升序排序，如果要使用降序的话，要更换比较器comp，与上述一样。

4。 std::equal_range 返回某个值在容器或序列中的范围

输入一个两个迭代器，输入一个数字，可选择输入一个比较器。

输出两个迭代器，分别代表这个数字在排序序列中的第一个位置(first)和最后一个位置(second)。其实是lower_bound和upper_bound的返回值

```
auto low = std::lower_bound(first, last, value);
auto up  = std::upper_bound(first, last, value);
// 等价于
auto range = std::equal_range(first, last, value);
// 此时 range.first == low, range.second == up
```

我们拿到这两个迭代器，想要输出就直接迭代就好。形式相当于在一个容器中的一个范围内迭代。

### 集合操作（需有序）

1. std::merge 合并两个有序序列

输入两个有序序列的首尾迭代器，再输入一个能容下它们合并后序列的容器，可选comp比较器。

merge内部实际上使用双指针归并的方式进行合并排序：两个序列都从开始的迭代器比较，谁小就先放到容器中，再对放入容器的原序列迭代器自增。

得到的result序列也是有序的。不是单纯的拼接。

2. std::set_union 取两个有序集合的并集

输入与上述merge相同，输出一个合并后的有序序列。

3. std::set_intersection / std::set_difference / std::set_symmetric_difference

输入与上述相同，输出分别是：取两集合交集、差集(A - B)、对称差集（A ∪ B - A ∩ B）

### 堆操作（默认大堆顶）

我们在讲sort排序时，从混合排序中简单的了解了**堆**这个数据结构，它是一个完全二叉树，可以用序列将他表示出来。

1. std::make_heap

这个函数可以将一个vector序列默认变为一个最大堆，也可以传递comp比较器将序列变为最小堆。这样查询修改中间键时，时间复杂度从O(n)降低到O(logn)。

2. std::push_heap

