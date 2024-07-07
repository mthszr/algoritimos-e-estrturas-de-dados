#include <iostream>
using namespace std;

class Pilha {
private:
    int* pilha; // ponteiro para a pilha
    int capacidade; // capacidade atual da pilha
    int topo; // indice do topo da pilha (-1 se vazia)

public:
    Pilha() : pilha(nullptr), capacidade(0), topo(-1) {} // construtor

    // função para adicionar um elemento à pilha
    void empilhar (int elemento) {

        // se a capacidade for zero, aloca espaço inicial
        if (capacidade == 0) {
            capacidade = 2;
            pilha = new int[capacidade];
        }

        // redimensiona o vetor, caso necessário
        if (topo + 1 >= capacidade) {
            capacidade *= 2;
            int* novaPilha = new int[capacidade];
            for (int i = 0; i <= topo; i++) {
                novaPilha[i] = pilha[i];
            }
            delete[] pilha;
            pilha = novaPilha; 
        }    

        // adiciona elemento ao vetor
        pilha[++topo] = elemento;
    
    }

    // função para verificar se a pilha está vazia
    bool vazia() {
        return topo == -1;
    }

    void processarParidade() {
        bool paridade = true;
        while (topo >= 1 && paridade) {
            if (pilha[topo] % 2 == pilha[topo - 1] % 2) {
                int novoValor = abs(pilha[topo] - pilha[topo - 1]);
                topo--;                  // remove o elemento abaixo
                pilha[topo] = novoValor; // substitui o novo valor no topo
                
            } else {
                paridade = false; // Encerra o loop se não houver mais paridade
            }
        }
    }

    int tamanho () {
        return topo + 1;
    }

    int top () {
        if (topo >= 0) {
            return pilha[topo]; // elemento no topo da pilha
        }
        return - 1; // retorna -1 se a pilha estiver vazia
    }
};

int main () {

    int t; // numero de casos
    cin >> t;

    Pilha casos[t];
    int elemento;

    // recebe os elementos e adiciona nas pilha
    // e em seguida verifica a paridade do topo e topo - 1
    for (int i = 0; i < t; i++) {
        while (true) {
            cin >> elemento;
            if (elemento == 0) {
                break;
            }
            casos[i].empilhar(elemento);
            casos[i].processarParidade();
        }
    }

    // e imprime o número de elementos e o elemento do topo
    for (int i = 0; i < t; ++i) {
        cout << "Pilha " << i + 1 << ": ";
        cout << casos[i].tamanho() << " " << casos[i].top() << endl;
    }


    return 0;
}