// Without full path → loader searches:
// a] LD_LIBRARY_PATH
// b] /lib, /usr/lib

// If library not found → dlopen fails
#include <stdio.h>
#include <dlfcn.h>

int main()
{
    void *h = dlopen("libmath.so", RTLD_LAZY);
    if (!h)
        printf("Error: %s\n", dlerror());
    else
        printf("Library loaded successfully\n");

    dlclose(h);
    return 0;
}
