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

3. std::list

list是STL中的双向链表，链表的数据结构由一个一个节点构成。每个节点中存放着上一个节点的指针（**前驱指针**）、下一个节点的指针（**后继指针**）和本节点的数据。

由节点我们可以看出，链表不像vector和deque，可以从序列号直接得到某个序列号中的节点数据，不过我们可以使用指针遍历的方式查找某一个节点的内存：通过前驱指针和后继指针，可以做到从头向尾部遍历，也可以做到从尾部向头部遍历。

不同于之前的vector和deque，双向链表支持直接修改中间的数据，而时间复杂度仅是O(1)。因为双向链表要在中间插入一个节点，只需要修改上下两个节点中指向彼此的指针就好，不需要修改这两个节点以外的内容。

在STL的双向链表中，第一个节点的prev(前驱指针)和末尾的节点的next(后继指针)会指向空指针`nullptr`；也可能指向一个哨兵指针，哨兵指针的前驱指针指向第一个节点，后继指针指向最后一个节点，首尾是不相连的。

```
int main_list(){
    std::list<int> mylist = {1, 2, 3, 4, 5};
    std::list<int> anotherList(mylist);
    for(const auto& elem : anotherList){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    mylist.push_back(6);
    mylist.push_front(0);
    for(const auto& elem : mylist){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    int firstElem = mylist.front();
    int lastElem = mylist.back();
    std::cout << "First element: " << firstElem << ", Last element: " << lastElem << std::endl;

    mylist.pop_back();
    mylist.pop_front();
    for(const auto& elem : mylist){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    auto it = mylist.begin();
    ++it; // Move to second element

    std::cout << "it points to: " << *it << std::endl;

    mylist.insert(it, 10); // Insert 10 before second element
    for(const auto& elem : mylist){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    mylist.erase(it); // Erase the element we just inserted
    for(const auto& elem : mylist){
        std::cout << elem << " ";   
    }
    std::cout << std::endl;

    mylist.erase(mylist.begin(), mylist.end()); // Clear the list
    std::cout << "List size after clear: " << mylist.size() << std::endl;
    

    return 0;
}
```

4. std::forward_list

这是STL容器中的单向链表，它的数据也是由一个一个节点串在一起的。不过相比于双向链表，单向链表的节点只有一个后继指针，数据只能找到它下一个数据的位置，而找不到它上一个数据在哪。

此时你还可以在节点之间插入数据，但是在首节点之前如何插入数据呢？

在单向链表中，有一个外部的的头指针`head`，它会指向第一个节点，这样在第一个节点前添加数据时，可以直接添加节点，然后让修改头指针指向这个节点即可。

5. std::array

这是STL中最像C语言中数据结构的一个容器：定长数组。

它的大小在创建的时候就会定下，内存存储在栈上，使用方式也和C语言相似，可以实现多维数组。

在C++中，STL为这个数组提供了整体赋值，拷贝，比较的功能。


#### 关联式容器（有序）

1. std:set

这是STL中基于**平衡二叉搜索树**实现的关联式容器。要说到什么是平衡二叉树，我们从树开始说起。

在计算机科学中，数是用来表示具有层次关系的数据。它由根、质感、叶子组成。根在最上方，叶子在最下方，质感就是其中的子节点。

```
        A          ← 根（Root）
       / \
      B   C        ← B 和 C 是 A 的“孩子”
     /   / \
    D   E   F      ← D、E、F 是“叶子”
```

树的基本术语如下：

术语	说明

节点（Node）	树中的一个元素（如 A、B、C）

根节点（Root）	最顶部的节点，没有父节点

父节点（Parent）	直接连接到上方的节点（A 是 B 的父节点）

子节点（Child）	直接连接到下方的节点（B 是 A 的子节点）

叶子节点（Leaf）	没有子节点的节点（D、E、F）

深度（Depth）	从根到该节点的路径长度（根深度=0）

高度（Height）	从该节点到最远叶子的最长路径（叶子高度=0）

而**二叉树**是一种特殊的树，其中每个节点最多只有两个节点，被称为：左子节点(Left leave)和右子节点(Right leave)。

**二叉搜索树**Binary Search Tree(BST)是树中最重要的一种，它规定在任意节点左子树中所有节点的值小于该节点，右子树中所有节点的值大于该节点。

