#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <iostream>
// Структура для представления узла в очереди
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Структура для представления очереди
typedef struct {
    Node* front;
    Node* rear;
} Queue;

// Функция для инициализации очереди
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// Функция для добавления элемента в очередь
void enqueue(Queue* q, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = node;
    }
    else {
        q->rear->next = node;
        q->rear = node;
    }
}

// Функция для удаления элемента из очереди
int dequeue(Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return -1;
    }
    int data = q->front->data;
    Node* node = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(node);
    return data;
}

// Функция для создания графа в виде матрицы смежности
int** createG(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            G[i][j] = rand() % 2;
            if (i == j) G[i][j] = 0;
            G[j][i] = G[i][j];
        }
    }
    return G;
}

// Функция для печати графа
void printG(int** G, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
}

// Функция для обхода в ширину с использованием стандартной очереди
void BFS_std(int** G, int size, int* vis, int s) {
    std::queue<int> q;
    q.push(s);
    vis[s] = 1;
    while (!q.empty()) {
        s = q.front();
        printf("%d ", s);
        q.pop();
        for (int i = 0; i < size; i++) {
            if (G[s][i] == 1 && vis[i] == 0) {
                q.push(i);
                vis[i] = 1;
            }
        }
    }
}

// Функция для обхода в ширину с использованием очереди, реализованной самостоятельно
void BFS_custom(int** G, int size, int* vis, int s) {
    Queue q;
    initQueue(&q);
    enqueue(&q, s);
    vis[s] = 1;
    while (q.front != NULL) {
        s = dequeue(&q);
        printf("%d ", s);
        for (int i = 0; i < size; i++) {
            if (G[s][i] == 1 && vis[i] == 0) {
                enqueue(&q, i);
                vis[i] = 1;
            }
        }
    }
}

// Основная функция
int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL)); // Инициализируем генератор случайных чисел

    int size;
    printf("Введите кол-во вершин: ");
    scanf_s("%d", &size);

    int** G = createG(size);
    printG(G, size);

    int* vis = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) vis[i] = 0;

    int s;
    printf("Введите начальную вершину: ");
    scanf_s("%d", &s);

    // Обход с использованием стандартной очереди
    printf("Обход графа с использованием стандартной очереди:\n");
    clock_t start = clock();
    BFS_std(G, size, vis, s);
    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nВремя выполнения: %f секунд\n", time_taken);

    // Сбросим массив vis для следующего обхода
    for (int i = 0; i < size; i++) vis[i] = 0;

    // Обход с использованием очереди, реализованной самостоятельно
    printf("Обход графа с использованием очереди:\n");
    start = clock();
    BFS_custom(G, size, vis, s);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nВремя выполнения (пользовательская очередь): %f секунд\n", time_taken);

    // Освобождение памяти
    for (int i = 0; i < size; i++) {
        free(G[i]);
    }
    free(G);
    free(vis);

    return 0;
}