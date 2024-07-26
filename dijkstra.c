/*
 * Trabalho: Implementação Algoritmo Dijkstra
 * Vencimento: 02/05/2024
 * Submissão: 18/04/2024
 * Nome: Heitor Silva Avila
 * Turma: M2
 */

/*
 * Implementar um programa C para calcular os caminhos mínimos entre os vértices de um Grafo utilizando o algorítmo de Dijsktra.
 * 1. Permitir o armazenamento de até 20 vértices
 * 2. Fazer a leitura dos pesos das arestas de cada vértice
 * 3. Considerar sempre vértices positivos
 * 4. Mostrar o caminho mínimo entre dois vértices solicitados
 */

/*
 * Nova submissão: 18/07/2024.
 * Justificativa para a nova sumissão do código fonte:
 * 1. A versão original é baseada no antigo arquivo grafos.c que foi totalmente reestruturado e enviado para o e-AULA.
 * 2. Nessa nova versão, o código está modularizado, o que permite criar as funções para expansão da lógica.
 * 3. As antigas funções auxiliares apresentavam problemas de funcionamento.
 * 4. Manteve-se a cultura de preservar a assinatura das funções acima do main para fazer apenas um único upload.
 * 5. A constante 20 foi alterada para uma definição para o compilador e também para garantir que o código possa ser modificado.
 */

#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 20

int matriz[MAX_VERTICES][MAX_VERTICES];
int qtdNodos = 0;

void chamadaDijkstra();
void exibeIntro();
void zerarMatriz();
void criarAresta(int origem, int destino, int peso);
void imprimeMatriz();
void obterAresta();
void limparBuffer();
void preencheMatriz();
void dijkstra(int origem, int destino);

int main(int argc, char **argv)
{
  exibeIntro();
  zerarMatriz();
  preencheMatriz();
  imprimeMatriz();
  chamadaDijkstra();
  return (0);
}

void chamadaDijkstra()
{
  int origem, destino;
  printf("------------------------------ \n");
  printf("Digite os vertices de origem e destino para encontrar o caminho minimo separados por um espaco: ");
  scanf("%d %d", &origem, &destino);

  // Verifica se origem é igual a destino
  if (origem == destino)
  {
    printf("Origem e destino sao iguais. Nao e necessario calcular o caminho minimo.\n");
    return;
  }

  dijkstra(origem, destino); // Chamada para o algoritmo de Dijkstra
}

void exibeIntro()
{
  printf("------------------------------ \n");
  printf("Este programa armazena um grafo ordenado na forma de matriz de adjascencia. \n");
  printf("------------------------------ \n");
  printf("A captura e feita informando os valores dos nodos de origem, destino e o peso do vertice. \n");
  printf("------------------------------ \n");
  printf("Exemplo: Ao digitar '15 4 8' voce cria um caminho de 15 para 4 com peso 8. \n");
  printf("------------------------------ \n");
  printf("O programa suporta armazenar ate 20 nodos classificados em um intervalo de 0 ate 19. \n");
  printf("------------------------------ \n");
  printf("Nessa versao, o programa solicita dois vertices para exibir o menor caminho entre eles. \n");
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

void criarAresta(int origem, int destino, int peso)
{
  if (origem >= 0 && origem < MAX_VERTICES && destino >= 0 && destino < MAX_VERTICES)
  {
    matriz[origem][destino] = peso;
    ++qtdNodos;
  }
  else
  {
    printf("------------------------------ \n");
    printf("Origem e destino devem estar entre o intervalo de 0 a %d! Tente novamente! \n", MAX_VERTICES - 1);
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
        printf("\t");
      }
      else
      {
        printf("%d \t", matriz[i][j]);
      }
    }
    printf("\n");
  }
  printf("------------------------------ \n");
}

void obterAresta()
{
  int origem, destino, peso;
  printf("------------------------------ \n");
  printf("Informe origem, destino e peso, separados por um unico espaco: ");
  scanf("%d %d %d", &origem, &destino, &peso);
  if (peso < 0)
  {
    printf("------------------------------ \n");
    printf("O valor referente ao peso deve ser positivo! Tente novamente! \n");
    return;
  }
  criarAresta(origem, destino, peso);
}

void limparBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
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
  } while (controle != 'N' && controle != 'n' && qtdNodos < MAX_VERTICES);
}

void dijkstra(int origem, int destino)
{
  int distMin[MAX_VERTICES];
  int visitado[MAX_VERTICES];
  int anterior[MAX_VERTICES];

  /*
   * Começamos indicando que a distâcia mínima entre os vértices é o máximo que um inteiro pode representar.
   * Essa estratégia permite que a cada teste lógico encontrar o menor valor possível de todos.
   * Também indicamos todos os vértices como "não visitado", sinalizado por "0".
   * É feita a sinalização de que nenhum vértice ainda foi visitado, sinalizado por "-1".
   */

  for (int i = 0; i < MAX_VERTICES; ++i)
  {
    distMin[i] = INT_MAX;
    visitado[i] = 0;
    anterior[i] = -1;
  }

  // Sair de um ponto A e ir para o mesmo ponto A a distância sempre vai ser zero!
  distMin[origem] = 0;

  // Fazemos MAX_VERTICES - 1 vezes o teste lógico para garantir que todas as distâncias mínimas sejam calculadas
  for (int loopMin = 0; loopMin < MAX_VERTICES - 1; ++loopMin)
  {
    // O vértice que está sendo processado naquela iteração é o "u" e a distância mínima conhecida é "-1"
    int u = -1;

    // Então para OUTRO vértice, representado por V, verificamos:
    for (int v = 0; v < MAX_VERTICES; ++v)
    {

      // SE o V NÃO foi visitado E a distância de U for -1 OU a distância de V for menor que U, então V assume o lugar de U.
      if (!visitado[v] && (u == -1 || distMin[v] < distMin[u]))
        u = v;
    }

    // Perceba que como estamos fazendo uma varredura entre os vértices, marcamos eles como visitados.
    visitado[u] = 1;

    // Modifica as distâncias mínimas para os vértices adjacentes de "u" não visitados.
    for (int v = 0; v < MAX_VERTICES; ++v)
    {
      // SE v não foi visitado, SE existe uma aresta de u para v E SE encontrou um caminho mais curto até v
      if (!visitado[v] && matriz[u][v] != 0 && distMin[u] != INT_MAX &&
          distMin[u] + matriz[u][v] < distMin[v])
      {

        // Atualiza a distância mínima para v
        distMin[v] = distMin[u] + matriz[u][v];
        // Define u como antecessor de v no caminho mínimo
        anterior[v] = u;
      }
    }
  }

  // Agora seria o equivalente a "tracejar" o menor caminho usando o array anterior[]
  printf("------------------------------ \n");
  printf("Caminho minimo de %d para %d:\n", origem, destino);

  // Array para armazenar o caminho mínimo encontrado
  int caminho[MAX_VERTICES];

  // Essa variável vai determinando a quantidade de arestas
  int tamCaminho = 0;

  // Nossa base é o ponto de partida, o passo indutivo é o ponto de destino.
  int passo = destino;

  // Para o destino é preciso que o tamanho do caminho precise de pelo menos uma aresta, senão estaríamos falando do mesmo ponto.
  caminho[tamCaminho++] = passo;

  // Reconstrói o caminho mínimo do destino até a origem.
  while (passo != origem)
  {
    // Capturamos como passo o anterior no caminho mínimo
    passo = anterior[passo];
    // Adicionamos esse antecessor na fila do caminho mínimo
    caminho[tamCaminho++] = passo;
  }

  // Imprime o caminho mínimo reconstruído usando os vetores auxiliares.
  for (int i = tamCaminho - 1; i >= 0; --i)
  {
    // Então do tamanho do caminho até chegar ao destino final, vamos diminuindo a distância.
    printf("%d", caminho[i]);

    // Vai exibindo a distância e colocando setinhas caso ainda exista caminho a ser percorrido.
    if (i > 0)
      printf(" -> ");
  }

  // Ao terminar, dá uma quebra de linha e exibe a distância mínima e o percurso da origem até o destino.
  printf("\n");

  // Imprime a distância mínima de origem a destino
  printf("Distancia minima: %d\n", distMin[destino]);
}