#include <algorithm>
#include <iostream>
using namespace std;

// Definição de limites máximos
const int MAX_N = 100;
const int MAX_V = 1000;
const int MAX_K = 25000;

// Estrutura para representar cada corrida como um item
struct Item {
    int cost;
    int fun;
};

// Função principal
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    // Arrays para armazenar S[i], B[i], C[i]
    int S[MAX_N], B[MAX_N], C[MAX_N];
    // Array de itens
    Item items[MAX_N * MAX_N];  // limite máximo estimado para corridas

    int totalItems = 0;

    // Leitura dos dados dos brinquedos e geração das corridas possíveis
    for (int i = 0; i < N; ++i) {
        cin >> S[i] >> B[i] >> C[i];
        int t = 1;
        while (true) {
            // Calcula a diversão para a t-ésima corrida
            long long F = (long long)S[i] - ((long long)(t - 1) * (t - 1) * (long long)B[i]);
            if (F <= 0) break;
            // Armazena o item
            items[totalItems++] = {C[i], (int)F};
            t++;
        }
    }

    int V;
    cin >> V;

    // Leitura de todas as visitas
    int K[MAX_V];
    for (int j = 0; j < V; ++j) {
        cin >> K[j];
    }

    // Para cada visita, realizar o Knapsack 0-1
    for (int j = 0; j < V; ++j) {
        int credit = K[j];
        // Inicialização do vetor de DP com tamanho máximo de créditos + 1
        int dp[MAX_K + 1] = {0};

        // Iteração sobre todos os itens
        for (int i = 0; i < totalItems; ++i) {
            // Iteração reversa para garantir 0-1 Knapsack
            for (int c = credit; c >= items[i].cost; --c) {
                dp[c] = max(dp[c], dp[c - items[i].cost] + items[i].fun);
            }
        }

        // Impressão do resultado
        cout << j << ": " << dp[credit] << "\n";
    }

    return 0;
}
