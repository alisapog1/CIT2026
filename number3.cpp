#include <iostream>
#include <vector>

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
        adj[v].push_back(u);
    }
    
    // Вывод графа (для наглядности)
    cout << "\nСписок смежности графа:\n";
    for (int i = 0; i < N; i++) {
        cout << i << ": ";
        for (int v : adj[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
    
    // Подсчёт и вывод степени каждой вершины
    cout << "\nСтепени вершин:\n";
    for (int i = 0; i < N; i++) {
        int degree = adj[i].size();  // Степень = количество соседей
        cout << "deg(" << i << ") = " << degree << endl;
    }
    
    return 0;
}