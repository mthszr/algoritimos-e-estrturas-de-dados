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
    Pilha() = default;

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
    bool estaVazia() const
    {
        return pilha.empty();
    }

    // Função para imprimir os elementos da pilha, de baixo para cima
    void imprimir() const
    {
        for (const auto &elem : pilha)
        {
            cout << elem << " ";
        }
    }

    // Função que retorna o tamanho da pilha
    int tamanho() const
    {
        return pilha.size();
    }

    // Função que retorna o elemento no topo da pilha
    int consultarTopo() const
    {
        return pilha.empty() ? -1 : pilha.back();
    }
};

// Definindo uma Fila onde cada nó é uma Pilha
class FilaDePilhas
{
    struct Node
    {
        Pilha pilha;
        Node *proximo = nullptr;
    };

private:
    Node *inicio = nullptr;
    Node *fim = nullptr;
    int tamanho = 0;

public:
    // Construtor
    FilaDePilhas() = default;

    // Função para verificar se a fila está vazia
    bool estaVazia() const
    {
        return inicio == nullptr;
    }

    // Função para adicionar uma nova pilha à fila
    void enfileirar()
    {
        Node *novoNode = new Node();
        if (estaVazia())
        {
            inicio = fim = novoNode;
        }
        else
        {
            fim->proximo = novoNode;
            fim = novoNode;
        }
        ++tamanho;
    }

    // Função para adicionar uma nova pilha ao começo da fila
    void adicionarAoComeco()
    {
        Node *novoNode = new Node();
        novoNode->proximo = inicio;
        if (estaVazia())
        {
            fim = novoNode;
        }
        inicio = novoNode;
        ++tamanho;
    }

    // Função para remover a pilha na frente da fila
    void desenfileirar()
    {
        if (estaVazia())
        {
            return;
        }

        Node *temp = inicio;
        inicio = inicio->proximo;
        delete temp;
        --tamanho;
    }

    // Função para empilhar um elemento em uma pilha específica
    void empilharNaPilha(int posicao, int elemento)
    {
        if (posicao < 0 || posicao >= tamanho)
        {
            cout << "Posição inválida" << endl;
            return;
        }

        Node *atual = inicio;
        for (int i = 0; i < posicao; ++i)
        {
            atual = atual->proximo;
        }
        atual->pilha.empilhar(elemento);
    }

    // Função para remover as pedras de uma coluna se o topo tiver a mesma cor
    void removerPedras(int posicao, int cor)
    {
        if (posicao < 0 || posicao >= tamanho)
        {
            cout << "Posição inválida" << endl;
            return;
        }

        Node *atual = inicio;
        for (int i = 0; i < posicao; ++i)
        {
            atual = atual->proximo;
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
                }
                else
                {
                    Node *temp = atual;
                    inicio = atual->proximo;
                    delete temp;
                    atual = inicio;
                }
                --tamanho;
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
        if (posicao < 0 || posicao >= tamanho)
        {
            return -1; // Posição inválida
        }

        Node *atual = inicio;
        for (int i = 0; i < posicao; ++i)
        {
            atual = atual->proximo;
        }
        return atual->pilha.consultarTopo();
    }

    // Função para imprimir os elementos da fila de pilhas no formato desejado
    void imprimirCaso(int caso) const
    {
        cout << "caso " << caso << ":";
        Node *atual = inicio;
        while (atual != nullptr)
        {
            cout << " " << atual->pilha.consultarTopo();
            atual = atual->proximo;
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
            ++coluna;
        }
        cout << endl;
    }

    // Destrutor
    ~FilaDePilhas()
    {
        while (!estaVazia())
        {
            desenfileirar();
        }
    }
};

void processarEntrada(FilaDePilhas &fila, istream &input)
{
    string linha;
    while (getline(input, linha))
    {
        int caso = 0;

        // Trim leading and trailing whitespaces from linha
        linha.erase(0, linha.find_first_not_of(" \t\n\r\f\v"));
        linha.erase(linha.find_last_not_of(" \t\n\r\f\v") + 1);
        if (linha.empty())
        {
            break; // Exit the loop if the line is empty
        }

        if (linha == "END")
        {
            continue;
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
        // cout << "Pilha: " << S << " e Cor: " << C << endl;
        // fila.imprimirEstado();
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
