#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <stdexcept>

const int MAX_DEGREE = 10;
const double REG = 1e-10;

double cheb(int n, double x) {
    if (n == 0) return 1.0;
    if (n == 1) return x;

    double T0 = 1.0, T1 = x, Tn;
    for (int i = 2; i <= n; i++) {
        Tn = 2.0 * x * T1 - T0;
        T0 = T1;
        T1 = Tn;
    }
    return T1;
}

std::vector<double> solveGaussian(std::vector<std::vector<double>> A,
                                  std::vector<double> b) {
    int n = A.size();

    for (int i = 0; i < n; i++) {
        // поиск главного элемента
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (std::abs(A[k][i]) > std::abs(A[maxRow][i])) {
                maxRow = k;
            }
        }

        std::swap(A[i], A[maxRow]);
        std::swap(b[i], b[maxRow]);

        double pivot = A[i][i];
        if (std::abs(pivot) < 1e-14) {
            throw std::runtime_error("Matrix is singular or ill-conditioned");
        }

        // нормализация
        for (int j = i; j < n; j++) A[i][j] /= pivot;
        b[i] /= pivot;

        // обнуление
        for (int k = 0; k < n; k++) {
            if (k == i) continue;
            double factor = A[k][i];
            for (int j = i; j < n; j++) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }

    return b;
}

std::vector<double> solve(std::vector<double> x, std::vector<double> y) {
    int m = x.size();

    int deg = std::min(MAX_DEGREE, m - 1);
    int n = deg + 1;

    if (MAX_DEGREE >= m) {
        std::cout << "Warning: degree reduced to " << deg
                  << " (not enough data points)\n";
    }

    std::vector<std::vector<double>> ATA(n, std::vector<double>(n, 0.0));

    // generate cheb
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                ATA[i][j] += cheb(i, x[k]) * cheb(j, x[k]);
            }
        }
    }

    // adding error
    for (int i = 0; i < n; i++) {
        ATA[i][i] += REG;
    }

    // generate y
    std::vector<double> ATy(n, 0.0);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < m; k++) {
            ATy[i] += y[k] * cheb(i, x[k]);
        }
    }

    std::vector<double> coefs;
    try {
        coefs = solveGaussian(ATA, ATy);
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return {};
    }

    return coefs;
}

int main() {
    std::vector<double> x = {
        -1.0, -0.8, -0.6, -0.4, -0.2,
        0.0,
        0.2,  0.4,  0.6,  0.8,  1.0
    };

    std::vector<double> y = {
        -0.84, -0.72, -0.56, -0.39, -0.20,
        0.0,
        0.20,  0.39,  0.56,  0.72,  0.84
    };
    std::vector<double> coefs = solve(x, y);

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "Chebyshev coefficients:\n";
    for (int i = 0; i < coefs.size(); i++) {
        std::cout << "c[" << i << "] = " << coefs[i] << std::endl;
    }

    return 0;
}