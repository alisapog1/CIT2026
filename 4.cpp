#include <iostream>
#include <vector>

using namespace std;

// Функция обхода в глубину (DFS)
void dfs(int v, const vector<vector<int>>& adj, vector<bool>& visited) {
    visited[v] = true;  // Помечаем текущую вершину как посещённую
    
    // Рекурсивно обходим всех соседей
    for (int to : adj[v]) {
        if (!visited[to]) {
            dfs(to, adj, visited);
        }
    }
}

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
        adj[u].push_back(v);  // Только в одну сторону!
    }
    
    int start;
    cout << "\nВведите начальную вершину: ";
    cin >> start;
    
    // Массив посещённых вершин (достижимых)
    vector<bool> visited(N, false);
    
    // Запускаем DFS из начальной вершины
    cout << "\nЗапуск обхода из вершины " << start << "...\n";
    dfs(start, adj, visited);
    
    // Вывод результатов
    cout << "\nРезультат\n";
    
    // Достижимые вершины
    cout << "Достижимые из " << start << ": ";
    bool hasReachable = false;
    for (int i = 0; i < N; i++) {
        if (visited[i]) {
            cout << i << " ";
            hasReachable = true;
        }
    }
    if (!hasReachable) {
        cout << "нет (только сама вершина, если нет петель)";
    }
    cout << endl;
    
    // недостижимые вершины (то, что нужно по заданию)
    cout << "недостижимые из " << start << ": ";
    bool hasUnreachable = false;
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            cout << i << " ";
            hasUnreachable = true;
        }
    }
    if (!hasUnreachable) {
        cout << "нет (все вершины достижимы)";
    }
    cout << endl;
    
    return 0;
}