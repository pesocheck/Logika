#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Edge {
    int vertex;
    Edge* next;
};

struct Graph {
    int size;
    Edge** edges;
};

// Функция для создания графа
Graph* createG(int size) {
    Graph* G = new Graph;
    G->size = size;
    G->edges = new Edge * [size];
    for (int i = 0; i < size; i++) {
        G->edges[i] = nullptr;
    }
    return G;
}

// Функция для добавления ребра
void addEdge(Graph* G, int v1, int v2) {
    Edge* edge = new Edge;
    edge->vertex = v2;
    edge->next = G->edges[v1];
    G->edges[v1] = edge;

    edge = new Edge;
    edge->vertex = v1;
    edge->next = G->edges[v2];
    G->edges[v2] = edge;
}

// Функция для печати графа
void printG(Graph* G) {
    for (int i = 0; i < G->size; i++) {
        printf("%d: ", i);
        Edge* edge = G->edges[i];
        while (edge) {
            printf("%d ", edge->vertex);
            edge = edge->next;
        }
        printf("\n");
    }
}

// Функция для удаления вершины
Graph* delV(Graph* G, int v) {
    Graph* Gtemp = createG(G->size - 1);

    for (int i = 0; i < G->size; i++) {
        if (i != v) {
            Edge* edge = G->edges[i];
            while (edge) {
                if (edge->vertex != v) {
                    addEdge(Gtemp, i < v ? i : i - 1, edge->vertex < v ? edge->vertex : edge->vertex - 1);
                }
                edge = edge->next;
            }
        }
    }

    // Освобождаем память старого графа
    for (int i = 0; i < G->size; i++) {
        Edge* edge = G->edges[i];
        while (edge) {
            Edge* temp = edge;
            edge = edge->next;
            delete temp;
        }
    }
    delete[] G->edges;
    delete G;

    return Gtemp;
}

// Функция для отождествления вершин
Graph* unionV(Graph* G, int v1, int v2) {
    if (v1 >= G->size || v2 >= G->size) {
        printf("Ошибка: неверные номера вершин\n");
        return G;
    }

    for (Edge* edge = G->edges[v2]; edge; edge = edge->next) {
        addEdge(G, v1, edge->vertex);
    }
    G = delV(G, v2);
    G->size--; // Уменьшаем размер графа
    printG(G); // Печатаем граф после объединения
    return G;
}

// Функция для стягивания ребра
Graph* countrE(Graph* G, int v1, int v2) {
    // Проверяем есть ли ребро
    bool edgeExists = false;
    for (Edge* edge = G->edges[v1]; edge; edge = edge->next) {
        if (edge->vertex == v2) {
            edgeExists = true;
            break;
        }
    }

    if (!edgeExists) {
        printf("Ребра нет\n");
        return G;
    }
    else {
        for (Edge* edge = G->edges[v2]; edge; edge = edge->next) {
            addEdge(G, v1, edge->vertex);
        }
        G = delV(G, v2);
        G->size--; // Уменьшаем размер графа
        printG(G); // Печатаем граф после стягивания
    }
    return G;
}

// Функция для расщепления вершины
Graph* splitVertex(Graph* G, int v) {
    if (v >= G->size) {
        printf("Ошибка: неверный номер вершины\n");
        return G;
    }

    Graph* Gtemp = createG(G->size + 1);

    // Копируем старые рёбра в новый граф
    for (int i = 0; i < G->size; i++) {
        if (i != v) {
            Edge* edge = G->edges[i while (edge) {
                addEdge(Gtemp, i < v ? i : i + 1, edge->vertex < v ? edge->vertex : edge->vertex + 1);
                edge = edge->next;
            }
        }
    }

    // Добавляем новые рёбра для новой вершины
    for (Edge* edge = G->edges[v]; edge; edge = edge->next) {
        addEdge(Gtemp, G->size, edge->vertex); // Соединяем новую вершину с соседями
    }

    // Освобождаем память старого графа
    for (int i = 0; i < G->size; i++) {
        Edge* edge = G->edges[i];
        while (edge) {
            Edge* temp = edge;
            edge = edge->next;
            delete temp;
        }
    }
    delete[] G->edges;
    delete G;

    return Gtemp;
}

int main(void) {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL)); // Инициализация генератора случайных чисел
    int nG;
    printf("Введите количество вершин графа\n");
    scanf("%d", &nG);
    Graph* G = createG(nG);

    // Заполнение графа случайными рёбрами
    for (int i = 0; i < nG; i++) {
        for (int j = i + 1; j < nG; j++) {
            if (rand() % 2) {
                addEdge(G, i, j);
            }
        }
    }

    printf("Исходный граф:\n");
    printG(G);

    int operation, v1, v2;
    printf("Выберите операцию:\n1. Отождествление вершин\n2. Стягивание ребра\n3. Расщепление вершины\n");
    scanf("%d", &operation);

    switch (operation) {
    case 1:
        printf("Введите номера вершин для отождествления (v1, v2):\n");
        scanf("%d %d", &v1, &v2);
        G = unionV(G, v1, v2);
        break;
    case 2:
        printf("Введите номера вершин для стягивания (v1, v2):\n");
        scanf("%d %d", &v1, &v2);
        G = countrE(G, v1, v2);
        break;
    case 3:
        printf("Введите номер вершины для расщепления:\n");
        scanf("%d", &v1);
        G = splitVertex(G, v1);
        printf("Граф после расщепления вершины %d:\n", v1);
        printG(G);
        break;
    default:
        printf("Неверная операция\n");
        break;
    }

    // Освобождение памяти
    for (int i = 0; i < G->size; i++) {
        Edge* edge = G->edges[i];
        while (edge) {
            Edge* temp = edge;
            edge = edge->next;
            delete temp;
        }
    }
    delete[] G->edges;
    delete G;

    return 0;
}