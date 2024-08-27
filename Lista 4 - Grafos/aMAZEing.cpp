#include <iostream>
#include <vector>

using namespace std;

const int MAX = 10000;  // número máximo de células

int pai[MAX], profundidade[MAX];

// função para encontrar o representante de um conjunto
int find(int x) {
    if (pai[x] != x) {
        pai[x] = find(pai[x]);  // compressão de caminho
    }
    return pai[x];
}

// função para unir dois conjuntos
void unir(int x, int y) {
    int raiz_x = find(x);
    int raiz_y = find(y);

    if (raiz_x != raiz_y) {
        if (profundidade[raiz_x] > profundidade[raiz_y]) {
            pai[raiz_y] = raiz_x;
        } else if (profundidade[raiz_x] < profundidade[raiz_y]) {
            pai[raiz_x] = raiz_y;
        } else {
            pai[raiz_y] = raiz_x;
            profundidade[raiz_x]++;
        }
    }
}

int main() {
    int k;
    cin >> k;

    for (int caso = 0; caso < k; caso++) {
        int n, m, q;
        cin >> n >> m >> q;

        int tamanho = n * n;

        // inicializar união-find
        for (int i = 0; i < tamanho; i++) {
            pai[i] = i;
            profundidade[i] = 0;
        }

        // processar as paredes removidas
        for (int i = 0; i < m; i++) {
            int w;
            cin >> w;

            int linha = w / (2 * (n - 1));   // linha onde a parede está localizada
            int coluna = w % (2 * (n - 1));  // coluna onde a parede está localizada

            if (coluna < n - 1) {  // parede vertical
                int cell1 = linha * n + coluna;
                int cell2 = cell1 + 1;
                unir(cell1, cell2);
            } else {  // parede horizontal
                int cell1 = (linha * n) + (coluna - (n - 1));
                int cell2 = cell1 + n;
                unir(cell1, cell2);
            }
        }

        // processar as consultas
        for (int j = 0; j < q; j++) {
            int a, b;
            cin >> a >> b;

            cout << caso << "." << j << " ";
            if (find(a) == find(b)) {
                cout << "1" << endl;
            } else {
                cout << "0" << endl;
            }
        }

        cout << endl;  // linha em branco entre os casos
    }

    return 0;
}
