#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <stack>

struct Graph {
    int size;
    std::vector<std::vector<int>> adjList; // Список смежности
};

// Функция для создания графа
Graph* createG(int size) {
    Graph* G = new Graph;
    G->size = size;
    G->adjList.resize(size);

    // Заполнение графа случайными рёбрами
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (rand() % 2) { // С вероятностью 50% добавляем ребро
                G->adjList[i].push_back(j);
                G->adjList[j].push_back(i);
            }
        }
    }
    return G;
}

// Функция для печати графа
void printG(Graph* G) {
    for (int i = 0; i < G->size; i++) {
        printf("%d: ", i);
        for (int j : G->adjList[i]) {
            printf("%d ", j);
        }
        printf("\n");
    }
}

// Функция для обхода в глубину
void DFS(int s, Graph* G) {
    std::vector<int> vis(G->size, 0); // Массив для отслеживания посещённых вершин
    std::stack<int> stack; // Стек для хранения вершин
    stack.push(s); // Начинаем с начальной вершины

    while (!stack.empty()) {
        int v = stack.top(); // Получаем вершину из стека
        stack.pop(); // Удаляем вершину из стека

        if (!vis[v]) { // Если вершина не посещена
            vis[v] = 1; // Помечаем её как посещённую
            printf("%d ", v); // Выводим текущую вершину

            // Добавляем все соседние вершины в стек
            for (int i = G->adjList[v].size() - 1; i >= 0; i--) { // Обходим в обратном порядке для правильного порядка обхода
                int neighbor = G->adjList[v][i];
                if (!vis[neighbor]) {
                    stack.push(neighbor);
                }
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(0)); // Инициализация генератора случайных чисел

    int size;
    printf("Введите кол-во вершин: ");
    scanf_s("%d", &size);

    Graph* G = createG(size); // Создаем граф
    printf("Список смежности:\n");
    printG(G); // Печатаем список смежности

    int s;
    printf("Введите начальную вершину (0-%d): ", size - 1);
    scanf_s("%d", &s);
    printf("Обход графа:\n");
    DFS(s, G); // Выполняем обход в глубину

    // Освобождение памяти
    delete G; // Освобождаем память для графа

    return 0;
}