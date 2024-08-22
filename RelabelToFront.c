// Nome: Heitor Silva Avila
// Turma: M2
// Algoritmo: Relabel-to-Front

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_VERTICES 20

// Estrutura para armazenar uma aresta
typedef struct
{
    int origem;
    int destino;
    int peso;
} Aresta;

// Matriz de Adjacência que representa o grafo
int matriz[MAX_VERTICES][MAX_VERTICES];

// Matriz de capacidades para o fluxo máximo
int capacidade[MAX_VERTICES][MAX_VERTICES];

// Matriz de fluxo para armazenar o fluxo atual nas arestas
int fluxo[MAX_VERTICES][MAX_VERTICES];

// Altura de cada nó na rede
int altura[MAX_VERTICES];

// Excesso de fluxo em cada nó
int excessos[MAX_VERTICES];

// Fila para processar nós no algoritmo Relabel-to-Front
bool fila[MAX_VERTICES];
int frente = 0; // Posição da frente da fila
int tras = 0;   // Posição do final da fila

// Protótipos das funções
void zerarMatriz();
void criarAresta(int origem, int destino, int peso);
void imprimeMatriz();
void inicializarFluxo();
void relabelToFront(int origem, int destino);
void empurrar(int u, int v);
void relabel(int u);
void enfileirar(int u);
void desenfileirar(int u);
bool estaNaFila(int u);
void imprimirFluxos();

int main(int argc, char **argv)
{
    // Zera a matriz de adjacência e de capacidades
    zerarMatriz();

    // Cria as arestas do grafo com seus respectivos pesos
    criarAresta(0, 1, 5);
    criarAresta(1, 2, 7);
    criarAresta(2, 3, 8);
    criarAresta(3, 4, 3);
    criarAresta(4, 5, 10);
    criarAresta(5, 6, 4);
    criarAresta(6, 7, 6);
    criarAresta(7, 8, 2);
    criarAresta(8, 9, 9);
    criarAresta(9, 10, 1);
    criarAresta(10, 11, 7);
    criarAresta(11, 12, 5);
    criarAresta(12, 13, 3);
    criarAresta(13, 14, 8);
    criarAresta(14, 15, 6);
    criarAresta(15, 16, 4);
    criarAresta(16, 17, 9);
    criarAresta(17, 18, 2);
    criarAresta(18, 19, 5);
    criarAresta(19, 0, 7);
    criarAresta(0, 2, 6);
    criarAresta(0, 8, 5);
    criarAresta(0, 9, 2);
    criarAresta(0, 10, 100);

    // Imprime a matriz de adjacência original
    printf("------------------------------ \n");
    printf("Imprimindo a matriz original: \n");
    imprimeMatriz();

    // Inicializa o fluxo, capacidades, alturas e excessos
    inicializarFluxo();

    // Preenche a matriz de capacidades com os valores das arestas
    for (int i = 0; i < MAX_VERTICES; ++i)
    {
        for (int j = 0; j < MAX_VERTICES; ++j)
        {
            capacidade[i][j] = matriz[i][j];
        }
    }

    // Executa o algoritmo Relabel-to-Front do nó 0 para o nó 10
    printf("Executando o algoritmo Relabel-to-Front de 0 a 10:\n");
    relabelToFront(0, 10);

    // Imprime a matriz de fluxos calculados
    imprimirFluxos();

    printf("------------------------------ \n");

    return 0;
}

// Função para empurrar o excesso de um nó u para um nó v
void empurrar(int u, int v)
{
    int delta = excessos[u];
    if (excessos[u] > capacidade[u][v] - fluxo[u][v])
    {
        delta = capacidade[u][v] - fluxo[u][v]; // Limita o fluxo ao restante da capacidade
    }
    fluxo[u][v] += delta;  // Adiciona fluxo ao nó v
    fluxo[v][u] -= delta;  // Remove fluxo do nó u
    excessos[u] -= delta;  // Atualiza o excesso do nó u
    excessos[v] += delta;  // Atualiza o excesso do nó v
}

// Função para relabelar um nó, aumentando sua altura
void relabel(int u)
{
    int minAltura = INT_MAX;
    
    // Encontra a menor altura dos vizinhos que têm capacidade restante
    for (int v = 0; v < MAX_VERTICES; ++v)
    {
        if (capacidade[u][v] > 0 && fluxo[u][v] < capacidade[u][v])
        {
            if (altura[v] < minAltura)
            {
                minAltura = altura[v];
            }
        }
    }
    
    // Aumenta a altura do nó u para um valor que seja maior que a menor altura dos vizinhos
    altura[u] = minAltura + 1;
}

