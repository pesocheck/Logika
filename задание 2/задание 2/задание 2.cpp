#include <iostream>
#include <windows.h>




int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int size;
    std::cout << "Введите размер массива: ";
    std::cin >> size;

    int* arr = new int[size];
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
    printf("Полученный массив: ");

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i] );
    }
    printf("\n");
    delete[] arr;
    return 0;
}