# 拷贝构造VS深构造

上一章我们讲到构造函数，是在定义对象的时候同时执行的函数：

```
class Student{
    int* ptr;

    Student(int value){
        ptr = new int(value);
    }

    ~Student(){
        delete ptr;
    }
}

int main(){
    Student s(10);
}
```

而拷贝函数用于使用对象初始化对象的方式：

```
class Student{
    int* ptr;

    Student(int value){
        ptr = new int(value);
    }

    ~Student(){
        delete ptr;
    }
}

int main(){
    Student s(10);
    Student s1 = s;
    Student s1(s);
}
```

这里我们在定义s1的时候，传入的参数是同一个类的另一个对象s，在我们的类中其实并没有定义这样一个函数，可以做到传入参数s做到初始化s1。

当我们专注于这一条代码：

```
Student s1 = s;
或 Student s1(s);
```

将s传递给s1，具体是如何做到的呢？

首先在编译的过程中，进行到这一步后，编译器首先会查看Student类中是否有自定义的拷贝函数，如果没有，他就会创建一个 **浅拷贝**函数。

这个浅拷贝函数能将s中的数据逐个复制传递给s1：

```
s1.ptr = s.ptr
```

这时聪明的你发现了一个问题，我将指针的值拷贝给了s1，但是我实际想要的是s1拥有自己的指针值，而仅仅是将指针指向的值传递给指针变量。

我们实际想做到的：

```
s1.ptr = new int(*s.ptr);
```

既然如此，我们就不能让编译器自动生成拷贝函数了，我们需要自己写一个拷贝函数：

在类中定义这样一个函数：

```
class Student{
    int* ptr;

    Student(int value){
        ptr = new int(value);
    }

    Student(const Student& other){        //深度拷贝函数
        ptr = new int(value);
    }

    ~Student(){
        delete ptr;
    }
}

int main(){
    Student s(10);
}
```

我们定义了一个与类的名字相同的函数，它的参数是只读的同一类的对象(other)的别名。

