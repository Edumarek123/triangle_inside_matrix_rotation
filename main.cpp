#include <iostream>
#include <cmath>

const int n = 5;

int tl_direction_to_angle(int x, int y)
{
    int a = 180 * atan2(x, y) / M_PI;
    return (int)a;
}

int **tl_rotate_2d_matrix(int **m, int n)
{
    int **rotated = (int **)malloc(n * (sizeof(int *)));
    for (int i = 0; i < n; i++)
    {
        rotated[i] = (int *)malloc(n * (sizeof(int)));
    }

    // transpose
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            rotated[i][j] = m[j][i];
        }
    }

    // reverse rows
    int temp;
    int j = 0;
    int k = n - 1;

    for (int i = 0; i < n; i++)
    {
        j = 0;
        k = n - 1;
        while (j < k)
        {
            temp = rotated[i][j];
            rotated[i][j] = rotated[i][k];
            rotated[i][k] = temp;

            j++;
            k--;
        }
    }

    return rotated;
}

void rotate_triangle(int **m, int t, int dx, int dy, int a)
{

    if (a == 0)
    {
        return;
    }

    if (a == -1)
    {
        a = tl_direction_to_angle(-dy, -dx);
        if (a <= 0)
            a = 360 + a;
        a /= 90;
    }
    int **r;

    r = tl_rotate_2d_matrix(m, t);

    for (int c = 0; c < t; c++)
    {
        for (int l = 0; l < t; l++)
        {
            m[c][l] = r[c][l];
        }
    }

    for (int i = 0; i < t; i++)
    {
        free(r[i]);
    }
    free(r);

    rotate_triangle(m, t, dx, dy, a - 1);
}

void coco()
{
    int dx = 0;
    int dy = 1;

    int t = (2 * n) - 1;

    // ALOCA MEMORIA
    int **data = (int **)malloc(t * (sizeof(int *)));
    for (int i = 0; i < (2 * n - 1); i++)
    {
        data[i] = (int *)malloc(t * (sizeof(int)));
    }

    // INICIALIZA COM 0s
    for (int i = 0; i < t; i++)
    {
        for (int j = 0; j < t; j++)
        {
            data[i][j] = 0;
        }
        printf("\n");
    }

    int x;
    int y;

    // POSICIONA TRIANGULO COM 1s
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            x = j - 1;
            y = i - 1;
            data[i - 1][j - 1 + (n - 1)] = 1;
        }
    }
    for (int i = n - 1; i >= 1; i--)
    {
        for (int j = 1; j <= i; j++)
        {
            x = j - 1;
            y = 2 * n - i - 1;
            data[(2 * n) - i - 1][j - 1 + (n - 1)] = 1;
        }
    }

    // ROTACIONA

    printf("\n");
    printf("\n");

    rotate_triangle(data, t, dx, dy, -1);

    // PRINT RESULT
    printf("\n");
    for (int i = 0; i < t; i++)
    {
        for (int j = 0; j < t; j++)
        {
            std::cout << data[i][j] << " ";
        }
        printf("\n");
    }

    // LIMPA MEMORIA
    for (int i = 0; i < t; i++)
    {
        free(data[i]);
    }
    free(data);
}

int main(void)
{
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    coco();
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    return EXIT_SUCCESS;
}
