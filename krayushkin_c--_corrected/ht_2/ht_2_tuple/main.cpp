#include <iostream>
#include <ostream>
#include <tuple>

template <typename TupleT, std::size_t... Is>
std::ostream& printTupleImp(std::ostream& os, const TupleT& tp, std::index_sequence<Is...>) {
    auto printElem = [&os](const auto& x, size_t id) {
        if (id > 0)
            os << ", ";
        os << id << ": " << x;
    };

    os << "(";
    (printElem(std::get<Is>(tp), Is), ...);
    os << ")";
    return os;
}

template <typename TupleT, std::size_t TupSize = std::tuple_size<TupleT>::value>
std::ostream& operator <<(std::ostream& os, const TupleT& tp) {
    return printTupleImp(os, tp, std::make_index_sequence<TupSize>{});
}

int main() {
    std::tuple tp { 1, 2, 3};
    std::cout << tp << '\n';
}