#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contato{
  char nome[101];
  char celular[11];
  char endereco[101];
  unsigned int cep;
  char nascimento[11];
  struct contato *prox;
  struct contato *ant;

} Contato;

void mostraMenu();
void inserirRegistro();
void removerRegistros();
void visualizarRegistroNome();
void visualizarTodosRegistros();
void salvaLista(Contato *lista);
Contato *carregaArquivoNaLista();

int main() {

  char select;
  FILE *arq;
  Contato *lista;

  if(lista = (Contato*)malloc(sizeof(Contato)),lista == NULL){
    printf("alocação falhou!\n");
  }

  lista = carregaArquivoNaLista();

  do {
    mostraMenu();
    scanf("%c",&select);

    switch (select) {
      case '1':
        inserirRegistro();
        break;
      case '2':
        removerRegistros();
        break;
      case '3':
        visualizarRegistroNome();
        break;
      case '4':
        visualizarTodosRegistros();
        break;
      case '0':
      if(arq = fopen("contatos.txt","w"),arq == NULL){
        printf("erro ao abrir o arquivo!\n");
        exit(1);
      }
        salvaLista(lista);
        fclose(arq);
    }
    system("clear");
  } while(select != '0');

  return 0;
}
////////////////////////////////////////////////////////////////////////////////
void mostraMenu(){
  printf("\n");
  printf("\t1 - Inserir novo registro\n\n");
  printf("\t2 - Remover registros que possuem o nome indicado\n\n");
  printf("\t3 - Visualizar registro a partir do nome indicado\n\n");
  printf("\t4 - Visualizar todos os registros em ordem alfabética de nomes\n\n");
  printf("\t0 - Sair\n\n");

}
////////////////////////////////////////////////////////////////////////////////
void inserirRegistro(){
}
////////////////////////////////////////////////////////////////////////////////
void removerRegistros(){
}
////////////////////////////////////////////////////////////////////////////////
void visualizarRegistroNome(){
}
////////////////////////////////////////////////////////////////////////////////
void visualizarTodosRegistros(){
}
////////////////////////////////////////////////////////////////////////////////
void abreArquivo(FILE *arq){
  if(arq = fopen("contatos.txt","r+"),arq == NULL){
    printf("erro ao abrir o arquivo!\n");
    exit(1);
  }
}
////////////////////////////////////////////////////////////////////////////////
void salvaLista(Contato *lista){
  FILE *arq;
  Contato *aux;

  if(arq = fopen("contatos.txt","w"),arq == NULL){
    printf("erro ao abrir o arquivo!\n");
    exit(1);
  }

  for (aux = lista;aux != NULL;aux = aux->prox) {

    fprintf(arq,"%s\n",aux->nome);
    fprintf(arq,"%s\n",aux->celular);
    fprintf(arq,"%s\n",aux->endereco);
    fprintf(arq,"%u\n",aux->cep);
    fprintf(arq,"%s\n",aux->nascimento);
    fprintf(arq,"$\n");

    if (aux != lista) {
      free(aux->ant);
    }
  }

  free(aux);
  fclose(arq);

}
////////////////////////////////////////////////////////////////////////////////
Contato *carregaArquivoNaLista(){
  FILE *arq;
  Contato *contatos,*aux,*primeiro;
  char cifrao;

  if(arq = fopen("contatos.txt","r"),arq == NULL){
    printf("erro ao abrir o arquivo!\n");
    exit(1);
  }

  if (!feof(arq)) {
    if(aux = (Contato*)malloc(sizeof(Contato)),aux == NULL){
      printf("alocação falhou!\n");
    }
    if(primeiro = (Contato*)malloc(sizeof(Contato)),primeiro == NULL){
      printf("alocação falhou!\n");
    }

    fscanf(arq,"%[^\n]\n%s\n%[^\n]\n%u\n%s\n%c\n",aux->nome,aux->celular,aux->endereco,&aux->cep,aux->nascimento,&cifrao);
    aux->ant = NULL;
    aux->prox = NULL;
    primeiro = aux;
  }

  while(!feof(arq)){
    if(contatos = (Contato*)malloc(sizeof(Contato)),contatos == NULL){
      printf("alocação falhou!\n");
    }

    fscanf(arq,"%[^\n]\n%s\n%[^\n]\n%u\n%s\n%c\n",contatos->nome,contatos->celular,contatos->endereco,&contatos->cep,contatos->nascimento,&cifrao);
    contatos->ant = aux;
    contatos->prox = NULL;
    aux->prox = contatos;
    aux = contatos;

  }

  fclose(arq);

  return primeiro;
}
