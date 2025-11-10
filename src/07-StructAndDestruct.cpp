#include <iostream>
#include <string>

class Students {
public:
    std::string name;
    int *age;

    // Students(std::string n, int a){
    //     name = n;
    //     age = new int(a);
    // }

    // ~Students(){
    //     delete age;
    // }

    void introduce() {
        std::cout << "我是 " << name << "，今年 " << *age << " 岁。" << std::endl;
    }
};

int main() {
    Students s;
    s.name = "张三";
    std::cout << *s.age << std::endl;
    s.introduce();
    while(true);
    return 0;
}