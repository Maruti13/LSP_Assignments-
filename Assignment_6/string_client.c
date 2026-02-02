#include <stdio.h>
#include <dlfcn.h>

int main()
{
    char str[100];
    scanf("%s", str);

    void *h = dlopen("./libstring.so", RTLD_LAZY);

    int (*l)(char*) = dlsym(h,"lower");
    int (*u)(char*) = dlsym(h,"upper");
    int (*d)(char*) = dlsym(h,"digit");

    printf("Lower: %d\nUpper: %d\nDigits: %d\n",
           l(str), u(str), d(str));

    dlclose(h);
    return 0;
}
