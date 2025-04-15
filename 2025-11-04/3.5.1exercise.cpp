#include <iostream>
#include <cmath>

typedef float REAL;

REAL sum1(int k);
//REAL sum2(int k);
//REAL sum3(int k);

int main (void){
    std::cout.precision(7);
    std::cout.setf(std::ios::scientific);

    for (int k = 1; k <= 10; k++){
        std::cout << k << "\t" << sum1(k) << "\n";
    }
}

REAL sum1(int k){
    REAL suma1 = 0.0;
    for (int i = 1; i <= 2*k; i++){
        suma1 += pow(-1, i)*(i/(i+1));
    }
    return suma1;
}

/*REAL sum2(int k){
    REAL suma2 = 0.0;
    for (int i = 1; i <= k; i++){
        suma2 += (-(2*i-1)/(2*i))+((2*i)/(2*i+1));
    }
    return suma2;
}

REAL sum3(int k){
    REAL suma3 = 0.0;
    for (int i = 1; i <= k; i++){
        suma3 += 1/(2*i*(2*i+1));
    }
    return suma3;
}*/