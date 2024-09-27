// https://iudex.io/problem/62797c280b5c8500010c5dd6

#include <cmath>
#include <iostream>
using namespace std;

const int MAX_N = 100;    // número máximo de brinquedos
const int MAX_K = 25000;  // número máximo de créditos

struct Brinquedo {
    int S;  // diversão inicial
    int B;  // fator de aborrecimento
    int C;  // custo
};

// função para calcular o número máximo de corridas válidas para um brinquedo
int max_corridas(int S, int B) {
    if (B == 0) return 1;
    return (int)(sqrt(S / (double)B)) + 1;
}

// função para calcular a diversão de um brinquedo na corrida t
int calcular_diversao(int S, int B, int t) {
    int F = S - (t - 1) * (t - 1) * B;  // calcula a diversão da t-ésima corrida
    return (F < 0) ? 0 : F;             // evita diversão negativa
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N;  // número de brinquedos
    cin >> N;

    Brinquedo brinquedos[MAX_N];  // array para armazenar os brinquedos

    // leitura dos dados dos brinquedos
    for (int i = 0; i < N; ++i) {
        cin >> brinquedos[i].S >> brinquedos[i].B >> brinquedos[i].C;
    }

    int V;  // número de visitas
    cin >> V;

    int K[V];  // array para armazenar os créditos de cada visita
    for (int j = 0; j < V; ++j) {
        cin >> K[j];  // lê os créditos para cada visita
    }

    int dp[MAX_K + 1];  // array dp para armazenar a diversão máxima para cada número de créditos

    // inicializa o array dp manualmente
    for (int i = 0; i <= MAX_K; ++i) {
        dp[i] = 0;  // todos os valores são inicializados como 0
    }

    // calcula o knapsack uma única vez para o valor máximo de créditos (MAX_K)
    for (int i = 0; i < N; ++i) {
        int max_t = max_corridas(brinquedos[i].S, brinquedos[i].B);

        // atualiza a tabela dp para cada corrida válida do brinquedo
        for (int t = 1; t <= max_t; ++t) {
            int F = calcular_diversao(brinquedos[i].S, brinquedos[i].B, t);  // calcula diversão
            if (F <= 0) break;                                               // evita processar diversões negativas
            for (int c = MAX_K; c >= brinquedos[i].C; --c) {
                dp[c] = max(dp[c], dp[c - brinquedos[i].C] + F);
            }
        }
    }

    // para cada visita, apenas consulta o valor máximo de diversão na tabela dp
    for (int j = 0; j < V; ++j) {
        cout << j << ": " << dp[K[j]] << "\n";  // imprime a diversão máxima para a visita j
    }

    return 0;  // finaliza o programa
}
