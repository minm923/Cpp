#include <iostream>

// 循环
int Sum1(int* arr, int n)
{
    if (!arr || n <= 0 )
        return -1;

    int sum = 0;

    for (int i=0; i<n; ++i)
    {
        sum += arr[i];
    }

    return sum;
}

// 减治
int sum2(int* arr, int hi)
{
    if (!arr || hi < 0 )
        return -1;
    
    if (0 == hi)
    {
        return *arr;
    }
    else
    {
        return arr[hi] + sum2(arr, hi-1);
    }
}
int Sum2(int *arr, int n)
{
    if (!arr || n <= 0 )
        return -1;
    
    return sum2(arr, n-1);
}

// 分治
int sum3(int * arr, int lo, int hi);
int Sum3(int *arr, int n)
{
    if ( !arr || n <= 0 )
        return -1;

    return sum3(arr, 0, n-1);
}

int sum3(int * arr, int lo, int hi)
{
    if ( !arr || lo < 0 || lo > hi )
        return -1;

    if (lo == hi)
    {
        return arr[lo];
    }
    else
    {
        int mid = ((hi - lo) >> 1) + lo;// trick + > >>
        //int mid = (hi - lo) / 2 + lo;
        //int mid = (hi + lo) >> 1;
        return sum3(arr, lo, mid) + sum3(arr, mid+1, hi);
    }
}

int main(int argc, char * argv[])
{
    int arr[] = {1, 2, 3, 4, 5};

    std::cout << Sum1(arr, 5) << std::endl;
    std::cout << Sum2(arr, 5) << std::endl;
    std::cout << Sum3(arr, 5) << std::endl;

    return 0;
}

