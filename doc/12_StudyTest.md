# 练习题

## 题目

### 基础语法与函数（第1–3题）
1. 温度转换器

编写两个函数：

double celsiusToFahrenheit(double c)

double fahrenheitToCelsius(double f)

在 main 中交互式输入温度值和单位（C 或 F），输出转换后的结果。要求输入验证（如非法单位提示重输）。

2. 质数判断与区间输出

实现函数 bool isPrime(int n)，判断一个正整数是否为质数。

在 main 中让用户输入两个整数 a 和 b（a < b），输出 [a, b] 范围内所有质数。

3.递归实现斐波那契数列

写一个递归函数 long long fib(int n) 返回第 n 项斐波那契数（F(0)=0, F(1)=1）。

并在 main 中测试 n=0 到 n=10 的结果。

思考题（可选）：为什么递归效率低？如何用循环优化？
### 类与对象（第4–7题）
4. 简单日期类 Date

实现一个 Date 类，包含私有成员 year, month, day。要求：

构造函数（带默认参数：2000-1-1）

成员函数 void print() 按 "YYYY-MM-DD" 格式输出

成员函数 bool isValid() 判断日期是否合法（如 2月30日非法）

不需要处理闰年，但需检查月份 1–12、日期 1–31

5. 矩形类 Rectangle

定义 Rectangle 类，私有成员为长 length 和宽 width。要求：

构造函数（默认长宽为 1）

成员函数 double getArea() 和 double getPerimeter()

重载 == 运算符：当两个矩形面积相等时返回 true

6. 银行账户类 BankAccount

实现一个简单的账户类：

私有成员：账户名（string name）、余额（double balance）

公有方法：deposit(double), withdraw(double), getBalance()

取款时若余额不足，打印错误信息并拒绝操作

构造函数初始化账户名和初始余额

7. 运算符重载：分数类 Fraction

实现 Fraction 类（分子 num，分母 den，保证分母>0）：

构造函数（自动约分，可用简单 gcd）

重载 + 运算符（如 1/2 + 1/3 = 5/6）

重载 << 运算符，支持 cout << frac; 输出如 "3/4"
### 继承与多态（第8–10题）
8. 动物基类与派生类

定义抽象基类 Animal，包含纯虚函数 virtual void makeSound() const = 0;。

派生两个类：Dog（叫“Woof!”）和 Cat（叫“Meow!”）。

在 main 中创建 Dog 和 Cat 对象，通过基类指针调用 makeSound()，验证多态行为。

9. 员工薪资系统（简单版）

基类 Employee：含姓名、工号，虚函数 virtual double calculateSalary() const

派生类 HourlyEmployee：每小时工资 + 工作小时数 → 薪资 = 小时工资 × 小时数

派生类 SalariedEmployee：固定月薪

在 main 中分别创建两类员工对象，调用 calculateSalary() 并输出。

10. 形状面积（无 STL 版）

定义抽象类 Shape，含纯虚函数 virtual double area() const = 0;。

派生 Circle（需半径）和 Square（需边长）。

在 main 中：

创建一个 Circle 对象和一个 Square 对象

分别通过基类指针调用 area() 并输出结果

注意：不要用 vector 存多个对象，直接单个测试即可

## 补充

在做题的时候发现了一些之前没有关注到的语法点：

### 友元函数

这个函数是定义在类之外，在类中声明后，可以调用类中private和protected的成员的函数,常用于流式运算符重载。

```
class Number {
private:
    int value;

public:
    Number(int v) : value(v) {}
    
    // 必须在类中声明友元函数！
    friend ostream& operator<<(ostream& os, const Number& num);
};

// 类外定义 - 不要加 friend，不要加 Number::
ostream& operator<<(ostream& os, const Number& num) {
    os << "Number value: " << num.value; // 可以访问私有成员 value
    return os;
}

int main() {
    Number num(100);
    cout << num << endl; // 正确输出: Number value: 100
    return 0;
} 
```
