#include <iostream>
#include <string>

class Animal{
    private:
        std::string type;
    public:
        virtual void speak(){
            std::cout << "Animal speaks" << std::endl;
        }
        virtual void spark() = 0; // 纯虚函数
};

class Dog  : public Animal{
    private:
        std::string breed;
    public:
        void speak() override {
            std::cout << "Dog barks" << std::endl;
        }
        void spark() override {
            std::cout << "Dog sparks" << std::endl;
        }
};

int main(){
    Animal* animalPtr = new Dog();
    animalPtr->speak();  // 输出: Dog barks
    animalPtr->spark();  // 输出: Dog sparks

    delete animalPtr;
    return 0;
}
