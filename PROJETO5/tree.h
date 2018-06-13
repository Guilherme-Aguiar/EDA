#ifndef TREE_H   // guardas de cabeçalho, impedem inclusões cíclicas
#define TREE_H

// extern int baz;    // declaração de uma variável global

typedef struct no {
  int value;
  struct no* esq;
  struct no* dir;
} No;         // como é global, valor inicial é zero.

No *loadTreeFromFile(char arquivo[]);
void showTree(No *raiz);
int isFull(No *raiz);
void searchValue(No *raiz,int value);
int getHeight(No *raiz);
No *removeValue(No *raiz,int value);
void printInOrder(No *raiz);
void printPreOrder(No *raiz);
void printPostOrder(No *raiz);
No *balanceTree(No *raiz);

#endif
