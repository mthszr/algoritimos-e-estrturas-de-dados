#include <iostream>  
#include <string>    
using namespace std; 

// estrutura representando um nó na árvore bst
struct Node
{
    string name;  // nome do jogador
    int score;    // pontuação do jogador
    Node *left;   // ponteiro para o filho esquerdo
    Node *right;  // ponteiro para o filho direito
    Node *parent; // ponteiro para o nó pai

    // construtor para inicializar um nó
    Node(string name, int score) : name(name), score(score), left(nullptr), right(nullptr), parent(nullptr) {}
};

// classe representando a árvore de busca binária (bst)
class BST
{
private:
    Node *root; // ponteiro para a raiz da bst

    // função recursiva para adicionar um nó à bst
    void addNode(Node *&node, Node *parent, const string &name, int score)
    {
        if (!node)
        {                                                     // se a posição atual estiver vazia
            node = new Node(name, score);                     // cria um novo nó
            node->parent = parent;                            // define o pai do novo nó
            cout << name << " inserido com sucesso!" << endl; // imprime mensagem de sucesso
        }
        else if (name == node->name)
        {                                                   // se o nome já existir
            cout << name << " ja esta no sistema." << endl; // imprime mensagem de duplicação
        }
        else if (score < node->score)
        {                                           // se a pontuação for menor que a pontuação do nó atual
            addNode(node->left, node, name, score); // adiciona recursivamente à subárvore esquerda
        }
        else
        {                                            // se a pontuação for maior ou igual à pontuação do nó atual
            addNode(node->right, node, name, score); // adiciona recursivamente à subárvore direita
        }
    }

    // função recursiva para encontrar um nó pela pontuação
    Node *findNode(Node *node, int score)
    {
        if (!node || node->score == score)
            return node; // se o nó for nulo ou a pontuação for encontrada
        if (score < node->score)
            return findNode(node->left, score); // busca na subárvore esquerda
        return findNode(node->right, score);    // busca na subárvore direita
    }

    // função para encontrar o nó com a menor pontuação
    Node *findMin(Node *node)
    {
        while (node->left)
            node = node->left; // percorre até o nó mais à esquerda
        return node;           // retorna o nó mínimo
    }

    // função para encontrar o nó com a maior pontuação
    Node *findMax(Node *node)
    {
        while (node->right)
            node = node->right; // percorre até o nó mais à direita
        return node;            // retorna o nó máximo
    }

    // função para encontrar o sucessor de um nó
    Node *findSuccessor(Node *node)
    {
        if (node->right)
            return findMin(node->right); // se existir subárvore direita, encontra o mínimo nela
        Node *parent = node->parent;     // caso contrário, percorre para cima usando os ponteiros de pai
        while (parent && node == parent->right)
        {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    // função para encontrar o predecessor de um nó
    Node *findPredecessor(Node *node)
    {
        if (node->left)
            return findMax(node->left); // se existir subárvore esquerda, encontra o máximo nela
        Node *parent = node->parent;    // caso contrário, percorre para cima usando os ponteiros de pai
        while (parent && node == parent->left)
        {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

public:
    // construtor para inicializar a bst
    BST() : root(nullptr) {}

    // função para adicionar um jogador à bst
    void addPlayer(const string &name, int score)
    {
        addNode(root, nullptr, name, score); // chama a função recursiva addNode
    }

    // função para imprimir o predecessor e sucessor de uma dada pontuação
    void prox(int score)
    {
        Node *node = findNode(root, score); // encontra o nó com a pontuação dada
        if (node)
        {                                       // se o nó for encontrado
            Node *pred = findPredecessor(node); // encontra o predecessor
            Node *succ = findSuccessor(node);   // encontra o sucessor

            if (!pred && !succ)
            { // se não houver predecessor e sucessor
                cout << "Apenas " << node->name << " existe no sistema..." << endl;
            }
            else if (!pred)
            { // se não houver predecessor
                cout << node->name << " e o menor! e logo apos vem " << succ->name << endl;
            }
            else if (!succ)
            { // se não houver sucessor
                cout << node->name << " e o maior! e logo atras vem " << pred->name << endl;
            }
            else
            { // se ambos, predecessor e sucessor, existirem
                cout << node->name << " vem apos " << pred->name << " e antes de " << succ->name << endl;
            }
        }
    }
};

int main()
{
    int K;        // variável para armazenar o número de comandos
    cin >> K;     // lê o número de comandos
    cin.ignore(); // ignora o caractere de nova linha após o número

    BST game; // cria uma instância da bst

    for (int i = 0; i < K; ++i)
    {                          // loop para processar cada comando
        string command;        // variável para armazenar o comando
        getline(cin, command); // lê o comando da entrada

        if (command.substr(0, 3) == "ADD")
        {                                                       // se o comando for ADD
            char name[8];                                       // array para armazenar o nome
            int score;                                          // variável para armazenar a pontuação
            sscanf(command.c_str(), "ADD %s %d", name, &score); // faz a análise do comando
            game.addPlayer(name, score);                        // adiciona o jogador à bst
        }
        else if (command.substr(0, 4) == "PROX")
        {                                               // se o comando for PROX
            int score;                                  // variável para armazenar a pontuação
            sscanf(command.c_str(), "PROX %d", &score); // faz a análise do comando
            game.prox(score);                           // imprime o predecessor e o sucessor
        }
    }

    return 0; // retorna sucesso
}
