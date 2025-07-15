#include <omp.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <numeric>

void fill(std::vector<double> & array);
double suma(const std::vector<double> & array);

int main(int argc, char *argv[])
{
  const int N = std::atoi(argv[1]);
  std::vector<double> data(N);

  // llenar el arreglo con some datos
  fill(data);
  //std::cout << data[0] << "\n";
  double start = omp_get_wtime();
  // calcular la suma y el promedio
  double total = suma(data);
  std::cout << total/data.size() << "\n";
  double end = omp_get_wtime();
  double execution_time = end - start;
  std::cout << execution_time << "\n";

  return 0;
}

void fill(std::vector<double> & array)
{
  int N = array.size();
#pragma omp parallel
  {
    int thid = omp_get_thread_num();
    int nth = omp_get_num_threads();
    int Nlocal = N/nth;
    int iimin = thid*Nlocal;
    int iimax = iimin + Nlocal;
    for(int ii = iimin; ii < iimax; ii++) {
      array[ii] = 2*ii*std::sin(std::sqrt(ii/56.7)) +
        std::cos(std::pow(1.0*ii*ii/N, 0.3));
    }
  }
}

double suma(const std::vector<double> & array)
{
  int N = array.size();
  int max_threads_possible = omp_get_max_threads();
  std::vector<double> sumaparcial(max_threads_possible, 0.0);

#pragma omp parallel
  {
    int thid = omp_get_thread_num();
    int nth = omp_get_num_threads();
    double localsum = 0.0;
    int Nlocal = N/nth;
    int iimin = thid*Nlocal;
    int iimax = iimin + Nlocal;
    for(int ii = iimin; ii < iimax; ii++) {
      localsum += array[ii];
    }
    sumaparcial[thid] = localsum; // save the localsum in a different place per thread
  }
  return std::accumulate(sumaparcial.begin(), sumaparcial.end(), 0.0); // sum up all partial sums
}