#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// classe que representa uma pilha usando vector
class Pilha
{
private:
    vector<int> pilha; // vetor que armazena os elementos da pilha

public:
    // construtor padrão
    Pilha() = default;

    // função para adicionar um elemento à pilha
    void empilhar(int elemento)
    {
        pilha.push_back(elemento); // adiciona o elemento ao final do vetor
    }

    // função para remover o elemento do topo da pilha
    void desempilhar()
    {
        if (!estaVazia()) // verifica se a pilha não está vazia
        {
            pilha.pop_back(); // remove o último elemento do vetor
        }
    }

    // função para verificar se a pilha está vazia
    bool estaVazia() const
    {
        return pilha.empty(); // retorna verdadeiro se o vetor estiver vazio
    }

    // função para imprimir os elementos da pilha, de baixo para cima
    void imprimir() const
    {
        for (const auto &elem : pilha) // percorre todos os elementos da pilha
        {
            cout << elem << " "; // imprime cada elemento seguido de um espaço
        }
    }

    // função que retorna o tamanho da pilha
    int tamanho() const
    {
        return pilha.size(); // retorna o tamanho do vetor
    }

    // função que retorna o elemento no topo da pilha
    int consultarTopo() const
    {
        return pilha.empty() ? -1 : pilha.back(); // retorna o último elemento do vetor ou -1 se a pilha estiver vazia
    }
};

// definindo uma fila onde cada nó é uma pilha
class FilaDePilhas
{
    // estrutura que representa um nó da fila, que contém uma pilha e um ponteiro para o próximo nó
    struct Node
    {
        Pilha pilha;             // pilha associada ao nó
        Node *proximo = nullptr; // ponteiro para o próximo nó
    };

private:
    Node *inicio = nullptr; // ponteiro para o início da fila
    Node *fim = nullptr;    // ponteiro para o fim da fila
    int tamanho = 0;        // tamanho da fila

public:
    // construtor padrão
    FilaDePilhas() = default;

    // função para verificar se a fila está vazia
    bool estaVazia() const
    {
        return inicio == nullptr; // retorna verdadeiro se o início for nulo
    }

    // função para adicionar uma nova pilha à fila
    void enfileirar()
    {
        Node *novoNode = new Node(); // cria um novo nó
        if (estaVazia())             // se a fila estiver vazia
        {
            inicio = fim = novoNode; // o novo nó é o início e o fim da fila
        }
        else
        {
            fim->proximo = novoNode; // o próximo do fim atual aponta para o novo nó
            fim = novoNode;          // o novo nó é o novo fim da fila
        }
        ++tamanho; // incrementa o tamanho da fila
    }

    // função para adicionar uma nova pilha ao começo da fila
    void adicionarAoComeco()
    {
        Node *novoNode = new Node(); // cria um novo nó
        novoNode->proximo = inicio;  // o próximo do novo nó aponta para o início atual
        if (estaVazia())             // se a fila estiver vazia
        {
            fim = novoNode; // o novo nó é o fim da fila
        }
        inicio = novoNode; // o novo nó é o novo início da fila
        ++tamanho;         // incrementa o tamanho da fila
    }

    // função para remover a pilha na frente da fila
    void desenfileirar()
    {
        if (estaVazia()) // se a fila estiver vazia
        {
            return; // não faz nada
        }

        Node *temp = inicio;      // armazena o início atual
        inicio = inicio->proximo; // o início é atualizado para o próximo nó
        delete temp;              // deleta o antigo início
        --tamanho;                // decrementa o tamanho da fila
    }

    // função para empilhar um elemento em uma pilha específica
    void empilharNaPilha(int posicao, int elemento)
    {
        if (posicao < 0 || posicao >= tamanho) // verifica se a posição é válida
        {
            cout << "posição inválida" << endl; // imprime mensagem de erro
            return;                             // retorna sem fazer nada
        }

        Node *atual = inicio;             // começa pelo início da fila
        for (int i = 0; i < posicao; ++i) // percorre até a posição desejada
        {
            atual = atual->proximo;
        }
        atual->pilha.empilhar(elemento); // empilha o elemento na pilha desejada
    }

    // função para remover as pedras de uma coluna se o topo tiver a mesma cor
    void removerPedras(int posicao, int cor)
    {
        if (posicao < 0 || posicao >= tamanho) // verifica se a posição é válida
        {
            cout << "posição inválida" << endl; // imprime mensagem de erro
            return;                             // retorna sem fazer nada
        }

        Node *atual = inicio;             // começa pelo início da fila
        for (int i = 0; i < posicao; ++i) // percorre até a posição desejada
        {
            atual = atual->proximo;
        }

        while (!atual->pilha.estaVazia() && atual->pilha.consultarTopo() == cor) // enquanto a pilha não estiver vazia e o topo for da mesma cor
        {
            atual->pilha.desempilhar(); // desempilha o elemento do topo
        }
    }

