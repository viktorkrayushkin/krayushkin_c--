#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>

#include "Timer.h"

class BicontainerClass{
public:
    int size=7;

    *arr = new int[size];
    std::vector vect;

    BicontainerClass() = default;

    BicontainerClass(const BicontainerClass &object){
        Timer ld("copy:");
        size = std::copy(object.size);
        arr = std::copy(object.arr);
        vect = std::copy(object.vect);
    };

    BicontainerClass operator=(const BicontainerClass& object){
        Timer ld("copy operator:");
        size = std::copy(object.size);
        arr = std::copy(object.arr);
        vect = std::copy(object.vect);
        return *this;
    };

    BicontainerClass(BicontainerClass&& Object) noexcept {
        Timer ld("move");
        size = std::move(object.size);
        arr = std::move(Object.arr);
        size = std::move(Object.size);
        vect = std::move(Object.vect);
    };

    BicontainerClass& operator=(const BicontainerClass&& object){
        Timer ld("move operator:");
        arr = std::move(Object.arr);
        size = std::move(Object.size);
        vect = std::move(Object.vect);
        return *this;
    };

    ~BicontainerClass() = default;
};


int main(){
    BicontainerClass aClass;
    std::vector<int> vect = {1, 2, 3}
    aClass.vect = vect;



    return 0;
};