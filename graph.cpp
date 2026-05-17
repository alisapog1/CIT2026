#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<vector<pair<int, double>>> graph(N);
    
    for (int i = 0; i < M; i++) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    
    int start;
    cin >> start;
    
    // Алгоритм Дейкстры
    vector<double> dist(N, INT_MAX);
    vector<int> parent(N, -1);
    dist[start] = 0;
    
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0, start});
    
    while (!pq.empty()) {
        double d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto& edge : graph[u]) {
            int v = edge.first;
            double w = edge.second;
            
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    
    // Вывод результатов с ПРАВИЛЬНЫМ восстановлением пути
    cout << "\nРезультаты от вершины " << start << "\n\n";
    
    for (int i = 0; i < N; i++) {
        cout << "Вершина " << i << ": расстояние = " << dist[i];
        
        if (dist[i] == INT_MAX) {
            cout << ", недостижима\n";
        } else {
            // Восстанавливаем путь в правильном порядке
            vector<int> path;
            int cur = i;
            while (cur != -1) {
                path.push_back(cur);
                cur = parent[cur];
            }
            
            cout << ", путь: ";
            for (int j = path.size() - 1; j >= 0; j--) {
                cout << path[j];
                if (j > 0) cout << " -> ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}