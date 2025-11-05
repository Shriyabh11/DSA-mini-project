#include "utils.h"

struct Edge {
    int u, v, w;
};
vector<vector<pair<int, int>>> adj;
vector<Edge> edges;

void dfsUtil(int u, vector<int>& vis) {
    vis[u] = 1;
    cout << u << " ";
    for (auto p : adj[u]) {
        int v = p.first;
        if (!vis[v]) dfsUtil(v, vis);
    }
}

void graphMenu() {
    int n = 5; // fixed lifestyle factors
    adj.assign(n, {});
    edges.clear();

    int choice;
    do {
        line();
        cout << CYAN << "Lifestyle Graph (Diabetes Health Model)" << RESET << endl;
        line();
        cout << "Factors: 0-Food, 1-Exercise, 2-Stress, 3-Sleep, 4-Insulin" << endl;
        cout << "1. Add Connection (Edge)\n";
        cout << "2. Show DFS\n";
        cout << "3. Show BFS\n";
        cout << "4. Dijkstra (Shortest Stability Path)\n";
        cout << "5. Kruskal (Minimal Change Network)\n";
        cout << "6. Back\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int u, v, w;
                cout << "Enter connection (u v effect_strength): ";
                cin >> u >> v >> w;
                adj[u].push_back(make_pair(v, w));
                adj[v].push_back(make_pair(u, w));
                edges.push_back({u, v, w});
                cout << GREEN << "Connection added successfully." << RESET << endl;
                break;
            }

            case 2: {
                vector<int> vis(n, 0);
                cout << "DFS from Food(0): ";
                dfsUtil(0, vis);
                cout << endl;
                break;
            }

            case 3: {
                vector<int> vis(n, 0);
                queue<int> q;
                q.push(0);
                vis[0] = 1;
                cout << "BFS from Food(0): ";
                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    cout << u << " ";
                    for (auto p : adj[u]) {
                        int v = p.first;
                        if (!vis[v]) {
                            vis[v] = 1;
                            q.push(v);
                        }
                    }
                }
                cout << endl;
                break;
            }

            case 4: { // Dijkstra
                int src = 0;
                vector<int> d(n, INT_MAX);
                d[src] = 0;
                priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
                pq.push(make_pair(0, src));

                while (!pq.empty()) {
                    pair<int, int> top = pq.top();
                    pq.pop();
                    int du = top.first;
                    int u = top.second;
                    if (du != d[u]) continue;

                    for (auto p : adj[u]) {
                        int v = p.first;
                        int w = p.second;
                        if (d[v] > du + w) {
                            d[v] = du + w;
                            pq.push(make_pair(d[v], v));
                        }
                    }
                }

                cout << "Optimal stability influence from Food(0):\n";
                for (int i = 0; i < n; i++)
                    cout << "Factor " << i << ": " << (d[i] == INT_MAX ? -1 : d[i]) << endl;
                break;
            }

            case 5: { // Kruskal
                vector<int> parent(n);
                iota(parent.begin(), parent.end(), 0);
                function<int(int)> find = [&](int x) {
                    if (parent[x] == x) return x;
                    return parent[x] = find(parent[x]);
                };
                auto unite = [&](int a, int b) {
                    a = find(a); b = find(b);
                    if (a != b) parent[b] = a;
                };

                sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
                    return a.w < b.w;
                });

                int cost = 0;
                cout << "Balanced lifestyle plan (edges in MST):\n";
                for (auto e : edges) {
                    if (find(e.u) != find(e.v)) {
                        unite(e.u, e.v);
                        cost += e.w;
                        cout << e.u << " - " << e.v << " (impact " << e.w << ")\n";
                    }
                }
                cout << "Total balance cost: " << cost << endl;
                break;
            }
        }
    } while (choice != 6);
}
