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

int main_deque(){
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

#include <list>

int main_list(){
    std::list<int> mylist = {1, 2, 3, 4, 5};
    std::list<int> anotherList(mylist);
    for(const auto& elem : anotherList){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    mylist.push_back(6);
    mylist.push_front(0);
    for(const auto& elem : mylist){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    int firstElem = mylist.front();
    int lastElem = mylist.back();
    std::cout << "First element: " << firstElem << ", Last element: " << lastElem << std::endl;

    mylist.pop_back();
    mylist.pop_front();
    for(const auto& elem : mylist){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    auto it = mylist.begin();
    ++it; // Move to second element

    std::cout << "it points to: " << *it << std::endl;

    mylist.insert(it, 10); // Insert 10 before second element
    for(const auto& elem : mylist){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    mylist.erase(it); // Erase the element we just inserted
    for(const auto& elem : mylist){
        std::cout << elem << " ";   
    }
    std::cout << std::endl;

    mylist.erase(mylist.begin(), mylist.end()); // Clear the list
    std::cout << "List size after clear: " << mylist.size() << std::endl;
    

    return 0;
}

#include <forward_list>

int main_forward_list(){
    std::forward_list<int> flist1 = {1, 2, 3, 4, 5};
    std::forward_list<int> flist2(3, 10);
    for(const auto& elem : flist1){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    for(const auto& elem : flist2){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    flist1.push_front(0);
    for(const auto& elem : flist1){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    flist1.pop_front();
    for(const auto& elem : flist1){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    auto it = flist1.begin();
    flist1.insert_after(it, 10);
    for(const auto& elem : flist1){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    flist1.erase_after(it);
    for(const auto& elem : flist1){
        std::cout << elem << " ";   
    }
    std::cout << std::endl;

    flist1.insert_after(flist1.before_begin(), 20);
    for(const auto& elem : flist1){
        std::cout << elem << " ";   
    }
    std::cout << std::endl;

    flist1.insert_after(flist1.before_begin(), 20);
    for(const auto& elem : flist1){
        std::cout << elem << " ";   
    }
    std::cout << std::endl;

    flist1.remove(20);
    for(const auto& elem : flist1){
        std::cout << elem << " ";   
    }
    std::cout << std::endl;

    flist1.remove_if([](int value){ return value % 2 == 0; });
    for(const auto& elem : flist1){
        std::cout << elem << " ";   
    }
    std::cout << std::endl;

    flist1.splice_after(flist1.before_begin(), flist2);
    for(const auto& elem : flist1){
        std::cout << elem << " ";   
    }
    std::cout << std::endl;

    flist1.sort();
    for(const auto& elem : flist1){
        std::cout << elem << " ";   
    }
    std::cout << std::endl;

    flist1.unique();
    for(const auto& elem : flist1){
        std::cout << elem << " ";   
    }
    std::cout << std::endl;

    return 0;
}

#include <array>

int main/*_array*/(){
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    std::cout << "Array elements: ";
    for(const auto& elem : arr){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::cout << "Array size: " << arr.size() << std::endl;
    std::cout << "First element: " << arr.front() << std::endl;
    std::cout << "Last element: " << arr.back() << std::endl;
    std::cout << "Element at index 2: " << arr.at(2) << std::endl;

    try {
        std::cout << "Element at index 10: " << arr.at(10) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    arr.fill(0);
    std::cout << "Array size after clear: " << arr.size() << std::endl;

    std::cout << "Is array empty? " << (arr.empty() ? "Yes" : "No") << std::endl;

    arr.fill(20);

    std::cout << "array.begin(): " << arr.begin() << std::endl;
    std::cout << "array.end(): " << arr.end() << std::endl;

    arr.fill(10);
    std::cout << "Array after fill(10): ";
    for(const auto& elem : arr){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}

// #include <set>

// int main(){

// }