//RTLD_LAZY → symbols resolved only when used
//RTLD_NOW → all symbols resolved immediately at dlopen()
#include <stdio.h>
#include <dlfcn.h>

int main()
{
    void *h1 = dlopen("./libmath.so", RTLD_LAZY);
    if (!h1)
        printf("LAZY error: %s\n", dlerror());
    else
        printf("Loaded with RTLD_LAZY\n");

    void *h2 = dlopen("./libmath.so", RTLD_NOW);
    if (!h2)
        printf("NOW error: %s\n", dlerror());
    else
        printf("Loaded with RTLD_NOW\n");

    dlclose(h1);
    dlclose(h2);
    return 0;
}
