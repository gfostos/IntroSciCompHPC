#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <numeric>

// function declaration
void fill(std::vector<double> & xdata); // llenar el vector
double average(const std::vector<double> & xdata); // calcular el promedio

int main(int argc, char **argv)
{
  // read command line args
  int N = std::atoi(argv[1]);

  // declare the data struct
  std::vector<double> data;
  data.resize(N);

  // fill the vector
  fill(data);

  // compute the mean
  double result = average(data);

  // print the result
  std::cout.precision(15);
  std::cout.setf(std::ios::scientific);
  std::cout << result << "\n";

  return 0;
}

// function implementation
void fill(std::vector<double> & xdata)
{
  std::iota(xdata.begin(), xdata.end(), 1.0); // 1.0 2.0 3.0
}

double average(const std::vector<double> & xdata)
{
  // forma 1
  return std::accumulate(xdata.begin(), xdata.end(), 0.0)/xdata.size();
  // forma 2
  // double suma = 0.0;
  // for (auto x : xdata) {
  //   suma += x;
  // }
  // return suma/data.size();
}