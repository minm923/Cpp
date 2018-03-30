#include <iostream>

void myswap(int* fi, int * se)
{
    int tmp = *fi;
    *fi = *se;
    *se = tmp;
}

void reverse(int* arr, int lo, int hi)
{
    if (!arr || lo < 0 || hi < lo) return ;

    if (lo < hi)
    {
        myswap(arr+lo, arr+hi);        
        reverse(arr, lo+1, hi-1);
    }
}

void reverse(int* arr, int n)
{
    if (!arr || n <=1) return ;    
    reverse(arr, 0, n-1);
}



int main (int argc, char * argv[])
{
    int arr[5] = {1, 2, 3, 4, 5};

    reverse(arr, 5);
    for (int i = 0; i < 5; ++i)
    {
        std::cout << arr[i] << std::endl;
    }

    return 0;
}

