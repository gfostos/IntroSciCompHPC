#include <iostream>
#include <chrono>
#include <cstdlib>

long long fib(int n);
long long fib_fast(int n);

int main(int argc, char* argv[]) {
    
    int n = std::atoi(argv[1]);

    // Mide tiempo de fib(n)
    auto t0 = std::chrono::high_resolution_clock::now();
    long long result_rec = fib(n);
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_rec = t1 - t0;

    // Mide tiempo de fib_fast(n)
    auto t2 = std::chrono::high_resolution_clock::now();
    long long result_itr = fib_fast(n);
    auto t3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_itr = t3 - t2;

    std::cout << n << "\t" << time_rec.count() << "\t" << time_itr.count() << "\n";

    return 0;
}

// Fibonacci recursivo
long long fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

// Fibonacci iterativo
long long fib_fast(int n) {
    if (n <= 1) return n;
    long long a = 0, b = 1, c = 0;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}
