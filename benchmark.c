#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "benchmark.h" // Inclui o cabecalho contendo prototipos de funcoes externas
extern int qtdTamanhos; // Variavel externa definida em outro arquivo

int comparacoes = 0; // Variavel global para contar o numero de comparacoes
int trocas = 0; // Variavel global para contar o numero de trocas

// Funcao para trocar elementos
void trocar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    trocas++;
}

// Algoritmo de ordenacao por insercao
void ordenacaoPorInsercao(int arr[], int inicio, int fim) {
    comparacoes = 0;
    trocas = 0;
    int i, chave, j;
    // Percorre os elementos do segundo ao ultimo no array
    for (i = inicio + 1; i <= fim; i++) {
        chave = arr[i];
        j = i - 1;
        
        comparacoes++;
        // Mover os elementos maiores que a chave uma posicao a frente
        while (j >= inicio && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j = j - 1;
            trocas++;
        }
        arr[j + 1] = chave; // Colocar a chave na posicao correta
        trocas++;
    }
}

// Algoritmo de ordenacao por selecao
void ordenacaoPorSelecao(int arr[], int inicio, int fim) {
    comparacoes = 0;
    trocas = 0;
    int i, j, indiceMin;
    // Percorre o array do inicio ate o penultimo elemento
    for (i = inicio; i < fim; i++) {
        indiceMin = i;

        // Encontrar o menor elemento no array nao ordenado
        for (j = i + 1; j <= fim; j++) {
            comparacoes++;
            if (arr[j] < arr[indiceMin]) {
                indiceMin = j;
            }
        }
        // Trocar o menor elemento com o primeiro elemento nao ordenado
        trocar(&arr[indiceMin], &arr[i]);
    }
}

// Algoritmo de ordenacao Merge Sort
void merge(int arr[], int inicio, int meio, int fim){
    int i, j, k;
    int n1 = meio - inicio + 1; // Tamanho do primeiro subarray
    int n2 = fim - meio;        // Tamanho do segundo subarray

    // Arrays temporarios para guardar os dados
    int L[n1], R[n2];

    // Copiar dados para os arrays temporarios L[] e R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[inicio + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[meio + 1 + j];

    // Merge dos arrays temporarios de volta em arr[l..r]
    i = 0;
    j = 0;
    k = inicio;
    while (i < n1 && j < n2) {
        comparacoes++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
        trocas++;
    }

    // Copiar os elementos restantes de L[], se houver algum
    comparacoes++;
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        trocas++;
    }

    // Copiar os elementos restantes de R[], se houver algum
    comparacoes++;
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        trocas++;
    }
}

// Funcao recursiva para realizar o merge sort
void mergeSort(int arr[], int inicio, int fim) {
    comparacoes++;
    if (inicio < fim){
        int meio = inicio + (fim - inicio) / 2;
        mergeSort(arr, inicio, meio); //Primeira metade do array
        mergeSort(arr, meio + 1, fim); //Segunda metade do array
        merge(arr, inicio, meio, fim); //Mesclar as duas metades ordenadas
    }
}

// Algoritmo de ordenacao Quick Sort
int particionar(int arr[], int baixo, int alto) {
    int pivo = arr[alto]; // Seleciona o elemento mais a direita como pivo
    int i = (baixo - 1);  // Indice do menor elemento

    // Itera sobre todos os elementos do array
    for (int j = baixo; j <= alto - 1; j++) {
        comparacoes++;
        if (arr[j] < pivo) {
            i++;
            // Trocar elementos
            trocar(&arr[i], &arr[j]);
        }
    }
    // Troca arr[i+1] com o pivo (arr[alto])
    trocar(&arr[i + 1], &arr[alto]);
    return (i + 1);
}

