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

int main(){
    Point p(10, 20);
    p.display(); // 输出: Point(10, 20)
    return 0;
}
