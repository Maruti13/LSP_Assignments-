#include <stdio.h>
#include <dlfcn.h>

int main()
{
    void *h = dlopen("./libmath.so", RTLD_LAZY);
    if (!h)
    {
        printf("%s\n", dlerror());
        return 1;
    }

    dlsym(h, "InvalidFunction");
    char *err = dlerror();
    if (err)
        printf("Error: %s\n", err);

    dlclose(h);
    return 0;
}
