#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
int main(void)
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    clock_t start, end;

    int i = 0, j = 0, r;
    const int N = 4000;
    int elem_c;

    int** a = new int* [N];
    int** b = new int* [N];
    int** c = new int* [N];

    for (int i = 0; i < N; ++i)
    {
        a[i] = new int[N];
        b[i] = new int[N];
        c[i] = new int[N];
    }

    srand(time(NULL));
    while (i < N)
    {
        while (j < N)
        {
            a[i][j] = rand() % 100 + 1;
            j++;
        }
        i++;
    }
    srand(time(NULL));
    i = 0; j = 0;
    while (i < N)
    {
        while (j < N)
        {
            b[i][j] = rand() % 100 + 1;
            j++;
        }
        i++;
    }

    start = clock();
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            elem_c = 0;
            for (r = 0; r < N; r++)
            {
                elem_c = elem_c + a[i][r] * b[r][j];
                c[i][j] = elem_c;
            }
        }
    }
    end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения: %f секунд\n", time_taken);

    for (int i = 0; i < N; ++i)
    {
        delete[] a[i];
        delete[] b[i];
        delete[] c[i];
    }

    delete[] a;
    delete[] b;
    delete[] c;

    return(0);
}