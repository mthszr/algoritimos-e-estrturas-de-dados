// https://iudex.io/problem/639e63568200550001708dd4

#include <iostream>
#include <string>

using namespace std;

// classe que representa uma carta
class carta
{
public:
    int valor;       // valor da carta (de 1 a 9)
    char naipe;      // naipe da carta (c, e, o, p)
    string original; // representação original da carta

    // construtor que inicializa a carta a partir de uma string
    carta(string carta_str = "")
    {
        if (!carta_str.empty())
        {                               // verifica se a string não está vazia
            original = carta_str;       // armazena a representação original da carta
            valor = carta_str[0] - '0'; // extrai o valor da carta do primeiro caractere
            naipe = carta_str[1];       // extrai o naipe da carta do segundo caractere
        }
    }

    // sobrecarga do operador de comparação para ordenar cartas
    bool operator<(const carta &outra) const
    {
        if (valor != outra.valor)
        {                               // compara os valores das cartas
            return valor < outra.valor; // ordena por valor primeiro
        }
        return naipe < outra.naipe; // em caso de valores iguais, ordena por naipe
    }
};

// estrutura de nó para a lista encadeada
struct node
{
    carta card; // carta armazenada no nó
    node *next; // ponteiro para o próximo nó

    // construtor que inicializa um nó com uma carta
    node(carta card) : card(card), next(nullptr) {}
};

// classe de lista encadeada para gerenciar cartas
class linked_list
{
public:
    node *head; // ponteiro para o primeiro nó da lista
    node *tail; // ponteiro para o último nó da lista

    // construtor que inicializa a lista como vazia
    linked_list() : head(nullptr), tail(nullptr) {}

    // função para adicionar uma carta à lista
    void add_card(carta card)
    {
        node *new_node = new node(card); // cria um novo nó com a carta
        if (!head)
        {                           // se a lista está vazia
            head = tail = new_node; // define o novo nó como primeiro e último
        }
        else
        {
            tail->next = new_node; // adiciona o novo nó ao final da lista
            tail = new_node;       // atualiza o ponteiro do último nó
        }
    }

    // função para remover a primeira carta da lista
    carta remove_card()
    {
        if (!head)
        {                                                                              // verifica se a lista está vazia
            cerr << "erro: tentativa de remover uma carta de uma lista vazia" << endl; // imprime mensagem de erro
            exit(1);                                                                   // encerra o programa com erro
        }
        node *temp = head;       // armazena o nó a ser removido
        carta card = head->card; // armazena a carta a ser removida
        head = head->next;       // atualiza o ponteiro do primeiro nó
        if (!head)
        {                   // se a lista ficou vazia
            tail = nullptr; // atualiza o ponteiro do último nó
        }
        delete temp; // libera a memória do nó removido
        return card; // retorna a carta removida
    }

    // função para verificar se a lista está vazia
    bool is_empty()
    {
        return head == nullptr; // retorna verdadeiro se a lista estiver vazia
    }
};

int main()
{
    int n;    // número de jogadores
    cin >> n; // lê o número de jogadores
    if (n <= 0)
    {                                                   // verifica se o número de jogadores é válido
        cerr << "número de jogadores inválido" << endl; // imprime mensagem de erro
        return 1;                                       // encerra o programa com erro
    }

    linked_list *jogadores = new linked_list[n]; // array de listas de cartas para cada jogador
    string linha;                                // armazena uma linha de entrada
    int contador_rodadas = 0;                    // contador de rodadas
    carta *cuscuz = new carta[n];                // array de cartas jogadas na rodada
    int cuscuz_size = 0;                         // tamanho do array de cartas jogadas
    cin.ignore();                                // ignorar o caractere de nova linha após o número de jogadores

    // loop principal para processar os comandos
    while (getline(cin, linha))
    {
        if (linha == "end")
        {          // verifica se o comando é "end"
            break; // encerra a execução
        }

        // processa o comando sem usar sstream
        if (linha.substr(0, 3) == "dea")
        { // verifica se o comando é "dea"
            // comando deal: distribuir cartas para os jogadores
            int pos = 4; // posição inicial após "dea "
            for (int i = 0; i < n; ++i)
            {
                string carta_str = linha.substr(pos, 2); // extrai a carta da linha
                jogadores[i].add_card(carta(carta_str)); // adiciona a carta ao jogador i
                pos += 3;                                // move para a próxima carta (incluindo espaço)
            }
        }
        else if (linha == "rnd")
        { // verifica se o comando é "rnd"
            // comando rnd: realizar uma rodada
            cuscuz_size = 0;                                            // limpa as cartas do cuscuz da rodada anterior
            pair<carta, int> *cartas_jogadas = new pair<carta, int>[n]; // array para registrar as cartas jogadas e os índices dos jogadores

            // coleta uma carta de cada jogador
            for (int i = 0; i < n; ++i)
            {
                if (jogadores[i].is_empty())
                {                                                                          // verifica se o jogador tem cartas
                    cerr << "erro: jogador " << i << " não tem cartas para jogar" << endl; // imprime mensagem de erro
                    return 1;                                                              // encerra o programa com erro
                }

                carta card = jogadores[i].remove_card(); // remove a primeira carta do jogador i
                cuscuz[cuscuz_size++] = card;            // adiciona a carta ao cuscuz da rodada
                cartas_jogadas[i] = {card, i};           // registra a carta jogada com o índice do jogador
            }

            // ordena as cartas jogadas para determinar o vencedor
            for (int i = 0; i < n - 1; ++i)
            {
                for (int j = i + 1; j < n; ++j)
                {
                    if (cartas_jogadas[j].first < cartas_jogadas[i].first)
                    {                                               // compara as cartas
                        swap(cartas_jogadas[i], cartas_jogadas[j]); // troca as cartas se necessário
                    }
                }
            }

            // determina a carta de maior valor e seu jogador
            carta carta_maxima = cartas_jogadas[n - 1].first; // carta de maior valor
            int valor_maximo = carta_maxima.valor;            // valor máximo
            char naipe_maximo = carta_maxima.naipe;           // naipe máximo
            int vencedor = cartas_jogadas[n - 1].second;      // índice do jogador vencedor
            bool empate = false;                              // flag para verificar empate

            // verifica se houve empate
            for (int i = n - 2; i >= 0; --i)
            {
                if (cartas_jogadas[i].first.valor == valor_maximo && cartas_jogadas[i].first.naipe == naipe_maximo)
                {
                    empate = true; // define a flag de empate
                    break;         // sai do loop
                }
            }

            // imprime o resultado da rodada
            if (empate)
            {
                cout << contador_rodadas << " -1" << endl; // imprime empate
            }
            else
            {
                cout << contador_rodadas << " " << vencedor << endl; // imprime vencedor
            }

            delete[] cartas_jogadas; // libera a memória do array de cartas jogadas
            contador_rodadas++;      // incrementa o contador de rodadas
        }
        else if (linha == "prt")
        { // verifica se o comando é "prt"
            // comando prt: imprimir as cartas no cuscuz da rodada atual
            for (int i = cuscuz_size - 1; i >= 0; --i)
            {
                cout << cuscuz[i].original; // imprime a representação original da carta
                if (i != 0)
                {
                    cout << " "; // adiciona espaço entre as cartas, exceto após a última
                }
            }
            cout << endl;
        }
    }

    delete[] jogadores;
    delete[] cuscuz;

    return 0;
}
