#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
#include <cmath>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<double> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    
    // Среднее арифметическое
    double sum = accumulate(v.begin(), v.end(), 0.0);
    double mean = sum / n;
    
    // Сумма квадратов отклонений
    double sq_sum = accumulate(v.begin(), v.end(), 0.0,
        [mean](double acc, double x) {
            return acc + (x - mean) * (x - mean);
        }
    );
    
    // Дисперсия (несмещенная)
    double var = sq_sum / (n - 1);
    
    cout << var << endl;
    
    return 0;
}