#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct trecho {
    int ida, volta, custo;
};

// função para encontrar o representante de um subconjunto
int encontrar(int aeroporto, vector<int> &pai) {
    if (pai[aeroporto] == aeroporto)
        return aeroporto;
    return pai[aeroporto] = encontrar(pai[aeroporto], pai);
}

// função para unir dois subconjuntos
void unir(int a, int b, vector<int> &pai, vector<int> &tamanho) {
    a = encontrar(a, pai);
    b = encontrar(b, pai);
    if (a != b) {
        if (tamanho[a] < tamanho[b])
            swap(a, b);
        pai[b] = a;
        tamanho[a] += tamanho[b];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int M, N;
    cin >> M >> N;

    vector<trecho> trechos(N);

    // lendo os trechos e seus custos
    for (int i = 0; i < N; ++i) {
        cin >> trechos[i].ida >> trechos[i].volta >> trechos[i].custo;
    }

    // ordena os trechos pelo custo
    sort(trechos.begin(), trechos.end(), [](const trecho &a, const trecho &b) {
        return a.custo < b.custo;
    });

    // inicializando a estrutura de união e achamento (union-find)
    vector<int> pai(M), tamanho(M, 1);
    for (int i = 0; i < M; ++i)
        pai[i] = i;

    int custo_total = 0;
    int trechos_incluidos = 0;

    // aplicando o algoritmo de Kruskal
    for (const auto &t : trechos) {
        if (encontrar(t.ida, pai) != encontrar(t.volta, pai)) {
            unir(t.ida, t.volta, pai, tamanho);
            custo_total += t.custo;
            trechos_incluidos++;
            // se incluímos M-1 trechos, já temos a árvore geradora mínima
            if (trechos_incluidos == M - 1)
                break;
        }
    }

    cout << custo_total << endl;

    return 0;
}
