#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
// Структура для представления списка смежности
typedef struct {
    int* neighbors;
    int size;
} List;

// Функция для создания графа в виде списков смежности
List* createGraph(int size) {
    List* graph = (List*)malloc(size * sizeof(List));
    for (int i = 0; i < size; i++) {
        graph[i].size = 0;
        graph[i].neighbors = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (rand() % 2) { // Случайное добавление ребра
                graph[i].neighbors[graph[i].size++] = j;
                graph[j].neighbors[graph[j].size++] = i;
            }
        }
    }
    return graph;
}

// Функция для печати графа
void printGraph(const List* graph, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d: ", i);
        for (int j = 0; j < graph[i].size; j++) {
            printf("%d ", graph[i].neighbors[j]);
        }
        printf("\n");
    }
}

// Функция для обхода в ширину
void BFS(const List* graph, int size, int start) {
    int* vis = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) vis[i] = 0;

    int* q = (int*)malloc(size * sizeof(int));
    int q_size = 0;

    q[q_size++] = start;
    vis[start] = 1;

    while (q_size > 0) {
        int s = q[--q_size];
        printf("%d ", s);

        for (int i = 0; i < graph[s].size; i++) {
            int neighbor = graph[s].neighbors[i];
            if (!vis[neighbor]) {
                q[q_size++] = neighbor;
                vis[neighbor] = 1;
            }
        }
    }

    free(q);
    free(vis);
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL)); // Инициализируем генератор случайных чисел

    int size;
    printf("Введите кол-во вершин: ");
    scanf_s("%d", &size);

    List* graph = createGraph(size);
    printGraph(graph, size);

    int start;
    printf("Введите начальную вершину: ");
    scanf_s("%d", &start);

    printf("Обход графа:\n");
    BFS(graph, size, start);

    for (int i = 0; i < size; i++) {
        free(graph[i].neighbors);
    }
    free(graph);

    return 0;
}