#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    setlocale(LC_ALL, "Russian");
    int n = 5, ** G = NULL, size = 0, * deg = NULL, * loop = NULL;

    printf("Введите количество вершин: ");
    scanf("%d", &n);

    deg = (int*)malloc(n * sizeof(int));
    loop = (int*)malloc(n * sizeof(int));
    G = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        deg[i] = 0;
        loop[i] = 0;
        G[i] = (int*)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            G[i][j] = 0;

    // Генерация случайного графа
    srand(time(NULL)); // Инициализация генератора случайных чисел
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            G[i][j] = rand() % 2;
            G[j][i] = G[i][j]; // Неориентированный граф
        }
    }

    // Печать матрицы смежности
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }

    // Подсчет размера графа
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            size += G[i][j];
        }
    }

    printf("Размер графа = %d \n", size);

    // Подсчет степени вершин
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                deg[i] += 2 * G[i][j];
                loop[i] += 2 * G[i][j];
            }
            else {
                deg[i] += G[i][j];
            }
        }
        printf("Loop[%d]: %d, Deg[%d]: %d\n", i, loop[i], i, deg[i]);
    }

    // Определение изолированных, концевых и доминирующих вершин
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0)
            printf("Вершина %d - изолированная\n", i);
        if (deg[i] == 1)
            printf("Вершина %d - концевой\n", i);
        if (deg[i] == n - 1)
            printf("Вершина %d - доминирующая\n", i);
    }

    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        free(G[i]);
    }
    free(G);
    free(deg);
    free(loop);

    return 0;
}