#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Algoritmos de ordenacao
void ordenacaoPorInsercao(int arr[], int inicio, int fim);
void ordenacaoPorSelecao(int arr[], int inicio, int fim);
void mergeSort(int arr[], int inicio, int fim);
void quickSort(int arr[], int baixo, int alto);
void heapSort(int arr[], int n);

//Funcoes de geracao de dados
int* gerarAleatorios(int tam, int semente);
int* gerarQuaseOrdenados(int tam, int porcentagem);
int* gerarOrdenados(int tam, int ordem);

//Funcao para executar o teste de desempenho
void executarTesteDesempenho(int tamanhosDados[], int qtdTamanhos, int metodo);

#endif