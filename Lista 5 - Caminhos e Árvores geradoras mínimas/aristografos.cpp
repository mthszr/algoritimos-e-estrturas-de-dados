#include <iostream>
#include <limits>
#include <queue>
#include <vector>
using namespace std;

const int INF = 1e9;  // valor representando o infinito

struct rua {
    int destino, tempo;
};

// função que aplica o algoritmo de dijkstra para encontrar o menor tempo de A até B
int dijkstra(int origem, int destino, const vector<vector<rua>> &grafo, int q) {
    vector<int> dist(q, INF);  // distâncias mínimas até cada quadra
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[origem] = 0;
    pq.push({0, origem});

    while (!pq.empty()) {
        int tempo_atual = pq.top().first;
        int quadra_atual = pq.top().second;
        pq.pop();

        if (tempo_atual > dist[quadra_atual]) continue;

        // explorando as ruas conectadas à quadra atual
        for (const rua &r : grafo[quadra_atual]) {
            int nova_dist = tempo_atual + r.tempo;
            if (nova_dist < dist[r.destino]) {
                dist[r.destino] = nova_dist;
                pq.push({nova_dist, r.destino});
            }
        }
    }

    return dist[destino] == INF ? -1 : dist[destino];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int q, r, n;
    cin >> q >> r >> n;

    // grafo com q quadras (0 a q-1)
    vector<vector<rua>> grafo(q);

    // lendo as ruas iniciais
    for (int i = 0; i < r; ++i) {
        int a, b, m;
        cin >> a >> b >> m;
        grafo[a].push_back({b, m});
    }

    // processando os eventos
    for (int i = 0; i < n; ++i) {
        int tipo;
        cin >> tipo;

        if (tipo == 1) {
            // evento de nova rua
            int a, b, m;
            cin >> a >> b >> m;
            grafo[a].push_back({b, m});
        } else if (tipo == 2) {
            // evento de consulta de tempo mínimo
            int a, b;
            cin >> a >> b;
            cout << dijkstra(a, b, grafo, q) << endl;
        }
    }

    return 0;
}