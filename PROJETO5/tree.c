#include "tree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void insereNo(No *raiz,No *aux);

int verificaCheia(No *raiz);

int verificaBalanceamento(No *raiz);
No *rotaciona(No *raiz,No *pai,No *raizReal);
No *rodaEsq(No *raiz,No *pai,No *raizReal);
No *rodaDir(No *raiz,No *pai,No *raizReal);

No *removeRaiz(No *raiz);
No *verificaValor(No *raiz,No *pai);
No *procuraSucessor(No *Raiz);

void encheMatriz(int **matrixTree,char **matrixTreeChar,No *raiz,int altura,int nivel,int coluna);
void mostraMatriz(int **matrixTree,char **matrixTreeChar,int height,int *retira);
void retiraEspacos(char **matrixTreeChar,int height,int *retira);
////////////////////////////////////////////////////////////////////////////////
No *loadTreeFromFile(char arquivo[])
{
  FILE *arq;
  int value;
  No *aux;
  No *raiz = NULL;
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
////////////////////////////////////////////////////////////////////////////////
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
 ////////////////////////////////////////////////////////////////////////////////
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
       raiz = rotaciona(raiz,NULL,raiz);
     } while(!verificaBalanceamento(raiz));
   }
   else
   {
     printf("arvore esta balanceada\n");
   }
   return raiz;
 }
