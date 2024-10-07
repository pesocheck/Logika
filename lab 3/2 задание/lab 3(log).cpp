#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <iostream>

struct node
{
	char inf[256];  // полезная информация
	struct node* next; // ссылка на следующий элемент 
};

struct node* head = NULL, * last = NULL, * f = NULL; // указатели на первый и последний элементы списка
int dlinna = 0;

// Функции добавления элемента, просмотра списка
void spstore(void), review(void), del(char* name);

char find_el[256];
struct node* find(char* name); // функция нахождения элемента
struct node* get_struct(void); // функция создания элемента

struct node* get_struct(void)
{
	struct node* p = NULL;
	char s[256];

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите название объекта: ");   // вводим данные
	scanf("%s", s);
	printf("\n");
	if (*s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->inf, s);

	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}

/* Последовательное добавление в список элемента (в конец)*/
void spstore(void)
{
	struct node* p = NULL;
	p = get_struct();
	if (head == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
	{
		head = p;
		last = p;
	}
	else if (head != NULL && p != NULL) // список уже есть, то вставляем в конец
	{
		last->next = p;
		last = p;
	}
	return;
}

node* get_element()
{
	node* res = head;
	head = head->next;
	res->next = NULL;
	return res;
}

/* Просмотр содержимого списка. */
void review(void)
{
	struct node* struc = head;
	int i = 1;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		printf("%d) Имя - %s \n", i++, struc->inf);
		struc = struc->next;
	}
	return;
}

/* Поиск элемента по содержимому. */
struct node* find(char* name)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			return struc;
		}
		struc = struc->next;
	}
	printf("Элемент не найден\n");
	return NULL;
}

void print_menu()
{
	printf("Выберете действие:\n");
	printf("1. Добавить элемент в очередь\n");
	printf("2. Получить элемент из очереди \n");
	printf("3. Вывести очередь \n");
	printf("4. Выход \n");
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	bool exit = false;
	while (!exit)
	{
		print_menu();
		int option = 0;
		scanf("%d", &option);

		switch (option)
		{
		case 1: spstore(); break;
		case 2: printf("Полученный элемент: %s\n", get_element()->inf); break;
		case 3: review(); break;
		case 4: exit = true; break;
		default: std::cin.get(); break;
		}
	}

	return 0;
}