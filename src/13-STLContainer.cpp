#include <iostream>
#include <vector>
#include <deque>

int main_vector(){
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    std::cout << "Vector size: " << numbers.size() << std::endl;
    std::cout << "Vector capacity: " << numbers.capacity() << std::endl;

    int ret = numbers.empty();
    if(ret){
        std::cout << "Vector is empty" << std::endl;
    } else {
        std::cout << "Vector is not empty" << std::endl;
    }

    std::cout << "first element: " << numbers.front() << std::endl;
    std::cout << "last element: " << numbers.back() << std::endl;

    std::cout << "push_back: ";
    numbers.push_back(6);
    for(const auto& num : numbers){
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "pop_back: ";
    numbers.pop_back();
    for(const auto& num : numbers){
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "clear vector" << std::endl;
    numbers.clear();
    std::cout << "Vector size after clear: " << numbers.size() << std::endl;

    numbers.resize(10);
    std::cout << "Vector size after resize to 10: " << numbers.size() << std::endl;

    numbers.shrink_to_fit();
    std::cout << "Vector size after shrink_to_fit: " << numbers.size() << std::endl;

    return 0;
}

int main(){
    std::deque<int> dq = {1, 2, 3, 4, 5};

    for(const auto& elem : dq){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::cout << "Element at index 2: " << dq[2] << std::endl;
    std::cout << "Element at index 3: " << dq.at(3) << std::endl;
    std::cout << "Front element: " << dq.front() << std::endl;
    std::cout << "Back element: " << dq.back() << std::endl;
    std::cout << "Deque size: " << dq.size() << std::endl;
    std::cout << "Is deque empty? " << (dq.empty() ? "Yes" : "No") << std::endl;
    std::cout << "Max size of deque: " << dq.max_size() << std::endl;

    dq.push_back(6);
    dq.push_front(0);
    std::cout << "Deque after push_back and push_front: ";
    for(const auto& elem : dq){
        std::cout << elem << " ";   
    }
    std::cout << std::endl;
    dq.pop_back();
    dq.pop_front();
    std::cout << "Deque after pop_back and pop_front: ";
    for(const auto& elem : dq){
        std::cout << elem << " ";   
    }
    std::cout << std::endl;

    dq.insert(dq.begin() + 2, 10);
    std::cout << "Deque after insert 10 at index 2: ";
    for(const auto& elem : dq){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    dq.erase(dq.begin() + 2);
    std::cout << "Deque after erase element at index 2: ";
    for(const auto& elem : dq){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    dq.clear();
    std::cout << "Deque size after clear: " << dq.size() << std::endl;

    return 0;
}

