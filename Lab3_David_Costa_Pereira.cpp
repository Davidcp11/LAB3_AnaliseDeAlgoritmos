#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

///Definindo o vetor de strings
#define MAX 52
typedef char tipelemento;
typedef tipelemento vetor [MAX];
///Contador e tamanho das strings
unsigned long contador;
int n;

///Funcao que contabiliza as comparacoes entre strings
int compara (const char * a, const char * b)
{
    contador ++;
    return strcmp (a, b);
}
///--------------------------------------------------
/// BUBBLE SORT
///--------------------------------------------------
void Bubble_sort(vetor *V, int j)
{
    vetor aux;
    for(int k=0; k<j; k++)
        ///Percorrer o vetor n vezes
        for(int i=0; i<j-1; i++)
        {
            ///Verificar se esta em ordem alfabetica, se nao estiver faz a troca
            if(compara(V[i],V[i+1])>0)
            {
                strcpy(aux, V[i]);
                strcpy(V[i], V[i + 1]);
                strcpy(V[i + 1], aux);
            }
        }
}
///--------------------------------------------------
///    MERGE
///--------------------------------------------------
/*
Dado um vetor V e dadas duas posicoes ini e fim.
A metade da esquerda desse trecho ja' esta' ordenada e
a metade da direita  desse trecho ja' esta' ordenada.
Fazer intercalacao (merge) e obter V ordenado.
*/

