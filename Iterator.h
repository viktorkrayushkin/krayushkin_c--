//
// Created by Viktor Krayushkin on 04.03.2023.
//

#ifndef PROGECT_ITERATOR_H
#define PROGECT_ITERATOR_H
#pragma once
#include <vector>
#include <iterator>

template <typename T>
class ForwardIterator : public std::iterator<std::forward_iterator_tag, T> {
protected:
    using t_iterator_ = typename std::vector<T>::iterator;
    t_iterator_ iter_;
public:
    ForwardIterator(const t_iterator_& std_iterator) : iter_(std_iterator) {}
    ForwardIterator(t_iterator_&& std_iterator) : iter_(std::move(std_iterator)) {}

    ForwardIterator<T> operator=(const t_iterator_& std_iter) {
        iter_ = std_iter;
        return *this;

    }
    ForwardIterator<T> operator=(t_iterator_&& std_iter) {
        iter_ = std_iter;
        return *this;
    }

    ForwardIterator<T> operator++() {
        ++iter_;
        return *this;
    }

    T& operator*() {
        return *iter_;
    }
};

template <typename T>
class BidirectionalIterator : public ForwardIterator<T> {
public:
    using ForwardIterator<T>::ForwardIterator;

    ForwardIterator<T> operator--() {
        --this->iter_;
        return *this;
    }
};

namespace std
{
    template <typename T>
    struct iterator_traits<BidirectionalIterator<T>>
{
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
};
} // other way to set iterator_category because double inheritance doesn't work
#endif //PROGECT_ITERATOR_H
