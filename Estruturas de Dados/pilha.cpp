#include <iostream>
using namespace std;

class Pilha {
private:
    int* pilha; // ponteiro para a pilha
    int capacidade; // capacidade atual da pilha
    int topo; // indice do topo da pilha (-1 se vazia)

public:
    Pilha() : pilha(nullptr), capacidade(0), topo(-1) {}

    ~Pilha() {
        delete[] pilha;
    }

    // função para adicionar um elemento à pilha
    void empilhar (int elemento) {

        // se a capacidade for zero, aloca espaço inicial
        if (capacidade == 0) {
            capacidade = 2;
            pilha = new int[capacidade];
        }

        // redimensiona a pilha, caso necessário
        if (topo + 1 >= capacidade) {
            capacidade++;
            int* novaPilha = new int[capacidade];
            for (int i = 0; i <= topo; i++) {
                novaPilha[i] = pilha[i];
            }
            delete[] pilha;
            pilha = novaPilha; 
        }    

        // adiciona elemento à pilha
        pilha[++topo] = elemento;
    
    }

    // função para verificar se a pilha está vazia
    bool vazia() {
        return topo == -1;
    }

    // função para imprimir os elementos da pilha, de baixo para cima
    void imprimirElementos () {
        cout << "Elementos da pilha:" << endl;
        for (int i = 0; i <= topo; i++) {
            cout << pilha[i] << " ";
        }
    }
};