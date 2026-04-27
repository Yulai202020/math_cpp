#include <iostream>
#include <algorithm>
#include <vector>

typedef std::pair<double, double> dot;

int sgn(int x) {
    return (x >= 0 ? 1 : -1);
}

int main() {
    int n;
    double x, y;
    std::cin >> n;
    std::vector<dot> dots(n);

    for (int i = 0; i < n; i++) {
        std::cin >> x >> y;
        dots[i] = dot(x,y);
    }
    
    std::sort(dots.begin(), dots.end(), [](const auto &a, const auto &b) {
        return a.first < b.first;
    });

    std::cin >> x;

    dot i_0, i_1;

    for (int i = 0; i < n - 1; i++) {
        if (x >= dots[i].first && x <= dots[i+1].first) {
            i_0 = dots[i];
            i_1 = dots[i+1];
            break;
        }
    }

    y = i_0.second*(i_1.first-x)/(i_1.first-i_0.first) + i_1.second * (x - i_0.first)/(i_1.first-i_0.first);

    std::cout << "F(x) = " << y << "\n";

    return 0;
}

