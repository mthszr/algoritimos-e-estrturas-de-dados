#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class Pilha
{
private:
    vector<int> pilha;

public:
    // Construtor
    Pilha() {}

    // Função para adicionar um elemento à pilha
    void empilhar(int elemento)
    {
        pilha.push_back(elemento);
    }

    // Função para remover o elemento do topo da pilha
    void desempilhar()
    {
        if (!estaVazia())
        {
            pilha.pop_back();
        }
    }

    // Função para verificar se a pilha está vazia
    bool estaVazia()
    {
        return pilha.empty();
    }

    // Função para imprimir os elementos da pilha, de baixo para cima
    void imprimir()
    {
        for (int elem : pilha)
        {
            cout << elem << " ";
        }
    }

    // Função que retorna o tamanho da pilha
    int tamanho()
    {
        return pilha.size();
    }

    // Função que retorna o elemento no topo da pilha
    int consultarTopo() const
    {
        if (!pilha.empty())
        {
            return pilha.back(); // Elemento no topo da pilha
        }
        return -1; // Retorna -1 se a pilha estiver vazia
    }
};

// Definindo uma Fila onde cada nó é uma Pilha
class FilaDePilhas
{
    struct Node
    {
        Pilha pilha;   // Pilha associada ao nó
        Node *proximo; // Ponteiro para o próximo nó
    };

private:
    Node *inicio; // Ponteiro para o primeiro elemento da fila
    Node *fim;    // Ponteiro para o último elemento da fila
    int tamanho;

public:
    // Construtor
    FilaDePilhas() : inicio(nullptr), fim(nullptr), tamanho(0) {}

    // Função para verificar se a fila está vazia
    bool estaVazia() const
    {
        return (inicio == nullptr);
    }

    // Função para adicionar uma nova pilha à fila
    void enfileirar()
    {
        Node *novoNode = new Node(); // Cria um novo nó
        novoNode->proximo = nullptr; // Define o ponteiro para o próximo nó como nulo

        if (estaVazia())
        {
            inicio = novoNode; // O novo nó é a frente da fila
            fim = novoNode;    // O novo nó também é o final da fila
        }
        else
        {
            fim->proximo = novoNode; // Adiciona o novo nó após o nó final atual
            fim = novoNode;          // Atualiza o nó final para o novo nó
        }
        tamanho++;
    }

    // Função para adicionar uma nova pilha ao começo da fila
    void adicionarAoComeco()
    {
        Node *novoNode = new Node(); // Cria um novo nó
        novoNode->proximo = inicio;  // Define o ponteiro para o próximo nó como o atual início

        if (estaVazia())
        {
            fim = novoNode; // Se a fila estava vazia, o novo nó é o fim da fila também
        }

        inicio = novoNode; // Atualiza o início da fila para o novo nó
        tamanho++;
    }

    // Função para remover a pilha na frente da fila
    void desenfileirar()
    {
        if (estaVazia())
        {
            return; // Se a fila estiver vazia, não faz nada
        }

        Node *temp = inicio;      // Armazena o nó da frente em um ponteiro temporário
        inicio = inicio->proximo; // Atualiza o ponteiro da frente para o próximo nó

        delete temp; // Libera a memória do nó removido
        tamanho--;
    }

    // Função para empilhar um elemento em uma pilha específica
    void empilharNaPilha(int posicao, int elemento)
    {
        Node *atual = inicio;
        for (int i = 0; i < posicao; ++i)
        {
            if (atual->proximo != nullptr)
            {
                atual = atual->proximo;
            }
            else
            {
                cout << "Posição inválida" << endl;
                return;
            }
        }
        atual->pilha.empilhar(elemento);
    }

