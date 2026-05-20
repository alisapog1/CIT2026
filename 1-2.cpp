#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    int N, M;
    cout << "Введите количество вершин и ребер: ";
    cin >> N >> M;
    
    // Список смежности для ориентированного графа
    vector<vector<int>> adj(N);
    
    cout << "Введите ребра (u v) - ребро от u к v:\n";
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    
    int target;
    cout << "Введите номер вершины: ";
    cin >> target;
    
    // Множество вершин, смежных с target
    set<int> adjacent;
    
    // 1. Вершины, в которые есть ребро из target
    for (int v : adj[target]) {
        adjacent.insert(v);
    }
    
    // 2. Вершины, из которых есть ребро в target
    for (int i = 0; i < N; i++) {
        for (int v : adj[i]) {
            if (v == target) {
                adjacent.insert(i);
                break;
            }
        }
    }
    
    // Вывод всех вершин, не смежных с target
    cout << "Вершины, не смежные с " << target << ": ";
    bool found = false;
    
    for (int i = 0; i < N; i++) {
        if (i == target) continue; // пропускаем саму вершину
        
        if (adjacent.find(i) == adjacent.end()) {
            cout << i << " ";
            found = true;
        }
    }
    
    if (!found) {
        cout << "нет таких вершин";
    }
    cout << endl;
    
    return 0;
}