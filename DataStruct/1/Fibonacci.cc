#include <iostream>

// 二阶常系数差分方程 O(2^n)
int Fibonacci(int n)
{
    if (n <= 0 )
        return -1;

    if (1 == n)
    {
        return 0;
    }
    else if ( 2 == n)
    {
        return 1;
    }
    else
    {
        return Fibonacci(n-1) + Fibonacci(n-2);
    }
}

// 线性递归
int Fi2(int n, int& prev)
{
    return 0;
}

// 迭代
int Fi3(int n)
{
    if (n <= 0 )
        return -1;
    
    int f = 0;
    int g = 1;

    if (1 == n)
    {
        return f;
    }
    else if (2 == n)
    {
        return g;
    }
    else
    {
        n = n - 2;

        while (n--)
        {
            int tmp = f + g;
            f = g;
            g = tmp;
        }
    }

    return g;
}
 
int main (int argc, char * argv[])
{
    std::cout << Fibonacci(5) << std::endl;
    std::cout << Fi3(6) << std::endl;

    return 0;
}
