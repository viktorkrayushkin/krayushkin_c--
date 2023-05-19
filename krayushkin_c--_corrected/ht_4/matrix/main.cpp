#include <iostream>
#include <memory>
#include <utility>
#include <vector>

using namespace std;


class Matrix {
private:
    std::vector<std::vector<int>> values;
    int Rows_n;
    int Col_n;

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

    Matrix(std::vector<std::vector<int>> &arr) {
        values = arr;
        Rows_n = values.size();
        Col_n = values[0].size();
        for (int i = 0; i < Rows_n; i++) {
            if (Col_n != values[i].size()) {
                delete this;
                throw (1);
            }

        }
    };
    Matrix(std::vector<std::vector<int>> &&arr) {
        values = arr;
        Rows_n = values.size();
        Col_n = values[0].size();
        for (int i = 0; i < Rows_n; i++) {
            if (Col_n != values[i].size()) {
                delete this;
                throw (1);
            }

        }
    };

    std::vector<int> &operator[](int i) {
        return values[i];
    };

    const std::vector<int> &operator[](int i) const {
        return values[i];
    };

    Matrix &operator+=(const Matrix &);

    Matrix &operator-=(const Matrix &);

    Matrix &operator=(const Matrix &);

    Matrix &operator=(Matrix &&);

    Matrix(const Matrix &other) {
        for (int i = 0; i < other.rows_n(); i++) {
            for (size_t j = 0; j < other.col_n(); j++) {
                values[i][j] = other[i][j];
            }
        }
    }

    Matrix(Matrix &&other) {
        for (size_t i = 0; i < other.rows_n(); i++) {
            for (size_t j = 0; j < other.col_n(); j++) {
                values[i][j] = move(other[i][j]);
            }
        }
    }
    Matrix& operator=(const std::vector<std::vector<int>>& other);

};
// проверка на сложение

bool AreSameSize(const Matrix& m1, const Matrix& m2) {
    if ((m1.rows_n() == m2.rows_n())and(m1.col_n() == m2.col_n()))
    {
        return true;
    }
    return false;
}

// сложение

Matrix&& operator+(const Matrix& m1,const Matrix& m2) {
    Matrix result;
    if (!AreSameSize(m1, m2))
    {
        throw(1);
    }
    for (int i = 0; i < m1.rows_n(); i++) {
        for (int j = 0; j < m1.col_n(); j++) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return move(result);
}

// вычетание

Matrix&& operator-(const Matrix& m1,const Matrix& m2) {
    Matrix result;
    if (!AreSameSize(m1, m2))
    {
        throw(1);
    }
    for (int i = 0; i < m1.rows_n(); i++) {
        for (int j = 0; j < m1.col_n(); j++) {
            result[i][j] = m1[i][j] - m2[i][j];
        }
    }
    return move(result);
}

// умножение

Matrix&& operator*(const Matrix& m1, const Matrix& m2) {
    Matrix result;
    if (m1.col_n() != m2.rows_n()){
        throw(1);
    }
    for (int i = 0; i < m1.rows_n(); i++) {
        for (int j = 0; j < m2.col_n(); j++) {
            for (int k = 0; k < m1.col_n() ; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return move(result);
}

// увелечение

Matrix& Matrix::operator+=(const Matrix& other) {
    if (!AreSameSize(*this, other))
    {
        throw(1);
    }
    for (int i = 0; i < other.rows_n(); i++) {
        for (size_t j = 0; j < other.col_n(); j++) {
            values[i][j] += other[i][j];
        }
    }
    return *this;
}

// уменьшение

Matrix& Matrix::operator-=(const Matrix& other) {
    if (!AreSameSize(*this, other))
    {
        throw(1);
    }
    for (int i = 0; i < other.rows_n() ; i++) {
        for (int j = 0; j < other.col_n(); j++) {
            values[i][j] -= other[i][j];
        }
    }
    return *this;
}

// присваивание

Matrix& Matrix::operator=(const Matrix& other) {
    values = other.values;
    return *this;
}

// замена

Matrix& Matrix::operator=(Matrix&& other) {
    values = move(other.values);
    return *this;
}
//  транспонирование
Matrix& Transpose(const Matrix& other){
    Matrix result;
    for (int i = 0; i < other.rows_n(); i++) {
        for (int j = 0; j < other.col_n(); j++) {
            result[i][j] = other[j][i];
        }
    }
    return result;
}

std::ostream& operator<< (std::ostream &out, const Matrix& m1) {
    for (int i = 0; i < m1.rows_n(); i++) {
        for (int j = 0; j < m1.col_n(); j++) {
            out << m1[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}
int main()
{
    std::vector<std::vector<int>> v = {{7, 5}, {3, 6}};
    Matrix m (v);
    Matrix m1({{1, 2},{3, 4}});
    std::cout<<m1;
    Matrix m2;
    m2 = m + m1;
    std::cout<<m2;
    m = m1 * m2;
    m = Transpose(std::move(m2));
    std::cout << m[1][0] << std::endl;
    m = Transpose(m1);
    std::cout << m[1][0] << std::endl;

    Matrix m3( {
                       {1},
                       {3},
                       {4}
               });

    Matrix m4 ({
                       {1, 1, 1 }
               });
    std::cout << (m4 * m3)[0][0] << std::endl;
}