#include <cstdint>
#include <iostream>

using namespace std;

struct conexao {
    uint32_t timestamp;
    uint32_t cliente;

    bool operator<(const conexao &other) const {
        return timestamp < other.timestamp;
    }
};

// função para busca binária
int busca_binaria(conexao registros[], int num_registros, uint32_t timestamp) {
    int esquerda = 0, direita = num_registros - 1;
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        if (registros[meio].timestamp < timestamp) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return esquerda;  // posição onde o timestamp deve ser inserido
}

int main() {
    const int max_registros = 10000;  // definir o tamanho máximo do array
    conexao registros[max_registros];
    int num_registros = 0;
    string comando;

    while (cin >> comando) {
        if (comando == "END") {
            break;
        }

        if (comando == "NEW") {
            uint32_t timestamp, cliente;
            cin >> timestamp >> cliente;
            conexao nova_conexao = {timestamp, cliente};

            // encontrar a posição onde inserir usando busca binária
            int pos = busca_binaria(registros, num_registros, timestamp);

            // deslocar os elementos para a direita para inserir o novo elemento
            for (int i = num_registros; i > pos; --i) {
                registros[i] = registros[i - 1];
            }

            // inserir o novo elemento na posição correta
            registros[pos] = nova_conexao;
            num_registros++;
        } else if (comando == "QRY") {
            uint32_t timestamp;
            cin >> timestamp;
            int pos = busca_binaria(registros, num_registros, timestamp);

            if (pos < num_registros && registros[pos].timestamp == timestamp) {
                cout << registros[pos].cliente << " " << pos << endl;
            } else {
                cout << "-1 -1" << endl;
            }
        }
    }

    return 0;
}