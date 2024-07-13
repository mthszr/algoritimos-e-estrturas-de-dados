// https://iudex.io/problem/64863a8324242400012d55ef

#include <iostream> // inclui a biblioteca padrão de entrada e saída
#include <string>   // inclui a biblioteca padrão de strings

using namespace std; // usa o namespace padrão para evitar a necessidade de prefixar std::

// classe que representa uma pilha
class Pilha
{
private:
    // estrutura de nó para a pilha
    struct Node
    {
        int data;   // dado armazenado no nó
        Node *next; // ponteiro para o próximo nó
    };
    Node *topo;  // ponteiro para o topo da pilha
    int tamanho; // tamanho da pilha

public:
    // construtor
    Pilha() : topo(nullptr), tamanho(0) {} // inicializa topo como nullptr e tamanho como 0

    // destrutor
    ~Pilha()
    {
        // remove todos os elementos da pilha ao destruí-la
        while (!estaVazia())
        {
            desempilhar(); // remove o elemento do topo até a pilha estar vazia
        }
    }

    // função para adicionar um elemento à pilha
    void empilhar(int elemento)
    {
        Node *novoNode = new Node{elemento, topo}; // cria um novo nó com o elemento e aponta para o topo atual
        topo = novoNode;                           // atualiza o topo para o novo nó
        ++tamanho;                                 // incrementa o tamanho da pilha
    }

    // função para remover o elemento do topo da pilha
    void desempilhar()
    {
        if (!estaVazia()) // verifica se a pilha não está vazia
        {
            Node *temp = topo; // armazena o nó do topo temporariamente
            topo = topo->next; // atualiza o topo para o próximo nó
            delete temp;       // deleta o nó antigo
            --tamanho;         // decrementa o tamanho da pilha
        }
    }

    // função para verificar se a pilha está vazia
    bool estaVazia() const
    {
        return topo == nullptr; // retorna true se topo for nullptr, indicando que a pilha está vazia
    }

    // função para imprimir os elementos da pilha de baixo para cima
    void imprimir() const
    {
        Node *atual = topo;      // começa do topo da pilha
        while (atual != nullptr) // percorre todos os nós
        {
            cout << atual->data << " "; // imprime o dado do nó atual
            atual = atual->next;        // move para o próximo nó
        }
    }

    // função que retorna o tamanho da pilha
    int tamanhoP() const
    {
        return tamanho; // retorna o tamanho da pilha
    }

    // função que retorna o elemento no topo da pilha
    int consultarTopo() const
    {
        return estaVazia() ? -1 : topo->data; // retorna -1 se a pilha estiver vazia, caso contrário, retorna o dado do topo
    }
};

// definindo uma fila onde cada nó é uma pilha
class FilaDePilhas
{
    struct Node
    {
        Pilha pilha;             // cada nó contém uma pilha
        Node *proximo = nullptr; // ponteiro para o próximo nó
    };

private:
    Node *inicio = nullptr; // ponteiro para o início da fila
    Node *fim = nullptr;    // ponteiro para o fim da fila
    int tamanho = 0;        // número de pilhas na fila

public:
    // construtor
    FilaDePilhas() = default; // inicializa os ponteiros como nullptr e tamanho como 0

    // destrutor
    ~FilaDePilhas()
    {
        while (!estaVazia())
        {
            desenfileirar(); // remove todas as pilhas da fila ao destruí-la
        }
    }

    // função para verificar se a fila está vazia
    bool estaVazia() const
    {
        return inicio == nullptr; // retorna true se início for nullptr, indicando que a fila está vazia
    }

    // função para adicionar uma nova pilha à fila
    void enfileirar()
    {
        Node *novoNode = new Node(); // cria um novo nó
        if (estaVazia())             // verifica se a fila está vazia
        {
            inicio = fim = novoNode; // se estiver vazia, define início e fim como o novo nó
        }
        else
        {
            fim->proximo = novoNode; // liga o fim atual ao novo nó
            fim = novoNode;          // atualiza o fim para o novo nó
        }
        ++tamanho; // incrementa o tamanho da fila
    }

