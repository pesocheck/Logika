#include <stdio.h>
#include <stdlib.h>
#include <random>

int main() {
    setlocale(LC_ALL, "Rus");
    int n = 10, ** G = NULL, size = 0, * deg = NULL, * loop = NULL;
    printf("Введите кол-во вершин: ");
    scanf_s("%d", &n);

    G = (int**)malloc(n * sizeof(int*));
    deg = (int*)malloc(n * sizeof(int));
    loop = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        deg[i] = 0;
        loop[i] = 0;
        G[i] = (int*)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            G[i][j] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            G[i][j] = rand() % 2;
            G[j][i] = G[i][j];
        }
    }

    printf("Матрица смежности:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }

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
    }

    printf("Размер = %d \n", size);

    for (int i = 0; i < n; i++) {
        if (deg[i] * loop[i] == 0)
            printf("Вершина %d, - изолирована\n", i);
        if (deg[i] * loop[i] == 1)
            printf("Вершина %d, - конецевая\n", i);
        if (deg[i] * loop[i] == n)
            printf("Вершина %d, - изолирована\n", i);
    }

    // Построение матрицы инцидентности
    int edge_count = 0;

    // Подсчет количества рёбер
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (G[i][j] == 1) {
                edge_count++;
            }
        }
    }

    // Создание матрицы инцидентности
    int** incident_matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        incident_matrix[i] = (int*)malloc(edge_count * sizeof(int));
        for (int j = 0; j < edge_count; j++) {
            incident_matrix[i][j] = 0; // Инициализация нулями
        }
    }

    // Заполнение матрицы инцидентности
    int edge_index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (G[i][j] == 1) {
                incident_matrix[i][edge_index] = 1;
                incident_matrix[j][edge_index] = 1;
                edge_index++;
            }
        }
    }

    // Вывод матрицы инцидентности
    printf("Матрица инцидентности:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < edge_count; j++) {
            printf("%d ", incident_matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}