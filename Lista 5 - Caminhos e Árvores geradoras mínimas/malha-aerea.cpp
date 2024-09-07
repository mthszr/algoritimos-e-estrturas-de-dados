// https://iudex.io/problem/6195d96b97713f0001037a14

#include <iostream>
using namespace std;

const int MAX_M = 100000;  // número máximo de aeroportos
const int MAX_N = 100000;  // número máximo de trechos

// estrutura para armazenar um trecho, que contém os aeroportos de ida, volta, e o custo associado
struct trecho {
    int ida, volta, custo;
};

trecho trechos[MAX_N];           // array para armazenar os trechos
int pai[MAX_M], tamanho[MAX_M];  // arrays para a estrutura de union-find

// função para encontrar o representante de um subconjunto
int encontrar(int aeroporto) {
    // se o aeroporto é o próprio representante, retorna ele mesmo
    if (pai[aeroporto] == aeroporto)
        return aeroporto;
    // recursivamente encontra o representante
    return pai[aeroporto] = encontrar(pai[aeroporto]);
}

// função para unir dois subconjuntos
void unir(int a, int b) {
    a = encontrar(a);                 // encontra o representante do aeroporto 'a'
    b = encontrar(b);                 // encontra o representante do aeroporto 'b'
    if (a != b) {                     // se os dois aeroportos não estão no mesmo subconjunto
        if (tamanho[a] < tamanho[b])  // une o menor subconjunto ao maior
            swap(a, b);               // garante que 'a' sempre tenha o maior tamanho
        pai[b] = a;                   // o representante de 'b' agora é 'a'
        tamanho[a] += tamanho[b];     // atualiza o tamanho do conjunto representado por 'a'
    }
}

// função de ordenação usando selection sort para ordenar os trechos pelo custo
void selection_sort(trecho arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;  // índice do elemento com menor custo encontrado
        for (int j = i + 1; j < n; ++j) {
            if (arr[j].custo < arr[min_idx].custo) {  // verifica se há um trecho com custo menor
                min_idx = j;                          // atualiza o índice do menor custo
            }
        }
        // troca o trecho com menor custo encontrado com o primeiro elemento não ordenado
        trecho temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // número de aeroportos (M) e o número de trechos (N)
    int M, N;
    cin >> M >> N;

    // lendo os trechos e seus custos
    for (int i = 0; i < N; ++i) {
        cin >> trechos[i].ida >> trechos[i].volta >> trechos[i].custo;
    }

    // ordena os trechos pelo custo usando selection sort
    selection_sort(trechos, N);

    // inicializando a estrutura de union-find
    for (int i = 0; i < M; ++i) {
        pai[i] = i;      // cada aeroporto é o representante de si mesmo no início
        tamanho[i] = 1;  // o tamanho inicial de cada subconjunto é 1
    }

    int custo_total = 0;        // variável para armazenar o custo total da árvore geradora mínima
    int trechos_incluidos = 0;  // contador para o número de trechos incluídos na solução

    // aplicando o algoritmo de kruskal para encontrar a árvore geradora mínima
    for (int i = 0; i < N; ++i) {
        int ida = trechos[i].ida;      // aeroporto de ida do trecho
        int volta = trechos[i].volta;  // aeroporto de volta do trecho
        int custo = trechos[i].custo;  // custo do trecho

        // se os aeroportos de ida e volta não pertencem ao mesmo subconjunto, podemos conectar eles
        if (encontrar(ida) != encontrar(volta)) {
            unir(ida, volta);      // une os subconjuntos contendo 'ida' e 'volta'
            custo_total += custo;  // adiciona o custo do trecho ao custo total
            trechos_incluidos++;   // incrementa o número de trechos incluídos

            // se já incluímos M-1 trechos, temos a árvore geradora mínima completa
            if (trechos_incluidos == M - 1)
                break;
        }
    }

    // imprime o custo total da árvore geradora mínima
    cout << custo_total << endl;

    return 0;
}
