#include <stdio.h>
#include "mystring.h"

int main()
{
    char str[100];
    int length;

    printf("Enter string: ");
    scanf(" %[^\n]", str);

    length = MyStrlen(str);

    if (length == -1)
        printf("NULL string passed\n");
    else
        printf("String length: %d\n", length);

    return 0;
}

