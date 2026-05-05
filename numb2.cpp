#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Ввод данных
    int n;
    cin >> n;
    
    vector<int> numbers(n);
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }
    
    // 1. Удаляем все максимальные элементы
    int maxVal = *max_element(numbers.begin(), numbers.end());
    vector<int> withoutMax;
    for (int x : numbers) {
        if (x != maxVal) {
            withoutMax.push_back(x);
        }
    }
    
    for (int x : withoutMax) {
        cout << x << " ";
    }
    cout << endl;
    
    // 2. Заменяем все четные минимальным
    int minVal = *min_element(numbers.begin(), numbers.end());
    vector<int> replacedEven = numbers;
    for (int& x : replacedEven) {
        if (x % 2 == 0) {
            x = minVal;
        }
    }
    
    for (int x : replacedEven) {
        cout << x << " ";
    }
    cout << endl;
    
    // 3. Сортируем
    vector<int> sorted = numbers;
    sort(sorted.begin(), sorted.end());
    
    for (int x : sorted) {
        cout << x << " ";
    }
    cout << endl;
    
    // 4. Удаляем повторяющиеся
    vector<int> uniqueNumbers = numbers;
    sort(uniqueNumbers.begin(), uniqueNumbers.end());
    auto last = unique(uniqueNumbers.begin(), uniqueNumbers.end());
    uniqueNumbers.erase(last, uniqueNumbers.end());
    
    for (int x : uniqueNumbers) {
        cout << x << " ";
    }
    cout << endl;
    
    return 0;
}