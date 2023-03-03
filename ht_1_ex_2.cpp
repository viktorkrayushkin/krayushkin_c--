#include "Timer.h"
#include "Iterator.h"
#include <vector>
#include <iterator>
#include <iostream>

#define BIG_SIZE      1e7
#define ITEM_TO_FIND  1e5

template <typename T, typename _iterator_, typename _iteratorcategor_>
void MoveIteratorHelper(std::vector<T>& v, _iterator_& iter, int& iter_pos, int new_pos, _iteratorcategor_) {
    if (iter_pos > new_pos) {
        iter = v.begin();
        iter_pos = 0;

    }

    for (; iter_pos < new_pos; iter_pos++, ++iter);
}

template <typename T, typename iterator>
void MoveIterator(std::vector<T>& v, iterator& iter, int& iter_pos, int new_pos, std::bidirectional_iterator_tag) {
    if (iter_pos > new_pos)
        for (; iter_pos > new_pos; iter_pos--, --iter);
    else
        for (; iter_pos < new_pos; iter_pos++, ++iter);
}

template <typename T, typename iterator>
void MoveIterator(std::vector<T>& v, iterator& iter, int& iter_pos, int new_pos, std::random_access_iterator_tag) {
    iter += new_pos - iter_pos;
    iter_pos = new_pos;
}

template <typename T, typename iterator>
void MoveIterator(std::vector<T>& v, iterator& iter, int& iter_pos, int new_pos) {
    MoveIterator<T, iterator>(v, iter, iter_pos, new_pos, typename std::iterator_traits<iterator>::iterator_category());
}

template <typename T, typename iterator>
int bin_search(std::vector<T>& v, const T& obj) {
    int n = v.size();
    iterator iter = v.begin();
    int iter_pos = 0;
    int left_bound = 0, right_bound = n;

    MoveIterator<T, iterator>(v, iter, iter_pos, (right_bound + left_bound) / 2);
    while (left_bound < right_bound) {
        if (*iter >= obj) {
            right_bound = (right_bound + left_bound) / 2;
        }
        else {
            left_bound = (right_bound + left_bound) / 2 + 1;
            if (left_bound >= n)
                return -1;

int main() {
    std::vector<int> v(BIG_SIZE, 0);
    for (int i = 0; i < BIG_SIZE; v[i] = i++);

    {
        Timer t("forward iterator binsearch");
        std::cout << bin_search < int, forward_iterator < int >>(v, ITEM_TO_FIND) << std::endl;
    }
    {
        Timer t("bidirectional iterator binsearch");
        std::cout << bin_search < int, bidirectional_iterator < int >>(v, ITEM_TO_FIND) << std::endl;
    }
}