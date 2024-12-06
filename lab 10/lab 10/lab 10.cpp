#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include<queue>
using namespace std;

int** createG(int size) {
    int** G = NULL;
    G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            G[i][j] = rand() % 15;
            if (i == j) G[i][j] = 0;
            G[j][i] = G[i][j];
        }
    }
    return G;
}

void printG(int** G, int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
    return;
}
//int **G=NULL, size=5, vis[5]={0};
void BFS(int** G, int size, int* dist, int s) {
    queue <int>  q;
    q.push(s);
    dist[s] = 0;
    while (!q.empty()) {
        s = q.front();
        q.pop();
        for (int i = 0; i < size; i++) {
            if (G[s][i] > 0 && dist[i] > dist[s] + G[s][i]) {
                q.push(i);
                dist[i] = dist[s] + G[s][i];
            }
        }
    }

}



int main() {
    setlocale(LC_ALL, "Rus");
    int** G = NULL;
    int* vis = NULL;
    int* dist = NULL;
    int size = 5;
    int s = 1;
    printf("Введите кол-во вершин: ");
    scanf("%d", &size);
    G = createG(size);
    printG(G, size);
    printf("Введите начальную вершину: ");

    //vis= (int*)malloc(size*sizeof(int));
    //for(int i=0; i<size;i++) vis[i]=0;

    dist = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) dist[i] = 120;

    scanf("%d", &s);

    //printf("Обход графа: \n");
    //BFS(G, size, dist, s);

    printf("Поиск расстояний: \n");
    for (int i = 0; i < size; i++)

        BFS(G, size, dist, s);
    for (int i = 0; i < size; i++) {
        printf("Расстояние до %d вершины = %d\n", i, dist[i]);
    }
    return 0;
}






