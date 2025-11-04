#include <iostream>
#include <string>

class Student {
public:               // 访问权限（public: 意味着外部可以访问）
    // 成员变量：描述学生的“属性”
    std::string name;
    int age;

    // 成员函数：描述学生能“做的事”
    void introduce() {
        std::cout << "我是 " << name << "，今年 " << age << " 岁。" << std::endl;
    }
};

int main() {
    Student s;      // 创建一个对象 s，类型是 Student
    s.name = "李笑";  // 访问成员变量
    s.age = 20;

    s.introduce();  // 调用成员函数
    return 0;
}