    // Função para remover as pedras de uma coluna se o topo tiver a mesma cor
    void removerPedras(int posicao, int cor)
    {
        Node *atual = inicio;
        for (int i = 0; i < posicao; ++i)
        {
            if (atual->proximo != nullptr)
            {
                atual = atual->proximo;
            }
            else
            {
                cout << "Posição inválida" << endl;
                return;
            }
        }
        while (!atual->pilha.estaVazia() && atual->pilha.consultarTopo() == cor)
        {
            atual->pilha.desempilhar();
        }
    }

    // Função para remover colunas vazias
    void removerColunasVazias()
    {
        while (!estaVazia() && inicio->pilha.estaVazia())
        {
            desenfileirar();
        }

        Node *atual = inicio;
        Node *anterior = nullptr;
        while (atual != nullptr)
        {
            if (atual->pilha.estaVazia())
            {
                if (anterior != nullptr)
                {
                    anterior->proximo = atual->proximo;
                    if (atual == fim)
                    {
                        fim = anterior;
                    }
                    delete atual;
                    atual = anterior->proximo;
                    tamanho--;
                }
                else
                {
                    Node *temp = atual;
                    inicio = atual->proximo;
                    delete temp;
                    atual = inicio;
                    tamanho--;
                }
            }
            else
            {
                anterior = atual;
                atual = atual->proximo;
            }
        }
    }

    // Função para obter o topo de uma pilha específica
    int consultarTopo(int posicao) const
    {
        Node *atual = inicio;
        for (int i = 0; i < posicao; ++i)
        {
            if (atual->proximo != nullptr)
            {
                atual = atual->proximo;
            }
            else
            {
                return -1; // Posição inválida
            }
        }
        return atual->pilha.consultarTopo();
    }

    // Função para imprimir os elementos da fila de pilhas no formato desejado
    void imprimirCaso(int caso) const
    {
        cout << "caso " << caso << ":";
        if (!estaVazia())
        {
            Node *atual = inicio;
            while (atual != nullptr)
            {
                cout << " " << atual->pilha.consultarTopo();
                atual = atual->proximo;
            }
        }
        cout << endl;
    }

    // Função que retorna o número de pilhas na fila
    int tamanhoF() const
    {
        return tamanho;
    }

    // Função para imprimir o estado atual das pilhas
    void imprimirEstado() const
    {
        Node *atual = inicio;
        int coluna = 1;
        while (atual != nullptr)
        {
            cout << "Coluna " << coluna << ": ";
            atual->pilha.imprimir();
            cout << endl;
            atual = atual->proximo;
            coluna++;
        }
        cout << endl;
    }

    // Destrutor
    ~FilaDePilhas()
    {
        while (!estaVazia())
        {
            desenfileirar(); // Remove cada elemento da fila (cada pilha)
        }
    }
};

void processarEntrada(FilaDePilhas &fila, istream &input)
{
    string linha;
    while (getline(input, linha))
    {
        if (linha == "END")
        {
            break;
        }
        stringstream ss(linha);
        int S, C;
        ss >> S >> C;

        int numColunas = fila.tamanhoF();
        if (C < 1000)
        {
            if (S == 0)
            {
                fila.adicionarAoComeco();
                fila.empilharNaPilha(0, C);
            }
            else if (S == numColunas + 1)
            {
                fila.enfileirar();
                fila.empilharNaPilha(numColunas, C);
            }
            else if (S > 0 && S <= numColunas)
            {
                int corTopo = fila.consultarTopo(S - 1);
                if (corTopo == C)
                {
                    fila.removerPedras(S - 1, C);
                    fila.removerColunasVazias();
                }
                else
                {
                    fila.empilharNaPilha(S - 1, C);
                }
            }
        }
        // Imprime o estado atual após cada jogada
        //fila.imprimirEstado();
    }
}

int main()
{
    int P;
    cin >> P;
    cin.ignore();

    for (int i = 0; i < P; ++i)
    {
        FilaDePilhas filaDePilhas;
        processarEntrada(filaDePilhas, cin);
        filaDePilhas.imprimirCaso(i);
    }

    return 0;
}
