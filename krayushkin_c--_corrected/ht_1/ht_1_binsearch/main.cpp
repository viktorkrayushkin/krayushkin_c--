#include <vector>
#include <iterator>
#include <chrono>
#include <iostream>

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
class forward_iterator : public std::iterator<std::forward_iterator_tag, T> {
protected:
    using t_iterator_ = typename std::vector<T>::iterator;
    t_iterator_ iter;
public:
    forward_iterator(const t_iterator_& std_iterator) : iter(std_iterator) {}
    forward_iterator(t_iterator_&& std_iterator) : iter(std::move(std_iterator)) {}

    forward_iterator<T> operator=(const t_iterator_& std_iter) {
        iter = std_iter;
        return *this;

    }
    forward_iterator<T> operator=(t_iterator_&& std_iter) {
        iter = std_iter;
        return *this;
    }

    forward_iterator<T> operator++() {
        ++iter;
        return *this;
    }

    T& operator*() {
        return *iter;
    }
};

template <typename T>
class bidirectional_iterator : public forward_iterator<T> {
public:
    using forward_iterator<T>::forward_iterator;

    forward_iterator<T> operator--() {
        --this->iter;
        return *this;
    }
};

namespace std
{
    template <typename T>
    struct iterator_traits<bidirectional_iterator < T>>
{
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
};
}

template <typename T, typename iterator, typename iter_categor>
void move_iterator(std::vector<T>& v, iterator& iter, int& iter_pos, int new_pos, iter_categor) {
    if (iter_pos > new_pos) {
        iter = v.begin();
        iter_pos = 0;
    }

    for (; iter_pos < new_pos; iter_pos++, ++iter);
}

template <typename T, typename iterator>
void move_iterator(std::vector<T>& v, iterator& iter, int& iter_pos, int new_pos, std::bidirectional_iterator_tag) {
    if (iter_pos > new_pos)
        for (; iter_pos > new_pos; iter_pos--, --iter);
    else
        for (; iter_pos < new_pos; iter_pos++, ++iter);
}

template <typename T, typename iterator>
void move_iterator(std::vector<T>& v, iterator& iter, int& iter_pos, int new_pos, std::random_access_iterator_tag) {
    iter += new_pos - iter_pos;
    iter_pos = new_pos;
}

template <typename T, typename iterator>
void move_iterator(std::vector<T>& v, iterator& iter, int& iter_pos, int new_pos) {
    move_iterator<T, iterator>(v, iter, iter_pos, new_pos, typename std::iterator_traits<iterator>::iterator_category());
}

template <typename T, typename Iterator>
int BinSearch(std::vector<T>& v, const T& obj) {
    int n = v.size();
    Iterator iter = v.begin();
    int iter_pos = 0;
    int left_bound = 0, right_bound = n;

    move_iterator<T, Iterator>(v, iter, iter_pos, (right_bound + left_bound) / 2);
    while (left_bound < right_bound) {
        if (*iter >= obj) {
            right_bound = (right_bound + left_bound) / 2;
        }
        else {
            left_bound = (right_bound + left_bound) / 2 + 1;
            if (left_bound >= n)
                return -1;
        }
        move_iterator<T, Iterator>(v, iter, iter_pos, (right_bound + left_bound) / 2);
    }

    if (*iter == obj)
        return iter_pos;
    else
        return -1;
}

int main() {
    std::vector<int> v( 1e8, 0);
    for (int i = 0; i <  1e8; v[i] = i++);

    {
        Timer t("forward_iterator binsearch");
        std::cout << BinSearch<int, forward_iterator<int>>(v, 1e4) << std::endl;
    }
    {
        Timer t("bidirectional_iterator binsearch");
        std::cout << BinSearch<int, bidirectional_iterator<int>>(v, 1e4) << std::endl;
    }
    {
        Timer t("random_access_iterator binsearch");
        std::cout << BinSearch<int, std::vector<int>::iterator>(v, 1e4) << std::endl;
    }
}