    // função para adicionar uma nova pilha ao começo da fila
    void adicionarAoComeco()
    {
        Node *novoNode = new Node(); // cria um novo nó
        novoNode->proximo = inicio;  // liga o novo nó ao início atual
        if (estaVazia())             // verifica se a fila estava vazia
        {
            fim = novoNode; // se estava vazia, define fim como o novo nó
        }
        inicio = novoNode; // atualiza o início para o novo nó
        ++tamanho;         // incrementa o tamanho da fila
    }

    // função para remover a pilha na frente da fila
    void desenfileirar()
    {
        if (estaVazia()) // verifica se a fila está vazia
        {
            return; // não faz nada se estiver vazia
        }

        Node *temp = inicio;      // armazena o nó do início temporariamente
        inicio = inicio->proximo; // atualiza o início para o próximo nó
        delete temp;              // deleta o nó antigo
        --tamanho;                // decrementa o tamanho da fila
    }

    // função para empilhar um elemento em uma pilha específica
    void empilharNaPilha(int posicao, int elemento)
    {
        if (posicao < 0 || posicao >= tamanho) // verifica se a posição é válida
        {
            cout << "posição inválida" << endl; // imprime mensagem de erro
            return;
        }

        Node *atual = inicio;             // começa do início da fila
        for (int i = 0; i < posicao; ++i) // percorre até a posição desejada
        {
            atual = atual->proximo; // move para o próximo nó
        }
        atual->pilha.empilhar(elemento); // empilha o elemento na pilha da posição desejada
    }

    // função para remover as pedras de uma coluna se o topo tiver a mesma cor
    void removerPedras(int posicao, int cor)
    {
        if (posicao < 0 || posicao >= tamanho) // verifica se a posição é válida
        {
            cout << "posição inválida" << endl; // imprime mensagem de erro
            return;
        }

        Node *atual = inicio;             // começa do início da fila
        for (int i = 0; i < posicao; ++i) // percorre até a posição desejada
        {
            atual = atual->proximo; // move para o próximo nó
        }

        // remove os elementos do topo enquanto a cor for a mesma
        while (!atual->pilha.estaVazia() && atual->pilha.consultarTopo() == cor)
        {
            atual->pilha.desempilhar(); // remove o elemento do topo
        }
    }

    // função para remover colunas vazias
    void removerColunasVazias()
    {
        // remove pilhas vazias do início da fila
        while (!estaVazia() && inicio->pilha.estaVazia())
        {
            desenfileirar(); // remove o início da fila
        }

        Node *atual = inicio;     // começa do início da fila
        Node *anterior = nullptr; // armazena o nó anterior
        while (atual != nullptr)  // percorre todos os nós
        {
            if (atual->pilha.estaVazia()) // verifica se a pilha atual está vazia
            {
                if (anterior != nullptr) // se houver um nó anterior
                {
                    anterior->proximo = atual->proximo; // atualiza o próximo do nó anterior
                    if (atual == fim)                   // se o nó atual é o fim
                    {
                        fim = anterior; // atualiza o fim para o nó anterior
                    }
                    delete atual;              // deleta o nó atual
                    atual = anterior->proximo; // move para o próximo nó
                }
                else
                {
                    Node *temp = atual;      // armazena o nó atual temporariamente
                    inicio = atual->proximo; // atualiza o início para o próximo nó
                    delete temp;             // deleta o nó antigo
                    atual = inicio;          // move para o próximo nó
                }
                --tamanho; // decrementa o tamanho da fila
            }
            else
            {
                anterior = atual;       // atualiza o nó anterior
                atual = atual->proximo; // move para o próximo nó
            }
        }
    }

    // função para obter o topo de uma pilha específica
    int consultarTopo(int posicao) const
    {
        if (posicao < 0 || posicao >= tamanho) // verifica se a posição é válida
        {
            return -1; // retorna -1 para indicar posição inválida
        }

        Node *atual = inicio;             // começa do início da fila
        for (int i = 0; i < posicao; ++i) // percorre até a posição desejada
        {
            atual = atual->proximo; // move para o próximo nó
        }
        return atual->pilha.consultarTopo(); // retorna o topo da pilha na posição desejada
    }

