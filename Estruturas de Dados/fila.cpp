#include <iostream>
using namespace std;

// fila implementada usando uma estrutura de lista encadeada

class Fila {
    // definindo a estrutura do nó
    struct Node {
        int dado;
        Node* proximo; // ponteiro para o próximo nó
    };

private:
    Node* inicio; // ponteiro para o primeiro elemento da fila
    Node* fim; // ponteiro para o último elemento da fila
    int tamanho;

public:
    // construtor
    Fila() : inicio(nullptr), fim(nullptr), tamanho(0) {}
    
    // função para verificar se a pilha está vazia
    bool estaVazia() {
        return (inicio == nullptr);
    }

    // função para adicionar um elemento à fila
    void enfileirar (int elemento) {
        Node* novoNode = new Node(); // cria um novo nó
        novoNode->dado = elemento; // atribui o valor do elemento ao nó
        novoNode->proximo = nullptr; // define o ponteiro para o próximo nó como nulo (último da fila)
        
        if(estaVazia()) { // se a fila estiver vazia
            inicio = novoNode; // o novo nó é a frente da fila
            fim = novoNode; // o novo nó também é final da fila
        } else { // se a fila não estiver vazia
            fim->proximo = novoNode; // adiciona o novo nó após o nó final atual
            fim = novoNode; // atualiza o nó final para o novo nó
        }
        tamanho++;
    }

    // função para remover um elemento da fila
    int desenfileirar () {
        if (estaVazia()) { // se a fila estiver vazia
            return INT_MIN;
        }

        Node *temp = inicio; // armazena o nó da frente em um ponteiro temporário
        int item = inicio->dado; // armazena o valor do nó da frente
        inicio = inicio->proximo; // atualiza o ponteiro da frente para o próximo nó

        if (inicio == nullptr) { // se a fila ficou vazia após a remoção
            fim = nullptr; // atualiza o ponteiro do final para nulo
        }
        delete temp; 
        tamanho--;   
        return item; // retorna o valor do nó removido
    }

    // função que retorna o primeiro elemento da fila
    int primeiroElemento () {
        if (estaVazia()) {
            return INT_MIN;
        }
        return inicio->dado;
    }

    // função que retorna o último elemento da fila
    int ultimoElemento() {
        if (estaVazia()) {
            return INT_MIN;
        }
        return fim->dado;
    }

    int tamanhoF () {
        return tamanho;
    }

    // destrutor
    ~Fila() {
        while (!estaVazia()) { // enquanto a fila não está vazia
            desenfileirar(); // remove cada elemento da fila
        }
    }
};