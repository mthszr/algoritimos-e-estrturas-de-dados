#include <iostream>
using namespace std;

// definindo a estrutura do nó da árvore
struct node {
    int chave;               // id do dispositivo
    int peso;                // total de bytes transmitidos por este dispositivo
    int altura;              // altura do nó na árvore
    int pesototalsubarvore;  // soma dos pesps na subárvore com raiz neste nó
    node* left;
    node* right;

    // construtor que inicializa um nó com chave e peso
    node(int chave, int peso)
        : chave(chave), peso(peso), altura(1), pesototalsubarvore(peso), left(nullptr), right(nullptr) {}
};

// função que retorna a altura de um nó ou 0 se o nó for nulo
int getaltura(node* node) {
    return node ? node->altura : 0;
}

// função que retorna o peso total da subárvore de um nó ou 0 se o nó for nulo
int getpesototalsubarvore(node* node) {
    return node ? node->pesototalsubarvore : 0;
}

// função que atualiza a altura e o peso total da subárvore de um nó
void atualizano(node* node) {
    if (node) {                                                                                                          // se o nó não for nulo
        node->altura = 1 + max(getaltura(node->left), getaltura(node->right));                                           // calcula a nova altura
        node->pesototalsubarvore = node->peso + getpesototalsubarvore(node->left) + getpesototalsubarvore(node->right);  // calcula o novo peso total da subárvore
    }
}

// realiza uma rotação simples à direita em um nó y
node* rotacaodireita(node* y) {
    node* x = y->left;    // define x como o filho à esquerda de y
    node* t2 = x->right;  // t2 é o filho à direita de x (subárvore que será reposicionada)

    x->right = y;  // x se torna a nova raiz da subárvore
    y->left = t2;  // t2 se torna o filho à esquerda de y

    atualizano(y);  // atualiza altura e peso total da subárvore para y
    atualizano(x);  // atualiza altura e peso total da subárvore para x

    return x;  // retorna a nova raiz da subárvore
}

// realiza uma rotação simples à esquerda em um nó x
node* rotacaoesquerda(node* x) {
    node* y = x->right;  // define y como o filho à direita de x
    node* t2 = y->left;  // t2 é o filho à esquerda de y (subárvore que será reposicionada)

    y->left = x;    // y se torna a nova raiz da subárvore
    x->right = t2;  // t2 se torna o filho à direita de x

    atualizano(x);  // atualiza altura e peso total da subárvore para x
    atualizano(y);  // atualiza altura e peso total da subárvore para y

    return y;  // retorna a nova raiz da subárvore
}

// retorna o fator de balanceamento de um nó (diferença entre altura da subárvore esquerda e direita)
int getbalanco(node* node) {
    return node ? getaltura(node->left) - getaltura(node->right) : 0;
}

// função para inserir um novo nó na árvore e manter o balanceamento
node* insert(node* raiz, int chave, int peso) {
    // caso base: se a raiz é nula, cria um novo nó e o retorna
    if (!raiz) return new node(chave, peso);

    // se a chave é menor, insere na subárvore esquerda
    if (chave < raiz->chave)
        raiz->left = insert(raiz->left, chave, peso);
    // se a chave é maior, insere na subárvore direita
    else if (chave > raiz->chave)
        raiz->right = insert(raiz->right, chave, peso);
    // se a chave já existe, apenas adiciona o peso ao nó existente
    else {
        raiz->peso += peso;
        raiz->pesototalsubarvore += peso;
        return raiz;  // retorna o nó sem mudanças estruturais na árvore
    }

    // recalcula a altura e o peso total da subárvore após a inserção
    atualizano(raiz);

    // verifica o fator de balanceamento para determinar se rotações são necessárias
    int balanco = getbalanco(raiz);

    // caso 1: rotação simples à direita
    if (balanco > 1 && chave < raiz->left->chave)
        return rotacaodireita(raiz);

    // caso 2: rotação simples à esquerda
    if (balanco < -1 && chave > raiz->right->chave)
        return rotacaoesquerda(raiz);

    // caso 3: rotação dupla à esquerda e depois à direita
    if (balanco > 1 && chave > raiz->left->chave) {
        raiz->left = rotacaoesquerda(raiz->left);
        return rotacaodireita(raiz);
    }

    // caso 4: rotação dupla à direita e depois à esquerda
    if (balanco < -1 && chave < raiz->right->chave) {
        raiz->right = rotacaodireita(raiz->right);
        return rotacaoesquerda(raiz);
    }

    // retorna a nova raiz da subárvore (pode ser a mesma se nenhuma rotação foi necessária)
    return raiz;
}


int calcularrank(node* raiz, int chave) {
    // se o nó é nulo, não há peso para somar
    if (!raiz)
        return 0;

    // se a chave no nó atual é maior ou igual à chave fornecida, busca na subárvore esquerda
    if (raiz->chave >= chave)
        return calcularrank(raiz->left, chave);

    // se a chave no nó atual é menor, soma o peso deste nó, o peso da subárvore esquerda, e continua buscando na direita
    else {
        int x = raiz->peso; // peso do nó atual
        int y = getpesototalsubarvore(raiz->left); // peso total da subárvore esquerda
        int z = calcularrank(raiz->right, chave); // continua a busca na subárvore direita
        return x + y + z; // retorna a soma dos pesos
    }
}

int main() {
    node* root = nullptr; 
    string command;        
    int totalweight = 0; 

    // loop para ler os comandos até o fim da entrada
    while (cin >> command) {
        if (command == "END") break; // se o comando for "end", termina o loop

        int x, w; // variáveis para armazenar os valores de x e w
        if (command == "WEI") {
            cin >> x >> w; // lê os valores de x e w
            root = insert(root, x, w); // insere na árvore
            totalweight += w; // atualiza o peso total
            cout << totalweight << endl; // imprime o peso total
        } else if (command == "WEI") {
            cin >> x;  // lê o valor de x
            int depth = 0; // variável para armazenar a profundidade do nó
            node* result = root; // começa a busca na raiz
            while (result && result->chave != x) { // busca pelo nó com chave x
                if (x < result->chave) { // se x for menor, vai para a esquerda
                    result = result->left;  
                } else { // se x for maior, vai para a direita
                    result = result->right;  
                }
                depth++; // incrementa a profundidade a cada passo
            }
            if (result) {
                cout << result->peso << " " << depth << endl; // se o nó for encontrado, imprime o peso e a profundidade
            } else {
                cout << "0 -1" << endl; // se o nó não for encontrado, imprime "0 -1"
            }
        } else if (command == "RNK") {
            cin >> x; // lê o valor de x
            cout << calcularrank(root, x) << endl; // calcula e imprime o rank de x
        }
    }

    return 0;
}