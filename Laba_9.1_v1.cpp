#include "pch.h"
#include <iostream>
#include <list>
#include <ctime>
#include <clocale>

using namespace std;

void main()
{
    setlocale(LC_CTYPE, "rus"); // вызов функции настройки локали
    list<int> myList; // объявляем пустой список
    srand(unsigned(time(0))); //настраиваем "правильный" рандом, зависящий от текущего времени

    int n;
    cout << "Введите начальное кол-во элементов списка" << endl;
    cin >> n;
    for (int i = 0; i < n; i++) myList.push_back(rand()); // добавляем в список n новых элементов

    cout << "Сгенерированный исходный список: " << endl;
    for (auto n : myList) cout << n << " ";

    myList.remove_if([](int n) { return n % 10 == 5; }); //удаляем элементы, для которых функция возвращает "true"

    cout << endl << "Список без элементов, заканчивающихся на 5: " << endl;
    for (auto n : myList) cout << n << " ";
}
