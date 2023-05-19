#include <iostream>
#include <chrono>
#include <vector>
#include <stdlib.h>
#include <set>


class Timer {
    const std::string id_;
    const std::chrono::steady_clock::time_point start_time_ = std::chrono::steady_clock::now();

public:
    Timer(std::string id) : id_(std::move(id)) {}

    ~Timer() {
        const auto end_time = std::chrono::steady_clock::now();
        const auto dur = end_time - start_time_;
        std::cout << id_ << ": ";
        std::cout << "operation time";
        std::cout << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count()
                  << " ms" << std::endl;
    }
};

void set_sort(int N){
    Timer ld("Set_sort time");
    std::set <int> cont_1;
    int i;

    for (i=0; i<N; i++){
        int random = std::rand();
        cont_1.insert(random);
    };
};

void array_sort(int N){
    Timer ld("array_sort time");
    int cont_1[N];
    int i;
    for (i=0; i<N; i++){
        int random = std::rand();
        cont_1[i] = random;
    };
    std::sort(cont_1, cont_1 + N);
};

void vector_sort(int N){
    Timer ld("vector_sort time");
    std::vector <int> cont_1(N);
    int i;
    for (i=0; i<N; i++){
        int random = std::rand();
        cont_1[i] = random;
    };
    std::sort(cont_1.begin(), cont_1.end());
};


int main(){

    int N = 10000;
    std::cout << "Comparison for N =" << N << std::endl;
    set_sort(N);
    array_sort(N);
    vector_sort(N);
};