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

int main(){
    // Dog dog("Buddy");
    // dog.speak();  // 输出: Dog speak
    // dog.barks();  // 输出: Dog barks
    // dog.typee();   // 输出: Animal type
    Base obj;
    obj.output(); // 可以访问 public 成员
    // obj.b = 20; // 错误: 无法访问 private 成员
    // obj.c = 30; // 错误: 无法访问 protected 成员

    return 0;
}