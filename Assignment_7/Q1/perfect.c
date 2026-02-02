#include "perfect.h"
#include "helper.h"

int IsPerfect(int No)
{
    int sum = SumOfFactors(No);

    if (sum == No)
        return 1;
    else
        return 0;
}
