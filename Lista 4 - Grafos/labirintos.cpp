#include <iostream>

using namespace std;

const int MAX = 1000;  // tamanho máximo do labirinto
int labirinto[MAX][MAX];
bool visitado[MAX][MAX];
int fila_linha[MAX * MAX];                                // fila para linhas
int fila_coluna[MAX * MAX];                               // fila para colunas
int fila_distancia[MAX * MAX];                            // fila para distâncias
int direcoes[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};  // cima, baixo, esquerda, direita

bool eh_valido(int linha, int coluna, int m, int n) {
    return (linha >= 0 && linha < m && coluna >= 0 && coluna < n &&
            labirinto[linha][coluna] != 1 && !visitado[linha][coluna]);
}

int bfs(int m, int n, int inicio_linha, int inicio_coluna) {
    int frente = 0, tras = 0;

    fila_linha[tras] = inicio_linha;
    fila_coluna[tras] = inicio_coluna;
    fila_distancia[tras] = 0;
    visitado[inicio_linha][inicio_coluna] = true;
    tras++;

    while (frente < tras) {
        int atual_linha = fila_linha[frente];
        int atual_coluna = fila_coluna[frente];
        int atual_distancia = fila_distancia[frente];
        frente++;

        // se encontrar o destino, retornar a distância
        if (labirinto[atual_linha][atual_coluna] == 3) {
            return atual_distancia;
        }

        // explorar as quatro direções
        for (int i = 0; i < 4; ++i) {
            int nova_linha = atual_linha + direcoes[i][0];
            int nova_coluna = atual_coluna + direcoes[i][1];

            if (eh_valido(nova_linha, nova_coluna, m, n)) {
                fila_linha[tras] = nova_linha;
                fila_coluna[tras] = nova_coluna;
                fila_distancia[tras] = atual_distancia + 1;
                visitado[nova_linha][nova_coluna] = true;
                tras++;
            }
        }
    }

    // se não encontrar o destino, o labirinto é impossível
    return -1;
}

int main() {
    int m, n;
    cin >> m >> n;

    int inicio_linha, inicio_coluna;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> labirinto[i][j];
            visitado[i][j] = false;  // inicializar como não visitado
            if (labirinto[i][j] == 2) {
                inicio_linha = i;
                inicio_coluna = j;
            }
        }
    }

    int resultado = bfs(m, n, inicio_linha, inicio_coluna);
    if (resultado == -1) {
        cout << "Labirinto Impossivel" << endl;
    } else {
        cout << resultado << endl;
    }

    return 0;
}
