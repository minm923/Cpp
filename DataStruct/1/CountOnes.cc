#include <iostream>

// log(n)

int CountOnes(int n)
{
    if (n < 0) return -1;

    int sum = 0;
    while (n)
    {
        sum += (n & 1);
        n >>= 1;
    }

}

int main (int argc, char * argv[])
{

    return 0;
}
