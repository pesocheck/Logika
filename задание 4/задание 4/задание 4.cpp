#include <iostream>
#include <windows.h>




int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    const int size=5;
    int sum=0;
    int arr[size][size];
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            arr[i][j] = rand() % 10;
        }
    }
    printf("Полученный массив: \n");

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
    
    for (int i = 0; i < size; i++) {
        sum += arr[i][0];
    }
    
    printf("Сумма элементов 0-ого столбца: %d", sum);
    return 0;
}
