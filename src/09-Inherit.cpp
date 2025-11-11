#include <iostream>
using namespace std;

class Animal {
public:
    string name;
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
    return 0;
}