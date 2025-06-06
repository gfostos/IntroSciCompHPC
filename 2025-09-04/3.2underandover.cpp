#include <iostream>
#include <cstdlib>

typedef float REAL;

int main(int argc, char **argv)
{
    std::cout.precision(16);
    std::cout.setf(std::ios::scientific);
    int N = std::atoi(argv[1]);
    REAL under = 1.0, over = 1.0;

    for (int i = 0; i < N; ++i){
        over *= 2;
        under /= 2;
        std::cout << i << "\t" << under << "\t" << over << "\n";
    }
    
}