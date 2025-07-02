#include <iostream>
#include <vector>
#include <numeric>
#include <execution>
#include <chrono>
#include <thread>
#include <string>
#include <memory>
#include <tbb/global_control.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Uso: " << argv[0] << " <vector_size> <num_threads> <policy (0: seq, 1: par, 2: par_unseq)>\n";
        return 1;
    }

    size_t vector_size = std::stoull(argv[1]);
    int num_threads = std::stoi(argv[2]);
    int policy = std::stoi(argv[3]);

    std::vector<double> vec(vector_size, 1.0);
    double result = 0.0;

    std::unique_ptr<tbb::global_control> gc;
    if (policy != 0) {
        gc = std::make_unique<tbb::global_control>(
            tbb::global_control::max_allowed_parallelism, num_threads
        );
    }

    auto start = std::chrono::high_resolution_clock::now();

    if (policy == 0) {
        result = std::reduce(std::execution::seq, vec.begin(), vec.end());
    } else if (policy == 1) {
        result = std::reduce(std::execution::par, vec.begin(), vec.end());
    } else if (policy == 2) {
        result = std::reduce(std::execution::par_unseq, vec.begin(), vec.end());
    } else {
        std::cerr << "Política inválida. Use 0 (seq), 1 (par), o 2 (par_unseq).\n";
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << policy << " "
              << num_threads << " "
              << elapsed.count() << " "
              << result
              << std::endl;

    return 0;
}