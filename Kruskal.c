/**
 * Implementação do Algoritmo de Kruskal    v0.0    15-10-2019
 *
 * Authors: Filipe de Lima Silva
 *          João Bruno Costa Cruz
 *          José Lucas da Costa Dantas
 *          Rafael Felix
 *
 * Instituto Federal de Educação, Ciência e Tecnologia do Ceará (IFCE) - Campus Fortaleza
 *
 * @Opensource
 * Este código-fonte pode ser utilizado, copiado, estudado, modificado e redistribuído sem restrições.
 *
 * Este software foi desenvolvido como um exercício programa da Disciplina de Grafos
 * do Professor Glauber Cintra do IFCE.
 *
 */

 /**
  * Entrada: Um Grafo Conexo
  * Saída: Um Árvore Gerado Mínima do Grafo (AGM)
  *
  * O programa recebe pela linha de comando o nome de um arquivo e uma descrição de
  * um Grafo.
  * Exemplo: C:\Users\aut> Kruskal.exe Grafo.txt
  *
  * O arquivo fornecido ao programa deverá ter o seguinte layout:
  *
  * n m
  * u1 v1 c1
  * u2 v2 c2
  * ...
  * um vm cm
  *
  * onde n é a quantidade de vértices, m a quantidade de arestas, ui e vi
  * são as extremidades da aresta i e ci é o custo da aresta i.
  *
  * Ao final, o algoritmo devolve quais aresta fazem parte da AGM e seu custo
  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define vertex int

/**
 * Cada aresta é representada por v-w e seu custo (cst)
 *
 */
typedef struct {
    vertex v, w;
    int cst;
} edge;

/**
 * A Função abaixo adiciona uma aresta v-w com custo (cst)
 */
static edge EDGE( vertex v, vertex w, int cst) {
   edge e;
   e.v = v, e.w = w;
   e.cst = cst;
   return e;
}

/**
 * Implementação do insertion sort
 *
 * Utilizado para colocar as arestas em ordem crescente de custo
 */
void ordernarVetorDeArestas (int quantidade, edge v[]) {
    int i, j, min;
    edge x;
    for (i = 0; i < quantidade - 1; i++) {
        min = i;
        for (j = i+1; j < quantidade; j++)
            if (v[j].cst < v[min].cst)
                min = j;
        x = v[i]; v[i] = v[min]; v[min] = x;
    }
}

/**
 * O algoritmo abaixo, recebe dois inteiros m e n, o vetor de arestas com custo
 * do grafo e armazena no vetor MST a Árvore Geradora Mínima do Grafo
 */
int Kruskal (int n, int m, edge vetorDeArestas[], edge MST[]) {
   int i, j, quantArestasMST = 0;
   /**
    * Cada componente tem um vértice chefe (a ideia de cores)
    */
   vertex chefe[n + 1];
   for (vertex v = 0; v < n + 1; ++v)
        chefe[v] = v;
   /**
    * Percorre o vetor de arestas
    */
   for (i = 0; i < m; i++) {
        /**
         * Verifica se os chefes são diferentes, se forem, significa que não são da mesma componente
         * e então a aresta pode ser adicionada que não ocosionará na criação de um ciclo
         *
         * A aresta é adicionada a AGM
         *
         * O chefe de uma componente deve se tornar o chefe da outra componente
         */
        if (chefe[vetorDeArestas[i].v] != chefe[vetorDeArestas[i].w]) {
            /**
             * A aresta é adicionada a AGM
             */
            MST[quantArestasMST++] = vetorDeArestas[i];
            /**
             * O chefe de uma componente deve se tornar o chefe da outra componente
             */
            int chefeASerMudado = chefe[vetorDeArestas[i].w];
            for (j = 0; j < n + 1; j++) {
                if (chefe[j] == chefeASerMudado) {
                    chefe[j] = chefe[vetorDeArestas[i].v];
                }
            }
        }
   }
   return quantArestasMST;
}

//Main
int main (int numargs, char *arg[]) {
    FILE *arquivo;
    /**
     * Em arg[1], está armazenado o nome do arquivo que contém o Grafo
     */
    arquivo = fopen (arg[1], "r");
    if (arquivo == NULL) {
        printf ("Erro na abertura do arquivo\n");
        exit (1);
    }

    /**
     * n = quantidade de vértices, m = quantidade de arestas
     */
    int n, m;
    fscanf (arquivo, "%d %d", &n, &m);
    int arquivoDoGrafo[m*3], posicaoAux = 0;

    /**
     * Leitura do arquivo que contém o Grafo
     *
     * Armazena todas as arestas e seu respectivos custo no vetor arquivoDoGrafo
     *
     * Para i comecando em 0. a Posicao i armazena v, i+1 armazena w e i+2 armazena o custo
     */
    while (! feof (arquivo) ) {
        fscanf (arquivo, "%d %d %d", &arquivoDoGrafo[posicaoAux], &arquivoDoGrafo[posicaoAux + 1], &arquivoDoGrafo[posicaoAux + 2]);
        posicaoAux += 3;
    }

    /**
     * Vetor que realmente armazena as arestas e seus respectivos custos
     */
    edge vetorDeArestas[m];
    posicaoAux = 0;
    for (int i = 0; i < m; i++) {
        vetorDeArestas[i].v = arquivoDoGrafo[posicaoAux++];
        vetorDeArestas[i].w = arquivoDoGrafo[posicaoAux++];
        vetorDeArestas[i].cst = arquivoDoGrafo[posicaoAux++];
    }

    /**
     * Coloca as arestas em ordem crescente de custo
     */
    ordernarVetorDeArestas (m, vetorDeArestas);

    /**
     * Vetor que armzena a AGM
     */
    edge MST[n - 1];

    /**
     * Algoritmo de Kruskal, armazena no vetor MST uma AGM do Grafo
     */
    int quantArestasDaMST = Kruskal (n, m, vetorDeArestas, MST);

    /**
     * Verifica se o Grafo continha uma AGM
     */
    if (quantArestasDaMST < n - 1) {
        printf ("\nNao existe AGM...\n");
        exit (1);
    }

    /**
     * Gera como saída as arestas que compoem a AGM
     */
    printf("\nArvore geradora de custo minimo: ");
    for (int i = 0; i < n-1; i++) {
        printf ("(%d, %d) ", MST[i].v, MST[i].w);
    }

    /**
     * Calcula o custo da AGM
     */
    int custo = 0;
    for (int i = 0; i < n-1; i++) {
        custo += MST[i].cst;
    }

    /**
     * Gera como saída, o custo da AGM
     */
    printf ("\n\nCusto: %d\n", custo);

    return 0;
}
