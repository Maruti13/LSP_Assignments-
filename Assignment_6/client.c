// client.c

#include <stdio.h>
#include <dlfcn.h>

int main()
{
    void *handle;
    int (*add)(int,int);
    int (*sub)(int,int);

    handle = dlopen("./libmath.so", RTLD_LAZY);
    if (!handle)
    {
        printf("dlopen error: %s\n", dlerror());
        return 1;
    }

    add = dlsym(handle, "Addition");
    sub = dlsym(handle, "Substraction");

    printf("Addition: %d\n", add(10, 5));
    printf("Substraction: %d\n", sub(10, 5));

    dlclose(handle);
    return 0;
}
