#include <stdio.h>
#include "perfect.h"

int main()
{
    int No;

    printf("Enter number: ");
    scanf("%d", &No);

    if (IsPerfect(No))
        printf("%d is a Perfect Number\n", No);
    else
        printf("%d is NOT a Perfect Number\n", No);

    return 0;
}
