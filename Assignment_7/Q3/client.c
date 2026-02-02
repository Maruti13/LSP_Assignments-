#include <stdio.h>
#include "display.h"

int main()
{
    char str[100];

    printf("Enter string: ");
    scanf(" %[^\n]", str);

    Display(str);

    return 0;
}
