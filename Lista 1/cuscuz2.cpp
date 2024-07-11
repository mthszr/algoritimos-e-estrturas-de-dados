#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// estrutura que representa uma carta
struct Carta
{
    int valor;       // valor da carta (de 1 a 9)
    char naipe;      // naipe da carta (C, E, O, P)
    string original; // representação original da carta

    // construtor que inicializa a carta a partir de uma string
    Carta(string cartaStr)
    {
        original = cartaStr;
        valor = cartaStr[0] - '0'; // extrai o valor da carta do primeiro caractere
        naipe = cartaStr[1];       // extrai o naipe da carta do segundo caractere
    }

    // sobrecarga do operador de comparação para ordenar cartas
    bool operator<(const Carta &outra) const
    {
        if (valor != outra.valor)
        {
            return valor < outra.valor; // ordena por valor primeiro
        }
        return naipe < outra.naipe; // em caso de valores iguais, ordena por naipe
    }
};

int main()
{
    int N;
    cin >> N;                           // número de jogadores
    vector<vector<Carta>> jogadores(N); // vetores de cartas para cada jogador
    string linha;
    int contador_rodadas = 0;
    vector<Carta> cuscuz; // pilha de cartas jogadas na rodada
    cin.ignore();         // ignorar o caractere de nova linha após o número de jogadores

    // loop principal para processar os comandos
    while (getline(cin, linha))
    {
        if (linha == "END")
        {
            break; // termina a execução quando encontrar "END"
        }
        istringstream iss(linha);
        string comando;
        iss >> comando; // extrai o comando da linha

        if (comando == "DEA")
        {
            // comando DEAL: distribuir cartas para os jogadores
            string carta;
            for (int i = 0; i < N; ++i)
            {
                iss >> carta;
                jogadores[i].push_back(Carta(carta)); // cria uma carta e adiciona ao jogador i
            }
        }
        else if (comando == "RND")
        {
            // comando RND: realizar uma rodada
            cuscuz.clear(); // limpa as cartas do cuscuz da rodada anterior
            vector<pair<Carta, int>> cartas_jogadas;

            // coleta uma carta de cada jogador
            for (int i = 0; i < N; ++i)
            {
                Carta carta = jogadores[i][0];            // pega a primeira carta do jogador i
                jogadores[i].erase(jogadores[i].begin()); // remove a carta do jogador
                cuscuz.push_back(carta);                  // adiciona a carta ao cuscuz da rodada
                cartas_jogadas.push_back({carta, i});     // registra a carta jogada com o índice do jogador
            }

            // implementação simples de ordenação sem usar algorithm
            // ordena as cartas jogadas para determinar o vencedor
            int n = cartas_jogadas.size();
            for (int i = 0; i < n - 1; ++i)
            {
                for (int j = i + 1; j < n; ++j)
                {
                    if (cartas_jogadas[j].first < cartas_jogadas[i].first)
                    {
                        swap(cartas_jogadas[i], cartas_jogadas[j]);
                    }
                }
            }

            // determina a carta de maior valor e seu jogador
            Carta carta_maxima = cartas_jogadas.back().first;
            int valor_maximo = carta_maxima.valor;
            char naipe_maximo = carta_maxima.naipe;
            int vencedor = cartas_jogadas.back().second;
            bool empate = false;

            // verifica se houve empate
            for (int i = cartas_jogadas.size() - 2; i >= 0; --i)
            {
                if (cartas_jogadas[i].first.valor == valor_maximo && cartas_jogadas[i].first.naipe == naipe_maximo)
                {
                    empate = true;
                    break;
                }
            }

            // imprime o resultado da rodada
            if (empate)
            {
                cout << contador_rodadas << " -1" << endl;
            }
            else
            {
                cout << contador_rodadas << " " << vencedor << endl;
            }

            contador_rodadas++;
        }
        else if (comando == "PRT")
        {
            // comando PRT: imprimir as cartas no cuscuz da rodada atual
            for (auto it = cuscuz.rbegin(); it != cuscuz.rend(); ++it)
            {
                cout << it->original; // imprime a representação original da carta
                if (it != cuscuz.rend() - 1)
                {
                    cout << " "; // adiciona espaço entre as cartas, exceto após a última
                }
            }
            cout << endl; // nova linha ao final da impressão das cartas
        }
    }

    return 0;
}
