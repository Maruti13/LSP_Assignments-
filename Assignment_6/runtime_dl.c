#include <stdio.h>
#include <dlfcn.h>

int main()
{
    void *handle;
    int (*func)(int,int);

    handle = dlopen("./libmath.so", RTLD_LAZY);
    if (!handle)
    {
        printf("Error: %s\n", dlerror());
        return 1;
    }

    func = dlsym(handle, "Addition");
    if (dlerror() != NULL)
    {
        printf("dlsym error\n");
        return 1;
    }

    printf("Result: %d\n", func(3,4));

    dlclose(handle);
    return 0;
}
