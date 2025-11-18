# This指针与智能设计

### This指针

This指针是什么？当类的对象定义之后，会在对象的**非静态**成员函数中隐式存在，表示指向调用这个成员函数的对象本身。

有什么用吗？我们可以在对象的成员函数中创建调用这个对象本身（包括它的成员变量），可以与提供给这个成员函数的参数区分开（同名称的情况下）：

```
class Point {
    private:
        int x;
        int y;
    public:
        Point(int x, int y) {
            this->x = x; // 使用 this 指针区分成员变量和参数
            this->y = y;
        }

        void display() {
            cout << "Point(" << this->x << ", " << this->y << ")" << endl;
        }
};
```

除此之外，我们还可以使用引用的方式与this打一个配合，实现链式调用的功能：

```
class Calculate{
    private:
        int data;
    public:
        Calculate& setData(int data){
            this->data = data;
            return *this; // 返回当前对象的引用
        }
        Calculate& add(int value){
            this->data += value;
            return *this; // 返回当前对象的引用
        }
        Calculate& subtract(int value){
            this->data -= value;
            return *this; // 返回当前对象的引用
        }
        Calculate& multiply(int value){
            this->data *= value;
            return *this; // 返回当前对象的引用
        }
        Calculate& divide(int value){
            if(value != 0){
                this->data /= value;
            }
            return *this; // 返回当前对象的引用
        }
        void display(){
            cout << "Result: " << this->data << endl;
        }
};

int main(){
    Calculate calc;
    calc.setData(10).add(5).subtract(3).multiply(4).divide(2).display(); // 链式调用，输出24
    return 0;
}
```

在上面的代码中我们可以知道，this指针的类型是`Calculate*`，如果成员函数是const定义的话，this指针也会编程`const Calculate*`的类型。

### 智能设计

在C++中，智能设计大多数体现在对资源的分配管理上。我们在学C++时会听到RALL这个名词，RALL是Resource Acquisition Is Initialization，
即资源在对象构造时获取，在对象析构时释放。而专注于智能指针的部分我们在下一大章节中慢慢讲解。
