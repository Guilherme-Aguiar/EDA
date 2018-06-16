#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tree.c"

void liberaArvore(No *raiz);
No *selecionaArquivo();
char menu();
void limpaBuff();
void continuar();

int main()
{
  char select;
  No *raiz;
  int valor;
  raiz = selecionaArquivo();
  do
  {
    select = menu();
    switch (select)
    {
      case '1':
        system("clear");
        //showTree(raiz);
        break;
      case '2':
        system("clear");
        isFull(raiz);
        break;
      case '3':
        system("clear");
        printf("Digite o valor que deseja procurar na arvore: \n");
        scanf("%d",&valor);
        getchar();
        printf("%d\n",valor);
        searchValue(raiz,valor);
        break;
      case '4':
        system("clear");
        printf("altura da arvore: %d\n",getHeight(raiz));
        break;
      case '5':
        system("clear");
        printf("Digite o valor que deseja remover da arvore: \n");
        scanf("%d\n",&valor);
        getchar();
        removeValue(raiz,valor);
        break;
      case '6':
        do
        {
          system("clear");
          printf("Escolha o algoritmo que deseja utlizar: \n\n");
          printf("1 - InOrder: \n");
          printf("2 - PreOrder: \n");
          printf("3 - PostOrder: \n");
          scanf("%c",&select );
          limpaBuff();
        } while(select < '1' || select > '3');
        switch (select)
        {
          case '1':
            system("clear");
            printInOrder(raiz);
            break;
          case '2':
            system("clear");
            printPreOrder(raiz);
            break;
          case '3':
            system("clear");
            printPostOrder(raiz);
            break;
        }
        break;
      case '7':
        system("clear");
        raiz = balanceTree(raiz);
        //showTree(raiz);
        break;
      case '0':
        liberaArvore(raiz);
    }
    if (select != '0')
    {
      continuar();
    }
  } while(select != '0');
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
No *selecionaArquivo()
{
  char arquivo;
  char nomeArquivo[50];
  No *raiz;
  do
  {
    system("clear");
    printf("\n");
    printf("Selecione um dos arquivos abaixo, ou digite 0 para utilizar um arquivo pessoal.\n\n");
    printf("\t1 - bst1.txt\n\n");
    printf("\t2 - bst2.txt\n\n");
    printf("\t3 - bst3.txt\n\n");
    printf("\t4 - bst4.txt\n\n");
    printf("\t5 - bst5.txt\n\n");
    printf("\t6 - bst6.txt\n\n");
    printf("\t0 - Utilizar arquivo pessoal\n\n");
    scanf("%c",&arquivo);
    limpaBuff();
  } while(arquivo < '0' || arquivo > '6');
  if (arquivo == '0')
  {
    printf("Digite o nome do seu arquivo (não é necessário digitar o tipo do arquivo): \n");
    scanf("%s",nomeArquivo);
    strcat(nomeArquivo,".txt");
    raiz = loadTreeFromFile(nomeArquivo);
  }
  else
  {
    strcat(nomeArquivo,"BSTs/bst");
    nomeArquivo[strlen(nomeArquivo)] = arquivo;
    //strcat(nomeArquivo,arquivo);
    strcat(nomeArquivo,".txt");
    raiz = loadTreeFromFile(nomeArquivo);
  }
  return raiz;
}
////////////////////////////////////////////////////////////////////////////////
char menu()
{
  char select;
  do
  {
    system("clear");
    printf("\n");
    printf("\t1 - Mostrar arvore\n\n");
    printf("\t2 - Verificar se a arvore é cheia(ok)\n\n");
    printf("\t3 - Procurar valor na arvore(ok)\n\n");
    printf("\t4 - Verificar altura da arvore(ok)\n\n");
    printf("\t5 - Remover valor da arvore\n\n");
    printf("\t6 - Mostrar valores da arvore usando algoritmos(ok)\n\n");
    printf("\t7 - Balancear arvore\n\n");
    printf("\t0 - Sair\n\n");
    scanf("%c",&select);
    limpaBuff();
  } while(select < '0' || select > '7');
}
////////////////////////////////////////////////////////////////////////////////
void liberaArvore(No *raiz)
{
  if(raiz != NULL)
  {
    liberaArvore(raiz->esq);
    liberaArvore(raiz->dir);
    free(raiz);
  }
}
////////////////////////////////////////////////////////////////////////////////
void limpaBuff()
{
  char c;
  do
  {
    c = getchar();
  } while(c != '\n');
}
////////////////////////////////////////////////////////////////////////////////
void continuar()
{
  char c;
  printf("\nAperte enter para continuar\n");
  do
  {
    c = getchar();
  } while(c != '\n');
}
