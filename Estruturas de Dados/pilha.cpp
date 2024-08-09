#include <iostream>
using namespace std;

class Pilha {
   private:
    int* pilha;      // ponteiro para a pilha
    int capacidade;  // capacidade atual da pilha
    int topo;        // indice do topo da pilha (-1 se vazia)

   public:
    // construtor
    Pilha() : pilha(nullptr), capacidade(0), topo(-1) {}

    // destrutor
    ~Pilha() {
        delete[] pilha;
    }

    // função para adicionar um elemento à pilha
    void empilhar(int elemento) {
        // se a capacidade for zero, aloca espaço inicial
        if (capacidade == 0) {
            capacidade = 2;
            pilha = new int[capacidade];
        }

        // redimensiona a pilha, caso necessário
        if (topo + 1 >= capacidade) {
            capacidade *= 2;
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

    int desempilhar() {
        if (estaVazia()) {
            throw runtime_error("A pilha está vazia");  // lança exceção se a pilha estiver vazia
        }
        return pilha[topo--];  // retorna o elemento do topo e decrementa o índice do topo
    }

    // função para verificar se a pilha está vazia
    bool estaVazia() {
        return topo == -1;
    }
    // função para imprimir os elementos da pilha, de baixo para cima
    void imprimir() {
        cout << "Elementos da pilha:" << endl;
        for (int i = 0; i <= topo; i++) {
            cout << pilha[i] << " ";
        }
    }

    // função que retorna o tamanho da pilha
    int tamanho() {
        return topo + 1;
    }

    // função que retorna o elemento no topo da pilha
    int top() {
        if (topo >= 0) {
            return pilha[topo];  // elemento no topo da pilha
        }
        return -1;  // retorna -1 se a pilha estiver vazia
    }
};