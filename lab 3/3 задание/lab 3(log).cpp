#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

struct node {
    char inf[256];  // полезная информация
    struct node* next; // ссылка на следующий элемент
};

struct node* head = NULL; // указатель на первый элемент списка

// Функции добавления элемента, просмотра списка
void spstore(void), review(void);
struct node* get_struct(void); // функция создания элемента

struct node* get_struct(void) {
    struct node* p = NULL;
    char s[256];

    if ((p = (node*)malloc(sizeof(struct node))) == NULL) { // выделяем память под новый элемент списка
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: \n"); // вводим данные
    scanf("%s", s);
    if (*s == 0) {
        printf("Запись не была произведена\n");
        free(p); // освобождаем память, если ввод пустой
        return NULL;
    }
    strcpy(p->inf, s);
    p->next = NULL;

    return p; // возвращаем указатель на созданный элемент
}

/* Добавление элемента в стек (в начало) */
void spstore(void) {
    struct node* p = get_struct();
    if (p != NULL) { // если элемент успешно создан
        p->next = head; // новый элемент указывает на текущую голову
        head = p; // новый элемент становится головой
    }
}

/* Получение элемента из стека (удаление из начала) */
struct node* get_element() {
    if (head == NULL) { // Проверяем, пуст ли стек
        printf("Список пуст, невозможно получить элемент.\n");
        return NULL; // Возвращаем NULL, если стек пуст
    }

    struct node* p = head; // Сохраняем текущую голову
    head = head->next; // Устанавливаем голову на следующий элемент
    return p; // Возвращаем старую голову
}

/* Просмотр содержимого списка. */
void review(void) {
    struct node* struc = head;
    int i = 1;
    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }
    while (struc) {
        printf("%d) %s\n", i++, struc->inf);
        struc = struc->next;
    }
}

void print_menu() {
    printf("Выберете действие:\n");
    printf("1. Добавить элемент в стек\n");
    printf("2. Получить элемент из стека \n");
    printf("3. Вывести стек \n");
    printf("4. Выход \n");
}

int main() {
   setlocale(LC_ALL,"Rus");

    bool exit = false;
    while (!exit) {
        print_menu();
        int option = 0;
        scanf("%d", &option);

        switch (option) {
        case 1: 
            spstore(); 
            break;
        case 2: {
            struct node* elem = get_element();
            if (elem != NULL) { // Проверяем, был ли получен элемент
                printf("Полученный элемент: %s\n", elem->inf);
                free(elem); // Освобождаем память, если элемент был получен
            }
            break;
        }
        case 3: 
            review(); 
            break;
        case 4: 
            exit = true; 
            break;
        default: 
            std::cin.get(); 
            break;
        }
    }

    // Освобождение оставшихся элементов в стеке перед выходом
    while (head != NULL) {
        struct node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
