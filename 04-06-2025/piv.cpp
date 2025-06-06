#include <iostream>
#include <eigen3/Eigen/Dense>

int main(int argc, char **argv)
{
    const int SEED = atoi(argv[1]);
    const int size = atoi(argv[2]);
    srand(SEED);
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(size, size);
    Eigen::VectorXd B = Eigen::VectorXd::Random(size);
    //std::cout << "Here is the matrix A:\n" << A << std::endl;
    //std::cout << "Here is the vector b:\n" << b << std::endl;
    Eigen::VectorXd x = A.colPivHouseholderQr().solve(B);
    //std::cout << "The solution is:\n" << x << std::endl;
    std::cout << "Verification:\n" << (A*x - B).norm() << std::endl;
}