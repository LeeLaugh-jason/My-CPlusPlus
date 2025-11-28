#include <iostream>
#include <vector>
#include <algorithm>

struct Adder {
    auto operator()(int a, int b) const {
        return a + b;
    }
};

int main_test1() {
    Adder add;
    std::cout << add(3, 4) << std::endl;  // Outputs: 7
    return 0;
}


int main(){
    std::vector<int> numbers = {12, 15, 7, 20, 33, 42, 8};
    int threshold = 20;
    auto count_above_threshold = [&threshold](const std::vector<int>& nums) {
        int count = 0;
        for (int num : nums) {
            if (num > threshold) {
                ++count;
            }
        }
        return count;
    };
    std::cout << "Count above threshold: " << count_above_threshold(numbers) << std::endl;

    int sum = 0;
    std::for_each(numbers.begin(), numbers.end(), [&sum](int num) {
        sum += num;
    });
    std::cout << "Sum of numbers: " << sum << std::endl;
    std::find_if(numbers.begin(), numbers.end(), [](int num) {
        return num % 2 == 0;
    });
    return 0;

}