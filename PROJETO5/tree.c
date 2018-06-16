#include "tree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

 // void showTree(No *raiz);

void verificaValor(No *raiz,No *pai);
void procuraSucessor(No *Raiz);
int verificaBalanceamento(No *raiz);
int verificaCheia(No *raiz);
No *rotacionaEsquerda(No *raiz);
No *rotacionaDireita(No *raiz);
void setaFamiliaEsq(No *avo,No *pai,No *filho);
void setaFamiliaDir(No *avo,No *pai,No *filho);
void insereNo(No *raiz,No *aux);
int verificaBackbone(No *raiz);
////////////////////////////////////////////////////////////////////////////////
No *loadTreeFromFile(char arquivo[])
{
  FILE *arq;
  int value;
  No *aux;
  No *raiz = NULL;
  printf("arq %s\n",arquivo );
  if(arq = fopen(arquivo,"a+"),arq == NULL)
  {
    printf("erro ao abrir o arquivo!\n");
    exit(1);
  }
  if (!feof(arq))
  {
    fscanf(arq," %d ",&value);
  }
  if (!feof(arq))
  {
    if(raiz = (No*)malloc(sizeof(No)),raiz == NULL)
    {
      printf("alocação falhou!\n");
    }
    raiz->value = value;
    raiz->esq = NULL;
    raiz->dir = NULL;
  }
  while(!feof(arq))
  {
    fscanf(arq," %d ",&value);
    if(aux = (No*)malloc(sizeof(No)),aux == NULL)
    {
      printf("alocação falhou!\n");
    }
    aux->value = value;
    aux->dir = NULL;
    aux->esq = NULL;
    insereNo(raiz,aux);
  }
  fclose(arq);
  return raiz;
}
////////////////////////////////////////////////////////////////////////////////
void insereNo(No *raiz,No *aux)
{
  if (raiz->value < aux->value)
  {
    if (raiz->dir == NULL)
    {
      raiz->dir = aux;
    }
    else
    {
      insereNo(raiz->dir,aux);
    }
  }
  else
  {
    if (raiz->esq == NULL)
    {
      raiz->esq = aux;
    }
    else
    {
      insereNo(raiz->esq,aux);
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
void isFull(No *raiz)
 {
   if (raiz == NULL)
   {
     printf("Arvore esta vazia\n");
     return;
   }
   if(verificaCheia(raiz))
   {
     printf("Arvore é cheia\n");
   }
   else
   {
     printf("Arvore não é cheia\n");
   }
 }
////////////////////////////////////////////////////////////////////////////////
int verificaCheia(No *raiz)
 {
   if (raiz != NULL)
   {
     if ((raiz->esq == NULL && raiz->dir != NULL) || (raiz->esq != NULL && raiz->dir == NULL))
     {
       return 0;
     }
     else
     {
       return verificaCheia(raiz->esq)*verificaCheia(raiz->dir);
     }
   }
   return 1;
 }
////////////////////////////////////////////////////////////////////////////////
No *balanceTree(No *raiz)
 {
   if (raiz == NULL)
   {
     printf("arvore esta vazia\n");
     return raiz;
   }
   if(!verificaBalanceamento(raiz))
   {
     do
     {
       raiz = rotacionaDireita(raiz);
       printf("\n" );
       printPostOrder(raiz);
       printf("\n" );
     } while(!verificaBackbone(raiz));
     do
     {
       raiz = rotacionaEsquerda(raiz);
       printf("\n" );
       printPostOrder(raiz);
       printf("\n" );
       getchar();
     } while(!verificaBalanceamento(raiz));
   }
   else
   {
     printf("arvore esta balanceada\n");
   }
   return raiz;
 }
////////////////////////////////////////////////////////////////////////////////
int verificaBackbone(No *raiz)
{
   if(raiz != NULL)
   {
     if (raiz->esq != NULL)
     {
       return 0;
     }
     else
     {
       return verificaBackbone(raiz->esq)*verificaBackbone(raiz->dir);
     }
   }
   return 1;
}
////////////////////////////////////////////////////////////////////////////////
No *rotacionaEsquerda(No *raiz)
{
   No *filho = raiz;
   No *pai=filho,*avo;
   if (filho->esq != NULL)
   {
     filho = pai->dir;
     if (filho != NULL)
     {
       raiz = filho;
     }
   }
   else
   {
     if (pai->esq != NULL || pai->dir != NULL)
     {
       filho = pai->dir;
       if (filho != NULL)
       {
         raiz = filho;
       }
     }
     else
     {
       avo = filho;
       if (avo->dir != NULL)
       {
         pai = avo->dir;
         if (pai->dir != NULL)
         {
           filho = pai->dir;
         }
         else
         {
           filho = NULL;
         }
       }
       else
       {
         filho = NULL;
       }
     }
   }
   if (filho != NULL)
   {
     if (filho == raiz)
     {
       pai->dir = filho->esq;
       filho->esq = pai;
     }
     else
     {
       avo->dir = filho;
       pai->dir = filho->esq;
       filho->esq = pai;
     }
   }
 return raiz;
}
////////////////////////////////////////////////////////////////////////////////
No *rotacionaDireita(No *raiz)
{
   No *filho = raiz;
   No *pai,*avo;
   do
   {
     if (filho->esq != NULL)
     {
       avo = filho;
       filho = avo->esq;
       if(filho->esq != NULL)
       {
         pai = avo->esq;
         filho = pai->esq;
       }
       while (filho->esq != NULL)
       {
         avo = pai;
         pai = filho;
         filho = pai->esq;
       }
     }
     else
     {
       do
       {
         avo = filho;
         filho = avo->dir;
       } while(filho != NULL && filho->esq == NULL);
       if (filho != NULL)
       {
         pai = filho;
         filho = pai->esq;
         while (filho->esq != NULL)
         {
           avo = pai;
           pai = filho;
           filho = pai->esq;
         }
       }
     }
     if (filho != NULL)
     {
       if (avo->esq == filho)
       {
         avo->esq = filho->dir;
         filho->dir = avo;
         puts("trocou");
         raiz = filho;
       }
       else
       {
         if (avo->dir == pai)
         {
           avo->dir = filho;
         }
         else
         {
           avo->esq = filho;
         }
         pai->esq = filho->dir;
         filho->dir = pai;
       }
     }
   }while (filho != NULL);
   return raiz;
 }
////////////////////////////////////////////////////////////////////////////////
void removeValue(No *raiz,int value)
{
  No *pai;
  while (raiz == NULL)
  {
    if (raiz->value != value)
    {
      break;
    }
    pai = raiz;
    if (raiz->value < value)
    {
      raiz = raiz->dir;
    }
    else
    {
      raiz = raiz->esq;
    }
  }
  if (raiz == NULL)
  {
    printf("Valor não encontrado\n");
  }
  else
  {
    verificaValor(raiz,pai);
  }
}
////////////////////////////////////////////////////////////////////////////////
void procuraSucessor(No *raiz)
{
    No *sucessor,*pai;
    sucessor = raiz->dir;
    while (sucessor->esq != NULL)
    {
      pai = sucessor;
      sucessor = sucessor->esq;
    }
    raiz->value = sucessor->value;
    verificaValor(sucessor,pai);
}
////////////////////////////////////////////////////////////////////////////////
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
  No *pai=NULL,*irmao=NULL;
  while (raiz != NULL)
  {
    if (raiz->value == value)
    {
      break;
    }
    nivel++;
    pai = raiz;
    if (raiz->value < value)
    {
      irmao = raiz->esq;
      raiz = pai->dir;
    }
    else
    {
      irmao = raiz->dir;
      raiz = pai->esq;
    }
  }
  if (raiz == NULL)
  {
    printf("Valor não encontrado\n");
  }
  else
  {
    printf("Nivel : %d\n",nivel);
    if (pai != NULL)
    {
      printf("Pai : %d\n",pai->value);
    }
    if (irmao != NULL)
    {
      printf("Irmão : %d\n",irmao->value);
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
int verificaBalanceamento(No *raiz)
{
  int dif;
  if (raiz != NULL)
  {
    dif = getHeight(raiz->esq) - getHeight(raiz->dir);
    printf("raiz %d %d %d\n",raiz->value,getHeight(raiz->esq) , getHeight(raiz->dir));
    if (dif < -1 || dif > 1)
    {
      return 0;
    }
    else
    {
      return verificaBalanceamento(raiz->esq)*verificaBalanceamento(raiz->dir);
    }
  }
  return 1;
}
////////////////////////////////////////////////////////////////////////////////
void verificaValor(No *raiz,No *pai)
{
  if (raiz->dir != NULL || raiz->esq != NULL)
  {
    if (raiz->dir != NULL && raiz->esq != NULL)
    {
      procuraSucessor(raiz);
      free(raiz);
    }
    else
    {
      if (raiz->dir == NULL)
      {
        if (pai->dir == raiz)
        {
          pai->dir = raiz->esq;
          free(raiz);
        }
        else
        {
          pai->esq = raiz->esq;
          free(raiz);
        }
      }
      else
      {
        if (pai->dir == raiz)
        {
          pai->dir = raiz->dir;
          free(raiz);
        }
        else
        {
          pai->esq = raiz->dir;
          free(raiz);
        }
      }
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
void showTree(No *raiz){
  int height = getHeight(raiz);
  // int matriz[2*height-1][pow(2,height)-1];
  int **matrixTree = (int **) calloc (2*height-1,sizeof(int*));
  if(matrixTree == NULL){
     puts("Alocação Falhou!");
     exit(1);
  }
  for(int i = 0; i < (2*height-1); i++){
     *(matrixTree+i) = (int*)calloc(pow(2,height)-1,sizeof(int));
     if(*(matrixTree+i) == NULL){
        puts("Alocação Falhou!");
        exit(1);
     }
 }



   for(int i=0; i < 2*height-1; i++)
      free(*(matrixTree+i));

   free(matrixTree);

}
