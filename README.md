# My-Cplusplus
作为一位刚入门C++的边缘计算小白，我将在从我自己的视角讲述，如何高效地学习C++.
### 一些疑问？
C++是什么？简单来说，C++是一种高级编程语言，它的源代码被编译器编译后会生成机器码，可以直接被CPU执行。相比于Python这类解释性语言，C++的运行速度极快，适合我们运行在边缘算力板端。

为什么不用C语言呢？那就要提到C语言对于边缘计算的局限性了。

首先，C语言自生没有线程的概念，在创建线程的时候常常需要用到平台库函数，这样要在不同平台运行的时候，需要切换不同平台的库，较为繁琐。但C++却可以实现std::thread直接创建代码，并可以应用于不同平台。

其次，C语言可以直接操控内存地址，但是不会检查是否安全，如果出现野指针、悬空指针、缓冲区溢出、内存泄漏等问题，程序运行时可能会随机崩溃。而C++提供了自动化内存管理机制，不需要手动malloc和free，使用智能指针和RAII可以实现资源的自动获取和释放。这个操作具体是怎么做到的呢？那就要提到C++最不同于C语言的特点了。

在C语言中，一切都是函数和数据，而在C++中多了类这一定义。它可以被理解为数据+行为的封装体。C++的底层结构其实是结构体+一组函数指针+一些隐藏信息组成的。类可以让我们把数据和操作封装到一起，还可以支持继承和代码的复用等。

总的来说，C++是更加适合于运行在边缘计算板端的设备。那么我们如何使用C++这门语言呢？首先从最基础的写代码开始。我们将开始从”HelloWorld！“开始搭建我们的第一个C++程序。

由于我使用的是windows系统，而边缘计算板端大部分都使用开源的Linux系统。为了体验更加全面的C++标准，我安装并搭建了Ubuntu24.04的环境，使用GCC13编译器编译C++程序。

同时我使用ChatGPT给了我学习的建议，由于我有C语言的基础，因此不需要从头重复搭轮子，而是直接深入C++特性：

C++基本语法：

<img width="311" height="241" alt="image" src="https://github.com/user-attachments/assets/7bca0c4f-57fe-4d1a-b9b8-a01ac2944a5d" />

<img width="351" height="188" alt="image" src="https://github.com/user-attachments/assets/dfc4ae90-46ad-4f2f-93c9-91954150f56a" />

面向对象编程OOP：

<img width="303" height="210" alt="image" src="https://github.com/user-attachments/assets/7a96948e-0cce-4a79-bf26-484fb2bdd0d2" />

<img width="345" height="214" alt="image" src="https://github.com/user-attachments/assets/18efad0e-37b6-419d-9fbc-438e1efeb896" />

现代C++与标准库：

<img width="404" height="266" alt="image" src="https://github.com/user-attachments/assets/b9160c8d-2912-4149-9330-b351b7055668" />

<img width="256" height="196" alt="image" src="https://github.com/user-attachments/assets/1d5ee080-6652-47f9-b3a3-fd0e04388a41" />

接下来我将按照这个顺序，推进C++的学习历程。
