/*
 * Trabalho: Implementação Algoritmo Kruskal
 * Submissão: 23/07/2024
 * Nome: Heitor Silva Avila
 * Turma: M2
 */

/*
 * Implementar a funçionalidade de geração de AGM no primeiro trabalho de grafos, mostrando a AGM resultante da execução do Algoritmo de Kruskal.
 * O docente no dia 19/07/2024 afirmou que não era necessário gravar o video solicitado no e-AULA. Essa atividade era somente para alunos pelos efeitos climáticos.
 */

#include <stdio.h>

/*
 * Mudanças no algoritmo principal:
 * 1. Para facilitar, vamos trabalhar com grafos não-orientados.
 * 2. Isso significa que para cada aresta agora vamos ter a ida e a volta.
 * 3. Para economizar variáveis e modularizar o código, usamos o comando DEFINE.
 */

#define MAX_VERTICES 20
#define MAX_ARESTAS ((MAX_VERTICES * (MAX_VERTICES - 1)) / 2)

/*
 * De maneira prática, tenho que ordenar de forma crescente os pesos das arestas.
 * Todavia, eu tenho que também armazenar a informação de origem e destino daquela aresta.
 * E uma maneira de fazer isso é criando uma estrutura e ordenando ela usando o peso como chave.
 */

typedef struct
{
  int origem;
  int destino;
  int peso;
} Aresta;

// Matriz de Adjascência:
int matriz[MAX_VERTICES][MAX_VERTICES];

// Lista de Arestas:
Aresta arrayDeArestas[MAX_ARESTAS];

// Quantidade de Arestas (útil para loop):
int qtdArestas = 0;

// Estrutura de Conjunto Disjunto:
int elemento[MAX_VERTICES];
int peso[MAX_VERTICES];

// Matriz de adjascência para a AGM:
int matrizAGM[MAX_VERTICES][MAX_VERTICES];

// Protótipos acima do main para simplificar o envio:
void preencheMatriz();
void limparBuffer();
void obterAresta();
void criarAresta(int origem, int destino, int peso);
void imprimeMatriz();
void exibeIntro();
void zerarMatriz();
void armazenarArestas();
void trocar(Aresta *a, Aresta *b);
void bubbleSort(Aresta arrayDeArestas[], int n);
void kruskal();
void inicializarConjuntos();
int encontrar(int x);
void unir(int x, int y);
void imprimirAGM();

int main(int argc, char **argv)
{
  // exibeIntro();
  zerarMatriz();
  // preencheMatriz();

  // Para demonstrar Kruskal,  o preenchimento foi subtituido por um grafo.
  criarAresta(0, 1, 5);
  criarAresta(0, 2, 7);
  criarAresta(0, 3, 8);
  criarAresta(0, 4, 9);
  criarAresta(1, 2, 5);
  criarAresta(1, 3, 8);
  criarAresta(1, 4, 1);
  criarAresta(2, 3, 2);
  criarAresta(2, 4, 9);
  criarAresta(3, 4, 3);

  printf("------------------------------ \n");
  printf("Imprimindo a matriz original: \n");
  imprimeMatriz();

  printf("Imprimindo a AGM de Kruskal: \n");
  // Gerando a Arvore Geradora Minima por meio de Kruskal:
  kruskal();

  printf("No console: Matriz original, matriz AGM e lista de arestas. \n");
  printf("------------------------------ \n");

  return(0);
}

void preencheMatriz()
{
  char controle = 'S';
  do
  {
    obterAresta();
    printf("------------------------------ \n");
    limparBuffer();
    printf("Adicionar novo caminho ao grafo (S/N)? ");
    scanf("%c", &controle);
  } while (controle != 'N' && controle != 'n' && qtdArestas < MAX_VERTICES - 1);
}

void limparBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
  {
  }
}

void obterAresta()
{
  int origem, destino, peso;
  printf("------------------------------ \n");
  printf("Informe origem, destino e peso, separados por um unico espaco: ");
  scanf("%d %d %d", &origem, &destino, &peso);
  criarAresta(origem, destino, peso);
}

