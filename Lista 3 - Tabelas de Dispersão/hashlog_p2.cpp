#include <cstdint>
#include <iostream>

using namespace std;

struct Pair {
    uint32_t timestamp;
    uint32_t client;
    Pair* next;

    Pair(uint32_t t, uint32_t c) : timestamp(t), client(c), next(nullptr) {}
};

class HashTable {
   private:
    Pair** table;  // array de ponteiros para a cabeça das listas
    int M;
    float Lmax;
    int count;

    int hash(uint32_t T) {
        return T % M;
    }

    float load_factor() {
        return static_cast<float>(count) / M;
    }

    void rehash() {
        int oldM = M;
        M = 2 * M + 1;
        Pair** new_table = new Pair*[M];
        for (int i = 0; i < M; ++i) {
            new_table[i] = nullptr;
        }

        for (int i = 0; i < oldM; ++i) {
            Pair* node = table[i];
            while (node != nullptr) {
                int newIndex = node->timestamp % M;
                Pair* nextNode = node->next;

                // insere o node na nova tabela mantendo a ordem
                Pair** newList = &new_table[newIndex];
                while (*newList != nullptr && (*newList)->timestamp < node->timestamp) {
                    newList = &(*newList)->next;
                }
                node->next = *newList;
                *newList = node;

                node = nextNode;
            }
        }

        delete[] table;
        table = new_table;
    }

   public:
    HashTable(int initialM, float maxLoadFactor) : M(initialM), Lmax(maxLoadFactor), count(0) {
        table = new Pair*[M];
        for (int i = 0; i < M; ++i) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < M; ++i) {
            Pair* node = table[i];
            while (node != nullptr) {
                Pair* temp = node;
                node = node->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(uint32_t T, uint32_t C) {
        if (load_factor() > Lmax) {
            rehash();
        }

        int index = hash(T);
        Pair** lst = &table[index];
        Pair* newNode = new Pair(T, C);
        // insere mantendo a ordem
        while (*lst != nullptr && (*lst)->timestamp < T) {
            lst = &(*lst)->next;
        }
        newNode->next = *lst;
        *lst = newNode;
        count++;

        // contar o tamanho da lista
        int listSize = 0;
        Pair* current = table[index];
        while (current != nullptr) {
            listSize++;
            current = current->next;
        }

        cout << index << " " << listSize << endl;
    }

    void query(uint32_t T) {
        int index = hash(T);
        Pair* node = table[index];
        int position = 0;

        while (node != nullptr) {
            if (node->timestamp == T) {
                cout << node->client << " " << position << endl;
                return;
            }
            node = node->next;
            position++;
        }

        cout << "-1 -1" << endl;
    }
};

int main() {
    int M;
    float Lmax;
    cin >> M >> Lmax;

    HashTable ht(M, Lmax);

    string command;
    while (cin >> command) {
        if (command == "END")
            break;
        else if (command == "NEW") {
            uint32_t T, C;
            cin >> T >> C;
            ht.insert(T, C);
        } else if (command == "QRY") {
            uint32_t T;
            cin >> T;
            ht.query(T);
        }
    }

    return 0;
}