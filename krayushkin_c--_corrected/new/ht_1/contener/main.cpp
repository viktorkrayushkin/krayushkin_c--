#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

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


class Multiclass {

public:
    int  sz_= 4e8;;
    int* arr_ = new int [sz_];
    std::vector<int> v_;

    Multiclass() = default;

    Multiclass(const Multiclass &other) {
        Timer t("copy constructor");
        sz_ = other.sz_;
        for (size_t i = 0; i < sz_; i++)
            new(arr_ + i) int(other.arr_[i]);
        v_ = other.v_;

    }


    Multiclass& operator=(const Multiclass& other) {
        Timer t("copy assignment: ");
        sz_ = other.sz_;
        for (size_t i = 0; i < sz_; i++)
            new(arr_ + i) int(other.arr_[i]);
        v_ = other.v_;
        return *this;
    }


    Multiclass (const Multiclass&& other) {
        Timer t("move constructor: ");
        sz_ = other.sz_;
        for (size_t i = 0; i < sz_; i++)
            new(arr_ + i) int(std::move(other.arr_[i]));
        v_ = std::move(other.v_);
    }

    Multiclass& operator=(Multiclass&& other) noexcept{
        Timer t("move assignment: ");
        for (size_t i = 0; i < sz_; i++)
            new(arr_ + i) int(std::move(other.arr_[i]));
        return *this;
    };

    ~Multiclass() = default;
};

int main() {
    Multiclass bc1;
    std::vector<int> v1(7,0);

    std::cout << "constructor test: " << std::endl;
    Multiclass bc2(bc1);
    Multiclass bc3(std::move(bc2));
    bc2.~Multiclass();
    bc3.~Multiclass();

    std::cout << std::endl;

    std::cout << "assignment test: " << std::endl;
    bc2 = bc1;
    bc3 = std::move(bc2);
    bc2.~Multiclass();
    bc3.~Multiclass();
    std::cout << std::endl;

    return 0;
}