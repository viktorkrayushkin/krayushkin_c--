#include <iostream>
#include <vector>

int main() {
    // Create a vector of integers
    std::vector<int> my_vector;

    // Add some elements to the vector
    for (int i = 0; i < 10; i++) {
        my_vector.push_back(i);
        std::cout << "capacity: " << (int) my_vector.capacity()  << std::endl;
    }

    // Print the elements in the vector
    std::cout << "Elements in the vector: ";
    for (int i = 0; i < my_vector.size(); i++) {
        std::cout << my_vector[i] << " ";
    }
    std::cout << std::endl;

    // Check the capacity of the vector
    std::cout << "Capacity of the vector: " << my_vector.capacity() << std::endl;


    std::vector<int> my_vector_;
    std::vector<int>::size_type sz;
    int i;
    my_vector_.reserve(700000);
    sz = my_vector_.capacity();
    for(i=0; i<70000000; i++){
        my_vector_.push_back(i);
        if(my_vector_.capacity() != sz){
            sz = my_vector_.capacity();
            std::cout << "new capacity = " << sz << std::endl;
        };
    };
    // Reserve more memory for the vector
    my_vector.reserve(20);
    for (int i = 10; i < 20; i++) {
        my_vector.push_back(i);
        std::cout << "capacity: " << (int) my_vector.capacity()<< std::endl;
    }

    // Print the elements in the vector
    std::cout << "Elements in the vector: ";
    for (int i = 0; i < my_vector.size(); i++) {
        std::cout << my_vector[i] << " ";
    }
    std::cout << std::endl;

    // Check the capacity of the vector
    std::cout << "Capacity of the vector: " << my_vector.capacity() << std::endl;


    return 0;
}
