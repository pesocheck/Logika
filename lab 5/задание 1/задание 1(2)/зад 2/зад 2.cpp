#include<stdio.h>
#include<random>

int main()
{
    setlocale(LC_ALL, "Rus");
    int n = 10, ** G = NULL, size = 0;
    printf("Введите кол-во вершин");
    scanf_s("%d", &n);
    G = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        G[i] = (int*)malloc(n * sizeof(int));
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            G[i][j] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {

            G[i][j] = rand() % 2;
            G[j][i] = G[i][j];
        }

    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            printf("%d ", G[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            size += G[i][j];
        }
    }
    printf("Размер = %d \n", size);


    return 0;
}
