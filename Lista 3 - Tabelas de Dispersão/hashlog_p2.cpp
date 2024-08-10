#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

struct conexao {
    uint32_t timestamp;
    uint32_t cliente;
};

class Hashtable {
   public:
    Hashtable(int m, float lmax)
        : M(m), Lmax(lmax), num_pares(0) {
        tabela.resize(M);
    }

    void inserir(uint32_t timestamp, uint32_t cliente) {
        verificar_rehashing();

        int pos = hash(timestamp);
        auto& lista = tabela[pos];

        // inserir a nova conexão de forma ordenada
        auto it = lista.begin();
        while (it != lista.end() && it->timestamp < timestamp) {
            ++it;
        }
        lista.insert(it, {timestamp, cliente});
        ++num_pares;

        // imprimir a posição e o tamanho da lista após inserção
        cout << pos << " " << lista.size() << endl;
    }

    void consultar(uint32_t timestamp) {
        int pos = hash(timestamp);
        auto& lista = tabela[pos];

        // procurar o cliente na lista
        int index = 0;
        for (const auto& c : lista) {
            if (c.timestamp == timestamp) {
                cout << c.cliente << " " << index << endl;
                return;
            }
            ++index;
        }
        cout << "-1 -1" << endl;
    }

   private:
    int M;                         // tamanho da tabela
    float Lmax;                    // fator de carga máximo
    int num_pares;                 // número total de pares
    vector<list<conexao>> tabela;  // tabela de hash

    int hash(uint32_t timestamp) const {
        return timestamp % M;
    }

    void verificar_rehashing() {
        float carga_atual = static_cast<float>(num_pares) / M;
        if (carga_atual > Lmax) {
            rehash();
        }
    }

    void rehash() {
        vector<list<conexao>> nova_tabela(2 * M + 1);
        M = 2 * M + 1;  // novo tamanho da tabela

        // redistribuir os pares na nova tabela
        for (const auto& lista : tabela) {
            for (const auto& c : lista) {
                int nova_pos = c.timestamp % M;
                nova_tabela[nova_pos].push_back(c);
            }
        }

        tabela = move(nova_tabela);  // substituir a tabela antiga
    }
};

int main() {
    int M;
    float Lmax;
    cin >> M >> Lmax;

    Hashtable hashtable(M, Lmax);

    string comando;
    while (cin >> comando) {
        if (comando == "END") {
            break;
        }

        uint32_t timestamp, cliente;
        if (comando == "NEW") {
            cin >> timestamp >> cliente;
            hashtable.inserir(timestamp, cliente);
        } else if (comando == "QRY") {
            cin >> timestamp;
            hashtable.consultar(timestamp);
        }
    }

    return 0;
}
