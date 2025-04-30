#include <random>
#include <iostream>
#include <cstdlib>
#include <vector>

void compute_pdf(int seed, int nsamples, double mu, double sigma, double xmin, double xmax, int nbins);

int main(int argc, char **argv)
{
  const int SEED = std::atoi(argv[1]);
  const int NSAMPLES = std::atoi(argv[2]);
  const double MU = std::atof(argv[3]);
  const double SIGMA = std::atof(argv[4]);
  const double XMIN = std::atof(argv[5]);
  const double XMAX = std::atof(argv[6]);
  const int NBINS = std::atoi(argv[7]);

  compute_pdf(SEED, NSAMPLES, MU, SIGMA, XMIN, XMAX, NBINS);
}

void compute_pdf(int seed, int nsamples, double mu, double sigma, double xmin, double xmax, int nbins)
{
    std::vector<int> counts(nbins, 0);

    std::mt19937 gen(seed);
    std::normal_distribution<double> dis{mu, sigma};

    for(int n = 0; n < nsamples; ++n) {
        double r = dis(gen);
        if (r < xmin || r >= xmax) 
            continue;
        int bin = ( (r - xmin) / (xmax - xmin) * nbins );
        if (bin == nbins) 
            bin = nbins - 1;
        counts[bin]++;
    }

    double dx = (xmax - xmin) / nbins;
    int total = 0;
    for(int c : counts) total += c;

    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);

    for(int i = 0; i < nbins; ++i) {
        double x_mid = xmin + (i + 0.5) * dx;
        double pdf = counts[i] / (total * dx);
        std::cout << x_mid << "  " << pdf << "\n";
    }
}
