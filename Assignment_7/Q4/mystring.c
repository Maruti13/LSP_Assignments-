#include "mystring.h"

int MyStrlen(const char *str)
{
    int count = 0;

    if (str == NULL)
        return -1;   // NULL safety

    while (str[count] != '\0')
    {
        count++;
    }

    return count;
}
