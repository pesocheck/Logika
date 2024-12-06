#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** createG(int size) {
    int** G = new int*[size];

    for (int i = 0; i < size; i++) {
        G[i] = new int[size];
    }
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

int** delV(int** G, int size, int v) {
    int** Gtemp = new int* [size - 1];
    for (int i = 0; i < size - 1; i++) {
        Gtemp[i] = new int [size - 1];
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i < v && j < v) {
                Gtemp[i][j] = G[i][j];
            }
            else if (i > v && j > v) {
                Gtemp[i - 1][j - 1] = G[i][j];
            }
            else if (i > v && j < v) {
                Gtemp[i - 1][j] = G[i][j];
            }
            else if (i < v && j > v) {
                Gtemp[i][j - 1] = G[i][j];
            }
        }
    }

    for (int i = 0; i < size; i++) {
        delete [] G[i];
    }
    delete[] G;
    return Gtemp;
}

void unionV(int** G, int* size, int v1, int v2) {
    for (int i = 0; i < *size; i++) {
        if (G[v2][i] == 1) {
            G[v1][i] = 1; // Объединяем вершины
            G[i][v1] = 1; // Объединяем вершины
        }
    }

    G = delV(G, *size, v2);
    (*size)--; // Уменьшаем размер графа
    printG(G, *size); // Печатаем граф после объединения
}

int** countrE(int** G, int* size, int v1, int v2) {
    // Проверяем есть ли ребро
    if (G[v1][v2] != 1) {
        printf("Ребра нет\n");
        return G;
    }
    else {
        for (int i = 0; i < *size; i++) {
            if (G[v2][i] == 1) {
                G[v1][i] = 1; // Стягиваем ребро
                G[i][v1] = 1; // Стягиваем ребро
            }
        }
        G = delV(G, *size, v2);
        (*size)--; // Уменьшаем размер графа
        printG(G, *size); // Печатаем граф после стягивания
    }
    return G;
}

int** splitVertex(int** G, int* size, int v) {
    int newSize = *size + 1; // Увеличиваем размер графа на 1
    int** Gtemp = new int* [newSize];
    for (int i = 0; i < newSize; i++) {
        Gtemp[i] = new int [newSize];
    }

    // Копируем старую матрицу смежности в новую
    for (int i = 0; i < newSize - 1; i++) {
        for (int j = 0; j < newSize - 1; j++) {
            if (i < v && j < v) {
                Gtemp[i][j] = G[i][j];
            }
            else if (i < v && j > v) {
                Gtemp[i][j] = G[i][j - 1];
            }
            else if (i > v && j < v) {
                Gtemp[i][j] = G[i - 1][j];
            }
            else {
                Gtemp[i][j] = G[i - 1][j - 1];
            }
        }
    }

    // Добавляем новые рёбра для новой вершины
    for (int i = 0; i < newSize - 1; i++) {
        Gtemp[v][i] = G[v][i]; // Соединяем новую вершину с исходной
        Gtemp[i][v] = G[i][v]; // Соединяем исходную вершину с новой
    }
    Gtemp[v][v] = 0; // Нет петель для новой вершины

    // Освобождаем память старого графа
    for (int i = 0; i < *size; i++) {
        delete [] G[i];
    }
    delete [] G;
    *size = newSize; // Обновляем размер графа
    return Gtemp;
}

int main(void) {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL)); // Инициализация генератора случайных чисел
    int nG1 = 3, nG2 = 5;
    printf("Введите количество вершин G1\n");
    scanf_s("%d", &nG1);
    printf("\nВведите количество вершин G2\n");
    scanf_s("%d", &nG2);
    int** G1 = createG(nG1);
    int** G2 = createG(nG2);
    printf("\nГраф G1\n");
    printG(G1, nG1);

    printf("Граф G2\n");
    printG(G2, nG2);

    int operation, v1, v2;
    printf("Выберите операцию:\n1. Отождествление вершин\n2. Стягивание ребра\n3. Расщепление вершины\n");
    scanf_s("%d", &operation);

    switch (operation) {
    case 1:
        printf("Введите номера вершин для отождествления (v1, v2):\n");
        scanf_s("%d %d", &v1, &v2);
        unionV(G2, &nG2, v1, v2);
        break;
    case 2:
        printf("Введите номера вершин для стягивания (v1, v2):\n");
        scanf_s("%d %d", &v1, &v2);
        G2 = countrE(G2, &nG2, v1, v2);
        break;
    case 3:
        printf("Введите номер вершины для расщепления:\n");
        scanf_s("%d", &v1);
        G2 = splitVertex(G2, &nG2, v1);
        printf("Граф G2 после расщепления вершины %d\n", v1);
        printG(G2, nG2);
        break;
    default:
        printf("Неверная операция\n");
        break;
    }

    // Освобождение памяти
    for (int i = 0; i < nG1; i++) {
        delete [] G1[i];
    }
    delete [] G1;

    for (int i = 0; i < nG2; i++) {
		delete[] G2[i];
    }
    free (G2);

    return 0;
}