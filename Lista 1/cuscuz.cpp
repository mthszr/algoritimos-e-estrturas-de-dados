#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Definição de uma carta
struct Carta
{
    int valor;
    char naipe;

    bool operator<(const Carta &outra) const
    {
        if (valor == outra.valor)
        {
            return naipe < outra.naipe;
        }
        return valor < outra.valor;
    }

    bool operator==(const Carta &outra) const
    {
        return valor == outra.valor && naipe == outra.naipe;
    }
};

// Função para imprimir a fila de cartas de cada jogador
void imprimir_filas(const vector<vector<Carta>> &jogadores)
{
    for (size_t i = 0; i < jogadores.size(); ++i)
    {
        cout << "Jogador " << i << ": ";
        for (const auto &carta : jogadores[i])
        {
            cout << carta.valor << carta.naipe << " ";
        }
        cout << endl;
    }
}

// Função para imprimir o cuscuz
void imprimir_cuscuz(const vector<Carta> &cuscuz)
{
    cout << "Cuscuz: ";
    for (const auto &carta : cuscuz)
    {
        cout << carta.valor << carta.naipe << " ";
    }
    cout << endl;
}

int main()
{
    int N;
    cin >> N;
    cin.ignore(); // Ignorar o newline após o número de jogadores

    vector<vector<Carta>> jogadores(N);
    string linha;
    int round_number = 0;

    while (getline(cin, linha))
    {
        if (linha == "END")
        {
            break;
        }

        if (linha.substr(0, 3) == "DEA")
        {
            istringstream iss(linha);
            string cmd;
            iss >> cmd;
            for (int i = 0; i < N; ++i)
            {
                string carta_str;
                iss >> carta_str;
                if (carta_str.empty())
                {
                    continue;
                }
                try
                {
                    int valor = stoi(carta_str.substr(0, carta_str.size() - 1));
                    char naipe = carta_str.back();
                    jogadores[i].push_back({valor, naipe});
                }
                catch (invalid_argument &e)
                {
                    cerr << "Erro ao converter a carta: " << carta_str << endl;
                    return 1;
                }
            }
        }
        else if (linha == "RND")
        {
            vector<Carta> cuscuz;
            vector<int> jogadores_ativos;
            for (int i = 0; i < N; ++i)
            {
                if (!jogadores[i].empty())
                {
                    jogadores_ativos.push_back(i);
                }
            }

            bool rodada_continua = true;
            while (rodada_continua)
            {
                if (jogadores_ativos.empty())
                {
                    cout << round_number << " -1 -1" << endl;
                    cout << -1 << endl;
                    return 0;
                }

                vector<pair<Carta, int>> cartas_da_rodada;
                for (int jogador : jogadores_ativos)
                {
                    if (!jogadores[jogador].empty())
                    {
                        cartas_da_rodada.push_back({jogadores[jogador].front(), jogador});
                        jogadores[jogador].erase(jogadores[jogador].begin());
                    }
                }

                for (const auto &p : cartas_da_rodada)
                {
                    cuscuz.push_back(p.first);
                }

                if (cartas_da_rodada.empty())
                {
                    cout << round_number << " -1 -1" << endl;
                    cout << -1 << endl;
                    return 0;
                }

                Carta max_carta = max_element(cartas_da_rodada.begin(), cartas_da_rodada.end(),
                                              [](const pair<Carta, int> &a, const pair<Carta, int> &b)
                                              {
                                                  return a.first < b.first;
                                              })
                                      ->first;

                vector<int> vencedores;
                for (const auto &p : cartas_da_rodada)
                {
                    if (p.first == max_carta)
                    {
                        vencedores.push_back(p.second);
                    }
                }

                if (vencedores.size() == 1)
                {
                    int vencedor = vencedores[0];
                    reverse(cuscuz.begin(), cuscuz.end()); // Inverter a ordem das cartas do cuscuz
                    jogadores[vencedor].insert(jogadores[vencedor].end(), cuscuz.begin(), cuscuz.end());
                    cout << round_number << " " << vencedor << " " << cuscuz.size() << endl;
                    if (round_number > 70)
                    {
                        imprimir_cuscuz(cuscuz); // Imprimir o cuscuz ao final da rodada
                    }

                    rodada_continua = false;
                }
                else
                {
                    // Todos os jogadores que ainda têm cartas continuam na disputa
                    vector<int> novos_jogadores_ativos;
                    for (int i = 0; i < N; ++i)
                    {
                        if (!jogadores[i].empty())
                        {
                            novos_jogadores_ativos.push_back(i);
                        }
                    }
                    jogadores_ativos = novos_jogadores_ativos;
                }
            }
            if (round_number > 70)
            {
                imprimir_filas(jogadores); // Imprimir a fila de cartas de cada jogador ao final da rodada
            }
            round_number++;
        }
    }

    // Determinar o vencedor da partida
    vector<int> jogadores_restantes;
    for (int i = 0; i < N; i++)
    {
        if (!jogadores[i].empty())
        {
            jogadores_restantes.push_back(i);
        }
    }

    if (jogadores_restantes.size() == 1)
    {
        cout << jogadores_restantes[0] << endl;
    }
    else
    {
        int max_cartas = 0;
        for (int jogador : jogadores_restantes)
        {
            max_cartas = max(max_cartas, (int)jogadores[jogador].size());
        }

        vector<int> possiveis_vencedores;
        for (int jogador : jogadores_restantes)
        {
            if (jogadores[jogador].size() == max_cartas)
            {
                possiveis_vencedores.push_back(jogador);
            }
        }

        if (possiveis_vencedores.size() == 1)
        {
            cout << possiveis_vencedores[0] << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }

    return 0;
}
