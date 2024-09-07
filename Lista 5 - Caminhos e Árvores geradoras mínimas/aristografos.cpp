// https://iudex.io/problem/64f74375e0c9bd0001fd45d6

#include <iostream>
using namespace std;

const int INF = 1e9;     // valor representando o infinito
const int MAX_Q = 1000;  // máximo de quadras suportadas pelo sistema
const int MAX_R = 1000;  // máximo de ruas permitidas

// estrutura que define uma rua conectando duas quadras
// 'destino' é a quadra de destino, e 'tempo' é o tempo necessário para viajar por essa rua
struct rua {
    int destino, tempo; 
};

// estrutura que define um grafo contendo as ruas que partem de uma quadra
struct grafo {
    rua ruas[MAX_R];  // vetor de ruas conectadas a essa quadra
    int tamanho = 0;  // contador que armazena o número de ruas conectadas à quadra
};

// função que aplica o algoritmo de dijkstra para encontrar o menor tempo de uma quadra de origem até uma quadra de destino
int dijkstra(int origem, int destino, grafo grafos[], int q) {
    int dist[MAX_Q];                 // vetor que armazena as distâncias mínimas de 'origem' até cada quadra
    bool visitado[MAX_Q] = {false};  // vetor booleano que indica se uma quadra já foi visitada (processada)

    // inicializando todas as distâncias com infinito
    for (int i = 0; i < q; ++i) {
        dist[i] = INF; 
    }

    dist[origem] = 0;  // a distância da quadra de origem até ela mesma é zero

    // loop principal do algoritmo de dijkstra, que percorre todas as quadras
    for (int i = 0; i < q; ++i) {
        int quadra_atual = -1;  // variável para armazenar a quadra atualmente sendo processada

        // procurando a quadra não visitada com a menor distância até agora
        for (int j = 0; j < q; ++j) {
            if (!visitado[j] && (quadra_atual == -1 || dist[j] < dist[quadra_atual])) {
                quadra_atual = j;  // atualiza a quadra atual se a quadra 'j' tem menor distância e ainda não foi visitada
            }
        }

        // se a menor distância encontrada for infinita, não há mais quadras acessíveis, então o loop é interrompido
        if (dist[quadra_atual] == INF) break;

        visitado[quadra_atual] = true;  // marca a quadra atual como visitada

        // explorando as ruas conectadas à quadra atual
        for (int j = 0; j < grafos[quadra_atual].tamanho; ++j) {
            rua r = grafos[quadra_atual].ruas[j];          // obtém a rua 'j' conectada à quadra atual
            int nova_dist = dist[quadra_atual] + r.tempo;  // calcula a nova distância até a quadra de destino através dessa rua

            // se a nova distância calculada for menor que a distância registrada, atualiza a distância
            if (nova_dist < dist[r.destino]) {
                dist[r.destino] = nova_dist;
            }
        }
    }

    // retorna a distância mínima até o destino; se for infinita, significa que não há caminho, e retorna -1
    return dist[destino] == INF ? -1 : dist[destino];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    // quantidade de quadras (q), ruas iniciais (r) e eventos (n)
    int q, r, n;
    cin >> q >> r >> n;  

    // cria um vetor de grafos para armazenar as ruas de cada quadra
    grafo grafos[MAX_Q];  

    // lendo as ruas iniciais
    for (int i = 0; i < r; ++i) {
        int a, b, m;
        cin >> a >> b >> m;                            // lê a quadra de origem (a), quadra de destino (b), e o tempo necessário (m)
        grafos[a].ruas[grafos[a].tamanho++] = {b, m};  // adiciona a rua no grafo correspondente à quadra de origem
    }

    // processando os eventos
    for (int i = 0; i < n; ++i) {
        int tipo;
        cin >> tipo; 
        
        // evento de nova rua
        if (tipo == 1) {
            // nova rua: origem (a), destino (b), e tempo (m)
            int a, b, m;
            cin >> a >> b >> m;         
            // adiciona essa rua ao grafo da quadra de origem
            grafos[a].ruas[grafos[a].tamanho++] = {b, m};   
        // evento de consulta de tempo mínimo
        } else if (tipo == 2) {
            // quadras de origem (a) e destino (b)
            int a, b;
            cin >> a >> b;                              
            // chama a função dijkstra para encontrar o menor tempo de 'a' até 'b' e imprime o resultado
            cout << dijkstra(a, b, grafos, q) << endl;  
        }
    }

    return 0;
}