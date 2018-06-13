#ifndef TREE_H
#define TREE_H

typedef struct no {
  int value;
  struct no* esq;
  struct no* dir;
} No;

No *loadTreeFromFile(char arquivo[]);
void showTree(No *raiz);
void isFull(No *raiz);
void searchValue(No *raiz,int value);
int getHeight(No *raiz);
void removeValue(No *raiz,int value);
void printInOrder(No *raiz);
void printPreOrder(No *raiz);
void printPostOrder(No *raiz);
No *balanceTree(No *raiz);

#endif