    // função para remover colunas vazias
    void removerColunasVazias()
    {
        while (!estaVazia() && inicio->pilha.estaVazia()) // enquanto a fila não estiver vazia e o início estiver vazio
        {
            desenfileirar(); // remove o início da fila
        }

        Node *atual = inicio;     // começa pelo início da fila
        Node *anterior = nullptr; // ponteiro para o nó anterior
        while (atual != nullptr)  // percorre todos os nós da fila
        {
            if (atual->pilha.estaVazia()) // se a pilha do nó atual estiver vazia
            {
                if (anterior != nullptr) // se não estiver no início da fila
                {
                    anterior->proximo = atual->proximo; // o próximo do anterior aponta para o próximo do atual
                    if (atual == fim)                   // se o atual for o fim da fila
                    {
                        fim = anterior; // o anterior é o novo fim
                    }
                    delete atual;              // deleta o nó atual
                    atual = anterior->proximo; // atualiza o atual para o próximo do anterior
                }
                else
                {
                    Node *temp = atual;      // armazena o nó atual
                    inicio = atual->proximo; // o início é atualizado para o próximo do atual
                    delete temp;             // deleta o antigo início
                    atual = inicio;          // atualiza o atual para o novo início
                }
                --tamanho; // decrementa o tamanho da fila
            }
            else
            {
                anterior = atual;       // atualiza o anterior para o atual
                atual = atual->proximo; // atualiza o atual para o próximo nó
            }
        }
    }

    // função para obter o topo de uma pilha específica
    int consultarTopo(int posicao) const
    {
        if (posicao < 0 || posicao >= tamanho) // verifica se a posição é válida
        {
            return -1; // posição inválida, retorna -1
        }

        Node *atual = inicio;             // começa pelo início da fila
        for (int i = 0; i < posicao; ++i) // percorre até a posição desejada
        {
            atual = atual->proximo;
        }
        return atual->pilha.consultarTopo(); // retorna o topo da pilha na posição desejada
    }

    // função para imprimir os elementos da fila de pilhas no formato desejado
    void imprimirCaso(int caso) const
    {
        cout << "caso " << caso << ":"; // imprime o número do caso
        Node *atual = inicio;           // começa pelo início da fila
        while (atual != nullptr)        // percorre todos os nós da fila
        {
            cout << " " << atual->pilha.consultarTopo(); // imprime o topo da pilha de cada nó
            atual = atual->proximo;                      // avança para o próximo nó
        }
        cout << endl; // quebra de linha após imprimir todos os nós
    }

    // função que retorna o número de pilhas na fila
    int tamanhoF() const
    {
        return tamanho; // retorna o tamanho da fila
    }

    // função para imprimir o estado atual das pilhas
    void imprimirEstado() const
    {
        Node *atual = inicio; // começa pelo início da fila
        int coluna = 1;       // contador de colunas

        while (atual != nullptr) // percorre todos os nós da fila
        {
            cout << "coluna " << coluna << ": "; // imprime o número da coluna
            atual->pilha.imprimir();             // imprime os elementos da pilha
            cout << endl;                        // quebra de linha após cada coluna
            atual = atual->proximo;              // avança para o próximo nó
            ++coluna;                            // incrementa o contador de colunas
        }
        cout << endl; // quebra de linha após imprimir todas as colunas
    }

    // destrutor
    ~FilaDePilhas()
    {
        while (!estaVazia()) // enquanto a fila não estiver vazia
        {
            desenfileirar(); // remove o início da fila
        }
    }
};

// função para processar a entrada
void processarEntrada(FilaDePilhas &fila, istream &input)
{
    string linha;
    while (getline(input, linha)) // lê cada linha da entrada
    {
        int caso = 0;

        // remove espaços em branco no início e no final da linha
        linha.erase(0, linha.find_first_not_of(" \t\n\r\f\v"));
        linha.erase(linha.find_last_not_of(" \t\n\r\f\v") + 1);
        if (linha.empty()) // se a linha estiver vazia
        {
            break; // sai do loop
        }

        if (linha == "END") // se a linha for "END"
        {
            continue; // continua para a próxima iteração
        }
        stringstream ss(linha);
        int S, C;
        ss >> S >> C; // lê os valores de S e C da linha

        int numColunas = fila.tamanhoF(); // obtém o número de colunas na fila
        if (C < 1000)
        {
            if (S == 0)
            {
                fila.adicionarAoComeco();   // adiciona uma nova pilha ao começo da fila
                fila.empilharNaPilha(0, C); // empilha o elemento na nova pilha
            }
            else if (S == numColunas + 1)
            {
                fila.enfileirar();                   // adiciona uma nova pilha ao fim da fila
                fila.empilharNaPilha(numColunas, C); // empilha o elemento na nova pilha
            }
            else if (S > 0 && S <= numColunas)
            {
                int corTopo = fila.consultarTopo(S - 1); // consulta o topo da pilha na posição S-1
                if (corTopo == C)
                {
                    fila.removerPedras(S - 1, C); // remove pedras se o topo tiver a mesma cor
                    fila.removerColunasVazias();  // remove colunas vazias
                }
                else
                {
                    fila.empilharNaPilha(S - 1, C); // empilha o elemento na pilha na posição S-1
                }
            }
        }
        // imprime o estado atual após cada jogada
        // cout << "pilha: " << S << " e cor: " << C << endl;
        // fila.imprimirEstado();
    }
}

int main()
{
    int P;
    cin >> P;     // lê o número de casos
    cin.ignore(); // ignora o caractere de nova linha após o número de casos

    for (int i = 0; i < P; ++i)
    {
        FilaDePilhas filaDePilhas;
        processarEntrada(filaDePilhas, cin); // processa a entrada para cada caso
        filaDePilhas.imprimirCaso(i);        // imprime o resultado do caso atual
    }

    return 0;
}