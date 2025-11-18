#include <iostream>
using namespace std;

class Point {
    private:
        int x;
        int y;
    public:
        Point(int x, int y) {
            this->x = x; // 使用 this 指针区分成员变量和参数
            this->y = y;
        }

        void display() {
            cout << "Point(" << this->x << ", " << this->y << ")" << endl;
        }
};

class Sample{
    private:
        int value;
    public:
        void SamplePtr(){
            cout << "SamplePtr's address: " << this << endl;
        }
};

class Calculate{
    private:
        int data;
    public:
        Calculate& setData(int data){
            this->data = data;
            return *this; // 返回当前对象的引用
        }
        Calculate& add(int value){
            this->data += value;
            return *this; // 返回当前对象的引用
        }
        Calculate& subtract(int value){
            this->data -= value;
            return *this; // 返回当前对象的引用
        }
        Calculate& multiply(int value){
            this->data *= value;
            return *this; // 返回当前对象的引用
        }
        Calculate& divide(int value){
            if(value != 0){
                this->data /= value;
            }
            return *this; // 返回当前对象的引用
        }
        void display(){
            cout << "Result: " << this->data << endl;
        }
};

int main_This(){
    Calculate calc;
    const Calculate& calcRef = calc.setData(10).add(5).subtract(3).multiply(4).divide(2);
    calcRef.display(); // 输出: Result: 26
    return 0;
}


