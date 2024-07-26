/*
 * Trabalho: Implementação de Grafos
 * Vencimento: 09/05/2024
 * Submissão: 20/04/2024
 * Nome: Heitor Silva Avila
 * Turma: M2
 */

/*
 * Implementar um programa na linguagem de sua escolha, que permita a representação em memória de um grafo.
 * Este programa deve permitir a entrada dos vértices e os pesos das arestas, considere as seguintes funcionalidades:
 * 1. Permitir o armazenamento de até 20 vértices
 * 2. Fazer a leitura dos pesos das arestas de cada vértice
 * 3. Considerar sempre vértices positivos
 * 4. Mostrar os dados armazenados
 */

/*
 * Nova submissão:  17/07/2024.
 * Justificativa para a nova sumissão do código fonte:
 * 1. A versão original cria uma matriz[20][20], o que significa que temos um intervalo de [0-19] posições.
 * 2. As funções auxiliares possuíam loops que agora funcionam com uma variação de 0 <= i <= 19.
 * 3. O programa deve permitir o armazenamento de ATÉ vinte nodos (vértices), isso significa que na versão anterior eu não poderia armazenar um grafo com menos nodos!
 * 4. Para a impressão dos nodos no console, vai ser preciso um tratamento especial na hora de analisar o peso de cada nodo afim de manter uma tabulação e apresentação aceitável.
 * 5. Afins de praticidade para compilar e enviar um único arquivo, os protótipos das funções foram declarados acima de main.
 * 6. O contador de nodos passou a ser uma variável global que só é incrementada caso o caminho informado seja válido, senão, o valor é preservado.
 */

#include <stdio.h>
int matriz[20][20];
int qtdNodos = 0;

void exibeIntro();
void zerarMatriz();
void criarAresta(int nodo_origem, int nodo_destino, int peso);
void imprimeMatriz();
void obterAresta();
void limparBuffer();
void preencheMatriz();

int main(int argc, char **argv)
{
  exibeIntro();
  zerarMatriz();
  preencheMatriz();
  imprimeMatriz();
  return(0);
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
}

void zerarMatriz()
{
  for (int i = 0; i <= 19; ++i)
  {
    for (int j = 0; j <= 19; ++j)
    {
      matriz[i][j] = 0;
    }
  }
}

void criarAresta(int origem, int destino, int peso)
{
  if (origem >= 0 && origem <= 19 && destino >= 0 && destino <= 19)
  {
    matriz[origem][destino] = peso;
    ++qtdNodos;
  }
  else { 
    printf("------------------------------ \n");
    printf("Origem e destino devem estar entre o intervalo de 0 a 19! Tente novamente! \n");
  }
}

void imprimeMatriz()
{
  printf("------------------------------ \n");
  for (int i = 0; i <= 19; ++i)
  {
    for (int j = 0; j <= 19; ++j)
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
    while ((c = getchar()) != '\n' && c != EOF);
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
    } while (controle != 'N' && controle != 'n' && qtdNodos < 19);
}