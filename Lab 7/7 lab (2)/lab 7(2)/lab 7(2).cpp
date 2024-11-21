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
    scanf_s("%d", &size);

    int** G = createG(size); // Создаем граф
    printf("Матрица смежности:\n");
    printG(G, size); // Печатаем матрицу смежности

    int s;
    printf("Введите начальную вершину (0-%d): ", size - 1);
    scanf_s("%d", &s);
    printf("Обход графа:\n");
    DFS(s, G, size); // Выполняем обход в глубину

    // Освобождение памяти
    for (int i = 0; i < size; i++) {
        free(G[i]);
    }
    free(G);

    return 0;
}