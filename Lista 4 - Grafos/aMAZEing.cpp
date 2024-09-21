// https://iudex.io/problem/5bcc95305cd44b0001fdbf74

#include <iostream>
using namespace std;

const int MAX_N = 100;                // tamanho máximo do labirinto
const int MAX_CELLS = MAX_N * MAX_N;  // número máximo de células no labirinto

// estrutura de dados para o Disjoint Set Union (DSU)
class DSU {
   private:
    int parent[MAX_CELLS], rank[MAX_CELLS];

   public:
    DSU(int n) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;  // inicializa cada elemento como seu próprio pai
            rank[i] = 0;    // inicializa o rank como 0
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // compressão de caminho
        }
        return parent[x];
    }

    void union_sets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            // união por rank
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int k;  // número de casos de teste
    cin >> k;

    // loop sobre cada caso de teste
    for (int caso = 0; caso < k; caso++) {
        int n, m, q;  // n = tamanho do labirinto, m = número de paredes removidas, q = número de consultas
        cin >> n >> m >> q;

        int total_cells = n * n;  // calcula o total de células no labirinto

        DSU dsu(total_cells);  // cria uma estrutura DSU para o número total de células

        // processar as paredes removidas e unir as células no grafo
        for (int i = 0; i < m; i++) {
            int wall;     // número da parede removida
            cin >> wall;  // lê o número da parede removida

            // cálculo das posições das células baseadas na parede
            int linha = wall / (2 * n - 1);  // 2n-1 paredes por linha
            int num = wall % (2 * n - 1);    // para uma linha, numera colunas de 0 a 2n-2
            if (num < n - 1) {
                // paredes verticais
                int esquerda = linha * n + num;
                int direita = esquerda + 1;
                // une as células adjacentes
                dsu.union_sets(esquerda, direita);
            } else {
                // paredes horizontais
                int cima = linha * n + (num - (n - 1));
                int baixo = cima + n;
                // une as células adjacentes
                dsu.union_sets(cima, baixo);
            }
        }

        // processar as consultas
        for (int j = 0; j < q; j++) {
            int a, b;  // células para verificar conectividade
            cin >> a >> b;

            // verificar se há caminho de 'a' para 'b'
            if (dsu.find(a) == dsu.find(b)) {
                cout << caso << "." << j << " 1\n";
            } else {
                cout << caso << "." << j << " 0\n";
            }
        }

        cout << "\n";  // linha em branco entre os casos
    }

    return 0;
}