例如：

```
        8
       / \
      3   10
     / \    \
    1   6    14
       / \   /
      4   7 13
```

当我们在其中插入一个数：9的时候，会从根节点开始遍历每一层。9>8，所以会走入其右子节点中，在第二层中，由于9<10，会走入10的左子节点。

由此你可以发现，二叉搜索树中所有的数据都是唯一的。这个遍历的过程时间复杂度是O(h)，h是树的高度。

那如何遍历一整棵树呢？有三种方式：

**前序遍历**：遍历顺序是：根->左子树->右子树。

步骤是：访问当前节点，递归遍历左子树，递归遍历右子树。

用途：复制一棵树，序列化树，表达式树求值

```
void preorder(TreeNode* root) {
    if (root == nullptr) return;
    cout << root->val << " ";   // 访问根
    preorder(root->left);       // 遍历左
    preorder(root->right);      // 遍历右
}
```

**中序遍历**：遍历顺序是：左子树->根->右子树

步骤是：递归遍历左子树，访问当前节点，递归遍历右子树

用途：输出BST的有序序列，验证是否是BST，找第k小的元素

```
void inorder(TreeNode* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->val << " ";   // 访问根
    inorder(root->right);
}
```

**后序遍历**：遍历顺序是：左子树->右子树->根

步骤是：遍历递归左子树，遍历递归右子树，访问当前节点

用途：删除整棵树，计算目录大小，表达式树求值

```
void postorder(TreeNode* root) {
    if (root == nullptr) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";   // 最后访问根
}
```

**表达式树**是一种特殊的二叉树：

如表达式(3 + 4) * 2 对应的树：

```
      *
     / \
    +   2
   / \
  3   4
```

其前序遍历得到**前缀表达式**（波兰表达式）：`* + 3 4 2`。这样子的表达式可以直接在栈中，从右到左计算求值，而不需要括号。当扫描到操作数就压栈，遇到从左副就弹出两个操作数进行运算，再把结果压回栈。

如果我们插入数据的顺序改变一下：

```
1
 \
  2
   \
    3
     \
      4
```

这下子就变成链表了，此时查找4需要4步，时间复杂度O(n)，复杂度由树的高度变成了序列的长度，这不是我们所希望的，这也叫性能退化。

如何解决这个问题呢，我们就要使用到**自平衡二叉搜索树**，在插入或删除数据后自动调整结构，让数的高度始终保持在O(logn)。

自平衡树采用：检测失衡->局部失衡->恢复平衡 的调整思路。流程如下：执行普通BST插入/删除，从修改点向上回溯，检查祖父节点是否失衡，一旦发现失衡就进行旋转等其他修复操作，然后更改元信息，继续向上检查。

std::set是基于**红黑树**实现的，红黑树是一种自平衡二叉搜索树，其使用一种颜色规则保证树的近似平衡。它有五条核心性质：

* 节点是红或黑
* 根节点是黑色
* 所有叶子是黑色（空指针被视为统一的黑色NIL叶子节点）
* 红色节点的子节点必须是黑色
* 从任一节点出发，到其左右后代NIL叶子的路径上，黑色节点的数量相同（被称为“黑高”一致）

如果插入的数据出现了红-红冲突（插入节点与其父节点），要根据“叔叔节点”的颜色分情况处理：

* 叔叔节点是红色：

```
     g(B)               g(R)
    /    \      →      /    \
  p(R)   u(R)        p(B)   u(B)
  /                  /
z(R)               z(R)
```

将叔叔节点和父节点都染成黑色，祖父节点染为红色。（如果此时祖父节点是根节点，就再把祖父节点染黑）

* 叔叔节点是黑色（或NIL），且z是“外侧”节点（LL或RR）:LL型指z节点是p节点左侧，p节点是g节点左侧。RR同理。

```
     g(B)                p(B)
    /    \      →      /    \
  p(R)   u(B)        z(R)   g(R)
  /                          \
z(R)                        u(B)
```

此时对g节点做**单旋转**（LL->右旋，RR->左旋），并将p染黑，g染红。

* 叔叔节点是黑色（或NIL），且z是“内侧”节点（LR或RL）：LR型
