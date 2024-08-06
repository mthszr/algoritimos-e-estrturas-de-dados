#include <iostream>
using namespace std;

// Closed Address Hashing
struct Node
{
    int chave;
    Node *proximo;
};

class HashTableFechada
{
private:
    int tamanho; // tamanho da tabela hash
    Node **tabela; // vetor de ponteiros para listas ligadas

    int hashFunction(int chave)
    {
        return chave % tamanho; // função hash simples
    }

public:
    HashTableFechada(int tamanho)
    {
        this->tamanho = tamanho;
        tabela = new Node *[tamanho]; // aloca memória para o vetor de ponteiros
        for (int i = 0; i < tamanho; i++)
        {
            tabela[i] = nullptr; // inicializa cada ponteiro com nullptr
        }
    }

    ~HashTableFechada()
    {
        for (int i = 0; i < tamanho; i++)
        {
            Node *node = tabela[i];
            while (node != nullptr)
            {
                Node *temp = node;
                node = node->proximo;
                delete temp;
            }
        }
        delete[] tabela; // libera a memória do vetor de ponteiros
    }

    void inserirItem(int chave)
    {
        int index = hashFunction(chave); // calcula o índice hash
        Node *novoNode = new Node;       // cria um novo nó
        novoNode->chave = chave;
        novoNode->proximo = tabela[index]; // insere o novo nó no início da lista
        tabela[index] = novoNode;
    }

    void deletarItem(int chave)
    {
        int index = hashFunction(chave); // calcula o índice hash
        Node *node = tabela[index];
        Node *anterior = nullptr;

        // encontra o nó na lista ligada e remove
        while (node != nullptr && node->chave != chave)
        {
            anterior = node;
            node = node->proximo;
        }

        if (node == nullptr)
        {
            // chave não encontrada
            cout << "Chave " << chave << " não encontrada na tabela hash." << endl;
            return;
        }

        if (anterior == nullptr)
        {
            // o nó a ser removido é o primeiro nó na lista
            tabela[index] = node->proximo;
        }
        else
        {
            anterior->proximo = node->proximo;
        }

        delete node; // libera a memória do nó
        cout << "Chave " << chave << " deletada da tabela hash." << endl;
    }

    bool buscarItem(int chave)
    {
        int index = hashFunction(chave); // calcula o índice hash
        Node *node = tabela[index];

        // percorre a lista ligada no índice calculado
        while (node != nullptr)
        {
            if (node->chave == chave)
            {
                return true; // chave encontrada
            }
            node = node->proximo;
        }
        return false; // chave não encontrada
    }

    void imprimirTabela()
    {
        for (int i = 0; i < tamanho; i++)
        {
            cout << i;
            Node *node = tabela[i];
            while (node != nullptr)
            {
                cout << " --> " << node->chave;
                node = node->proximo;
            }
            cout << endl;
        }
    }
};

// Open Address Hashing
class HashTableAberta
{
private:
    int tamanho;  // tamanho da tabela hash
    int *tabela;  // vetor para armazenar as chaves
    int *estados; // vetor para armazenar estados (0: vazio, 1: ocupado, 2: deletado)

    int hashFunction(int chave)
    {
        return chave % tamanho; // função hash simples
    }

public:
    HashTableAberta(int tamanho)
    {
        this->tamanho = tamanho;
        tabela = new int[tamanho];  // aloca memória para o vetor de chaves
        estados = new int[tamanho]; // aloca memória para o vetor de estados
        for (int i = 0; i < tamanho; i++)
        {
            estados[i] = 0; // inicializa todos os estados como vazios
        }
    }

    ~HashTableAberta()
    {
        delete[] tabela;  // libera a memória do vetor de chaves
        delete[] estados; // libera a memória do vetor de estados
    }

    void inserirItem(int chave)
    {
        int index = hashFunction(chave); // calcula o índice hash
        int i = 0;
        while (estados[index] == 1)
        {                                  // encontra o próximo índice livre
            index = (index + 1) % tamanho; // linear probing
            i++;
            if (i == tamanho)
            {
                cout << "Tabela hash cheia, não é possível inserir a chave " << chave << endl;
                return;
            }
        }
        tabela[index] = chave; // insere a chave
        estados[index] = 1;    // marca o estado como ocupado
    }

    void deletarItem(int chave)
    {
        int index = hashFunction(chave); // calcula o índice hash
        int i = 0;
        while (estados[index] != 0 && tabela[index] != chave)
        {                                  // encontra a chave na tabela
            index = (index + 1) % tamanho; // linear probing
            i++;
            if (i == tamanho)
            {
                cout << "Chave " << chave << " não encontrada na tabela hash." << endl;
                return;
            }
        }
        if (estados[index] == 1)
        {
            estados[index] = 2; // marca o estado como deletado
            cout << "Chave " << chave << " deletada da tabela hash." << endl;
        }
        else
        {
            cout << "Chave " << chave << " não encontrada na tabela hash." << endl;
        }
    }

    bool buscarItem(int chave)
    {
        int index = hashFunction(chave); // calcula o índice hash
        int i = 0;
        while (estados[index] != 0)
        {
            if (estados[index] == 1 && tabela[index] == chave)
            {
                return true; // chave encontrada
            }
            index = (index + 1) % tamanho;
            i++;
            if (i == tamanho)
            {
                return false; // chave não encontrada
            }
        }
        return false; // chave não encontrada
    }

    void imprimirTabela()
    {
        for (int i = 0; i < tamanho; i++)
        {
            cout << i << ": ";
            if (estados[i] == 1)
            {
                cout << tabela[i];
            }
            else if (estados[i] == 2)
            {
                cout << "deletado";
            }
            else
            {
                cout << "vazio";
            }
            cout << endl;
        }
    }
};