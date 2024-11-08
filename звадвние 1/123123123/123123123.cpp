#include <iostream>
#include <stdio.h>
#include <cstdlib>

int **createG(int size){
    int **G = NULL;
    G = (int**)malloc(size*sizeof(int *));
    for(int i = 0; i < size; i++){
        G[i] = (int *)malloc(size*sizeof(int));
    }
    for(int i = 0; i < size; i++){
        for (int j = i; j < size; j++){
            G[i][j] = rand()%2;
            if(i == j) G[i][j] = 0;
            G[j][i] = G[i][j];
        }
    }
    return G;
}

void printG(int **G, int size)
{
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
    return;
}
int **G=NULL, size=5, vis[5]={0};
void DFS(int s,int **G, int size, int *vis){
    vis[s]=1;
    printf("%d ", s);
    for(int i=0; i<size; i++){
        if(G[s][i]==1&&vis[i]==0){
            DFS(i, G, size, vis);
        }
    }
}



int main () {
	setlocale(LC_ALL, "Rus");
    int **G=NULL;
    int *vis=NULL;
    int size=5;
    int s=1;
    printf("¬ведите кол-во вершин: ");
    scanf("%d", &size);
    G=createG(size);
    printG(G, size);
    printf("¬ведите начальную вершину: ");
    
    vis= (int*)malloc(size*sizeof(int));

    scanf("%d", &s);
    printf("ќбход графа:\n");
    DFS(s, G, size, vis);

return 0;
}







