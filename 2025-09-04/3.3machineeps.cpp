#include <iostream>
#include <cstdlib>

typedef float REAL;

int main(int argc, char **argv)
{
    std::cout.precision(16);
    std::cout.setf(std::ios::scientific);
    int N = std::atoi(argv[1]);
    REAL eps = 1.0, one = 1.0;   

    for (int i = 0; i < N; ++i){
        eps /= 2;
        one = 1.0 + eps;
        std::cout << eps << "\t" << one << "\n";
    }
    
}