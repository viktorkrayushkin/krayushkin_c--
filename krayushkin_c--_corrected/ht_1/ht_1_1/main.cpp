#include <iostream>
#include <vector>
#include <string>
#include <chrono>

class Timer {
public:
    Timer(std::string id)
            : id_(std::move(id)) {
    }

    ~Timer() {
        const auto end_time = std::chrono::steady_clock::now();
        const auto dur = end_time - start_time_;
        std::cout << id_ << ": ";
        std::cout << "operation time"
                  << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count()
                  << " ms" << std::endl;
    }

private:
    const std::string id_;
    const std::chrono::steady_clock::time_point start_time_ = std::chrono::steady_clock::now();
};


template <typename T>
class Multiclass {
    T* arr_;
    std::size_t sz_;
    std::vector<T> v_;

public:
    Multiclass(T* array = nullptr, std::size_t size = 0, const std::vector<T>& vec = { }) : arr_(array), sz_(size), v_(vec) {}
    Multiclass(T* array, std::size_t size, std::vector<T>&& vec) : arr_(array), sz_(size), v_(std::move(vec)) {}

    Multiclass(const Multiclass<T>& other);
    Multiclass(Multiclass<T>&& other);

    Multiclass& operator=(const Multiclass<T>& other);
    Multiclass& operator=(Multiclass<T>&& other);

    ~Multiclass();
};

template <typename T>
Multiclass<T>::Multiclass(const Multiclass<T>& other) {
    Timer t("copy constructor");
    sz_ = other.sz_;

    arr_ = reinterpret_cast<T*>(new int8_t[sz_ * sizeof(T)]);

    for (size_t i = 0; i < sz_; i++)
        new(arr_ + i) T(other.arr_[i]);

    //v_ = other.v_;

}

template <typename T>
Multiclass<T>::Multiclass(Multiclass<T>&& other) {
    Timer t("move constructor: ");

    sz_ = other.sz_;

    arr_ = reinterpret_cast<T*>(new int8_t[sz_ * sizeof(T)]);
    for (size_t i = 0; i < sz_; i++)
        new(arr_ + i) T(std::move(other.arr_[i]));

    v_ = std::move(other.v_);
}

template <typename T>
Multiclass<T>& Multiclass<T>::operator=(const Multiclass<T>& other) {
    Timer t("copy assignment: ");

    if (sz_ > 0) {
        for (size_t i = 0; i < sz_; i++)
            (arr_ + i)->~T();

        delete[] reinterpret_cast<int8_t*>(arr_);
    }

    sz_ = other.sz_;

    arr_ = reinterpret_cast<T*>(new int8_t[sz_ * sizeof(T)]);
    for (size_t i = 0; i < sz_; i++)
        new(arr_ + i) T(other.arr_[i]);

    v_ = other.v_;

    return *this;
}

template <typename T>
Multiclass<T>& Multiclass<T>::operator=(Multiclass<T>&& other) {
    Timer t("move assignment: ");

    if (sz_ > 0) {
        for (size_t i = 0; i < sz_; i++)
            (arr_ + i)->~T();

        delete[] reinterpret_cast<int8_t*>(arr_);
    }

    sz_ = other.sz_;

    arr_ = reinterpret_cast<T*>(new int8_t[sz_ * sizeof(T)]);
    for (size_t i = 0; i < sz_; i++)
        new(arr_ + i) T(std::move(other.arr_[i]));
    v_ = std::move(other.v_);
    return *this;
};
template <typename T>
Multiclass<T>::~Multiclass() {
    v_.~vector();
    sz_ = 0;
}

int main() {
    std::vector<int> v1(4e8, 0);
    int *ptr;
    ptr = new int[4e8]{ 0};

    Multiclass<int> bc1(ptr, 4e8, std::move(v1));

    std::cout << "constructor test: " << std::endl;
    Multiclass<int> bc2(bc1);
    Multiclass<int> bc3(std::move(bc2));
    bc2.~Multiclass();
    bc3.~Multiclass();

    std::cout << std::endl;

    std::cout << "assignment test: " << std::endl;
    bc2 = bc1;
    bc3 = std::move(bc2);
    bc2.~Multiclass();
    bc3.~Multiclass();
    std::cout << std::endl;
}