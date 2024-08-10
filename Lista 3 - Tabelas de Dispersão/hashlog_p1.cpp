// https://iudex.io/problem/63e163178216f900013be1a5

#include <cstdint>
#include <iostream>

using namespace std;

// definindo a estrutura para armazenar informações da conexão
struct conexao {
    uint32_t timestamp;
    uint32_t cliente;  // armazena o IP do cliente

    // sobrecarga do operador < para comparar conexões com base no timestamp
    bool operator<(const conexao& other) const {
        return timestamp < other.timestamp;
    }
};

// função para busca binária em um array de registros
int busca_binaria(conexao registros[], int num_registros, uint32_t timestamp) {
    int esquerda = 0, direita = num_registros - 1;
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        // se o timestamp do meio for menor que o timestamp buscado
        if (registros[meio].timestamp < timestamp) {
            esquerda = meio + 1; // move o limite esquerdo para a direita
        } else {
            direita = meio - 1; // move o limite direito para a esquerda
        }
    }
    return esquerda; // posição onde o timestamp deve ser inserido
}

int main() {
    int capacidade = 10; // capacidade inicial
    conexao* registros = new conexao[capacidade];
    int num_registros = 0; // inicializa o contador de registros
    string comando;  // variável para armazenar os comandos de entrada

    // loop principal para processar comandos
    while (cin >> comando) {
        if (comando == "END") {
            break; // encerra o loop se o comando for "END"
        }

        if (comando == "NEW") {
            if (num_registros >= capacidade) { // se o array ficou cheio
                capacidade *= 2; // dobra a capacidade
                conexao* novo_array = new conexao[capacidade];

                // copia os elementos do array antigo para o novo
                for (int i = 0; i < num_registros; i++) {
                    novo_array[i] = registros[i];
                }

                // libera a memória do array antigo
                delete[] registros;
                registros = novo_array;
            }

            uint32_t timestamp, cliente;
            cin >> timestamp >> cliente; // le o timestamp e o IP do cliente
            conexao nova_conexao = {timestamp, cliente}; // cria uma nova conexão

            // encontra a posição onde inserir usando busca binária
            int pos = busca_binaria(registros, num_registros, timestamp);

            // deslocar os elementos para a direita para inserir o novo elemento
            for (int i = num_registros; i > pos; --i) {
                registros[i] = registros[i - 1];
            }

            // insere o novo elemento na posição correta
            registros[pos] = nova_conexao;
            num_registros++;
        } else if (comando == "QRY") {
            uint32_t timestamp;
            cin >> timestamp; // le o timestamp a ser consultado
            int pos = busca_binaria(registros, num_registros, timestamp); // busca a posição do timestamp

            // verifica se o timestamp existe na posição encontrada
            if (pos < num_registros && registros[pos].timestamp == timestamp) {
                cout << registros[pos].cliente << " " << pos << endl;
            } else {
                cout << "-1 -1" << endl;
            }
        }
    }

    delete[] registros;

    return 0;
}