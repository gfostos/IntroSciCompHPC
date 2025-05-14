#include <iostream>
#include <cstdlib>
#include <cmath>

int foo(int a, int b);
int bar(int a, int b);
double baz(double x);
void print_array(const double data[], const int & size);

int main(int argc, char **argv)
{
    int ii = 0, jj = -1;

    // Manejo de posibles divisiones por cero
    if (jj != 0 && ii != 0)
    {
        foo(ii, jj);
        foo(jj, ii);
    }

    std::cout << "baz(25.9): " << baz(25.9) << std::endl;

    const int NX = 2, NY = 3, NZ = 4;
    double *x = new double[NX];
    double y[NY] = {0.0}, z[NZ] = {0.0};

    print_array(x, NX);
    print_array(y, NY);
    print_array(z, NZ);
    std::cout << std::endl;

    for (int i = 0; i < NX; ++i) {
        x[i] = i;
    }

    print_array(x, NX);
    print_array(y, NY);
    print_array(z, NZ);
    std::cout << std::endl;

    for (int j = 0; j < NY && j < NX; ++j) {
        x[j] = NX + j;
    }

    for (int j = 0; j < NY; ++j) {
        y[j] = j;
    }

    print_array(x, NX);
    print_array(y, NY);
    print_array(z, NZ);
    std::cout << std::endl;

    delete[] x;

    return EXIT_SUCCESS;
}

int foo(int a, int b)
{
    if (b == 0 || a == 0) return 0;  // evitar división por cero
    return a / b + b / bar(a, b) + b / a;
}

int bar(int a, int b)
{
    unsigned int c = a;
    return c + a - b;
}

double baz(double x)
{
    if (x == 0.0) return 0.0;
    double v = 1 - (x + 1);
    return std::sqrt(x);
}

void print_array(const double data[], const int & size)
{
    std::cout << std::endl;
    for (int ii = 0; ii < size; ++ii) {
        std::cout << data[ii] << "  ";
    }
    std::cout << std::endl;
}
