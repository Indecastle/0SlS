#include <stdlib.h>
#include <iostream>
using namespace std;

struct Node                             //Структура, являющаяся звеном списка
{
	int x;                             //Значение x будет передаваться в список
	Node* Next, * Prev;                 //Указатели на адреса следующего и предыдущего элементов списка
};

class List                              //Создаем тип данных Список
{
	Node* Head, * Tail;                 //Указатели на адреса начала списка и его конца
public:
	List() :Head(NULL), Tail(NULL) {};    //Инициализируем адреса как пустые
	~List();                           //Прототип деструктора
	void Show();                       //Прототип функции отображения списка на экране
	void Add(int x);                   //Прототип функции добавления элементов в список
};

List::~List()                           //Деструктор
{
	while (Head)                       //Пока по адресу на начало списка что-то есть
	{
		Tail = Head->Next;             //Резервная копия адреса следующего звена списка
		delete Head;                   //Очистка памяти от первого звена
		Head = Tail;                   //Смена адреса начала на адрес следующего элемента
	}
}

void List::Add(int x)
{
	Node* temp = new Node;               //Выделение памяти под новый элемент структуры
	temp->Next = NULL;                   //Указываем, что изначально по следующему адресу пусто
	temp->x = x;                         //Записываем значение в структуру

	if (Head != NULL)                    //Если список не пуст
	{
		temp->Prev = Tail;    
		Tail->Next = temp;  
		Tail = temp;    
	}
	else 
	{
		temp->Prev = NULL;      
		Head = Tail = temp;    
	}
}

void List::Show()
{
	Node* temp = Tail;    

	while (temp != NULL)    
	{
		cout << temp->x << " "; 
		temp = temp->Prev;    
	}
	cout << "\n";

	temp = Head;     
	while (temp != NULL)      
	{
		cout << temp->x << " ";   
		temp = temp->Next;         
	}
	cout << "\n";
}

int main()
{
	system("CLS");
	List lst; //Объявляем переменную, тип которой есть список
	lst.Add(100); //Добавляем в список элементы
	lst.Add(200);
	lst.Add(900);
	lst.Add(888);

	lst.Show(); //Отображаем список на экране
	system("PAUSE");
	return 0;
}