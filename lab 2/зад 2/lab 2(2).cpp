#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
void shell(int* items, int count)
{

    int i, j, gap, k;
    int x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
    int i, j;
    int x, y;



    i = left; j = right;

    /* выбор компаранда */
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

int compare(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    const int N = 10000;
    int arr[N]; // объявляем массив из 1000 элементов
    int arr2[N];
    int arr3[N];
    srand(time(0));
    // заполняем массив случайными числами
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 100 + 1;

    for (int i = 0; i < N; i++)
    {
        arr2[i] = arr[i];
        arr3[i] = arr[i];
    }
    clock_t start, end; // объявляем переменные для измерения времени выполнения
    
    start = clock(); // начинаем измерять время выполнения
    shell(arr, N);
    end = clock(); // останавливаем измерение времени выполнения

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения shell случайном наборе массива: %f секунд\n", time_taken);

    start = clock(); // начинаем измерять время выполнения
    qs(arr, 0, N-1);
    end = clock(); // останавливаем измерение времени выполнения

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения qs случайном наборе массива: %f секунд\n", time_taken);

    start = clock(); // начинаем измерять время выполнения
    qsort(arr, N, sizeof(int), compare);
    end = clock(); // останавливаем измерение времени выполнения

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения qsort случайном наборе массива: %f секунд\n", time_taken);


    for (int i = 0; i < N; i++)
        arr[i] = i;

    for (int i = 0; i < N; i++)
    {
        arr2[i] = arr[i];
        arr3[i] = arr[i];
    }
    printf("\n");
    
    start = clock(); // начинаем измерять время выполнения
    shell(arr, N);
    end = clock(); // останавливаем измерение времени выполнения

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения shell возростающая последовательность: %f секунд\n", time_taken);

    start = clock(); // начинаем измерять время выполнения
    qs(arr, 0, N - 1);
    end = clock(); // останавливаем измерение времени выполнения

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения qs возростающая последовательность: %f секунд\n", time_taken);

    start = clock(); // начинаем измерять время выполнения
    qsort(arr, N, sizeof(int), compare);
    end = clock(); // останавливаем измерение времени выполнения

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения qsort возростающая последовательность: %f секунд\n", time_taken);


    for (int i = 0; i < N; i++)
        arr[i] = N-i;

    for (int i = 0; i < N; i++)
    {
        arr2[i] = arr[i];
        arr3[i] = arr[i];
    }
    printf("\n");

    start = clock(); // начинаем измерять время выполнения
    shell(arr, N);
    end = clock(); // останавливаем измерение времени выполнения

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения shell убывающая последовательность: %f секунд\n", time_taken);

    start = clock(); // начинаем измерять время выполнения
    qs(arr, 0, N - 1);
    end = clock(); // останавливаем измерение времени выполнения

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения qs убывающая последовательность: %f секунд\n", time_taken);

    start = clock(); // начинаем измерять время выполнения
    qsort(arr, N, sizeof(int), compare);
    end = clock(); // останавливаем измерение времени выполнения

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения qsort убывающая последовательность: %f секунд\n", time_taken);


    for (int i = 0; i < N; i++)
        arr[i] = i < N / 2 ? i:N-i;

    for (int i = 0; i < N; i++)
    {
        arr2[i] = arr[i];
        arr3[i] = arr[i];
    }
    printf("\n");

    start = clock(); // начинаем измерять время выполнения
    shell(arr, N);
    end = clock(); // останавливаем измерение времени выполнения

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения shell возростающая и убывающая последовательность: %f секунд\n", time_taken);

    start = clock(); // начинаем измерять время выполнения
    qs(arr, 0, N - 1);
    end = clock(); // останавливаем измерение времени выполнения

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения qs возростающая и убывающая последовательность: %f секунд\n", time_taken);

    start = clock(); // начинаем измерять время выполнения
    qsort(arr, N, sizeof(int), compare);
    end = clock(); // останавливаем измерение времени выполнения

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения qsort возростающая и убывающая последовательность: %f секунд\n", time_taken);
    return(0);
}
