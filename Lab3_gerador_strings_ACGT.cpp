/*  Autor:  Armando Gouveia                   */
/*                                            */
/*  CES-11: Algoritmos e Estruturas de Dados  */
/*                                            */
/*  Programa compilado com Code::Blocks 17.12 */
/*
--------------------------------------------------
       GERADOR  DE  STRINGS  ALEATORIAS
--------------------------------------------------

Este programa gera um arquivo contendo strings aleatorias, uma por linha.
Quantidade de strings: pergunta ao usuario.
Tamanho das strings  : 50
Conteudo das strings : caracteres A,C,G,T
A primeira linha do arquivo contera' a quantidade de strings
Nome do arquivo: ACGT_aleatorias.txt
OBS.:
Uma "sequencia genetica" contem letras A,C,G,T
(adenina, citosina, guanina, timina)
que sao os quatro nucleotideos das cadeias de DNA.
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main( )
{
   char   s [51];    // string
   int    i,
          k,
          n,         // quantidade de strings
          cart;      // numero carteado
   FILE * sai;       // arquivo de saida

   // ler quantidade
   printf ("Quantos elementos? ");
   scanf  ("%d", & n);
   // abre arquivo e escreve quantidade
   sai = fopen ("entrada3.txt", "w");
   fprintf (sai, "%d\n", n);
   // inicializa o gerador de numeros aleatorios
   time_t t;
   srand((unsigned) time(&t));
   // gera  n  strings
   for(i=0; i<n; i++)
   {
      // para cada posicao na string
      for (k=0; k<50; k++)
      {
         // sorteia um numero entre 0 e 3
         cart = rand () % 4;
         // atribui um caractere `a string
         switch (cart)
         {
             case 0 : s[k] = 'A';  break;
             case 1 : s[k] = 'C';  break;
             case 2 : s[k] = 'G';  break;
             case 3 : s[k] = 'T';  break;
         }
      }
      // marca fim de string e escreve na saida
      s[50] = '\0';
      fprintf (sai, "%s\n", s);
   }
   fclose (sai);
   return 0;
}
