#include <iostream>
#include <windows.h>
int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int findMin(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int size;
    std::cout << "Введите размер массива: ";
    std::cin >> size;

    int* arr = new int[size];
    std::cout << "Введите элементы массива: ";
    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }

    int max = findMax(arr, size);
    int min = findMin(arr, size);

    int diff = max - min;

    std::cout << "Разница между максимальным и минимальным элементами: " << diff << std::endl;

    delete[] arr;
    return 0;
}