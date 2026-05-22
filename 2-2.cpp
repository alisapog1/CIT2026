#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, M;
    cout << "Введите количество вершин и ребер: ";
    cin >> N >> M;
    
    // Список смежности для неориентированного графа
    vector<vector<int>> adj(N);
    
    cout << "Введите ребра (u v):\n";
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);  // Для неориентированного графа добавляем в оба направления
    }
    
    // Вывод текущего графа
    cout << "\nТекущий граф:\n";
    for (int i = 0; i < N; i++) {
        cout << i << ": ";
        for (int v : adj[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
    
    int A, B;
    cout << "\nВведите вершины A и B для добавления ребра: ";
    cin >> A >> B;
    
    // Проверка на существование ребра
    bool edgeExists = false;
    for (int v : adj[A]) {
        if (v == B) {
            edgeExists = true;
            break;
        }
    }
    
    if (edgeExists) {
        cout << "Ребро между " << A << " и " << B << " уже существует!\n";
    } else {
        // Добавляем ребро в обе стороны (неориентированный граф)
        adj[A].push_back(B);
        adj[B].push_back(A);
        cout << "Ребро (" << A << ", " << B << ") успешно добавлено!\n";
    }
    
    // Вывод графа после добавления
    cout << "\nГраф после добавления:\n";
    for (int i = 0; i < N; i++) {
        // Сортируем для красивого вывода
        sort(adj[i].begin(), adj[i].end());
        cout << i << ": ";
        for (int v : adj[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
    
    return 0;
}