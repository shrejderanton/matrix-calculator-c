#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#define MAX 50
void info()
{
    system("cls");
    printf("========================================\n");
    printf("      MATRIX CALCULATOR\n");
    printf("========================================\n\n");
    printf("Course project:\n");
    printf("\"Calculator for matrix operations\"\n\n");
    printf("Author: Shreider Anton\n");
    printf("Group: E-64/25\n\n");
    printf("Program functions:\n");
    printf("- addition of matrices\n");
    printf("- subtraction of matrices\n");
    printf("- multiplication of matrices\n");
    printf("- transpose\n");
    printf("- multiplication by scalar\n\n");
    printf("Controls:\n");
    printf("UP / DOWN - move menu\n");
    printf("ENTER - select\n\n");
    printf("Press any key...");
    _getch();
}
void pause_screen()
{
    printf("\nPress any key...");
    _getch();
}
void slozhenie(int a[MAX][MAX], int b[MAX][MAX], int c[MAX][MAX], int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            c[i][j] = a[i][j] + b[i][j];
}
void vichitanie(int a[MAX][MAX], int b[MAX][MAX], int c[MAX][MAX], int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            c[i][j] = a[i][j] - b[i][j];
}
void umnozhenie(int a[MAX][MAX], int b[MAX][MAX], int c[MAX][MAX], int n, int m, int k)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < k; j++)
        {
            c[i][j] = 0;

            for (int p = 0; p < m; p++)
                c[i][j] += a[i][p] * b[p][j];
        }
}
void transponirovanie(int a[MAX][MAX], int c[MAX][MAX], int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            c[j][i] = a[i][j];
}
void umnozhenie_skalar(int a[MAX][MAX], int c[MAX][MAX], int n, int m, int s)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            c[i][j] = a[i][j] * s;
}
void print(int a[MAX][MAX], int n, int m)
{
    printf("\nResult:\n\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%4d ", a[i][j]);

        printf("\n");
    }
    printf("\n");
}
void create_matrix(int a[MAX][MAX], int n, int m)
{
    int type = 0;
    int ch;

    char *items[] =
        {
            "manual",
            "zero",
            "identity",
            "random"};
    while (1)
    {
        system("cls");
        printf("=== CREATE MATRIX ===\n\n");
        for (int i = 0; i < 4; i++)
        {
            if (i == type)
                printf("-> %s\n", items[i]);
            else
                printf("   %s\n", items[i]);
        }
        ch = _getch();
        if (ch == 224)
        {
            ch = _getch();
            if (ch == 72)
            {
                type--;
                if (type < 0)
                    type = 3;
            }
            if (ch == 80)
            {
                type++;
                if (type > 3)
                    type = 0;
            }
        }
        if (ch == 13)
            break;
    }
    system("cls");
    switch (type)
    {
    case 0:
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                printf("a[%d][%d] = ", i, j);
                scanf("%d", &a[i][j]);
            }

        break;
    case 1:
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                a[i][j] = 0;

        break;
    case 2:
        if (n != m)
        {
            printf("Only NxN matrix!\n");
            pause_screen();
            return;
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i][j] = (i == j);
        break;
    case 3:
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                a[i][j] = rand() % 10;
        break;
    }
}
int read_size(const char *name, int *r, int *c)
{
    printf("Size of matrix %s (rows cols): ", name);
    scanf("%d %d", r, c);
    if (*r <= 0 || *c <= 0 || *r > MAX || *c > MAX)
    {
        printf("Error: wrong size\n");
        pause_screen();
        return 0;
    }
    return 1;
}
int menu()
{
    int pos = 0;
    int ch;
    char *items[] =
        {
            "slozhenie",
            "vichitanie",
            "umnozhenie",
            "transpose",
            "umnozhenie na skalar",
            "exit"};
    while (1)
    {
        system("cls");
        printf("=== MATRIX CALCULATOR ===\n\n");
        for (int i = 0; i < 6; i++)
        {
            if (i == pos)
                printf("-> %s\n", items[i]);
            else
                printf("   %s\n", items[i]);
        }
        ch = _getch();
        if (ch == 224)
        {
            ch = _getch();
            if (ch == 72)
            {
                pos--;
                if (pos < 0)
                    pos = 5;
            }
            if (ch == 80)
            {
                pos++;
                if (pos > 5)
                    pos = 0;
            }
        }
        if (ch == 13)
            return pos + 1;
    }
}
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    info();
    printf("Program started successfully!");
    int a[MAX][MAX];
    int b[MAX][MAX];
    int c[MAX][MAX];
    int nA, mA;
    int nB, mB;
    int s;
    int vibor;
    srand(time(NULL));
    while (1)
    {
        vibor = menu();
        switch (vibor)
        {
        case 1:
            system("cls");
            if (!read_size("A", &nA, &mA))
                continue;
            if (!read_size("B", &nB, &mB))
                continue;
            if (nA != nB || mA != mB)
            {
                printf("Error: matrix sizes are not equal\n");
                pause_screen();
                continue;
            }
            printf("\nMatrix A\n");
            create_matrix(a, nA, mA);
            printf("\nMatrix B\n");
            create_matrix(b, nB, mB);
            slozhenie(a, b, c, nA, mA);
            print(c, nA, mA);
            pause_screen();
            break;
        case 2:
            system("cls");
            if (!read_size("A", &nA, &mA))
                continue;
            if (!read_size("B", &nB, &mB))
                continue;
            if (nA != nB || mA != mB)
            {
                printf("Error: matrix sizes are not equal\n");
                pause_screen();
                continue;
            }
            printf("\nMatrix A\n");
            create_matrix(a, nA, mA);
            printf("\nMatrix B\n");
            create_matrix(b, nB, mB);
            vichitanie(a, b, c, nA, mA);
            print(c, nA, mA);
            pause_screen();
            break;
        case 3:
            system("cls");
            if (!read_size("A", &nA, &mA))
                continue;
            if (!read_size("B", &nB, &mB))
                continue;
            if (mA != nB)
            {
                printf("Error: columns of A != rows of B\n");
                pause_screen();
                continue;
            }
            printf("\nMatrix A\n");
            create_matrix(a, nA, mA);
            printf("\nMatrix B\n");
            create_matrix(b, nB, mB);
            umnozhenie(a, b, c, nA, mA, mB);
            print(c, nA, mB);
            pause_screen();
            break;
        case 4:
            system("cls");
            if (!read_size("A", &nA, &mA))
                continue;
            printf("\nMatrix A\n");
            create_matrix(a, nA, mA);
            transponirovanie(a, c, nA, mA);
            print(c, mA, nA);
            pause_screen();
            break;
        case 5:
            system("cls");
            if (!read_size("A", &nA, &mA))
                continue;
            printf("Scalar: ");
            scanf("%d", &s);
            printf("\nMatrix A\n");
            create_matrix(a, nA, mA);
            umnozhenie_skalar(a, c, nA, mA, s);
            print(c, nA, mA);
            pause_screen();
            break;
        case 6:
            system("cls");
            printf("Exit...\n");
            return 0;
        }
    }
}