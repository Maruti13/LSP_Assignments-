#include <stdio.h>
#include <dlfcn.h>

int main()
{
    void *h = dlopen("./libglobal.so", RTLD_LAZY);

    void (*mod)() = dlsym(h, "modify");
    int (*get)() = dlsym(h, "get");
    void (*reset)() = dlsym(h, "reset");

    mod(); mod();
    printf("Value: %d\n", get());

    reset();
    printf("After reset: %d\n", get());

    dlclose(h);
    return 0;
}