void Merge (vetor *V, int ini, int fim)
{
    static vetor *T=(vetor *)(malloc(n*sizeof(vetor)));/// temporario;
    int med,
        i,     /// percorre T
        j,     /// percorre lado esquerdo de V
        k;     /// percorre lado direito  de V

    med = (ini+fim)/2; ///mesmo arredondamento feito ao chamar MergeSort
    j = ini;
    k = med+1;
    i = ini;
    ///percorrer selecionando os menores
    while (j <= med && k <= fim)
    {
        if (compara(V[j],V[k])<=0)
        {
            strcpy(T[i],V[j]);
            j++;
        }
        else
        {
            strcpy(T[i],V[k]);
            k++;
        }
        i++;
    }
    ///se sobrou algo `a esquerda, copiar para T
    while(j <= med)
    {
        strcpy(T[i],V[j]);
        i++;
        j++;
    }
    ///se sobrou algo `a direita, copiar para T
    while(k<=fim)
    {
        strcpy(T[i],V[k]);
        i++;
        k++;
    }
    /// V recebe T
    for(i=ini; i<=fim; i++)
        strcpy(V[i],T[i]);
}
///--------------------------------------------------
///    MERGE SORT
///--------------------------------------------------
void MergeSort (vetor *V, int ini, int fim)
{
    int med;
    if (ini < fim)
    {
        med = (ini+fim)/2;          // dividir ao meio
        MergeSort (V, ini,   med);  // ordenar lado esquerdo
        MergeSort (V, med+1, fim);  // ordenar lado direito
        Merge     (V, ini,   fim);  // mesclar as duas metades
    }
}
///--------------------------------------------------
///    PARTITION
///--------------------------------------------------
/*
Dado um vetor V com elementos em qualquer ordem,
escolher um elemento para ser pivo^
e então dividir os elementos de V em duas partes:
  `a esquerda: menores que o pivo
  `a direita:  maiores ou iguais ao pivo
*/
int Partition (vetor *V, int ini, int fim)
{
    char pivo[55], aux[55];
    int esq, dir;
    strcpy(pivo, V[ini]);    /// neste exemplo, o pivo é o primeiro da esquerda
    esq  = ini + 1;
    dir  = fim;
    do
    {
        /// percorrer da esquerda para a direita. encontrar alguem >= pivo
        while (esq < fim && compara(V[esq],pivo)<0)
            esq++;
        /// percorrer da direita para a esquerda. encontrar alguem < pivo
        while (ini < dir && compara(pivo,V[dir])<=0)
            dir--;
        /// se achou um `a esquerda e outro `a direita
        if(esq < dir)
        {
            //// permutar
            strcpy(aux,V[esq]);
            strcpy(V[esq],V[dir]);
            strcpy(V[dir],aux);
        }
        /// caso contrario, terminara´ a repeticao
    }
    while (esq < dir);
    /// trocar o pivo com o elemento que "divide" os subvetores
    strcpy(V[ini],V[dir]);
    strcpy(V[dir],pivo);
    /// retornar a posição da "divisa"
    return dir;
}
void QuickSort (vetor *V, int ini, int fim)
{
    int p; //posição do pivo
    if (ini < fim)
    {
        p = Partition (V, ini, fim);
        QuickSort     (V, ini, p-1);
        QuickSort     (V, p+1, fim);
    }
}
///------------------------------------------------
///     MAIN
///------------------------------------------------
int main ()
{
    FILE *entrada, *sai_merge, *sai_quick, *sai_bubble;
    ///Arquivos de entrada e saida
    entrada= fopen("entrada3.txt","r");
    sai_merge= fopen("Lab3_David_Costa_Pereira_merge.txt","w");
    sai_quick= fopen("Lab3_David_Costa_Pereira_quick.txt","w");
    sai_bubble= fopen("Lab3_David_Costa_Pereira_bubble.txt","w");
    ///Para marcar o tempo de execucao dos algoritmos
    clock_t inicio,
            fim;
    float   delta_t;
    ///Tamanho da entrada
    fscanf(entrada,"%d ", &n);
    ///Alocando o vetor leitura e V (que sera usado nas funcoes)
    vetor *leitura=(vetor *)(malloc(n*sizeof(vetor)));
    vetor *V=(vetor *)(malloc(n*sizeof(vetor)));
    ///Lendo a entrada
    for (int i = 0; i < n; i++)
    {
        fgets(leitura[i], 52, entrada);
        if (i != n - 1)
            leitura[i][strlen(leitura[i]) - 1] = '\0';
    }
    ///Copiando para V
    for (int i = 0; i < n; i++)
    {
        strcpy(V[i],leitura[i]);
    }
    ///******************* BUBBLE SORT ************************
    contador=0;
    fprintf(sai_bubble,"Algoritmo: Bubble-Sort\n\n");
    fprintf(sai_bubble,"Tamanho da entrada: %d\n", n);
    ///Tempo de execução
    inicio = clock();
    Bubble_sort(V,n);
    fim    = clock();
    delta_t = (fim - inicio) / (float) CLOCKS_PER_SEC;
    fprintf(sai_bubble,"Comparacoes feitas: %lu\n", contador);
    fprintf(sai_bubble,"Tempo de execucao : %.3f\n\n", delta_t);
    for(int i=0; i< strlen(V[0]); i++)
        fprintf(sai_bubble,"-");
    fprintf(sai_bubble,"\n");
    for(int i=0; i<n; i++)
        fprintf(sai_bubble,"%s\n", V[i]);
    ///-------------------------------------------------------------
    ///Copiando para V, pois V ja esta ordenado
    for (int i = 0; i < n; i++)
    {
        strcpy(V[i],leitura[i]);
    }
    ///******************** MERGE SORT ***********************
    contador=0;
    fprintf(sai_merge,"Algoritmo: Merge-Sort\n\n");
    fprintf(sai_merge,"Tamanho da entrada: %d\n", n);
    inicio = clock();
    MergeSort(V,0,n-1);
    fim    = clock();
    delta_t = (fim - inicio) / (float) CLOCKS_PER_SEC;
    fprintf(sai_merge,"Comparacoes feitas: %lu\n", contador);
    fprintf(sai_merge,"Tempo de execucao : %.3f\n\n", delta_t);
    for(int i=0; i< strlen(V[0]); i++)
        fprintf(sai_merge,"-");
    fprintf(sai_merge,"\n");
    for(int i=0; i<n; i++)
        fprintf(sai_merge,"%s\n", V[i]);
    ///----------------------------------------------------------------------------
    ///Copiando para V, pois V ja esta ordenado
    for (int i = 0; i < n; i++)
    {
        strcpy(V[i],leitura[i]);
    }
    ///************************** QUICK SORT ***************************
    contador=0;
    fprintf(sai_quick,"Algoritmo: Quick-Sort\n\n");
    fprintf(sai_quick,"Tamanho da entrada: %d\n", n);
    inicio = clock();
    QuickSort(V,0,n-1);
    fim    = clock();
    delta_t = (fim - inicio) / (float) CLOCKS_PER_SEC;
    fprintf(sai_quick,"Comparacoes feitas: %lu\n", contador);
    fprintf(sai_quick,"Tempo de execucao : %.3f\n\n", delta_t);
    for(int i=0; i< strlen(V[0]); i++)
        fprintf(sai_quick,"-");
    fprintf(sai_quick,"\n");
    for(int i=0; i<n; i++)
        fprintf(sai_quick,"%s\n", V[i]);
    ///---------------------------------------------------
    ///Fechando arquivos de entrada e saida e dando free nos vetores alocados
    free(V);
    free(leitura);
    fclose(entrada);
    fclose(sai_bubble);
    fclose(sai_merge);
    fclose(sai_quick);
    return 0;

}
