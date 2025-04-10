#include <iostream>
#include <cmath>

typedef double REAL;

int factorial(int n);
REAL fnaive(REAL x, int N);
REAL fsmart(REAL x, int N);

int main(void)
{
  std::cout.precision(16); std::cout.setf(std::ios::scientific);
  REAL x = 1.234534534;
  const REAL exact = std::exp(-x);
  for (int NMAX = 0; NMAX <= 100; ++NMAX) {
    std::cout << NMAX
              << "\t" << fnaive(x, NMAX)
              << "\t" << std::fabs(fnaive(x, NMAX) - exact)/exact
              << "\t" << fsmart(x, NMAX)
              << "\t" << std::fabs(fsmart(x, NMAX) - exact)/exact
              << std::endl;
  }
  return 0;
}

REAL fnaive(REAL x, int N)
{
    //TODO
    REAL term =0, suma = 0;
    for (int k = 0; k<=N; ++k){
        term = std::pow(-x, k)/factorial(k);
        suma += term;
    }
    return suma;
}

int factorial(int n)
{
  if (n <= 0) return 1;
  return n*factorial(n-1);
}

REAL fsmart(REAL x, int N)
{
    REAL term =1, suma = 1;
    for (int k = 0; k<N; ++k){
        term = -x*term/(k+1);
        suma += term;
    }
    return suma;
}
