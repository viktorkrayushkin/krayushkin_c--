#include <iostream>
#include <tuple>


double sum = 0;
double multiplication = 1;

template <class Tuple, class Func, size_t N>
struct TupleIterator {
    static void ApplyToEach(Tuple& t, Func& func) {
        TupleIterator<Tuple, Func, N - 1>::ApplyToEach(t, func);
        func(std::get<N - 1>(t));
    }
};

template <class Tuple, class Func>
struct TupleIterator<Tuple, Func, 1> {
    static void ApplyToEach(Tuple& t, Func& func) {
        func(std::get<0>(t));
    }
};

template<typename Tuple, class Func>
void TupleApplyToEach(Tuple& t, Func& func) {
    TupleIterator<Tuple, Func, std::tuple_size_v<Tuple>>::ApplyToEach(t, func);
}

template <typename T>
void Add(const T& obj) {
    sum += obj;
}

void Multiply(const int& obj) {
    multiplication *= obj;
}

void Square(double& obj) {
    obj = obj * obj;
}

void Print(double& obj) {
    std::cout << obj << " ";
}

int main() {
    std::tuple<double, double, double> t(1, 1.7, 4.2);
    TupleApplyToEach(t, Add<double>);
    std::cout << sum << std::endl;
    TupleApplyToEach(t, Multiply);
    std::cout << multiplication << std::endl;

    std::cout << std::endl;
    TupleApplyToEach(t, Square);
    TupleApplyToEach(t, Print);
    std::cout << std::endl;
}