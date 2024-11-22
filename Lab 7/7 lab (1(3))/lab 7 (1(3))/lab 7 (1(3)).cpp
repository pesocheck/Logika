#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <stack>

struct Graph {
    int size; // Количество вершин 
    std::vector<std::vector<int>> adjList; // Список смежности
    std::vector<std::vector<int>> adjMatrix; // Матрица смежности
};

// Функция для создания графа
Graph* createG(int size) {
    Graph* G = new Graph;
    G->size = size;
    G->adjList.resize(size);

    G->adjMatrix.resize(size, std::vector<int>(size, 0));

    // Заполнение графа случайными рёбрами
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (rand() % 2) { // С вероятностью 50% добавляем ребро
                G->adjList[i].push_back(j);
                G->adjList[j].push_back(i);

                G->adjMatrix[i][j] = 1; // Обновление матрицы смежности
                G->adjMatrix[j][i] = 1;
            }
        }
    }
    return G;
}

// Функция для печати графа (список смежности)
void printAdjList(Graph* G) {
    for (int i = 0; i < G->size; i++) {
        printf("%d: ", i);
        for (int j : G->adjList[i]) {
            printf("%d ", j);
        }
        printf("\n");
    }
}

// Функция для печати графа (матрица смежности)
void printAdjMatrix(Graph* G) {
    printf("Матрица смежности: \n");
    for (int i = 0; i < G->size; i++) {
        for (int j = 0; j < G->size; j++) {
            printf("%d ", G->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Функция для обхода в глубину по списку смежности
void DFS_AdjList(int s, Graph* G) {
    std::vector<int> vis(G->size, 0); // Массив для отслеживания посещённых вершин
    std::stack<int> stack; // Стек для хранения вершин
    stack.push(s); // Начинаем с начальной вершины

    printf("Обход графа (список смежности):\n");
    while (!stack.empty()) {
        int v = stack.top(); // Получаем вершину из стека
        stack.pop(); // Удаляем вершину из стека

        if (!vis[v]) { // Если вершина не посещена
            vis[v] = 1; // Помечаем её как посещённую
            printf("%d ", v); // Выводим текущую вершину

            // Добавляем все соседние вершины в стек
            for (int neighbor : G->adjList[v]) { // Обходим в порядке возрастания
                if (!vis[neighbor]) {
                    stack.push(neighbor);
                }
            }
        }
    }
    printf("\n");
}

// Функция для обхода в глубину по матрице смежности
void DFS_AdjMatrix(int s, Graph* G) {
    std::vector<int> vis(G->size, 0); // Массив для отслеживания посещённых вершин
    std::stack<int> stack; // Стек для хранения вершин
    stack.push(s); // Начинаем с начальной вершины

    printf("Обход графа ( матрица смежности):\n");
    while (!stack.empty()) {
        int v = stack.top(); // Получаем вершину из стека
        stack.pop(); // Удаляем вершину из стека

        if (!vis[v]) { // Если вершина не посещена
            vis[v] = 1; // Помечаем её как посещённую
            printf("%d ", v); // Выводим текущую вершину

            // Добавляем все соседние вершины в стек
            for (int neighbor = 0; neighbor < G->size; neighbor++) { // Обходим все вершины
                if (G->adjMatrix[v][neighbor] == 1 && !vis[neighbor]) { // Проверяем смежность
                    stack.push(neighbor);
                }
            }
        }
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(0)); // Инициализация генератора случайных чисел

    int size;
    printf("Введите кол-во вершин: ");
    scanf_s("%d", &size);

    Graph* G = createG(size); // Создаем граф
    printf("Список смежности:\n");
    printAdjList(G); // Печатаем список смежности

    printf("Матрица смежности:\n");
    printAdjMatrix(G); // Печатаем матрицу смежности

    int s;
    printf("Введите начальную вершину (0-%d): ", size - 1);
    scanf_s("%d", &s);
    DFS_AdjList(s, G); // Выполняем обход в глубину по списку смежности
    DFS_AdjMatrix(s, G); // Выполняем обход в глубину по матрице смежности

    // Освобождение памяти
    delete G; // Освобождаем память для графа
    return 0;
}