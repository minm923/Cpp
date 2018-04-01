#include <iostream>

int sqr(int a)
{
    return a * a;
}

int pow2(int n)
{
    if (n < 0) return -1;

    if (0 == n)
    {
        return 1;
    }
    else
    {
        return (0 == (n & 1)) ? sqr(pow2(n>>1)) : sqr(pow2(n>>1)) * 2; // trick
    }
}

int main (int argc, char * argv[])
{
    std::cout << pow2(1) << std::endl;
    std::cout << pow2(2) << std::endl;
    std::cout << pow2(3) << std::endl;

    return 0;
}
