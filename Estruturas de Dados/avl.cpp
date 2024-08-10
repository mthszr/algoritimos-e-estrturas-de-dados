#include <iostream>
using namespace std;

// estrutura do nó
struct Node {
    int chave;       // valor da chave do nó
    Node *esquerda;  // ponteiro para o filho esquerdo
    Node *direita;   // ponteiro para o filho direito
    Node *pai;       // ponteiro para o pai do nó
    int altura;      // altura do nó

    Node(int chave, Node *pai = nullptr) : chave(chave), esquerda(nullptr), direita(nullptr), pai(pai), altura(1) {}
};

class AVLTree {
private:
    Node *raiz;

    // função para obter a altura do nó, retorna 0 se o nó não existe
    int obterAltura(Node *N) {
        if (N == nullptr)
            return 0;
        return N->altura;
    }

    // função para rotacionar à direita a subárvore enraizada no nó y
    Node *rotacionarDireita(Node *y) {
        Node *x = y->esquerda;  // x é o filho esquerdo de y
        Node *T2 = x->direita;  // T2 é o filho direito de x

        // realiza a rotação à direita
        x->direita = y;    // o filho direito de x passa a ser y
        y->esquerda = T2;  // o filho esquerdo de y passa a ser T2

        // atualiza o ponteiro do pai
        if (T2 != nullptr) {
            T2->pai = y;  // atualiza o pai de T2 para y
        }
        x->pai = y->pai;  // atualiza o pai de x para o pai original de y
        y->pai = x;       // atualiza o pai de y para x

        // atualiza as alturas
        y->altura = max(obterAltura(y->esquerda), obterAltura(y->direita)) + 1;
        x->altura = max(obterAltura(x->esquerda), obterAltura(x->direita)) + 1;

        // retorna a nova raiz da subárvore
        return x;
    }

    // função para rotacionar à esquerda a subárvore enraizada no nó x
    Node *rotacionarEsquerda(Node *x) {
        Node *y = x->direita;    // y é o filho direito de x
        Node *T2 = y->esquerda;  // T2 é o filho esquerdo de y

        // realiza a rotação à esquerda
        y->esquerda = x;  // o filho esquerdo de y passa a ser x
        x->direita = T2;  // o filho direito de x passa a ser T2

        // atualiza o ponteiro do pai
        if (T2 != nullptr) {
            T2->pai = x;  // atualiza o pai de T2 para x
        }
        y->pai = x->pai;  // atualiza o pai de y para o pai original de x
        x->pai = y;       // atualiza o pai de x para y

        // atualiza as alturas
        x->altura = max(obterAltura(x->esquerda), obterAltura(x->direita)) + 1;
        y->altura = max(obterAltura(y->esquerda), obterAltura(y->direita)) + 1;

        // retorna a nova raiz da subárvore
        return y;
    }

    // obtém o fator de balanceamento do nó N
    int obterBalanceamento(Node *N) {
        if (N == nullptr)
            return 0;
        return obterAltura(N->esquerda) - obterAltura(N->direita);
    }

    // função recursiva para inserir uma chave na subárvore enraizada com o nó
    // retorna a nova raiz da subárvore
    Node *inserir(Node *node, int chave, Node *pai) {
        // insere o novo nó
        if (node == nullptr)
            return new Node(chave, pai);

        // insere na subárvore esquerda se a chave for menor que a chave do nó
        if (chave < node->chave)
            node->esquerda = inserir(node->esquerda, chave, node);
        // insere na subárvore direita se a chave for maior que a chave do nó
        else if (chave > node->chave)
            node->direita = inserir(node->direita, chave, node);
        else  // chaves iguais não são permitidas
            return node;

        // 2. atualiza a altura deste nó ancestral
        node->altura = 1 + max(obterAltura(node->esquerda), obterAltura(node->direita));

        // 3. obtém o fator de balanceamento deste nó ancestral
        // para verificar se este nó ficou desbalanceado
        int balanceamento = obterBalanceamento(node);

        // se este nó ficou desbalanceado, então há 4 casos

        // caso esquerda-esquerda
        if (balanceamento > 1 && chave < node->esquerda->chave)
            return rotacionarDireita(node);

        // caso direita-direita
        if (balanceamento < -1 && chave > node->direita->chave)
            return rotacionarEsquerda(node);

        // caso esquerda-direita
        if (balanceamento > 1 && chave > node->esquerda->chave) {
            node->esquerda = rotacionarEsquerda(node->esquerda);
            return rotacionarDireita(node);
        }

        // caso direita-esquerda
        if (balanceamento < -1 && chave < node->direita->chave) {
            node->direita = rotacionarDireita(node->direita);
            return rotacionarEsquerda(node);
        }

        // retorna o ponteiro do nó 
        return node;
    }

    // função para buscar uma chave na árvore
    Node *buscar(Node *raiz, int chave) {
        // caso base: raiz é nula ou a chave está presente na raiz
        if (raiz == nullptr || raiz->chave == chave)
            return raiz;

        // a chave é maior que a chave da raiz, então busca na subárvore direita
        if (raiz->chave < chave)
            return buscar(raiz->direita, chave);

        // a chave é menor que a chave da raiz, então busca na subárvore esquerda
        return buscar(raiz->esquerda, chave);
    }

    // função para encontrar o valor mínimo na árvore
    Node *encontrarMinimo(Node *node) {
        Node *atual = node;
        // percorre a subárvore esquerda para encontrar o nó mais à esquerda
        while (atual->esquerda != nullptr)
            atual = atual->esquerda;
        return atual;
    }

    // função para encontrar o valor máximo na árvore
    Node *encontrarMaximo(Node *node) {
        Node *atual = node;
        // percorre a subárvore direita para encontrar o nó mais à direita
        while (atual->direita != nullptr)
            atual = atual->direita;
        return atual;
    }