////////////////////////////////////////////////////////////////////////////////
No *rodaDir(No *raiz,No *pai,No *raizReal)
{
  No *aux = raiz->dir;
  if (pai != NULL)
  {
    if (pai->esq == raiz)
    {
      pai->esq = aux;
    }
    else
    {
      pai->dir = aux;
    }
    raiz->dir = aux->esq;
    aux->esq = raiz;
  }
  else
  {
    raiz->dir = aux->esq;
    aux->esq = raiz;
    raizReal = aux;
  }

  return raizReal;
}
////////////////////////////////////////////////////////////////////////////////
No *rodaEsq(No *raiz,No *pai,No *raizReal)
{
  No *aux = raiz->esq;
  if (pai != NULL)
  {
    if (pai->esq == raiz)
    {
      pai->esq = aux;
    }
    else
    {
      pai->dir = aux;
    }
    raiz->esq = aux->dir;
    aux->dir = raiz;
  }
  else
  {
    raiz->esq = aux->dir;
    aux->dir = raiz;
    raizReal = aux;
  }
  return raizReal;
}
////////////////////////////////////////////////////////////////////////////////
No *rotaciona(No *raiz,No *pai,No *raizReal)
{
  if (raiz != NULL)
  {
    if (!verificaBalanceamento(raiz))
    {
      raizReal = rotaciona(raiz->esq,raiz,raizReal);
      if (verificaBalanceamento(raiz))
      {
        return raizReal;
      }
      raizReal = rotaciona(raiz->dir,raiz,raizReal);
      if (verificaBalanceamento(raiz))
      {
        return raizReal;
      }
      if (getHeight(raiz->esq) > getHeight(raiz->dir))
      {
        raizReal = rodaEsq(raiz,pai,raizReal);
      }
      else
      {
        raizReal = rodaDir(raiz,pai,raizReal);
      }
    }
  }
  return raizReal;
}
 ////////////////////////////////////////////////////////////////////////////////
 int verificaBalanceamento(No *raiz)
 {
   int dif;
   if (raiz != NULL)
   {
     dif = getHeight(raiz->esq) - getHeight(raiz->dir);
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
 ////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
No *removeValue(No *raiz,int value)
{
  No *pai=NULL,*aux=raiz;
  while (aux != NULL)
  {
    if (aux->value == value)
    {
      break;
    }
    pai = aux;
    if (aux->value < value)
    {
      aux = pai->dir;
    }
    else
    {
      aux = pai->esq;
    }
  }
  if (aux == NULL)
  {
    printf("Valor não encontrado\n");
  }
  else
  {
    if (pai == NULL)
    {
      raiz = removeRaiz(raiz);
    }
    else
    {
      aux = verificaValor(aux,pai);
      free(aux);
    }
    printf("\nValor removido\n\n");
    showTree(raiz);
  }
  return raiz;
}
////////////////////////////////////////////////////////////////////////////////
No *removeRaiz(No *raiz)
{
  No *aux;
  if (raiz->dir != NULL || raiz->esq != NULL)
  {
    if (raiz->dir != NULL && raiz->esq != NULL)
    {
      aux = procuraSucessor(raiz);
      free(aux);
      return raiz;
    }
    else
    {
      if (raiz->dir != NULL)
      {
        aux = raiz->dir;
        free(raiz);
        return aux;
      }
      else
      {
        aux = raiz->esq;
        free(raiz);
        return aux;
      }
    }
  }
  else
  {
    free(raiz);
    return NULL;
  }
}
////////////////////////////////////////////////////////////////////////////////
No *verificaValor(No *raiz,No *pai)
{
  if (raiz->dir != NULL || raiz->esq != NULL)
  {
    if (raiz->dir != NULL && raiz->esq != NULL)
    {
      return procuraSucessor(raiz);
    }
    else
    {
      if (raiz->dir != NULL)
      {
        if (pai->dir == raiz)
        {
          pai->dir = raiz->dir;
          return raiz;
        }
        else
        {
          pai->esq = raiz->dir;
          return raiz;
        }
      }
      else
      {
        if (pai->dir == raiz)
        {
          pai->dir = raiz->esq;
          return raiz;
        }
        else
        {
          pai->esq = raiz->esq;
          return raiz;
        }
      }
    }
  }
  else
  {
    if (pai->value < raiz->value)
    {
      pai->dir = NULL;
    }
    else
    {
      pai->esq = NULL;
    }
    return raiz;
  }
}
////////////////////////////////////////////////////////////////////////////////
No *procuraSucessor(No *raiz)
{
    No *sucessor,*pai,*aux;
    int value;
    sucessor = raiz->dir;
    pai = raiz;
    while (sucessor->esq != NULL)
    {
      pai = sucessor;
      sucessor = pai->esq;
    }
    value = sucessor->value;
    aux = verificaValor(sucessor,pai);
    raiz->value = value;
    return aux;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void searchValue(No *raiz,int value)
{
  int nivel = 1;
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
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void showTree(No *raiz)
{
  if (raiz == NULL)
  {
    return;
  }
  int height = getHeight(raiz);
  int *retira;
  retira = (int*)calloc((int)pow(2,height)-1,sizeof(int));
  if(retira == NULL)
  {
     puts("Alocação Falhou!");
     exit(1);
  }
  int **matrixTree = (int **) calloc (height,sizeof(int*));
  if(matrixTree == NULL)
  {
     puts("Alocação Falhou!");
     exit(1);
  }
  for(int i = 0; i < (height); i++)
  {
     *(matrixTree+i) = (int*)calloc(pow(2,height)-1,sizeof(int));
     if(*(matrixTree+i) == NULL)
     {
        puts("Alocação Falhou!");
        exit(1);
     }
  }

  char **matrixTreeChar = (char **) calloc (height-1,sizeof(char*));
  if(matrixTreeChar == NULL)
  {
     puts("Alocação Falhou!");
     exit(1);
  }
  for(int i = 0; i < (height-1); i++)
  {
     *(matrixTreeChar+i) = (char*)calloc(pow(2,height)-1,sizeof(char));
     if(*(matrixTreeChar+i) == NULL)
     {
        puts("Alocação Falhou!");
        exit(1);
     }
  }

  for (int i = 0; i < height-1; i++)
  {
    for (int j = 0; j < pow(2,height)-1; j++)
    {
      matrixTreeChar[i][j] = ' ';
    }
  }

  encheMatriz(matrixTree,matrixTreeChar,raiz,height,0,(pow(2,height)-1)/2);

  retiraEspacos(matrixTreeChar,height,retira);

  mostraMatriz(matrixTree,matrixTreeChar,height,retira);


   for(int i=0; i < height; i++)
      free(*(matrixTree+i));

   free(matrixTree);

   for(int i=0; i < height-1; i++)
      free(*(matrixTreeChar+i));

   free(matrixTreeChar);

}
////////////////////////////////////////////////////////////////////////////////
void retiraEspacos(char **matrixTreeChar,int height,int *retira)
{
  for (int j = 0; j < pow(2,height)-1; j++)
  {
    for (int i = 0; i < height-1; i++)
    {
      if (matrixTreeChar[i][j] == '/' || matrixTreeChar[i][j] == '\\')
      {
        retira[j] = 1;
      }
    }
  }
  int aux = (pow(2,height)-1)/2;
  retira[aux] = 1;
}
////////////////////////////////////////////////////////////////////////////////
void encheMatriz(int **matrixTree,char **matrixTreeChar,No *raiz,int altura,int linha,int coluna)
{
  int aux = pow(2,altura-2-linha);
  *(*(matrixTree+linha)+coluna) = raiz->value;
  if (raiz->esq != NULL)
  {
    *(*(matrixTreeChar+linha)+coluna-aux) = '/';
    encheMatriz(matrixTree,matrixTreeChar,raiz->esq,altura,linha+1,coluna-aux);

  }
  if (raiz->dir != NULL)
  {
    *(*(matrixTreeChar+linha)+coluna+aux) = '\\';
    encheMatriz(matrixTree,matrixTreeChar,raiz->dir,altura,linha+1,coluna+aux);
  }
}
////////////////////////////////////////////////////////////////////////////////
void mostraMatriz(int **matrixTree,char **matrixTreeChar,int height,int *retira)
{
  printf("|+| ");
  for (int j = 0; j < pow(2,height)-1 ; j++)
  {
    if (retira[j])
    {
      if (j != (int)(pow(2,height)-1)/2)
      {
        printf(" ");
      }
      else
      {
        printf("%d",matrixTree[0][j]);
      }
    }
  }
  printf(" |+|\n");
  for (int i = 0; i < height-1; i++)
  {
    printf("|+| ");
    for (int j = 0; (j < pow(2,height)-1) ; j++)
    {
      if (retira[j])
      {
        if (matrixTreeChar[i][j] == '/' || matrixTreeChar[i][j] == '\\')
        {
          for(int aux = matrixTree[i+1][j]/10; aux != 0; aux = aux/10)
          {
            printf(" ");
          }
          printf("%c",matrixTreeChar[i][j]);
        }
        else
        {
          printf(" ");
        }
      }
    }
    printf(" |+|\n");
    printf("|+| ");
    for (int j = 0; j < pow(2,height)-1 ; j++)
    {
      if (retira[j])
      {
        if (matrixTreeChar[i][j] == '/' || matrixTreeChar[i][j] == '\\')
        {
          printf("%d",matrixTree[i+1][j]);
        }
        else
        {
          printf("%c",matrixTreeChar[i][j]);
        }
      }
    }
    printf(" |+|\n");
  }
}
