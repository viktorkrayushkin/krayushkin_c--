#include <iostream>
#include <array>
#include <initializer_list>


using namespace std;

template <typename T, int M, int N>
class Matrix {
private:
    int Rows_n;
    int Col_n;
    array<array<T, N>, M> values;

public:
    int rows_n() const {
        return Rows_n;
    }

    int col_n() const {
        return Col_n;
    }

    Matrix() {
        values = {};
    }
    Matrix<T, M, N>& operator=(const Matrix<T, M, N>&);
    Matrix<T, M, N>& operator=(Matrix<T, M, N>&&);
    Matrix(initializer_list<initializer_list<T>>);
    array<T, N>& operator[](int);
    const array<T, N>& operator[](int) const;
};

template <typename T, int M, int N>
Matrix<T, M, N>::Matrix(initializer_list<initializer_list<T>> lst) {
    if (lst.size() != M) {
        delete this;
        throw(1);
    }

    auto rows = lst.begin();
    for (size_t i = 0; i < M; i++, rows++) {
        if (rows->size() != N) {
            delete this;
            throw(1);
        }

        auto column = rows->begin();
        for (size_t j = 0; j < N; j++, column++) {
            values[i][j] = *column;
        }
    }
}

template <typename T, int M, int N>
std::ostream& operator<< (std::ostream& out, const Matrix<T, M, N>& m1)
{
    for (int i = 0; i < m1.rows_n(); i++) {
        for (int j = 0; j < m1.col_n(); j++) {
            out << m1[i][j] << " ";
        }
    }
    return out;
}

template <typename T, int M, int N>
Matrix<T, M, N>& Matrix<T, M, N>::operator=(const Matrix<T, M, N>& other) {
    values = other.values;
    return *this;
}

template <typename T, int M, int N>
array<T, N>& Matrix<T, M, N>::operator[](int col) {
    return values[col];
}

template <typename T, int M, int N>
const array<T, N>& Matrix<T, M, N>::operator[](int col) const {
    return values[col];
}

template <typename T, int M, int N>
Matrix<T, M, N>& operator+(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2) {
    Matrix<T, M, N> result;
    for (size_t i = 0; i < M; i++) {
        for (size_t j = 0; j < N; j++) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return result;
}

template <typename T, int M, int N>
Matrix<T, M, N>& operator-(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2) {
    Matrix<T, M, N> result;
    for (size_t i = 0; i < M; i++) {
        for (size_t j = 0; j < N; j++) {
            result[i][j] = m1[i][j] - m2[i][j];
        }
    }
    return result;
}

template <typename T, int M, int N, int K>
Matrix<T, M, N>& operator*(const Matrix<T, M, K>& m1, const Matrix<T, K, N>& m2) {
    Matrix<T, M, N> result;
    for (size_t i = 0; i < M; i++) {
        for (size_t j = 0; j < N; j++) {
            for (size_t k = 0; k < K; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return result;
}


template <typename T, int M, int N>
Matrix<T, M, N>& Matrix<T, M, N>::operator=(Matrix<T, M, N>&& other) {
    values = move(other.values);
    return *this;
}

int main() {
    Matrix<int, 2, 2> m;
    m[0][0] = 1;
    std::cout << m[0][0] << std::endl;
    Matrix<int, 2, 2> m1 = {{1, 2},{3, 4}};
    Matrix<int, 2, 2> m2;
    m2 = m + m1;
    m = m1 * m2;
    std::cout << m[0][0] << std::endl;
}