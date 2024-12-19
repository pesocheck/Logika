#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
#include <locale.h> 
#include <time.h> 
#include <limits.h>
#include <string.h>
#include <queue>  
using namespace std;

// Функция для создания графа
int** createG(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; ++i) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            G[i][j] = (rand() % 2) ? (rand() % 10 + 1) : 0;
            if (i == j) G[i][j] = 0; // Вес самопетли равен 0
        }
    }
    return G;
}

// Функция для преобразования ориентированного графа в неориентированный
void mor(int** G, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            G[j][i] = G[i][j];
        }
    }
}

// Функция для печати графа
void printG(int** G, int size) {
    printf("  ");
    for (int i = 0; i < size; ++i) printf("%2d ", i);
    printf("\n");
    for (int i = 0; i < size; ++i) {
        printf("%d ", i);
        for (int j = 0; j < size; ++j) {
            printf("%2d ", (G[i][j] != INT_MAX) ? G[i][j] : -1);
        }
        printf("\n");
    }
    printf("\n");
}

// Функция для поиска расстояний с помощью BFS
void DiFS(int** G, int size, int* dist, int s) {
    queue<int> q;
    q.push(s);
    dist[s] = 0;

    while (!q.empty()) {
        s = q.front();
        q.pop();

        for (int i = 0; i < size; ++i) {
            if (G[s][i] > 0 && dist[i] > dist[s] + G[s][i]) {
                dist[i] = dist[s] + G[s][i];
                q.push(i);
            }
        }
    }
}

// Функция для создания матрицы расстояний
void createDist(int** G, int size, int** D) {
    int* dist = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) dist[j] = INT_MAX;
        DiFS(G, size, dist, i);
        for (int j = 0; j < size; ++j) D[i][j] = dist[j];
    }
    free(dist); // Освобождение памяти
}

// Функция для нахождения эксцентриситета
void getE(int** D, int size, int* ecc) {
    int max;
    for (int i = 0; i < size; ++i) {
        max = INT_MIN;
        for (int j = 0; j < size; ++j) {
            if (D[i][j] != INT_MAX) {
                max = (D[i][j] > max) ? D[i][j] : max;
            }
        }
        ecc[i] = (max == INT_MIN) ? INT_MAX : max; // Устанавливаем INT_MAX для изолированных вершин
    }
}

// Функция для нахождения радиуса
int getR(int* ecc, int size) {
    int min = INT_MAX;
    for (int i = 0; i < size; ++i) { // Исправлено: добавлена закрывающая скобка
        if (ecc[i] != INT_MAX) { // Игнорируем изолированные вершины
            min = (ecc[i] < min && ecc[i]!=0) ? ecc[i] : min;
        }
    }
    return (min == INT_MAX) ? -1 : min; // Возвращаем -1, если все вершины изолированы
}

// Функция для нахождения диаметра
int getD(int* ecc, int size) {
    int max = INT_MIN;
    for (int i = 0; i < size; ++i) {
        if (ecc[i] != INT_MAX) { // Игнорируем изолированные вершины
            max = (ecc[i] > max) ? ecc[i] : max;
        }
    }
    return (max == INT_MIN) ? -1 : max; // Возвращаем -1, если все вершины изолированы
}

int main() {
    setlocale(LC_ALL, "Rus");
    int n;
    int weighted = 0, oriented = 0;
    int** G = NULL;
    srand(time(NULL));
    printf("Введите n:");
    scanf("%d", &n);

    printf("n=%d w=%d o=%d\n", n, weighted, oriented);
    G = createG(n);
    if (!oriented) mor(G, n);
    printG(G, n);

    int** D = (int**)malloc(n * sizeof(int*));
    int* ecc = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        D[i] = (int*)malloc(n * sizeof(int));
    }
    createDist(G, n, D);
    printG(D, n);

    getE(D, n, ecc);
    int r = getR(ecc, n);
    int d = getD(ecc, n);
    for (int i = 0; i < n; ++i) {
        if (ecc[i] != INT_MAX) { // Проверяем, что вершина не изолированная
            if (ecc[i] == d) printf("Вершина %d: переферийная\n", i);
            if (ecc[i] == r) printf("Вершина %d: центральная\n", i);
        }
    }
    printf("\nРадиус: %d\nДиаметр: %d\n", r, d);

    // Освобождение памяти
    for (int i = 0; i < n; ++i) {
        free(G[i]);
        free(D[i]);
    }
    free(G);
    free(D);
    free(ecc);

    return 0;
}