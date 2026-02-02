#include <stdio.h>
#include <dlfcn.h>

int main()
{
    void *h = dlopen("./libarith.so", RTLD_LAZY);
    int (*f)(int,int);
    int ch,a,b;

    printf("1.Add 2.Sub 3.Mul 4.Div\n");
    scanf("%d",&ch);
    printf("Enter numbers: ");
    scanf("%d%d",&a,&b);

    if(ch==1) f = dlsym(h,"add");
    else if(ch==2) f = dlsym(h,"sub");
    else if(ch==3) f = dlsym(h,"mul");
    else f = dlsym(h,"div");

    printf("Result: %d\n", f(a,b));
    dlclose(h);
    return 0;
}
