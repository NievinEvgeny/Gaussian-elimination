#include <stdio.h>
#include <stdlib.h>
#define n 3 //разрядность матрицы

int main()
{
    int i, j, k;
    double x;
    double a[n][n + 1];
    double res[n];
    FILE* in;
    FILE* out;
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");

    if (in == NULL || out == NULL)
    {
        printf("ошибка открытия файла\n");
        return -1;
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n + 1; j++)
        {
            fscanf(in, "%lf", &a[i][j]);
        }
    }

    for (i = 0; i < n; i++) //инициализация результирующего массива нулями
    {
        res[i] = 0;
    }

    for (k = 0; k < n; k++)
    {
        x = abs(a[k][k]);
        i = k;
        for (j = k + 1; j < n; j++)
        {
            if (abs(a[j][k]) > x)
            {
                i = j;
                x = abs(a[j][k]);
            }
        }

        if (x == 0) //деление на ноль
        {
            printf("Система линейных уравнений не имеет решений\n");
            return -1;
        }

        if (i != k) //меняем строки
        {
            for (j = k; j < n + 1; j++)
            {
                x = a[k][j];
                a[k][j] = a[i][j];
                a[i][j] = x;
            }
        }

        for (i = k + 1; i < n; i++) //Преобразуем строки
        {
            x = a[i][k] / a[k][k];      //Коэффициент для строки
            for (j = k; j < n + 1; j++) //Преобразуем элементы строки
            {
                a[i][j] -= x * a[k][j];
            }
        }
    }

    for (i = n - 1; i >= 0; i--)
    {
        x = a[i][n];
        for (j = n - 1; j >= i; j--)
        {
            if (j > i)
            {
                x -= res[j] * a[i][j];
            }
            if (j == i)
            {
                x /= a[i][j];
            }
        }
        res[i] = x;
    }

    for (i = 0; i < n; i++)
    {
        fprintf(out, "x%d = %lf\n", i + 1, res[i]);
    }
}