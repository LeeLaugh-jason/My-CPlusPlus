# 继承（private、public、protection）

继承是什么意思？继承是指在C++中在定义一个新的类时，可以基于另一个类来创建，拓展更多特定的类的成员。

```
#include <iostream>
using namespace std;

class Animal {
public:
    string name;

private:
    string type;
    // void typee(){
    //     cout << "Animal type" << endl;
    // }
public:
    Animal(string n){}
    void speak(){
        cout << "Animal speaks" << endl;
    }
};

class Dog : public Animal {
public:
    Dog(string n) : Animal(n) {}
    void barks(){
        cout << "Dog barks" << endl;
    }
};

int main(){
    Dog dog("Buddy");
    dog.speak();  // 输出: Dog speak
    dog.barks();  // 输出: Dog barks
    // dog.typee();   // 输出: Animal type
    return 0;
}
```

这里面private、protection、public是访问说明符，用于表示类中成员的可见性和可访问性。我们拿一个类来表示：

```
class Base{
    public:
    int a;
    private:
    int b;
    protected:
    int c;
}
```

我们在main中创建一个Base的对象obj，发现只有public中定义的变量可以 **对外**使用：

```
    Base obj;
    obj.a = 10; // 可以访问 public 成员
    // obj.b = 20; // 错误: 无法访问 private 成员
    // obj.c = 30; // 错误: 无法访问 protected 成员
```

而在类内部，三种访问控制符中的成员都可以被类自己访问。

```
class Base{
    private:
    int b = 0;
    public:
    int a;
    void output(){
        cout << "Base output b = " << b << endl;
    }
    
    protected:
    int c;
};
```

调用output后发现可以打印出类中private的内容，其实也就是在类中，所有成员都对内开放。

总结来说：
public：对外对内开放
private：对内开放
protected：对内开放，对派生类开放

这样我们继续往下，我们在本章的第一段长代码中出现了`class Dog : public Animal `的代码，这一段就是派生类(Dog)基于基类(Animal)声明的方式：
通过`:`指定基类，可以选择继承的方式（public、private、protected）。

当我们使用public继承的时候，基类中的public、protected对于派生类的访问权限与基类一致；当我们使用protected继承时，基类中的public、protected对于派生类的访问权限都是protected；当使用private继承时，基类中的public、protected对于派生类的访问权限都是private。
