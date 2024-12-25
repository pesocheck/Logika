#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <time.h>

void symmetric_difference(int* setA, int sizeA, int* setB, int sizeB) {
    int* result = (int*)malloc((sizeA + sizeB) * sizeof(int));
    int resultSize = 0;

    
    for (int i = 0; i < sizeA; i++) {
        int found = 0;
        for (int j = 0; j < sizeB; j++) {
            if (setA[i] == setB[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            result[resultSize++] = setA[i];
        }
    }

    
    for (int i = 0; i < sizeB; i++) {
        int found = 0;
        for (int j = 0; j < sizeA; j++) {
            if (setB[i] == setA[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            result[resultSize++] = setB[i];
        }
    }

    
    printf("Симметрическая разность: ");
    for (int i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
}

void input_set(int** set, int* size) {
    printf("Введите количество элементов множества: ");
    scanf("%d", size);
    *set = (int*)malloc((*size) * sizeof(int));
    int uniqueCount = 0;

    printf("Введите элементы множества:\n");
    while (uniqueCount < *size) {
        int element;
        scanf("%d", &element);

        int exists = 0;
        for (int i = 0; i < uniqueCount; i++) {
            if ((*set)[i] == element) {
                exists = 1;
                break;
            }
        }

        if (!exists) {
            (*set)[uniqueCount++] = element;
        }
        else {
            printf("Элемент %d уже существует в множестве. Пожалуйста, введите другой элемент.\n", element);
        }
    }

    *size = uniqueCount;

    printf("Вы ввели множество: { ");
    for (int i = 0; i < *size; i++) {
        printf("%d ", (*set)[i]);
    }
    printf("}\n");
}

void input_random_set(int** set, int* size) {
    printf("Хотите ли вы задать количество элементов вручную (1) или использовать случайное количество (2)? ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Введите количество элементов множества: ");
        scanf("%d", size);
    }
    else {
        
        *size = rand() % 10 + 1;
        printf("Случайное количество элементов: %d\n", *size);
    }

    *set = (int*)malloc((*size) * sizeof(int));
    int uniqueCount = 0;

    
    while (uniqueCount < *size) {
        int element = rand() % 100; 

        int exists = 0;
        for (int i = 0; i < uniqueCount; i++) {
            if ((*set)[i] == element) {
                exists = 1;
                break;
            }
        }

        if (!exists) {
            (*set)[uniqueCount++] = element;
        }
    }

    printf("Сгенерированное множество: { ");
    for (int i = 0; i < *size; i++) {
        printf("%d ", (*set)[i]);
    }
    printf("}\n");
}

void display_intro() {
    printf("===============================================================================================\n");
    printf("         Реализация операции нахождения симметрической разности двух и более множеств           \n");
    printf("         Выполнил: Макаров Алексей Сергеевич                                                   \n");
    printf("         Учебная группа: 23ВВВ1                                                                \n");
    printf("===============================================================================================\n");
    printf("\nНажмите Enter для продолжения...\n");
    getchar();
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    display_intro();

    int* sets[2] = { NULL, NULL }; 
    int sizes[2] = { 0, 0 }; 
    int numSets = 0;
    int choice;

    do {
        system("cls");

        printf("\n==============================\n");
        printf("          МЕНЮ               \n");
        printf("==============================\n");
        printf("1. Ввести множество вручную\n");
        printf("2. Создать множество с случайными значениями\n");
        printf("3. Найти симметрическую разность\n");
        printf("4. Выход\n");
        printf("==============================\n");
        printf("Выберите опцию: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            if (numSets < 2) {
                system("cls");
                input_set(&sets[numSets], &sizes[numSets]);
                numSets++;
            }
            else {
                printf("Вы уже ввели два множества.\n");
            }
            printf("\nНажмите Enter для перехода в меню...\n");
            getchar();
            getchar();
            break;
        }
        case 2: {
            if (numSets < 2) {
                system("cls");
                input_random_set(&sets[numSets], &sizes[numSets]);
                numSets++;
            }
            else {
                printf("Вы уже ввели два множества.\n");
            }
            printf("\nНажмите Enter для перехода в меню...\n");
            getchar();
            getchar();
            break;
        }
        case 3:
            if (numSets == 2) {
                system("cls");
                printf("Первое множество: ");
                for (int j = 0; j < sizes[0]; j++) printf("%d ", sets[0][j]);
                printf("\nВторое множество: ");
                for (int j = 0; j < sizes[1]; j++) printf("%d ", sets[1][j]);
                printf("\n");
                symmetric_difference(sets[0], sizes[0], sets[1], sizes[1]);
                printf("\nНажмите Enter для перехода в меню...\n");
                getchar();
                getchar();
            }
            else {
                printf("Пожалуйста, введите два множества для нахождения симметрической разности.\n");
                printf("\nНажмите Enter для перехода в меню...\n");
                getchar();
                getchar();
            }
            break;

        case 4:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор. Пожалуйста, попробуйте снова.\n");
            printf("\nНажмите Enter для перехода в меню...\n");
            getchar();
            getchar();
        }
    } while (choice != 4);

    for (int i = 0; i < numSets; i++) {
        free(sets[i]);
    }

    return 0;
}