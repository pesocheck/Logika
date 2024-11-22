#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <stack>

int** createG(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        G[i] = (int*)malloc(size * sizeof(int));
    }

    // Инициализация матрицы смежности
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                G[i][j] = 0; // Нет петель
            }
            else {
                G[i][j] = rand() % 2; // Случайное значение 0 или 1
            }
        }
    }

    // Обеспечиваем симметричность для неориентированного графа
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            G[j][i] = G[i][j]; // Делаем граф неориентированным
        }
    }

    return G;
}

void printG(int** G, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
}

// Рекурсивная версия DFS
void DFS_recursive(int v, int** G, int size, int* vis) {
    vis[v] = 1; // Помечаем вершину как посещённую
    printf("%d ", v); // Выводим текущую вершину

    // Рекурсивно посещаем все соседние вершины
    for (int i = 0; i < size; i++) {
        if (G[v][i] == 1 && !vis[i]) {
            DFS_recursive(i, G, size, vis);
        }
    }
}

// Нерекурсивная версия DFS
void DFS(int s, int** G, int size) {
    int* vis = (int*)malloc(size * sizeof(int)); // Массив для отслеживания посещённых вершин
    for (int i = 0; i < size; i++) {
        vis[i] = 0; // Изначально все вершины непосещены
    }

    std::stack<int> stack; // Стек для хранения вершин
    stack.push(s); // Начинаем с начальной вершины

    while (!stack.empty()) {
        int v = stack.top(); // Получаем вершину из стека
        stack.pop(); // Удаляем вершину из стека

        if (!vis[v]) { // Если вершина не посещена
            vis[v] = 1; // Помечаем её как посещённую
            printf("%d ", v); // Выводим текущую вершину

            // Добавляем все соседние вершины в стек
            for (int i = size - 1; i >= 0; i--) { // Обходим в обратном порядке для правильного порядка обхода
                if (G[v][i] == 1 && !vis[i]) {
                    stack.push(i);
                }
            }
        }
    }

    free(vis); // Освобождаем память
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(0)); // Инициализация генератора случайных чисел

    int size;
    printf("Введите кол-во вершин: ");
    while (scanf_s("%d", &size) != 1 || size <= 0) { // Проверка на валидность ввода
        printf("Пожалуйста, введите положительное целое число: ");
        while (getchar() != '\n'); // Очистка ввода
    }

    int** G = createG(size); // Создаем граф
    printf("Матрица смежности:\n");
    printG(G, size); // Печатаем матрицу смежности

    int s;
    printf("Введите начальную вершину (0-%d): ", size - 1);
    while (scanf_s("%d", &s) != 1 || s < 0 || s >= size) { // Проверка на валидность ввода
        printf("Пожалуйста, введите число в диапазоне от 0 до %d: ", size - 1);
        while (getchar() != '\n'); // Очистка ввода
    }

    printf("Обход графа (рекурсивный):\n");
    int* vis_recursive = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        vis_recursive[i] = 0; // Изначально все вершины непосещены
    }
    DFS_recursive(s, G, size, vis_recursive); // Выполняем рекурсивный обход
    free(vis_recursive); // Освобождаем память

    printf("\nОбход графа (нерекурсивный):\n");
    DFS(s, G, size); // Выполняем нерекурсивный обход

    // Освобождение памяти
    for (int i = 0; i < size; i++) {
        free(G[i]);
    }
    free(G);

    return 0;
}