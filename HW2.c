#include <stdio.h>
#include <stdlib.h>

int max(int, int);

struct order
{
    int id, start, end;
};
typedef struct order order;

int main(void)
{
    int n, i, j, min_bound, max_bound;
    scanf("%d", &n);
    order data[n];
    for (i = 0; i < n; i++)
    {
        data[i].id = i + 1;
        scanf("%d %d", &data[i].start, &data[i].end);
    }
    scanf("%d %d", &min_bound, &max_bound);

    for (i = 1; i < n; i++)
    {
        order temp = data[i];
        for (j = i; j > 0 && data[j].end < data[j - 1].end; j--)
        {
            data[j] = data[j - 1];
            data[j - 1] = temp;
        }
    }

    int cutoff = min_bound - 1;
    int table[n + 1][max_bound - min_bound + 2];
    order *ptr;
    for (i = min_bound - 1; i <= max_bound; i++)
    {
        table[0][i - cutoff] = 0;
    }
    for (i = 1; i <= n; i++)
    {
        table[i][0] = 0;
        for (j = min_bound; j <= max_bound; j++)
        {
            ptr = &data[i - 1];
            if (ptr->start < min_bound || ptr->end > max_bound)
            {
                table[i][j - cutoff] = table[i - 1][j - cutoff];
            }
            else if (j < ptr->end)
            {
                table[i][j - cutoff] = table[i - 1][j - cutoff];
            }
            else
            {
                int value = ptr->end - ptr->start;
                table[i][j - cutoff] = max(table[i - 1][j - cutoff], table[i - 1][(ptr->start) - cutoff] + value);
            }
        }
    }
    printf("%d\n", table[n][max_bound - cutoff]);
    return 0;
}

int max(int n1, int n2)
{
    if (n1 > n2)
    {
        return n1;
    }
    else
    {
        return n2;
    }
}