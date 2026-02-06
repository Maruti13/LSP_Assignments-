#include <stdio.h>
#include "helper.h"

int main()
{
    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    printf("Addition = %d\n", Add(a, b));
    return 0;
}
