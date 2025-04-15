#include <iostream>
#include <cmath>

typedef float REAL;

REAL sum1(int k);
REAL sum2(int k);

int main (void){
    std::cout.precision(7);
    std::cout.setf(std::ios::scientific);

    for (int k = 1; k <= 100; k++){
        REAL delta = std::fabs(1.0 - (sum1(k) / sum2(k)));
        std::cout << k << "\t" << sum1(k) << "\t" << sum2(k) << "\t" << delta << "\n";
    }
}

REAL sum1(int k){
    REAL suma1 = 0.0;
    for (int i = 1; i <= k; i++){
        suma1 += 1.0/i;
    }
    return suma1;
}

REAL sum2(int k){
    REAL suma2 = 0.0;
    for (int i = k; i >= 1; i--){
        suma2 += 1.0/i;
    }
    return suma2;
}