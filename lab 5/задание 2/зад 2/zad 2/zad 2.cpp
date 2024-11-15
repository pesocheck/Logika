#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    setlocale(LC_ALL, "Russian");
    int n = 5, ** G = NULL, ** I = NULL, size = 0, * deg = NULL;

    printf("Введите количество вершин: ");
    scanf("%d", &n);

    deg = (int*)malloc(n * sizeof(int));
    G = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        deg[i] = 0;
        G[i] = (int*)malloc(n * sizeof(int));
    }

    // Инициализация матрицы смежности
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            G[i][j] = 0;

    // Генерация случайного графа
    srand(time(NULL)); // Инициализация генератора случайных чисел
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) { // j начинается с i + 1, чтобы избежать дублирования
            G[i][j] = rand() % 2;
            G[j][i] = G[i][j]; // Неориентированный граф
        }
    }

    // Печать матрицы смежности
    printf("Матрица смежности:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }

    // Подсчет размера графа и степени вершин
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) { // j начинается с i + 1, чтобы избежать дублирования
            size += G[i][j];
        }
    }

    printf("Размер графа = %d \n", size);

    // Подсчет степени вершин
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            deg[i] += G[i][j];
        }
        printf("Deg[%d]: %d\n", i, deg[i]);
    }

    // Построение матрицы инцидентности
    int m = size; // Количество рёбер
    I = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        I[i] = (int*)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            I[i][j] = 0; // Инициализация матрицы инцидентности
        }
    }

    // Заполнение матрицы инцидентности
    int edgeIndex = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (G[i][j] == 1) {
                I[i][edgeIndex] = 1; // Вершина i инцидентна ребру
                I[j][edgeIndex] = 1; // Вершина j инцидентна ребру
                edgeIndex++;
            }
        }
    }

    // Печать матрицы инцидентности
    printf("Матрица инцидентности:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", I[i][j]);
        }
        printf("\n");
    }

    // Определение изолированных, концевых и доминирующих вершин
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0)
            printf("Вершина %d - изолированная\n", i);
        else if (deg[i] == 1)
            printf("Вершина %d - концевой\n", i);
        else if (deg[i] == n - 1)
            printf("Вершина %d - доминирующая\n", i);
    }

    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        free(G[i]);
        free(I[i]);
    }
    free(G);
    free(I);
    free(deg);

    return 0;
}