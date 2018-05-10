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
void abreArquivo(FILE *arq);
void salvaLista();
void carregaArquivoNaLista();

int main() {

  char select;
  FILE *arq;
  Contato *lista;

  abreArquivo(arq);
  carregaArquivoNaLista();
  fclose(arq);

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
        abreArquivo(arq);
        salvaLista();
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
void salvaLista(){
}
////////////////////////////////////////////////////////////////////////////////
void carregaArquivoNaLista(){
}
