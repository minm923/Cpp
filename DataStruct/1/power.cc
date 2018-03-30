#include <iostream>

int pow2(int n)
{
    if (n < 0) return -1;

    if (0 == n)
    {
        return 1;
    }
    else if (1 == n)
    {
        return 2;
    }
    else
    {
        if (0 == (n & 1))
        {
            return (pow2(n>>1)) << 1;
        }
        else
        {
            return (pow2(n>>1) << 1) * 2;
        }
    }
}

int main (int argc, char * argv[])
{
    std::cout << pow2(1) << std::endl;
    std::cout << pow2(2) << std::endl;
    std::cout << pow2(3) << std::endl;

    return 0;
}

