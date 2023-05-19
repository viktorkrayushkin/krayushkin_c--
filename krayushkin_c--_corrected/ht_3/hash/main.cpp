#include <iostream>
#include <string>
#include <functional>
int main( ) {
    std::string str = "Hello, world!";
    std::hash<std::string> str_hash; // создание объекта хеш-функции для строки
    std::size_t hash_val = str_hash(str); // вычисление хеша для строки
    std::cout << "Хеш-значение для строки'" << str << "'равно"<<hash_val << std::endl;

    return 0;
}