    // função para encontrar o sucessor de um nó na árvore avl
    Node *encontrarSucessor(Node *node) {
        // se o nó tem um filho direito, o sucessor é o menor nó na subárvore direita
        if (node->direita != nullptr)
            return encontrarMinimo(node->direita);

        // caso contrário, o sucessor é um dos ancestrais
        Node *pai = node->pai;
        while (pai != nullptr && node == pai->direita) {
            node = pai;
            pai = pai->pai;
        }
        return pai;
    }

    // função para encontrar o antecessor de um nó na árvore avl
    Node *encontrarAntecessor(Node *node) {
        // se o nó tem um filho esquerdo, o antecessor é o maior nó na subárvore esquerda
        if (node->esquerda != nullptr)
            return encontrarMaximo(node->esquerda);

        // caso contrário, o antecessor é um dos ancestrais
        Node *pai = node->pai;
        while (pai != nullptr && node == pai->esquerda) {
            node = pai;
            pai = pai->pai;
        }
        return pai;
    }

    // função para transplantar uma subárvore enraizada no nó u por outra subárvore enraizada no nó v
    void transplantar(Node *&raiz, Node *u, Node *v) {
        if (u->pai == nullptr) {
            raiz = v;  // se u for a raiz, a nova raiz é v
        } else if (u == u->pai->esquerda) {
            u->pai->esquerda = v;  // se u for o filho esquerdo de seu pai, substitui-o por v
        } else {
            u->pai->direita = v;  // se u for o filho direito de seu pai, substitui-o por v
        }
        if (v != nullptr) {
            v->pai = u->pai;  // atualiza o pai de v para o pai de u
        }
    }

    // função para deletar um nó na árvore
    Node *deletarNode(Node *raiz, int chave) {
        // passo 1: realiza a deleção padrão
        if (raiz == nullptr)
            return raiz;

        // encontra o nó a ser deletado
        if (chave < raiz->chave)
            raiz->esquerda = deletarNode(raiz->esquerda, chave);
        else if (chave > raiz->chave)
            raiz->direita = deletarNode(raiz->direita, chave);
        else {
            // nó com apenas um filho ou nenhum filho
            if (raiz->esquerda == nullptr) {
                Node *temp = raiz->direita;
                transplantar(raiz, raiz, raiz->direita);
                delete raiz;  // deleta o nó
                raiz = temp;  // atualiza a raiz
            } else if (raiz->direita == nullptr) {
                Node *temp = raiz->esquerda;
                transplantar(raiz, raiz, raiz->esquerda);
                delete raiz;  // deleta o nó
                raiz = temp;  // atualiza a raiz
            } else {
                // nó com dois filhos: obtém o sucessor (menor na subárvore direita)
                Node *temp = encontrarMinimo(raiz->direita);

                // cópia do valor do sucessor para este nó
                raiz->chave = temp->chave;

                // deleta o sucessor
                raiz->direita = deletarNode(raiz->direita, temp->chave);
            }
        }

        // se a árvore tinha apenas um nó então retorna
        if (raiz == nullptr)
            return raiz;

        // passo 2: atualiza a altura do nó atual
        raiz->altura = 1 + max(obterAltura(raiz->esquerda), obterAltura(raiz->direita));

        // passo 3: obtém o fator de balanceamento deste nó
        // (para verificar se este nó ficou desbalanceado)
        int balanceamento = obterBalanceamento(raiz);

        // se este nó ficou desbalanceado, então há 4 casos

        // caso esquerda-esquerda
        if (balanceamento > 1 && obterBalanceamento(raiz->esquerda) >= 0)
            return rotacionarDireita(raiz);

        // caso esquerda-direita
        if (balanceamento > 1 && obterBalanceamento(raiz->esquerda) < 0) {
            raiz->esquerda = rotacionarEsquerda(raiz->esquerda);
            return rotacionarDireita(raiz);
        }

        // caso direita-direita
        if (balanceamento < -1 && obterBalanceamento(raiz->direita) <= 0)
            return rotacionarEsquerda(raiz);

        // caso direita-esquerda
        if (balanceamento < -1 && obterBalanceamento(raiz->direita) > 0) {
            raiz->direita = rotacionarDireita(raiz->direita);
            return rotacionarEsquerda(raiz);
        }

        return raiz;
    }

    // função para imprimir o encaminhamento em pré-ordem da árvore
    void preOrdem(Node *node) {
        if (node != nullptr) {
            cout << node->chave << " ";
            preOrdem(node->esquerda);
            preOrdem(node->direita);
        }
    }

    // função para imprimir o encaminhamento em ordem da árvore
    void emOrdem(Node *node) {
        if (node != nullptr) {
            emOrdem(node->esquerda);
            cout << node->chave << " ";
            emOrdem(node->direita);
        }
    }

    // função para imprimir o encaminhamento em pós-ordem da árvore
    void posOrdem(Node *node) {
        if (node != nullptr) {
            posOrdem(node->esquerda);
            posOrdem(node->direita);
            cout << node->chave << " ";
        }
    }

public:
    AVLTree() : raiz(nullptr) {}

    void inserir(int chave) {
        raiz = inserir(raiz, chave, nullptr);
    }

    Node* buscar(int chave) {
        return buscar(raiz, chave); 
    }

    void deletar(int chave) {
        raiz = deletarNode(raiz, chave);
    }

    void preOrdem() {
        preOrdem(raiz);
    }

    void emOrdem() {
        emOrdem(raiz);
        cout << "\n";
    }

    void posOrdem() {
        posOrdem(raiz);
        cout << "\n";
    }
};