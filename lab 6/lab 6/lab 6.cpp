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

int **delV(int **G, int size, int v){
    int **Gtemp = createG(size-1);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
             if (i < v && j < v) Gtemp [i][j] = G[i][j];
             if (i > v && j > v) Gtemp [i-1][j-1] = G[i][j];
             if (i > v && j < v) Gtemp [i-1][j] = G[i][j];
             if (i < v && j > v) Gtemp [i][j-1] = G[i][j];
        }
    } 
    
    for(int i = 0; i < size; i++){
        free(G[i]);
    }
    free(G);
        G = NULL;
//    printf("Удаленный\n");
//    printG(G,size);
    return Gtemp;
}

// отождествление
void unionV(int **G, int size, int v1, int v2){
    
        for(int i = 0; i < size; i++){
            if(G[v2][i] == 1){
             G[v1][i] =  G[v2][i];
             G[i][v1] =  G[i][v2];
        }
    }
    
    
    
    G = delV(G, size, v2);
    printG(G, size);
    return;
}
//стягивание ребра
int **countrE(int **G, int size, int v1, int v2){
    //проверяем есть ли ребро
    if (G[v1][v2] != 1){
        printf("Ребра нет");
        return G;
    }
    else{
        for(int i = 0; i < size; i++){
            if(G[v2][i] == 1){
             G[v1][i] =  G[v2][i];
             G[i][v1] =  G[i][v2];
        }
    }
    G = delV(G, size, v2);
    printG(G, size);
}
return G;
}


int **splitV(int **G, int size, int v){
    int **Gtemp = createG(size+1);
    
    for(int i = 0; i < size; i++){
        Gtemp[i][size] = G[i][v];
        Gtemp[size][i] = G[v][i];
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            Gtemp[i][j] = G[i][j];
        }
    }
    Gtemp[v][v] = 0;
    Gtemp[size][size] = 0;
    
    for(int i = 0; i < size; i++){
        free(G[i]);
    }
    free(G);
    G = NULL;
    
    return Gtemp;
}

int **unionG(int **G1, int **G2, int size1, int size2){
    int sizemax = (size1>size2)?size1:size2;
    int sizemin = (size1<size2)?size1:size2;
    int **Gmax = (size1>size2)?G1:G2;
    int **Gmin = (size1<size2)?G1:G2;
    int **Gtemp = createG(sizemax);
    
    /*if(size1>size2){
        sizemax = size1;
    }
    else{
        sizemax = size2;
    }*/
    
    for(int i = 0; i < sizemin; i++){
        for(int j = 0; j<sizemin; j++){
            Gtemp[i][j] = Gmin[i][j] | Gmax[i][j];
        }
    }
    
   for(int i = 0; i < sizemax; i++){
        for(int j = sizemin; j < sizemax; j++){
            Gtemp[i][j] = Gmax[i][j];
            Gtemp[j][i] = Gtemp[i][j];
        }
   }
    return Gtemp;
}

int **intersectG(int **G1, int **G2, int size1, int size2){
    int sizemin = (size1<size2)?size1:size2;
    int **Gtemp = createG(sizemin);
    
    for(int i = 0; i < sizemin; i++){
        for(int j = 0; j < sizemin; j++){
            Gtemp[i][j] = G1[i][j]&G2[i][j];
        }
    }
    return Gtemp;
}

int **xorG(int **G1, int **G2, int size1, int size2){
    int sizemax = (size1>size2)?size1:size2;
    int sizemin = (size1<size2)?size1:size2;
    int **Gmax = (size1>size2)?G1:G2;
    int **Gmin = (size1<size2)?G1:G2;
    int **Gtemp = createG(sizemax-sizemin);
    
    for(int i = sizemin; i<sizemax; i++){
        for(int j = sizemin; j<sizemax; j++){
            Gtemp[i-sizemin][j-sizemin] = Gmax[i][j];
        }
    }
    return Gtemp;
}

int main (void) {
	setlocale(LC_ALL, "Rus");
    int nG1 = 3, nG2 = 5;
    printf("Введите количество вершин G1\n");
    scanf("%d", &nG1);
    printf("\nВведите количество вершин G2\n");
    scanf("%d", &nG2);
    int **G1 = createG(nG1);
    int **G2 = createG(nG2);
    printf("\nГраф G1\n");
    printG(G1, nG1);
    
    printf("\nГраф G2\n");
    printG(G2, nG2);

G1 = splitV(G1, nG1, 2);
nG1++;
printf("\nРасщепленние вершины \n");
printG(G1, nG1);

int **G3 = unionG(G1, G2, nG1, nG2);
int nG3 = (nG1>nG2)?nG1:nG2;
printf("\nОбъединиение графов\n");
printG(G3, nG3);

int **G4 = intersectG(G1, G2, nG1, nG2);
int nG4 = (nG1<nG2)?nG1:nG2;
printf("\nПересечение графов\n");
printG(G4, nG4);

int **G5 = xorG(G1, G2, nG1, nG2);
int nG5 = abs(nG2-nG1);
printf("\nКольцевая сумма графов\n");
printG(G5, nG5);

G2 = delV(G2, nG2, 2);
nG2--;
printf("\nГраф G2del\n");
printG(G2,nG2);

unionV(G2, nG2, 2,3);
nG2--;
printG(G2, nG2);

G2 = countrE(G2, nG2, 2,3);
nG2--;
printG(G2, nG2);
return 0;
}
