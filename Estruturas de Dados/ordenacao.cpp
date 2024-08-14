#include <iostream>
using namespace std;

// BUBLESORT

// função auxiliar para trocar dois elementos no vetor
void trocar(int v[], int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// função que implementa o algoritmo bubble sort
void bubblesort(int v[], int N) {
    // loop externo que diminui o tamanho do subvetor a ser ordenado
    for (int i = N - 1; i > 0; i--) {
        // loop interno para comparar e trocar elementos adjacentes
        for (int j = 0; j < i; j++) {
            if (v[j] > v[j + 1]) {
                trocar(v, j, j + 1);  // troca elementos se estiverem fora de ordem
            }
        }
    }
}

// SELECTIONSORT

// função auxiliar para trocar dois elementos no vetor
void trocar(int v[], int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// função que implementa o algoritmo selection sort
void selectionsort(int v[], int N) {
    // loop externo que percorre cada posição do vetor
    for (int i = 0; i < N; i++) {
        int min = i;  // assume que o menor elemento está na posição i
        // loop interno para encontrar o menor elemento na sublista não ordenada
        for (int j = i + 1; j < N; j++) {
            if (v[min] > v[j]) {
                min = j;  // atualiza o índice do menor elemento encontrado
            }
        }
        // troca o menor elemento encontrado com o elemento na posição i
        trocar(v, i, min);
    }
}

// INSERTION SORT

// função que implementa o algoritmo insertion sort
void insertionsort(int v[], int N) {
    // loop externo que percorre o vetor começando do segundo elemento
    for (int i = 1; i < N; i++) {
        int aux = v[i];  // elemento a ser inserido
        int j = i - 1;   // índice do elemento anterior

        // move os elementos maiores que aux para a direita
        while (j >= 0 && v[j] > aux) {
            v[j + 1] = v[j];
            j--;
        }

        // insere o elemento aux na posição correta
        v[j + 1] = aux;
    }
}

// MERGESORT

// função merge que combina duas metades ordenadas de um vetor
void merge(int v[], int esq, int meio, int dir) {
    int i = esq;       // índice inicial da primeira metade do vetor
    int j = meio + 1;  // índice inicial da segunda metade do vetor
    int k = 0;         // índice para o vetor auxiliar

    // vetor auxiliar para armazenar temporariamente a combinação das duas metades
    int* aux = new int[dir - esq + 1];

    // mescla os elementos das duas metades até que uma delas seja esgotada
    while (i <= meio && j <= dir) {
        // se o elemento da primeira metade for menor ou igual, copia para aux
        if (v[i] <= v[j]) {
            aux[k++] = v[i++];
        // se o elemento da segunda metade for menor, copia para aux
        } else {
            aux[k++] = v[j++];
        }
    }

    // caso ainda existam elementos na primeira metade, copia-os para aux
    while (i <= meio) {
        aux[k++] = v[i++];
    }

    // caso ainda existam elementos na segunda metade, copia-os para aux
    while (j <= dir) {
        aux[k++] = v[j++];
    }

    // copia os elementos do vetor auxiliar de volta para o vetor original
    for (i = esq, k = 0; i <= dir; i++, k++) {
        v[i] = aux[k];
    }

    // libera a memória alocada para o vetor auxiliar
    delete[] aux;
}

// função recursiva que implementa a lógica do merge sort
void TD_mergesort(int v[], int esq, int dir) {
    // se o intervalo tiver apenas um elemento, já está ordenado (condição de parada)
    if (esq >= dir) return;

    // calcula o índice do meio para dividir o vetor em duas partes
    int meio = (esq + dir) / 2;

    // chama a função recursiva para ordenar a primeira metade
    TD_mergesort(v, esq, meio);

    // chama a função recursiva para ordenar a segunda metade
    TD_mergesort(v, meio + 1, dir);

    // mescla as duas metades ordenadas em uma única sequência ordenada
    merge(v, esq, meio, dir);
}

// função principal que inicia o processo de ordenação usando merge sort
void mergesort(int v[], int N) {
    // chama a função recursiva passando o vetor completo
    TD_mergesort(v, 0, N - 1);
}

// QUICKSORT

// função auxiliar para trocar dois elementos no vetor
void trocar(int v[], int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// função de partição que organiza o vetor em torno de um pivô
int particao(int v[], int esq, int dir) {
    int pivo = v[esq];  // escolhe o primeiro elemento como pivô
    int i = esq + 1;    // índice inicial logo após o pivô
    int j = dir;        // índice inicial na posição final do vetor

    while (true) {
        // encontra o primeiro elemento maior ou igual ao pivô
        while (i <= dir && v[i] < pivo) {
            i++;
        }

        // encontra o primeiro elemento menor ou igual ao pivô
        while (j >= esq && v[j] > pivo) {
            j--;
        }

        // se os índices se cruzarem, a partição está concluída
        if (i >= j) {
            break;
        }

        // troca os elementos v[i] e v[j]
        trocar(v, i, j);
    }

    // coloca o pivô na posição correta (no meio do vetor)
    trocar(v, esq, j);

    // retorna o índice do pivô
    return j;
}

// função recursiva que implementa a lógica do quicksort
void qs(int v[], int esq, int dir) {
    if (esq >= dir) {
        return;  // condição de parada: sublista com um ou zero elementos
    }

    // faz a partição do vetor e obtém a posição do pivô
    int p = particao(v, esq, dir);

    // ordena recursivamente a sublista à esquerda do pivô
    qs(v, esq, p - 1);

    // ordena recursivamente a sublista à direita do pivô
    qs(v, p + 1, dir);
}

// função principal que inicia o processo de ordenação usando quicksort
void quicksort(int v[], int N) {
    qs(v, 0, N - 1);
}

int main() {
    int v[] = {38, 27, 43, 3, 9, 82, 10};
    int N = sizeof(v) / sizeof(v[0]);

    quicksort(v, N);

    // imprime o vetor ordenado
    for (int i = 0; i < N; i++) {
        cout << v[i] << " ";
    }

    return 0;
}