#include "tree.h"
 #include <stdio.h>

 // No *loadTreeFromFile(char arquivo[]);
 // void showTree(No *raiz);
 // int isFull(No *raiz);
 // void searchValue(No *raiz,int value);
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
//
// int searchValue(No *raiz,int value)
// {
//   if(raiz != NULL)
//   {
//     if (raiz->value == value)
//     {
//       printf("Nível : 1\n");
//     }
//     else
//     {
//       if (raiz->value < value)
//       {
//         if (raiz->esq->value == value)
//         {
//           printf("Pai : %d\n",raiz->value);
//           if (raiz->dir != NULL)
//           {
//             printf("Irmão : %d\n",raiz->dir->value);
//           }
//           return 1;
//         }
//         else
//         {
//           return 1 + searchValue(raiz->esq,value);
//         }
//       }
//       else
//       {
//         if (raiz->dir->value == value)
//         {
//           printf("Pai : %d\n",raiz->value);
//           if (raiz->esq != NULL)
//           {
//             printf("Irmão : %d\n",raiz->esq->value);
//           }
//           return 1;
//         }
//         else
//         {
//           return 1 + searchValue(raiz->dir,value);
//         }
//       }
//     }
//   }
//   else
//   {
//     printf("Valor não encontrado\n");
//     return
//   }
//
// }
////////////////////////////////////////////////////////////////////////////////
