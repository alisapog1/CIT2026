#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Ввод количества элементов с клавиатуры
    int n;
    cout << "Введите количество чисел: ";
    cin >> n;
    
    // Создаём вектор нужного размера
    vector<int> numbers(n);
    
    // Ввод чисел с клавиатуры
    cout << "Введите " << n << " чисел: ";
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }
    
    // Находим минимальный элемент
    int minValue = *min_element(numbers.begin(), numbers.end());
    
    // Заменяем все чётные числа минимальным
    replace_if(numbers.begin(), numbers.end(),
               [](int x) { return x % 2 == 0; },
               minValue);
    
    // Выводим результат
    cout << "Результат: ";
    for (int x : numbers) {
        cout << x << " ";
    }
    cout << endl;
    
    return 0;
}