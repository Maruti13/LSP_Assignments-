#include <stdio.h>
#include <dlfcn.h>

int main()
{
    void *h = dlopen("./libarith.so", RTLD_LAZY);
    int (*fp[3])(int,int);

    fp[0] = dlsym(h,"add");
    fp[1] = dlsym(h,"sub");
    fp[2] = dlsym(h,"mul");

    for(int i=0;i<3;i++)
        printf("Addr: %p Result: %d\n", fp[i], fp[i](6,2));

    dlclose(h);
    return 0;
}
