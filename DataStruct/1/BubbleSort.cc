#include <iostream>

void myswap(int * a, int * b)
{
    int c = *a;
    *a    = *b;
    *b    = c;
}

void BubbleSort(int * arr, int n)
{
    if (!arr || n <= 0) return ;
    bool sorted = false;

    while (!sorted)
    {
        sorted = true;
        for(int i=1; i<n; ++i)
        {
            if (arr[i-1] > arr[i])
            {
                myswap(arr+i-1, arr+i);
                sorted = true;
            }
        }

        --n;
    }
}

int main (int argc, char * argv[])
{
    int arr[5] = {5, 4, 3, 2, 1};

    BubbleSort(arr, 5);

    for (int i=0; i<5; ++i)
    {
        std::cout << i << std::endl;
    }

    return 0;
}