// Função para inicializar as matrizes de fluxo e capacidades e os vetores de altura e excessos
void inicializarFluxo()
{
    for (int i = 0; i < MAX_VERTICES; ++i)
    {
        for (int j = 0; j < MAX_VERTICES; ++j)
        {
            fluxo[i][j] = 0; // Inicializa a matriz de fluxos com zeros
        }
        altura[i] = 0;   // Inicializa a altura dos nós
        excessos[i] = 0; // Inicializa os excessos de fluxo dos nós
        fila[i] = false; // Inicializa a fila como vazia
    }
}

// Função para adicionar um nó à fila de processamento
void enfileirar(int u)
{
    if (!fila[u])
    {
        fila[u] = true;  // Marca o nó como presente na fila
        tras++;          // Avança a posição do final da fila
    }
}

// Função para remover um nó da fila de processamento
void desenfileirar(int u)
{
    fila[u] = false;  // Marca o nó como ausente na fila
    frente++;         // Avança a posição da frente da fila
}

// Função para verificar se um nó está na fila
bool estaNaFila(int u)
{
    return fila[u];  // Retorna se o nó está presente na fila
}

// Função para zerar a matriz de adjacência
void zerarMatriz()
{
    for (int i = 0; i < MAX_VERTICES; ++i)
    {
        for (int j = 0; j < MAX_VERTICES; ++j)
        {
            matriz[i][j] = 0; // Inicializa a matriz com zeros
        }
    }
}

// Função para criar uma aresta entre dois nós com um peso específico
void criarAresta(int origem, int destino, int peso)
{
    // Verifica se os índices estão dentro dos limites e o peso é positivo
    if (origem >= 0 && origem < MAX_VERTICES && destino >= 0 && destino < MAX_VERTICES && peso > 0)
    {
        matriz[origem][destino] = peso;
        matriz[destino][origem] = peso; // Grafo não direcionado
    }
    else if (peso < 0)
    {
        printf("------------------------------ \n");
        printf("Peso deve ser maior que zero! \n");
        return;
    }
    else
    {
        printf("------------------------------ \n");
        printf("Origem e destino devem estar entre 0 e %d!\n", MAX_VERTICES - 1);
        return;
    }
}

// Função para imprimir a matriz de fluxos
void imprimirFluxos()
{
    printf("------------------------------ \n");
    printf("Matriz de fluxos: \n");
    printf("------------------------------ \n");
    
    // Itera sobre a matriz de fluxos e imprime os valores
    for (int i = 0; i < MAX_VERTICES; ++i)
    {
        for (int j = 0; j < MAX_VERTICES; ++j)
        {
            if (fluxo[i][j] == 0)
            {
                printf("| \t |"); // Espaço reservado para fluxos nulos
            }
            else
            {
                printf("| %d \t |", fluxo[i][j]); // Imprime o valor do fluxo
            }
        }
        printf("\n");
    }
    
    printf("------------------------------ \n");
}

// Função para imprimir a matriz de adjacência
void imprimeMatriz()
{
    printf("------------------------------ \n");
    for (int i = 0; i < MAX_VERTICES; ++i)
    {
        for (int j = 0; j < MAX_VERTICES; ++j)
        {
            if (matriz[i][j] == 0)
            {
                printf("| \t |"); // Espaço reservado para ausências de arestas
            }
            else
            {
                printf("| %d \t |", matriz[i][j]); // Imprime o peso da aresta
            }
        }
        printf("\n");
    }
    printf("------------------------------ \n");
}

// Função principal que executa o algoritmo Relabel-to-Front
void relabelToFront(int origem, int destino)
{
    // Define a altura do nó origem como o número de vértices
    altura[origem] = MAX_VERTICES;
    excessos[origem] = 0;
    excessos[destino] = 0;

    // Inicializa os excessos para os vizinhos do nó de origem
    for (int v = 0; v < MAX_VERTICES; ++v)
    {
        if (matriz[origem][v] > 0)
        {
            fluxo[origem][v] = matriz[origem][v];
            fluxo[v][origem] = -fluxo[origem][v];
            excessos[v] += fluxo[origem][v];
            excessos[origem] -= fluxo[origem][v];
            if (v != destino)
            {
                enfileirar(v); // Adiciona o nó à fila para processamento
            }
        }
    }

    // Processa a fila até que não haja mais excessos a serem empurrados
    while (frente <= tras)
    {
        int u = frente;
        desenfileirar(u); // Remove o nó da fila

        // Tenta empurrar o excesso do nó u para seus vizinhos
        for (int v = 0; v < MAX_VERTICES; ++v)
        {
            if (capacidade[u][v] > 0 && excessos[u] > 0)
            {
                empurrar(u, v);
            }
        }

        // Se houver excesso no nó u, relabel o nó e coloque-o de volta na fila
        if (excessos[u] > 0)
        {
            relabel(u);
            enfileirar(u);
        }
    }
}
