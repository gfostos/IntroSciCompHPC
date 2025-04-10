// imprima los numeros del 1 al 10 usando while
#include <iostream> 

int main(void) 
{
    int n;

    n = 1;
    while (n <= 10) {
         std::cout << n << std::endl;
         ++n;  
    } 

    /*for(n = 1; n <= 10; --n) {
        std::cout << n << std::endl;
    }*/


  return 0;
}