#include "pch.h"
#include <iostream>
#include <ctime>
#include <clocale>

using namespace std;

struct Item {
    int data; //data - переменная, в которой будут храниться числа для каждого элемента списка
    Item * next; // next - указатель на следующий(с такой же структурой) элемент списка
};

Item *head;

void Add(int data) // функция добавления нового элемента в конец списка
{
    Item *temp = new Item; // создаем
    temp->data = data;
    temp->next = NULL;

    if (head == NULL) { head = temp; return; }; //если список пуст - элемент будет первым

    Item *p = head;
    while (p->next) //ищем конец списка
    {
        p = p->next;
    };
    p->next = temp; //ссылка в последнем элементе теперь указывает на наш новый элемент, т.е. он становится последним
};

void Show() //Функция отбражения списка
{
    Item *p = head;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    };
};

void Delete5() //Функция удаления элементов, заканчивающихся на 5
{
    Item *p = head;
    while (p != NULL && p->next != NULL) {                          // пока следующий элемент не последний
        if (p->next->data % 10 == 5) {                              // если он заканчивается на 5
            if (p->next->next != NULL) { p->next = p->next->next; } // если за ним есть еще элемент - указываем на него
            else { p->next = NULL; break; }                         // а если за ним нет элементов, просто удаляем на него ссылку
        }
        p = p->next;
    }
    if (head->data % 10 == 5) head = head->next;                    //чтоб не потерять ссылки, мы проверяли следующие элементы(p->next) за перебираемым (p)
                                                                    //теперь проверим первый
};


void main()
{
    setlocale(LC_CTYPE, "rus"); // вызов функции настройки локали
    srand(unsigned( time(0) )); //настраиваем "правильный" рандом, зависящий от текущего времени
    int n;
    cout << "Введите начальное кол-во элементов списка" << endl;
    cin >> n;

    for (int i = 0; i < n; i++) { // добавляем в список n новых элементов
        Add(rand());
    };

    cout << "Сгенерированный исходный список: " << endl; // Пройти список и вывести элементы
    Show();

    cout << "\nСписок после удаления: " << endl; // Пройти список и удалить элементы заканчивающиеся на 5, вывести элементы
    Delete5();
    Show();
}