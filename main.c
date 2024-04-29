#include <stdio.h>
#include "benchmark.h"

int main() {
    int qtdTamanhos; // Variavel para armazenar a quantidade de tamanhos de dados a serem testados
    int tamanhosDados[100]; // Array para armazenar os tamanhos dos conjuntos de dados
    int qtdMetodos; // Variavel para armazenar a quantidade de metodos de ordenacao a serem testados
    int opcao = -1; // Variavel para armazenar a opcao selecionada pelo usuario

    // Solicita ao usuario que digite a quantidade de metodos de ordenacao a serem testados
    printf("Digite a quantidade de metodos de ordenacao a serem testados: ");
    scanf("%d", &qtdMetodos);

    // Solicita ao usuÃƒÂ¡rio que digite a quantidade de tamanhos de dados a serem testados
    printf("\nDigite a quantidade de tamanhos de dados a serem testados: ");
    scanf("%d", &qtdTamanhos);
    printf("\n");

    // Verifica se a quantidade de tamanhos eh igual a zero e, se for, encerra o programa
    if (qtdTamanhos == 0) {
        printf("Encerrando o programa.\n");
        return 0;
    }

    // Solicita ao usuario que digite os tamanhos dos conjuntos de dados a serem testados
    printf("Digite os tamanhos dos conjuntos de dados a serem testados: ");
    for (int i = 0; i < qtdTamanhos; i++) {
        scanf("%d", &tamanhosDados[i]);
    }

    // Loop para executar os metodos de ordenacao conforme a quantidade especificada
    while (qtdMetodos--) {
        // Solicita ao usuario que selecione o metodo de ordenacao
        printf("\nSelecione o metodo de ordenacao:\n");
        printf("1. Insercao\n");
        printf("2. Selecao\n");
        printf("3. Mergesort\n");
        printf("4. QuickSort\n");
        printf("5. HeapSort\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        // Executa o metodo de ordenacao escolhido pelo usuario com base na opcao selecionada
        switch (opcao){
            case 1:
                executarTesteDesempenho(tamanhosDados, qtdTamanhos, 1); // 1 para Insercao
                break;
            case 2:
                executarTesteDesempenho(tamanhosDados, qtdTamanhos, 2); // 2 para Selecao
                break;
            case 3:
                executarTesteDesempenho(tamanhosDados, qtdTamanhos, 3); // 3 para Mergesort
                break;
            case 4:
                executarTesteDesempenho(tamanhosDados, qtdTamanhos, 4); // 4 para QuickSort
                break;
            case 5:
                executarTesteDesempenho(tamanhosDados, qtdTamanhos, 5); // 5 para HeapSort
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }

    return 0;
}