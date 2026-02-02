#include <ctype.h>

int lower(char *s)
{
    int c=0;
    while(*s) 
    if(islower(*s++)) 
    c++; 
return c; 
}

int upper(char *s)
{ 
    int c=0; 
    while(*s) 
    if(isupper(*s++))
    c++; 
return c; 
}

int digit(char *s)
{ 
    int c=0; 
    while(*s) 
    if(isdigit(*s++))
    c++; 
return c; 
}
