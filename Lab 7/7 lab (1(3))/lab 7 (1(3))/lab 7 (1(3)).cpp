#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale>
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int size;
    Node** adjLists;
} Graph;

// Функция для создания графа
Graph* createGraph(int size) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->size = size;
    graph->adjLists = (Node**)malloc(size * sizeof(Node*));

    for (int i = 0; i < size; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// Функция для добавления ребра в граф
void addEdge(Graph* graph, int src, int dest) {
    // Добавляем ребро от src к dest
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Добавляем ребро от dest к src (для неориентированного графа)
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Функция для печати графа
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->size; i++) {
        Node* temp = graph->adjLists[i];
        printf("Соседи вершины %d: ", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Функция для обхода в глубину
void DFS(int vertex, int* visited, Graph* graph) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            DFS(adjVertex, visited, graph);
        }
        temp = temp->next;
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    int size, src, dest;

    printf("Введите количество вершин: ");
    scanf("%d", &size);

    Graph* graph = createGraph(size);

    // Ввод ребер
    printf("Введите количество ребер: ");
    int edges;
    scanf("%d", &edges);
    printf("Введите ребра (src dest):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    // Печать графа
    printGraph(graph);

    // Обход в глубину
    int* visited = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        visited[i] = 0; // Инициализация массива посещенных вершин
    }

    printf("Введите начальную вершину для обхода в глубину: ");
    int startVertex;
    scanf("%d", &startVertex);
    printf("Обход графа:\n");
    DFS(startVertex, visited, graph);

    // Освобождение памяти
    for (int i = 0; i < size; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }
    free(graph->adjLists);
    free(graph);
    free(visited);

    return 0;
}
