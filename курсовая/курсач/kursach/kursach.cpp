#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

void symmetric_difference(int** sets, int* sizes, int numSets) {
    int* result = (int*)malloc(1000 * sizeof(int));
    int resultSize = 0;

    int* added = (int*)calloc(1000, sizeof(int));

    for (int i = 0; i < numSets; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            int found = 0;

            for (int k = 0; k < numSets; k++) {
                if (k != i) {
                    for (int l = 0; l < sizes[k]; l++) {
                        if (sets[i][j] == sets[k][l]) {
                            found = 1;
                            break;
                        }
                    }
                }
                if (found) break;
            }

            if (!found && !added[sets[i][j]]) {
                result[resultSize++] = sets[i][j];
                added[sets[i][j]] = 1;
            }
        }
    }

    printf("Симметрическая разность: ");
    for (int i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    free(added);
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

void display_intro() {
    printf("===============================================================================================\n");
    printf("         Реализация операции нахождения симметрической разности двух и более множеств          \n");
    printf("         Выполнил: Макаров Алексей Сергеевич                                                   \n");
    printf("         Учебная группа: 23ВВВ1                                                                \n");
    printf("===============================================================================================\n");
    printf("\nНажмите Enter для продолжения...\n");
    getchar();
}

int main() {
    setlocale(LC_ALL, "Rus");
    display_intro();

    char y = '0';
    int** sets = NULL;
    int* sizes = NULL;
    int numSets = 0;
    int choice;

    do {
        system("cls");

        printf("\n==============================\n");
        printf("          МЕНЮ               \n");
        printf("==============================\n");
        printf("1. Ввести множество\n");
        printf("2. Найти симметрическую разность\n");
        printf("3. Выход\n");
        printf("==============================\n");
        printf("Выберите опцию: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            system("cls");
            sets = (int**)realloc(sets, (numSets + 1) * sizeof(int*));
            sizes = (int*)realloc(sizes, (numSets + 1) * sizeof(int));
            input_set(&sets[numSets], &sizes[numSets]);
            numSets++;
            printf("\nНажмите Enter для перехода в меню...\n");
            getchar();
            getchar();
            break;
        }
        case 2:
            if (numSets > 0) {
                system("cls");
                for (int i = 0; i < numSets; i++) {
                    printf("В %d множестве находятся: ", i + 1);
                    for (int j = 0; j < sizes[i]; j++) printf("%d ", sets[i][j]);
                    printf("\n");
                }

                if (numSets < 2) {
                    printf("Пожалуйста, введите хотя бы два множества для нахождения симметрической разности.\n");
                }
                else {
                    symmetric_difference(sets, sizes, numSets);
                }
                printf("\nНажмите Enter для перехода в меню...\n");
                getchar();
                getchar();
            }
            else {
                printf("Сначала введите хотя бы одно множество.\n");
                printf("\nНажмите Enter для перехода в меню...\n");
                getchar();
                getchar();
            }
            break;

        case 3:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор. Пожалуйста, попробуйте снова.\n");
            printf("\nНажмите Enter для перехода в меню...\n");
            getchar();
            getchar();
        }
    } while (choice != 3);

    for (int i = 0; i < numSets; i++) {
        free(sets[i]);
    }
    free(sets);
    free(sizes);

    return 0;
}