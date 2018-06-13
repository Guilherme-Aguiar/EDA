#include "tree.h"
 #include <stdio.h>

 // No *loadTreeFromFile(char arquivo[]);
 // void showTree(No *raiz);
 // int isFull(No *raiz);
 // No *removeValue(No *raiz,int value);
 // No *balanceTree(No *raiz);

int getHeight(No *raiz)
{
  if (raiz == NULL)
  {
    return 0;
  }
  if (getHeight(raiz->esq) > getHeight(raiz->dir))
  {
    return 1 + getHeight(raiz->esq);
  }
  else
  {
    return 1 + getHeight(raiz->dir);
  }
}
////////////////////////////////////////////////////////////////////////////////
 void printPostOrder(No *raiz)
 {
   if (raiz != NULL)
   {
     printPostOrder(raiz->esq);
     printPostOrder(raiz->dir);
     printf("%d ",raiz->value);
   }
 }
 ////////////////////////////////////////////////////////////////////////////////

 void printPreOrder(No *raiz)
 {
   if (raiz != NULL)
   {
     printf("%d ",raiz->value);
     printPreOrder(raiz->esq);
     printPreOrder(raiz->dir);
   }
 }
 ////////////////////////////////////////////////////////////////////////////////

 void printInOrder(No *raiz)
 {
   if (raiz != NULL)
   {
     printInOrder(raiz->esq);
     printf("%d ",raiz->value);
     printInOrder(raiz->dir);
   }
 }
////////////////////////////////////////////////////////////////////////////////
void searchValue(No *raiz,int value)
{
  int nivel = 0;
  No *pai,*irmao;
  while (raiz->value != value || raiz == NULL)
  {
    nivel++;
    pai = raiz;
    if (raiz->value < value)
    {
      irmao = raiz->esq;
      raiz = raiz->dir;
    }
    else
    {
      irmao = raiz->dir;
      raiz = raiz->esq;
    }
  }
  if (raiz == NULL)
  {
    printf("Valor não encontrado\n");
  }
  else
  {
    printf("Nivel : %d\n",nivel);
    printf("Pai : %d\n",pai->value);
    if (irmao != NULL)
    {
      printf("Irmão : %d\n",irmao->value);
    }
  }
}
