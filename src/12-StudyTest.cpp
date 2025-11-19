#include <iostream>
#include <string>
using namespace std;


//Test01
class MyString{
    private:
        string str;
    public:
        MyString(){;}
        MyString(const char* s): str(s){;}
        MyString(const MyString& other): str(other.str){;}
        ~MyString(){;}
        MyString operator=(const MyString& other){
            if(this != &other){
                str = other.str;
            }
            return *this;
        }
        MyString operator+(const MyString& other){
            return MyString((str + other.str).c_str());
        }
        friend ostream& operator<<(ostream& os, const MyString& myString);
        friend istream& operator>>(istream& is, MyString& myString);
};

ostream& operator<<(ostream& os, const MyString& myString){
    os << myString.str;
    return os;
}

istream& operator>>(istream& is, MyString& myString){
    is >> myString.str; 
    return is;
}


//Test02
int main_test01(){
    MyString str1("Hello, ");
    MyString str2("World!");
    MyString str3 = str1 + str2;
    cout << str3 << endl; // 输出: Hello, World!
    cin >> str3;
    cout << "You entered: " << str3 << endl;
    return 0;
}

double celsiusToFahrenheit(double celsius){
    return (celsius * 9.0 / 5.0) + 32.0;
}

double fahrenheitToCelsius(double fahrenheit){
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

int main_test02(){
    while(1){
        cout << "Select input way:(q/c/f): ";
        string input;
        cin >> input;
        if(input == "q"){
            break;
        }
        else if(input == "f"){
            cout << "Enter temperature in Fahrenheit: ";
            cin >> input;
            double fahrenheit = stod(input);
            double celsius = fahrenheitToCelsius(fahrenheit);
            cout << fahrenheit << " Fahrenheit is " << celsius << " Celsius." << endl;
            continue;
        }
        else{
            cout << "Enter temperature in Celsius: ";
            cin >> input;   
            double celsius = stod(input);
            double fahrenheit = celsiusToFahrenheit(celsius);
            cout << celsius << " Celsius is " << fahrenheit << " Fahrenheit." << endl;
        }
    }
    return 0;
}

//Test03

bool isPrime(int n){
    if(n <= 1) return false;
    for(int i = 2; i * i <= n; ++i){
        if(n % i == 0) return false;
    }
    return true;
}

int main_test03(){
    cout << "Enter a positive integer: ";
    int num;
    cin >> num;
    if(isPrime(num)){
        cout << num << " is a prime number." << endl;
    } else {
        cout << num << " is not a prime number." << endl;
    }
    return 0;
}

//Test04
long long fib(int n){
    if(n <= 0) return 0;
    if(n == 1) return 1;
    long long a = 0, b = 1, c;
    for(int i = 2; i <= n; ++i){
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main_test04(){
    cout << "Enter a positive integer: ";
    int num;
    cin >> num;
    long long result = fib(num);
    cout << "Fibonacci number F(" << num << ") = " << result << endl;
    return 0;
}

//Test05
class Date {
private:
    int year, day, month;
public:
    Date(int y=2000, int m=1, int d=1) : year(y), month(m), day(d) {}
    void printDate() {
        cout << year << "-" << month << "-" << day << endl;
    }
    bool isVaild(){
        if(month < 1 || month > 12) return false;
        if(day < 1) return false;
        int daysInMonth;
        switch(month){
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                daysInMonth = 31; break;
            case 4: case 6: case 9: case 11:
                daysInMonth = 30; break;
            case 2:
                daysInMonth = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 29 : 28; break;
            default:
                return false;
        }
        return day <= daysInMonth;
    } 
};

int main_test05(){
    Date date1(2024, 2, 29);
    Date date2(2023, 2, 29);
    cout << "Date 1: ";
    date1.printDate();
    cout << "Is valid? " << (date1.isVaild() ? "Yes" : "No") << endl;
    cout << "Date 2: ";
    date2.printDate();
    cout << "Is valid? " << (date2.isVaild() ? "Yes" : "No") << endl;
    return 0;
}

//Test06

class Rectangle{
private:
    double length;
    double width;
public:
    Rectangle(double l=1.0, double w=1.0) : length(l), width(w) {}
    double area(){
        return length * width;
    }
    double perimeter(){
        return 2 * (length + width);
    }
    void operator==(const Rectangle& other){
        if(length == other.length && width == other.width){
            cout << "Rectangles are equal." << endl;
        } else {
            cout << "Rectangles are not equal." << endl;
        }
    }
};

int main_test06(){
    Rectangle rect1(4.0, 5.0);
    Rectangle rect2(4.0, 5.0);
    cout << "Area of rect1: " << rect1.area() << endl;
    cout << "Perimeter of rect1: " << rect1.perimeter() << endl;
    rect1 == rect2;
    return 0;
}

//Test07
class BankAccount{
private:
    string name;
    double balance;
public:
    BankAccount(string n, double b) : name(n), balance(b) {}
    void deposit(double amount){
        cout << "User:" << name << endl;
        if(amount > 0){
            balance += amount;
            cout << "Deposited: " << amount << ", New balance: " << balance << endl;
        } else {
            cout << "Deposit amount must be positive." << endl;
        }
    }
    void withdraw(double amount){
        cout << "User:" << name << endl;
        if(amount > 0 && amount <= balance){
            balance -= amount;
            cout << "Withdrew: " << amount << ", New balance: " << balance << endl;
        } else {    
            cout << "Invalid withdrawal amount." << endl;
        }
    }
    void getBalance(){
        cout << "User:" << name << endl;
        cout << "Current balance: " << balance << endl;
    }
};

int main_test07(){
    BankAccount account("Alice", 1000.0);
    account.getBalance();
    account.deposit(500.0);
    account.withdraw(200.0);
    account.getBalance();
    return 0;
}

//Test08

class Fraction{
private:
    int num;
    int den;
    int gcd(int a, int b){
        return b == 0 ? a : gcd(b, a % b);
    }
    void simplify(){
        int divisor = gcd(abs(num), abs(den));
        num /= divisor;
        den /= divisor;
        if(den < 0){
            num = -num;
            den = -den;
        }
    }
public:
    Fraction(int n, int d) : num(n), den(d){
        simplify();
    }
    Fraction operator+(const Fraction& other){
        int newNum = num * other.den + other.num * den;
        int newDen = den * other.den;
        Fraction result(newNum, newDen);
        result.simplify();
        return result;
    }
    friend ostream& operator<<(ostream& os, const Fraction& frac){
        os << frac.num << "/" << frac.den;
        return os;
    }
};

int main_test08(){
    Fraction frac1(1, 2);
    Fraction frac2(3, 4);
    Fraction result = frac1 + frac2;
    cout << "Result: " << result << endl; // 输出: Result: 5/4
    return 0;
}

//Test09

class Animal {
private:
    string name;
public:
    Animal(string n) : name(n) {}
    virtual void makeSound() const = 0; // 纯虚函数
};

class Dog : public Animal{
public:
    Dog(string n) : Animal(n){;}
    void makeSound() const override {
        cout << "Woof! Woof!" << endl;
    }
};

class Cat : public Animal{
public:
    Cat(string n) : Animal(n){;}
    void makeSound() const override {   
        cout << "Meow! Meow!" << endl;
    }
};

int main_test09(){
    Animal* dog = new Dog("Buddy");
    Animal* cat = new Cat("Kitty");
    dog->makeSound(); // 输出: Woof! Woof!
    cat->makeSound(); // 输出: Meow! Meow!
    delete dog;
    delete cat;
    return 0;
}

//Test10

class Employee{
private:
    string name;
    string id;
    double salary;
public:
    virtual double calculateSalary() const = 0; // 纯虚函数
};

class HourlyEmployee : public Employee{
private:
    double hourlyRate;
    int hoursWorked;
public:
    HourlyEmployee(string n, string i, double rate, int hours)
        : hourlyRate(rate), hoursWorked(hours) {;}
    double calculateSalary() const override {
        return hourlyRate * hoursWorked;
    }
};

class SalariedEmployee : public Employee{
private:
    double monthlySalary;
public:
    SalariedEmployee(string n, string i, double salary)
        : monthlySalary(salary) {;}
    double calculateSalary() const override {
        return monthlySalary;
    }
};

int main_test10(){
    Employee* emp1 = new HourlyEmployee("Alice", "E001", 20.0, 160);
    Employee* emp2 = new SalariedEmployee("Bob", "E002", 3000.0);
    cout << "Hourly Employee Salary: " << emp1->calculateSalary() << endl; // 输出: 3200
    cout << "Salaried Employee Salary: " << emp2->calculateSalary() << endl; // 输出: 3000
    delete emp1;
    delete emp2;
    return 0;
}

//Test11
class Shape {
public:
    virtual double area() const = 0; // 纯虚函数
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {;}
    double area() const override {
        return 3.14159 * radius * radius;
    }
};

class Square : public Shape {
private:
    double side;
public:
    Square(double s) : side(s) {;}
    double area() const override {
        return side * side;
    }
};

int main_test11(){
    Shape* shape1 = new Circle(5.0);
    Shape* shape2 = new Square(4.0);
    cout << "Circle Area: " << shape1->area() << endl; // 输出: Circle Area: 78.53975
    cout << "Square Area: " << shape2->area() << endl; // 输出: Square Area: 16
    delete shape1;
    delete shape2;
    return 0;
}

//Main
int main(){
    //return main_test01();
    //return main_test02();
    //return main_test03();
    //return main_test04();
    //return main_test05();
    //return main_test06();
    //return main_test07();
    //return main_test08();
    //return main_test09();
    //return main_test10();
    return main_test11();
}

