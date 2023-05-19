#include <iostream>
#include <vector>

using namespace std;

class Matrix
{
private:
    vector<vector<int> > matrix;
    int row;
    int column;
public:
    Matrix() : row(0), column(0) {}
    Matrix(int row, int column) : row(row), column(column)
    {
        matrix.resize(row, vector<int>(column));
    }
    void EnterMatrix() //ввод матрицы
    {
        int element;
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++)
            {
                cin >> element;
                matrix[i][j] = element;
            }
    }
    friend Matrix operator+(const Matrix& a, const Matrix& b);
    friend ostream& operator<<(ostream& out, const Matrix& m);
    friend Matrix operator*(const Matrix& a, const Matrix& b);
};

Matrix operator*(const Matrix& a, const Matrix& b)
{

    cout << "Произведение матриц равно:" << endl;
    Matrix result(a.row, b.column);
    for (int i = 0; i < a.row; i++)
    {
        for (int j = 0; j < b.column; j++)
        {
            result.matrix[i][j] = 0;
            for (int t = 0; t < b.row; t++)
            {
                result.matrix[i][j] += a.matrix[i][t] * b.matrix[t][j];
            }
        }
    }
    return result;
}

Matrix operator+(const Matrix& a, const Matrix& b)
{
    cout << "Сумма матриц равна: " << endl;
    Matrix result(a.row, a.column);
    for (int i = 0; i < a.row; i++)
    {
        for (int j = 0; j < a.column; j++)
        {
            result.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
        }
    }
    return result;
}

ostream& operator<<(ostream& out, const Matrix& m) //ф-ция для вывода матрицы
{
    for (int i = 0; i < m.row; i++)
    {
        for (int j = 0; j < m.column; j++)
            out << m.matrix[i][j] << " ";
        out << endl;
    }
    return out;
}

int main()
{
    setlocale(LC_ALL, "rus");

    cout << "Выберите операцию: \n 1) Сложение матриц \n 2) Умножение матриц \n 3) Умножение матрицы на вектор" << endl;
    int n;
    cin >> n;

    switch (n)
    {
        case 1: // ввод для сложения
        {
            int r1, c1, r2, c2;
            cout << "Введите количество строк матриц: ";
            cin >> r1;
            r2 = r1;
            cout << "Введите количество столбцов матриц: ";
            cin >> c1;
            c2 = c1;
            cout << "Введите элементы 1 матрицы: ";

            Matrix mat(r1, c1);
            mat.EnterMatrix();
            cout << mat;

            cout << "Введите элементы 2 матрицы: ";

            Matrix mat2(r2, c2);
            mat2.EnterMatrix();
            cout << mat2;

            cout << endl;

            cout << mat + mat2;
            break;
        }
        case 2: // ввод для умножения между матрицами
        {
            int r1, c1, r2, c2;
            cout << "Введите количество строк для 1 матрицы: ";
            cin >> r1;
            cout << "Введите количество столбцов для 1 матрицы: ";
            cin >> c1;

            r2 = c1;

            cout << "Введите элементы 1 матрицы: ";

            Matrix mat(r1, c1);
            mat.EnterMatrix();
            cout << mat;

            cout << "Количество строк для 2 матрицы: " << r2 << endl;
            cout << "Введите количество столбцов для 2 матрицы: ";
            cin >> c2;

            cout << "Введите элементы 2 матрицы: ";

            Matrix mat2(r2, c2);
            mat2.EnterMatrix();
            cout << mat2;

            cout << endl;

            cout << mat * mat2;
            break;
        }
        case 3: // ввод для умножения матрицы на вектор
        {
            int r1, c1, r2;
            cout << "Введите количество строк для 1 матрицы: ";
            cin >> r1;
            cout << "Введите количество столбцов для 1 матрицы: ";
            cin >> c1;

            r2 = c1;

            cout << "Введите элементы 1 матрицы: ";

            Matrix mat(r1, c1);
            mat.EnterMatrix();
            cout << mat;

            cout << "Размерность вектора: " << r2 << endl;

            cout << "Введите элементы вектора: ";

            Matrix mat2(r2, 1);
            mat2.EnterMatrix();
            cout << mat2;

            cout << endl;

            cout << mat * mat2;
            break;
        }
    }
    return 0;
}