// Funcao recursiva para realizar o quick sort
void quickSort(int arr[], int baixo, int alto) {
    comparacoes++;
    if (baixo < alto) {
        // pi e a posicao do pivo
        int pi = particionar(arr, baixo, alto);
        // Ordena os elementos antes e depois da particao recursivamente
        quickSort(arr, baixo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}

// Algoritmo de ordenacao Heap Sort
void heapify(int arr[], int n, int i) {
    // Inicializar a raiz como o maior elemento
    int maior = i;
    // Calcular o Indice do filho esquerdo e direito na arvore
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    // Verificar se o filho esquerdo eh maior que o pai
    comparacoes++;
    if (esquerda < n && arr[esquerda] > arr[maior])
        maior = esquerda;

    // Verificar se o filho direito eh maior que o pai
    comparacoes++;
    if (direita < n && arr[direita] > arr[maior])
        maior = direita;

    // Se o maior nÃ£o for o pai, trocar e chamar a funcao novamente
    comparacoes++;
    if (maior != i) {
        trocar(&arr[i], &arr[maior]);
        heapify(arr, n, maior);
    }
}

// Funcao para realizar o heap sort
void heapSort(int arr[], int n) {
    // Construir um heap maximo a partir do array
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extrair elementos do heap um por um
    for (int i = n - 1; i > 0; i--) {
        trocar(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// Funcao para gerar dados aleatorios
int* gerarAleatorios(int tam, int semente) {
    srand(semente);
    int* arr = (int*)malloc(tam * sizeof(int));
    for (int i = 0; i < tam; i++) {
        arr[i] = rand() % 1000; // Numeros aleatorios entre 0 e 999
    }
    return arr;
}

// Funcao para gerar dados quase ordenados
int* gerarQuaseOrdenados(int tam, int porcentagem) {
    srand(time(NULL)); // Inicializa o gerador de nÃºmeros aleatorios com a hora atual
    int* arr = (int*)malloc(tam * sizeof(int));
    for (int i = 0; i < tam; i++) {
        arr[i] = i; // Preenche o array com numeros ordenados
    }
    int qtdDesordenados = (porcentagem * tam) / 100; // Calcula a quantidade de elementos a serem desordenados
    for (int i = 0; i < qtdDesordenados; i++) {
        // Troca aleatoria de alguns elementos para criar desordem
        int pos1 = rand() % tam; // Gera uma posiÃ§Ã£o aleatoria dentro do tamanho do array
        int pos2 = rand() % tam; // Gera outra posiÃ§Ã£o aleatoria dentro do tamanho do array
        trocar(&arr[pos1], &arr[pos2]);
    }
    return arr; // Retorna o ponteiro para o array gerado
}

// Funcao para gerar dados em ordem crescente ou decrescente
int* gerarOrdenados(int tam, int ordem) {
    int* arr = (int*)malloc(tam * sizeof(int));

    // Verifica o tipo de ordem solicitada
    if (ordem == 0) {
        // Caso de numeros ordenados em ordem crescente
        for (int i = 0; i < tam; i++) {
            arr[i] = i + 1; // Adiciona 1 para evitar zeros
        }
    } else if (ordem == 1) {
        // Caso de numeros ordenados em ordem decrescente
        for (int i = 0; i < tam; i++) {
            arr[i] = tam - i; // Atribui valores decrescentes ao array
        }
    }
    return arr;
}

// Funcao para calcular o tempo decorrido em milissegundos
double tempoDecorrido(struct timeval inicio, struct timeval fim) {
    double inicio_ms = (double)inicio.tv_sec * 1000.0 + (double)inicio.tv_usec / 1000.0;
    double fim_ms = (double)fim.tv_sec * 1000.0 + (double)fim.tv_usec / 1000.0;
    return fim_ms - inicio_ms;
}

void executarTesteDesempenho(int tamanhosDados[], int qtdTamanhos, int metodo) {
    char* nomeMetodo;
    switch (metodo) {
        case 1:
            nomeMetodo = "Insercao";
            break;
        case 2:
            nomeMetodo = "Selecao";
            break;
        case 3:
            nomeMetodo = "Merge";
            break;
        case 4:
            nomeMetodo = "Quick";
            break;
        case 5:
            nomeMetodo = "Heap";
            break;
        default:
            printf("Metodo de ordenacao invalido.\n");
            return;
    }

    printf("\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Tamanho dos Dados |                Aleatorio               |              Quase Ordenado              |                 Crescente                |                Decrescente               |\n");
  printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < qtdTamanhos; i++) {
        int tamanho = tamanhosDados[i];
        printf("%-17d | ", tamanho); //Imprime o tamanho dos dados de forma formatada. A string "%-17d" especifica o valor inteiro (%d) justificado a esquerda
        struct timeval inicio, fim;
        double tempo;

        // Teste de desempenho para dados aleatorios
        double tempoTotalAleatorio = 0.0;
        comparacoes = 0;
        trocas = 0;
        for (int j = 0; j < 5; j++) {
            int* arr = gerarAleatorios(tamanho, j + 1);
            gettimeofday(&inicio, NULL);
            switch (metodo) {
                case 1:
                    ordenacaoPorInsercao(arr, 0, tamanho - 1);
                    break;
                case 2:
                    ordenacaoPorSelecao(arr, 0, tamanho - 1);
                    break;
                case 3:
                    mergeSort(arr, 0, tamanho - 1);
                    break;
                case 4:
                    quickSort(arr, 0, tamanho - 1);
                    break;
                case 5:
                    heapSort(arr, tamanho);
                    break;
                default:
                    printf("Metodo de ordenacao invalido.\n");
                    free(arr);
                    return;
            }
            gettimeofday(&fim, NULL);
            tempoTotalAleatorio += tempoDecorrido(inicio, fim);
            free(arr);
        }

        printf("%9.5f ms,%9lld tr,%9lld cp | ", tempoTotalAleatorio / 5, trocas / 5, comparacoes / 5); //O especificador de formato %-9.5f eh usado para imprimir um numero de ponto flutuante (%f) com 5 casas decimais e justificado a esquerda. Os demais representam um long long int

        // Teste de desempenho para dados quase ordenados
        double tempoTotalQuaseOrdenado = 0.0;
        comparacoes = 0;
        trocas = 0;
        for (int j = 0; j < 5; j++) {
            int* arr = gerarQuaseOrdenados(tamanho, 10);
            gettimeofday(&inicio, NULL);
            switch (metodo) {
                case 1:
                    ordenacaoPorInsercao(arr, 0, tamanho - 1);
                    break;
                case 2:
                    ordenacaoPorSelecao(arr, 0, tamanho - 1);
                    break;
                case 3:
                    mergeSort(arr, 0, tamanho - 1);
                    break;
                case 4:
                    quickSort(arr, 0, tamanho - 1);
                    break;
                case 5:
                    heapSort(arr, tamanho);
                    break;
                default:
                    printf("Metodo de ordenacao invalido.\n");
                    free(arr);
                    return;
            }
            gettimeofday(&fim, NULL);
            tempoTotalQuaseOrdenado += tempoDecorrido(inicio, fim);
            free(arr);
        }
        printf("%9.5f ms, %9lld tr, %9lld cp | ", tempoTotalQuaseOrdenado / 5, trocas / 5, comparacoes / 5); 

        // Teste de desempenho para dados ordenados em ordem crescente
        comparacoes = 0;
        trocas = 0;
        int* arrCrescente = gerarOrdenados(tamanho, 0);
        gettimeofday(&inicio, NULL);
        switch (metodo) {
            case 1:
                ordenacaoPorInsercao(arrCrescente, 0, tamanho - 1);
                break;
            case 2:
                ordenacaoPorSelecao(arrCrescente, 0, tamanho - 1);
                break;
            case 3:
                mergeSort(arrCrescente, 0, tamanho - 1);
                break;
            case 4:
                quickSort(arrCrescente, 0, tamanho - 1);
                break;
            case 5:
                heapSort(arrCrescente, tamanho);
                break;
            default:
                printf("Metodo de ordenacao invalido.\n");
                free(arrCrescente);
                return;
        }
        gettimeofday(&fim, NULL);
        tempo = tempoDecorrido(inicio, fim);
        printf("%9.5f ms, %9lld tr, %9lld cp | ", tempo, trocas, comparacoes);
        free(arrCrescente);

        // Teste de desempenho para dados ordenados em ordem decrescente
        comparacoes = 0;
        trocas = 0;
        int* arrDecrescente = gerarOrdenados(tamanho, 1);
        gettimeofday(&inicio, NULL);
        switch (metodo) {
            case 1:
                ordenacaoPorInsercao(arrDecrescente, 0, tamanho - 1);
                break;
            case 2:
                ordenacaoPorSelecao(arrDecrescente, 0, tamanho - 1);
                break;
            case 3:
                mergeSort(arrDecrescente, 0, tamanho - 1);
                break;
            case 4:
                quickSort(arrDecrescente, 0, tamanho - 1);
                break;
            case 5:
                heapSort(arrDecrescente, tamanho);
                break;
            default:
                printf("Metodo de ordenacao invalido.\n");
                free(arrDecrescente);
                return;
        }
        gettimeofday(&fim, NULL);
        tempo = tempoDecorrido(inicio, fim);
        printf("%9.5f ms, %9lld tr, %9lld cp |\n", tempo, trocas, comparacoes);
        free(arrDecrescente);
    }
  printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
 printf("Legenda: \n");
 printf("ms = milisegundos\n");
 printf("tr = trocas\n");
 printf("cp = comparacoes\n");
 printf("\n");

}