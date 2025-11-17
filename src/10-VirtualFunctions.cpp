#include <iostream>
#include <string>

class Animal{
    private:
        std::string type;
    public:
        virtual void speak(){
            std::cout << "Animal speaks" << std::endl;
        }
};

class Dog  : public Animal{
    private:
        std::string breed;
    public:
        void speak() override {
            std::cout << "Dog barks" << std::endl;
        }
};

int main(){
    Animal* animalPtr = new Dog();
    animalPtr->speak();  // 输出: Dog barks

    delete animalPtr;
    return 0;
}
