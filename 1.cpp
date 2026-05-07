#include <iostream>
#include <set>
#include <cmath>

using namespace std;

int main() {
    set<int> digitsInTwoDigit;
    set<int> digitsInThreeDigit;

    int n;
    cout << "Введите количество чисел: ";
    cin >> n;

    cout << "Введите числа:" << endl;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        int absNum = abs(num);

        if (absNum >= 10 && absNum <= 99) {
            // Двузначное
            int temp = absNum;
            while (temp > 0) {
                digitsInTwoDigit.insert(temp % 10);
                temp /= 10;
            }
        } else if (absNum >= 100 && absNum <= 999) {
            // Трёхзначное
            int temp = absNum;
            while (temp > 0) {
                digitsInThreeDigit.insert(temp % 10);
                temp /= 10;
            }
        }
    }

    // Поиск общих цифр
    set<int> result;
    for (int d : digitsInTwoDigit) {
        if (digitsInThreeDigit.count(d)) {
            result.insert(d);
        }
    }

    // Вывод результата
    cout << "Цифры, встречающиеся и в двузначных, и в трёхзначных числах:" << endl;
    if (result.empty()) {
        cout << "Таких цифр нет" << endl;
    } else {
        for (int d : result) {
            cout << d << " ";
        }
        cout << endl;
    }

    return 0;
}