void criarAresta(int origem, int destino, int peso)
{
  if (origem >= 0 && origem < MAX_VERTICES && destino >= 0 && destino < MAX_VERTICES && peso > 0)
  {
    matriz[origem][destino] = peso;
    matriz[destino][origem] = peso;
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

void imprimeMatriz()
{
  printf("------------------------------ \n");
  for (int i = 0; i < MAX_VERTICES; ++i)
  {
    for (int j = 0; j < MAX_VERTICES; ++j)
    {
      if (matriz[i][j] == 0)
      {
        printf("| \t |");
      }
      else
      {
        printf("| %d \t |", matriz[i][j]);
      }
    }
    printf("\n");
  }
  printf("------------------------------ \n");
}

void exibeIntro()
{
  printf("------------------------------ \n");
  printf("Este programa armazena um grafo ordenado na forma de matriz de adjacencia. \n");
  printf("------------------------------ \n");
  printf("A captura e feita informando os valores dos nodos de origem, destino e o peso do vertice. \n");
  printf("------------------------------ \n");
  printf("Exemplo: Ao digitar '15 4 8' voce cria um caminho de 15 para 4 com peso 8. \n");
  printf("------------------------------ \n");
  printf("O programa suporta armazenar ate 20 nodos classificados em um intervalo de 0 ate 19. \n");
}

void zerarMatriz()
{
  for (int i = 0; i < MAX_VERTICES; ++i)
  {
    for (int j = 0; j < MAX_VERTICES; ++j)
    {
      matriz[i][j] = 0;
    }
  }
}

void armazenarArestas()
{

  /*
   * E como que eu vou preencher isso? Bom...
   * Uma lógica é usar a mesma lógica do loop aninhado da impressão da matriz.
   * Entretanto, ao invés de "imprimir", eu armazeno, lembrando que só temos pesos positivos!
   * Primeiro vou me preocupar em armazenar, depois eu vou me preocupar em ordenar!
   * E tem o pulo do gato: Por ser um grafo não-orientado, eu posso me preocupar apenas com metade da matriz!
   * Então ao armazenar apenas a metade da matriz, não preociso ficar me preocupando com conexões repetidas.
   */

  for (int i = 0; i < MAX_VERTICES; ++i)
  {
    for (int j = i; j < MAX_VERTICES; ++j)
    {
      if (matriz[i][j] > 0)
      {
        arrayDeArestas[qtdArestas].origem = i;
        arrayDeArestas[qtdArestas].destino = j;
        arrayDeArestas[qtdArestas].peso = matriz[i][j];
        qtdArestas++;
      }
    }
  }
}

/*
 * Agora para ORDENAR este vetor do tipo Arestas eu vou partir para o uso do BubbleSort.
 * É uma técnica simples, porém eficaz se bem utilizada.
 * Vamos adaptar o método para que ele funcione com a estrutura que modelamos:
 */

// Método que faz o swap:
void trocar(Aresta *a, Aresta *b)
{
  Aresta temp = *a;
  *a = *b;
  *b = temp;
}

// Método recursivo do BubbleSort adaptado ordenar conforme o peso:
void bubbleSort(Aresta arrayDeArestas[], int n)
{
  for (int i = 0; i < n - 1; ++i)
  {
    for (int j = 0; j < n - i - 1; ++j)
    {
      if (arrayDeArestas[j].peso > arrayDeArestas[j + 1].peso)
      {
        trocar(&arrayDeArestas[j], &arrayDeArestas[j + 1]);
      }
    }
  }
}

void kruskal()
{
  // Armazena todas as arestas do grafo original em arrayDeArestas
  armazenarArestas();

  // Lista que irá conter as arestas da Arvore Geradora Minima (AGM)
  Aresta listaArestas[MAX_VERTICES - 1];
  // Contador de arestas na AGM
  int numArestasAGM = 0;

  // Inicializa a estrutura de conjuntos disjuntos
  inicializarConjuntos();

  // Ordena todas as arestas em ordem crescente de peso
  bubbleSort(arrayDeArestas, qtdArestas);

  // Percorre todas as arestas ordenadas
  for (int i = 0; i < qtdArestas; ++i)
  {
    int origem = arrayDeArestas[i].origem;
    int destino = arrayDeArestas[i].destino;
    int peso = arrayDeArestas[i].peso;

    // Verifica se a aresta conecta dois conjuntos diferentes na estrutura de conjuntos disjuntos
    if (encontrar(origem) != encontrar(destino))
    {
      // Adiciona a aresta à lista da AGM
      listaArestas[numArestasAGM++] = arrayDeArestas[i];
      // Preenche a matriz de adjacência da AGM tanto na "ida" quanto na "volta"
      matrizAGM[origem][destino] = peso;
      matrizAGM[destino][origem] = peso;
      // Une os conjuntos que estão conectados pela aresta
      unir(origem, destino);
    }
  }

  // Imprimindo a matriz de adjascência da AGM:
  imprimirAGM();

  // Imprime todas as arestas da Arvore Geradora Minima encontrada
  printf("Arestas da Arvore Geradora Minima:\n");
  printf("------------------------------ \n");
  for (int i = 0; i < numArestasAGM; ++i)
  {       
    printf("(%d - %d): peso %d\n", listaArestas[i].origem, listaArestas[i].destino, listaArestas[i].peso);
  }
  printf("------------------------------ \n");
}

void inicializarConjuntos()
{
  // Inicializa cada elemento como seu próprio conjunto
  for (int i = 0; i < MAX_VERTICES; ++i)
  {
    elemento[i] = i;
    peso[i] = 1; // Inicialmente cada conjunto tem peso 1
  }
}

int encontrar(int x)
{
  // Encontra o representante (raiz) do conjunto que contém x
  if (elemento[x] != x)
  {
    // Compressão de caminho: otimização para tornar as buscas mais eficientes
    elemento[x] = encontrar(elemento[x]);
  }
  return elemento[x];
}

void unir(int x, int y)
{
  // Encontra as raizes dos conjuntos que contêm x e y
  int raizX = encontrar(x);
  int raizY = encontrar(y);

  // Realiza a união dos conjuntos apenas se eles forem diferentes
  if (raizX != raizY)
  {
    // União por peso: mantém a Arvore de conjuntos balanceada
    if (peso[raizX] < peso[raizY])
    {
      elemento[raizX] = raizY; // Conecta raizX sob raizY
    }
    else if (peso[raizX] > peso[raizY])
    {
      elemento[raizY] = raizX; // Conecta raizY sob raizX
    }
    else
    {
      elemento[raizY] = raizX; // Conecta raizY sob raizX
      peso[raizX]++; // Incrementa o peso de raizX
    }
  }
}

void imprimirAGM()
{
  // Imprime a matriz de adjacência da Arvore Geradora Minima
  printf("------------------------------ \n");
  printf("Matriz da Arvore Geradora Minima: \n");
  printf("------------------------------ \n");
  for (int i = 0; i < MAX_VERTICES; ++i)
  {
    for (int j = 0; j < MAX_VERTICES; ++j)
    {
      if (matrizAGM[i][j] == 0)
      {
        printf("| \t |"); // Célula vazia na matriz
      }
      else
      {
        printf("| %d \t |", matrizAGM[i][j]); // Preenche com o peso da aresta
      }
    }
    printf("\n");
  }
  printf("------------------------------ \n");
}
