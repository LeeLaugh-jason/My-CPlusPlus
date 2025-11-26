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

    auto it = std::find(vec.begin(), vec.end(), 5);
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

    std::cout << std::count(vec.begin(), vec.end(), 5) << " occurrences of 5 found." << std::endl;

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
    
    std::vector<int> vec2 = {3, 1, 4, 1, 5, 9, 4};

    std::nth_element(vec2.begin(), vec2.begin() + 1, vec2.end());
    std::cout << "Vector after nth_element (2nd smallest element at index 1): ";
    for(const auto& num : vec2){
        std::cout << num << " ";
    }
    std::cout << std::endl;

    if(std::is_sorted(vec2.begin(), vec2.end())){
        std::cout << "vec2 is sorted." << std::endl;
    } else {
        std::cout << "vec2 is not sorted." << std::endl;
    }

    std::sort(vec2.begin(), vec2.end());
    std::binary_search(vec2.begin(), vec2.end(), 5) ?
        std::cout << "5 found in vec2 using binary search." << std::endl :
        std::cout << "5 not found in vec2 using binary search." << std::endl;

    std::lower_bound(vec2.begin(), vec2.end(), 4) != vec2.end() ?
        std::cout << "Element >= 4 found: " << *std::lower_bound(vec2.begin(), vec2.end(), 4) << std::endl :
        std::cout << "No element >= 4 found." << std::endl;

    std::upper_bound(vec2.begin(), vec2.end(), 4) != vec2.end() ?
        std::cout << "Element > 4 found: " << *std::upper_bound(vec2.begin(), vec2.end(), 4) << std::endl :
        std::cout << "No element > 4 found." << std::endl;

    auto range = std::equal_range(vec2.begin(), vec2.end(), 4);
    std::cout << "Elements equal to 4: ";
    for(auto it = range.first; it != range.second; ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::vector<int> vec3 = {1, 2, 3, 4, 5};
    std::vector<int> vec4 = {4, 5, 6, 7, 8};
    std::vector<int> intersection(10);
    std::merge(vec3.begin(), vec3.end(), vec4.begin(), vec4.end(), intersection.begin());
    std::cout << "Intersection of vec3 and vec4: ";
    for(const auto& num : intersection){
        std::cout << num << " ";
    }
    std::cout << std::endl;
    intersection.clear();
    intersection.resize(10);
    std::set_union(vec3.begin(), vec3.end(), vec4.begin(), vec4.end(), intersection.begin());
    std::cout << "Union of vec3 and vec4: ";
    for(const auto& num : intersection){
        std::cout << num << " ";
    }
    std::cout << std::endl;
    intersection.clear();
    intersection.resize(10);
    std::set_intersection(vec3.begin(), vec3.end(), vec4.begin(), vec4.end(), intersection.begin());
    std::cout << "Set intersection of vec3 and vec4: ";
    for(const auto& num : intersection){
        std::cout << num << " ";
    }
    std::cout << std::endl;
    intersection.clear();
    intersection.resize(10);
    std::set_difference(vec3.begin(), vec3.end(), vec4.begin(), vec4.end(), intersection.begin());
    std::cout << "Set difference of vec3 and vec4 (vec3 - vec4): ";
    for(const auto& num : intersection){
        std::cout << num << " ";
    }
    std::cout << std::endl;
    intersection.clear();
    intersection.resize(10);
    std::set_symmetric_difference(vec3.begin(), vec3.end(), vec4.begin(), vec4.end(), intersection.begin());
    std::cout << "Set symmetric difference of vec3 and vec4: ";
    for(const auto& num : intersection){
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::vector<int> vec5 = {3, 2, 5, 56, 23, 78, 12, 5};
    std::make_heap(vec5.begin(), vec5.end());
    std::cout << "Heap created from vec5: ";
    for(const auto& num : vec5){
        std::cout << num << " ";
    }
    std::cout << std::endl;
    vec5.push_back(22);
    std::push_heap(vec5.begin(), vec5.end());
    std::cout << "Heap after push_heap: ";
    for(const auto& num : vec5){
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::pop_heap(vec5.begin(), vec5.end());
    vec5.pop_back();
    std::cout << "Heap after pop_heap: ";
    for(const auto& num : vec5){
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::sort_heap(vec5.begin(), vec5.end());
    std::cout << "Sorted heap: ";
    for(const auto& num : vec5){
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::vector<int> vec6 = {1, 2, 3, 4, 5};
    std::sort(vec6.begin(), vec6.end());
    do {
        for(const auto& num : vec6){
            std::cout << num << " ";
        }
        std::cout << std::endl;
    } while(std::next_permutation(vec6.begin(), vec6.end()));
    std::cout << "Previous permutations:" << std::endl;
    std::sort(vec6.begin(), vec6.end(), std::greater<int>());
    do {
        for(const auto& num : vec6){
            std::cout << num << " ";
        }
        std::cout << std::endl;
    } while(std::prev_permutation(vec6.begin(), vec6.end()));
    

    return 0;
}