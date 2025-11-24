#include <iostream>
#include <algorithm>
#include <vector>

int main(){
    std::vector<int> vec = {5, 2, 9, 1, 5, 6};

    std::cout << "Original vector: ";
    for(const auto& num : vec){
        std::cout << num << " ";
    }
    std::cout << std::endl;

    auto it = std::find(vec.begin(), vec.end(), 9);
    std::cout << "vec end: " << *vec.end() << std::endl;
    if(it != vec.end()){
        std::cout << "Found element: " << *it << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }

    std::vector<int> src = {1,2,3};
    std::vector<int> dst(3);
    std::copy(src.begin(), src.end(), dst.begin());
    std::cout << "Copied vector: ";
    for(const auto& num : dst){
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::fill(vec.begin(), vec.end(), 0);
    std::cout << "Vector after fill with 0: ";
    for(const auto& num : vec){ 
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::transform(src.begin(), src.end(), vec.begin(), [](int val){ return val * 2; });
    std::cout << "Vector after transform (multiply by 2): ";
    for(const auto& num : vec){
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::replace(vec.begin(), vec.end(), 0, 10);
    std::cout << "Vector after replace 0 with 10: ";
    for(const auto& num : vec){
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::sort(vec.begin(), vec.end());

    struct Student {
        std::string name;
        int score;
    };

    std::vector<Student> students = {
        {"Alice", 85},
        {"Bob", 90},
        {"Charlie", 85},
        {"David", 90}
    };

    // 按分数升序排序，但相同分数时保持输入顺序
    std::sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return a.score < b.score;
        });

    std::cout << "Sorted students: ";
    for (const auto& s : students) {
        std::cout << s.name << ": " << s.score << "\n";
    }
    std::cout << std::endl;

    std::vector<int> v = {10, 4, 9, 1, 7, 3};
    std::partial_sort(v.begin(), v.begin() + 3, v.end());
    std::cout << "Partially sorted vector (first 3 elements): ";
    for (const auto& num : v) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Sorted vector: ";
    for(const auto& num : vec){
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}