    // função para imprimir os elementos da fila de pilhas no formato desejado
    void imprimirCaso(int caso) const
    {
        cout << "caso " << caso << ":"; // imprime o número do caso
        Node *atual = inicio;           // começa do início da fila
        while (atual != nullptr)        // percorre todos os nós
        {
            cout << " " << atual->pilha.consultarTopo(); // imprime o topo da pilha atual
            atual = atual->proximo;                      // move para o próximo nó
        }
        cout << endl; // imprime uma nova linha
    }

    // função que retorna o número de pilhas na fila
    int tamanhoF() const
    {
        return tamanho; // retorna o tamanho da fila
    }

    // função para imprimir o estado atual das pilhas
    void imprimirEstado() const
    {
        Node *atual = inicio;    // começa do início da fila
        int coluna = 1;          // número da coluna
        while (atual != nullptr) // percorre todos os nós
        {
            cout << "coluna " << coluna << ": "; // imprime o número da coluna
            atual->pilha.imprimir();             // imprime os elementos da pilha na coluna atual
            cout << endl;                        // imprime uma nova linha
            atual = atual->proximo;              // move para o próximo nó
            ++coluna;                            // incrementa o número da coluna
        }
        cout << endl; // imprime uma nova linha
    }
};

// função para processar a entrada
void processarEntrada(FilaDePilhas &fila, istream &input)
{
    string linha;                 // variável para armazenar cada linha da entrada
    while (getline(input, linha)) // lê cada linha da entrada
    {
        int caso = 0; // número do caso

        // remove espaços em branco no início e no final da linha
        linha.erase(0, linha.find_first_not_of(" \t\n\r\f\v"));
        linha.erase(linha.find_last_not_of(" \t\n\r\f\v") + 1);

        if (linha.empty()) // se a linha estiver vazia
        {
            break; // sai do loop
        }

        if (linha == "END") // se a linha for "END"
        {
            continue; // pula para a próxima iteração
        }

        // lê os números da linha
        int S, C;
        sscanf(linha.c_str(), "%d %d", &S, &C); // lê S e C da linha

        int numColunas = fila.tamanhoF(); // obtém o número de colunas na fila

        if (C < 1000) // se C for menor que 1000
        {
            if (S == 0) // se S for 0
            {
                fila.adicionarAoComeco();   // adiciona uma nova pilha ao começo da fila
                fila.empilharNaPilha(0, C); // empilha C na nova pilha
            }
            else if (S == numColunas + 1) // se S for o próximo número de colunas
            {
                fila.enfileirar();                   // adiciona uma nova pilha ao final da fila
                fila.empilharNaPilha(numColunas, C); // empilha C na nova pilha
            }
            else if (S > 0 && S <= numColunas) // se S estiver dentro do intervalo válido
            {
                int corTopo = fila.consultarTopo(S - 1); // obtém a cor do topo da pilha na posição S - 1
                if (corTopo == C)                        // se a cor do topo for igual a C
                {
                    fila.removerPedras(S - 1, C); // remove as pedras com a cor C da pilha
                    fila.removerColunasVazias();  // remove colunas vazias
                }
                else
                {
                    fila.empilharNaPilha(S - 1, C); // empilha C na pilha na posição S - 1
                }
            }
        }

        // imprime o estado atual após cada jogada
        // fila.imprimirEstado();
    }
}

int main()
{
    int P;        // número de casos
    cin >> P;     // lê o número de casos
    cin.ignore(); // ignora o caractere de nova linha após o número de casos

    for (int i = 0; i < P; ++i) // para cada caso
    {
        FilaDePilhas filaDePilhas;           // cria uma nova fila de pilhas
        processarEntrada(filaDePilhas, cin); // processa a entrada e atualiza a fila de pilhas
        filaDePilhas.imprimirCaso(i);        // imprime o estado da fila de pilhas para o caso atual
    }

    return 0; // retorna 0 para indicar que o programa terminou com sucesso
}