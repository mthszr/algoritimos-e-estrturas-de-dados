// https://iudex.io/problem/62e444b2f485b80001381e27

#include <iostream>
#include <cstdint>

         using namespace std;

struct Par {
    uint32_t timestamp;
    uint32_t cliente;
    // estrutura para armazenar o timestamp e o cliente associado
};

class TabelaHash {
   private:
    Par** tabela;         // array de ponteiros para arrays de Par, representando as listas de colisão
    int* tamanhos;        // array que armazena o tamanho de cada lista (número de elementos)
    int M;                // tamanho da tabela hash (número de listas)
    float fatorCargaMax;  // fator de carga máximo permitido antes de um rehash
    int contador;         // contador total de elementos na tabela

    // função de hash simples que retorna o índice na tabela usando o módulo do timestamp
    int funcaoHash(uint32_t T) {
        return T % M;
    }

    // calcula o fator de carga atual da tabela
    float fator_carga() {
        return static_cast<float>(contador) / M;
    }

    // função para redimensionar a tabela hash quando o fator de carga excede o limite
    void rehash() {
        int M_antigo = M;                    // armazena o tamanho antigo da tabela
        M = 2 * M + 1;                       // dobra o tamanho da tabela e soma 1 para manter um número ímpar
        Par** nova_tabela = new Par*[M];     // cria uma nova tabela com o novo tamanho
        int* novos_tamanhos = new int[M]();  // inicializa os tamanhos das novas listas para zero

        // inicializa os ponteiros das novas listas para nullptr
        for (int i = 0; i < M; ++i) {
            nova_tabela[i] = nullptr;
            novos_tamanhos[i] = 0;
        }

        // realoca todos os elementos da tabela antiga para a nova tabela
        for (int i = 0; i < M_antigo; ++i) {
            for (int j = 0; j < tamanhos[i]; ++j) {
                Par p = tabela[i][j];                      // copia cada elemento das listas antigas
                int novoIndice = funcaoHash(p.timestamp);  // calcula o novo índice na nova tabela

                novos_tamanhos[novoIndice]++;  // incrementa o tamanho da nova lista
                Par* novoArray = new Par[novos_tamanhos[novoIndice]];

                // insere o elemento na posição correta, mantendo a ordem na nova lista
                int k = 0;
                while (k < novos_tamanhos[novoIndice] - 1 && nova_tabela[novoIndice] && nova_tabela[novoIndice][k].timestamp < p.timestamp) {
                    novoArray[k] = nova_tabela[novoIndice][k];
                    k++;
                }

                novoArray[k] = p;

                // copia os elementos restantes da lista antiga
                while (k < novos_tamanhos[novoIndice] - 1) {
                    novoArray[k + 1] = nova_tabela[novoIndice][k];
                    k++;
                }

                delete[] nova_tabela[novoIndice];     // libera a memória da lista antiga
                nova_tabela[novoIndice] = novoArray;  // atualiza a lista com a nova
            }
            delete[] tabela[i];  // libera a memória da lista antiga na posição `i`
        }

        delete[] tabela;            // libera a memória da tabela antiga
        delete[] tamanhos;          // libera a memória do array de tamanhos antigo
        tabela = nova_tabela;       // aponta para a nova tabela
        tamanhos = novos_tamanhos;  // atualiza o array de tamanhos
    }

   public:
    // construtor que inicializa a tabela hash com o tamanho inicial e o fator de carga máximo
    TabelaHash(int M_inicial, float fatorCargaMaximo) : M(M_inicial), fatorCargaMax(fatorCargaMaximo), contador(0) {
        tabela = new Par*[M];     // aloca a tabela com `M` listas
        tamanhos = new int[M]();  // inicializa o array de tamanhos com zeros
        for (int i = 0; i < M; ++i) {
            tabela[i] = nullptr;  // inicializa todas as listas como vazias
        }
    }

    // destrutor que libera toda a memória alocada
    ~TabelaHash() {
        for (int i = 0; i < M; ++i) {
            delete[] tabela[i];  // libera a memória de cada lista na tabela
        }
        delete[] tabela;    // libera a memória do array de ponteiros da tabela
        delete[] tamanhos;  // libera a memória do array de tamanhos
    }

    void inserir(uint32_t T, uint32_t C) {
        // se o fator de carga exceder o limite, redimensiona a tabela
        if (fator_carga() > fatorCargaMax) {
            rehash();
        }

        int indice = funcaoHash(T);             // calcula o índice na tabela
        int tamanho = tamanhos[indice];         // obtém o tamanho atual da lista nesse índice
        Par* novoArray = new Par[tamanho + 1];  // cria um novo array para a lista, com espaço extra para o novo elemento

        // busca binária para encontrar a posição correta de inserção na lista ordenada
        int baixo = 0, alto = tamanho;
        while (baixo < alto) {
            int meio = (baixo + alto) / 2;
            if (tabela[indice][meio].timestamp < T) {
                baixo = meio + 1;
            } else {
                alto = meio;
            }
        }

        // copia os elementos da lista antiga até a posição de inserção
        for (int i = 0; i < baixo; ++i) {
            novoArray[i] = tabela[indice][i];
        }

        novoArray[baixo] = {T, C};  // insere o novo elemento na posição correta

        // copia os elementos restantes após a posição de inserção
        for (int i = baixo; i < tamanho; ++i) {
            novoArray[i + 1] = tabela[indice][i];
        }

        delete[] tabela[indice];     // libera a memória do array antigo da lista
        tabela[indice] = novoArray;  // atualiza a lista com o novo array
        tamanhos[indice]++;          // incrementa o tamanho da lista
        contador++;                  // incrementa o contador total de elementos na tabela

        // imprime o índice e o tamanho atual da lista no índice
        cout << indice << " " << tamanhos[indice] << endl;
    }

    void consultar(uint32_t T) {
        int indice = funcaoHash(T);      // calcula o índice na tabela
        int tamanho = tamanhos[indice];  // obtém o tamanho da lista nesse índice

        // busca binária para encontrar a posição do elemento na lista
        int baixo = 0, alto = tamanho;
        while (baixo < alto) {
            int meio = (baixo + alto) / 2;
            if (tabela[indice][meio].timestamp < T) {
                baixo = meio + 1;
            } else {
                alto = meio;
            }
        }

        // verifica se o elemento foi encontrado e imprime o cliente e a posição
        if (baixo < tamanho && tabela[indice][baixo].timestamp == T) {
            cout << tabela[indice][baixo].cliente << " " << baixo << endl;
        } else {
            // se o elemento não foi encontrado, imprime "-1 -1"
            cout << "-1 -1" << endl;
        }
    }
};

int main() {
    int M;
    float fatorCargaMax;
    cin >> M >> fatorCargaMax;

    TabelaHash th(M, fatorCargaMax);

    string comando;
    while (cin >> comando) {
        if (comando == "END")
            break;
        else if (comando == "NEW") {
            uint32_t T, C;
            cin >> T >> C;
            th.inserir(T, C);
        } else if (comando == "QRY") {
            uint32_t T;
            cin >> T;
            th.consultar(T);
        }
    }

    return 0;
}
