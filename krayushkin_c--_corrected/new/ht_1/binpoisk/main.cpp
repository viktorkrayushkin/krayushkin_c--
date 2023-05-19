#include <iostream>
#include <vector>
#include <chrono>


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

template <typename T>
class ForwardIterator : public std::iterator<std::forward_iterator_tag, T> {
private:
    using Iter_t = typename std::vector<T>::iterator;
    Iter_t it;
public:
    ForwardIterator(const Iter_t& std_iter) : it(std_iter) {}

    ForwardIterator<T> operator=(const Iter_t& std_iter) {
        it = std_iter;
        return *this;
    }

    ForwardIterator<T> operator++() {
        ++it;
        return *this;
    }

    T& operator*() {
        return *it;
    }
};

template <typename T>
class BidirectionalIterator : public ForwardIterator<T> {
public:
    using ForwardIterator<T>::ForwardIterator;

    ForwardIterator<T> operator--() {
        --this->it;
        return *this;
    }
};

template <typename T, typename Iterator, typename IterCategory>
void MoveIteratorHelper(std::vector<T>& v, Iterator& iter, int& was, int is, IterCategory) {
    if (was > is) {
        iter = v.begin();
        was = 0;
    }
    for (; was < is; was++, ++iter);
}

template <typename T, typename Iterator>
void MoveIteratorHelper(std::vector<T>& v, Iterator& iter, int& was, int is, std::bidirectional_iterator_tag) {
    if (was > is)
        for (; was > is; was--, --iter);
    else
        for (; was < is; was++, ++iter);
}

template <typename T, typename Iterator>
void MoveIteratorHelper(std::vector<T>& v, Iterator& iter, int& was, int is, std::random_access_iterator_tag) {
    iter += is - was;
    was = is;
}

template <typename T, typename Iterator>
void MoveIterator(std::vector<T>& v, Iterator& iter, int& was, int is) {
    MoveIteratorHelper<T, Iterator>(v, iter, was, is, typename std::iterator_traits<Iterator>::iterator_category());
}

template <typename T, typename Iterator>
int BinSearch(std::vector<T>& v, const T& obj) {
    int n = v.size();
    Iterator iter = v.begin();
    int iter_pos = 0;
    int left_bound = 0, right_bound = n;

    MoveIterator<T, Iterator>(v, iter, iter_pos, (right_bound + left_bound) / 2);
    while (left_bound < right_bound) {
        if (*iter >= obj) {
            right_bound = (right_bound + left_bound) / 2;
        }
        else {
            left_bound = (right_bound + left_bound) / 2 + 1;
            if (left_bound >= n)
                return -1;
        }
        MoveIterator<T, Iterator>(v, iter, iter_pos, (right_bound + left_bound) / 2);
    }

    if (*iter == obj)
        return iter_pos;
    else
        return -1;
}

int main() {
    std::vector<int> vect = {1, 2, 3, 4, 5};
    int key = 3;

    Timer("Forward iterator binsearch");
    std::cout << BinSearch<int, ForwardIterator<int>>(vect, key) << std::endl;

    Timer("Bidirectional iterator binsearch");
    std::cout << BinSearch<int, BidirectionalIterator<int>>(vect, key) << std::endl;

    Timer("Random access iterator binsearch");
    std::cout << BinSearch<int, std::vector<int>::iterator>(vect, key) << std::endl;
}