#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cctype>

using namespace std;

// Проверка, является ли строка числом
bool isNumber(const string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(c) && c != '-') return false;
    }
    return true;
}

int main() {
    cout << "Введите строку (слова и числа через пробел):" << endl;
    string line;
    getline(cin, line); // считываем всю строку

    map<string, int> freq; // слово -> частота

    stringstream ss(line);
    string token;
    while (ss >> token) {
        // Если это слово (не число)
        if (!isNumber(token)) {
            // Приводим к нижнему регистру
            for (char& c : token) {
                c = tolower(c);
            }
            freq[token]++;
        }
    }

    // Переносим в вектор для сортировки
    vector<pair<string, int>> words(freq.begin(), freq.end());

    // Сортируем по убыванию частоты, при равной частоте — по алфавиту
    sort(words.begin(), words.end(),
         [](const pair<string, int>& a, const pair<string, int>& b) {
             if (a.second != b.second) return a.second > b.second;
             return a.first < b.first;
         });

    int k;
    cout << "Введите k: ";
    cin >> k;

    cout << "Топ-" << k << " слов:" << endl;
    for (int i = 0; i < min(k, (int)words.size()); ++i) {
        cout << words[i].first << " — " << words[i].second << " раз(а)" << endl;
    }

    return 0;
}