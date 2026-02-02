/* 
1] dlopen() → loads shared library at runtime

2] dlsym() → searches for symbol inside loaded library

3] dlerror() → returns error message if lookup fails

4] Symbol address printed if found

5] Library unloaded using dlclose()*/
#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char *argv[])
{
    void *handle;
    void *sym_addr;
    char *error;

    if (argc != 3)
    {
        printf("Usage: %s <shared_library_path> <symbol_name>\n", argv[0]);
        return 1;
    }

    // Load shared library
    handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle)
    {
        printf("dlopen error: %s\n", dlerror());
        return 1;
    }

    // Clear any existing error
    dlerror();

    // Lookup symbol
    sym_addr = dlsym(handle, argv[2]);
    error = dlerror();

    if (error != NULL)
    {
        printf("Symbol '%s' not found: %s\n", argv[2], error);
    }
    else
    {
        printf("Symbol '%s' found at address: %p\n", argv[2], sym_addr);
    }

    dlclose(handle);
    return 0;
}
