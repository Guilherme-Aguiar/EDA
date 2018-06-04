#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TAMNOME 101
#define TAMCEL 11
#define TAMEND 101
#define TAMDATA 11

typedef struct contato{
  char nome[TAMNOME];
  char celular[TAMCEL];
  char endereco[TAMEND];
  unsigned int cep;
  char nascimento[TAMDATA];
  struct contato *prox;
  struct contato *ant;

} Contato;

void mostraMenu();
Contato *inserirRegistro(Contato *lista);
Contato *removerRegistros(Contato *lista,char nome[]);
void visualizarRegistroNome(Contato *lista,char nome[]);
void visualizarTodosRegistros(Contato *lista,char modo);
void salvaLista(Contato *lista);
Contato *carregaArquivoNaLista();
Contato *insertSort(Contato *lista,Contato *termo);
int validaCelular(char celular[]);
void continuar();

int main() {

  char select,c,modo,nome[TAMNOME];
  FILE *arq;
  Contato *lista;

  lista = carregaArquivoNaLista();

  do {
    mostraMenu();
    scanf("%c",&select);
    do {
      c = getchar();
    } while(c != '\n');

    switch (select) {
      case '1':
        system("clear");
        lista = inserirRegistro(lista);
        continuar();

        break;
      case '2':
        system("clear");
        printf("digite o nome que deseja retirar dos contatos:\n");
        scanf("%[^\n]",nome);
        getchar();
        lista = removerRegistros(lista,nome);
        strcpy(nome,"");
        continuar();
        break;
      case '3':
        system("clear");
        printf("digite o nome que deseja visualizar dos contatos:\n");
        scanf("%[^\n]",nome);
        getchar();
        visualizarRegistroNome(lista,nome);
        strcpy(nome,"");
        continuar();
        break;
      case '4':
        system("clear");
        do{
          printf("digite o modo que deseja visualizar os contatos:\n");
          printf("1 - ordem crescente\n");
          printf("2 - ordem decrescente\n");
          scanf("%c",&modo);
          do {
            c = getchar();
          } while(c != '\n');
        }while(modo < '1' || modo > '2');
        system("clear");
        visualizarTodosRegistros(lista,modo);
        continuar();
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
  printf("\t3 - Visualizar registros que possuem o nome indicado\n\n");
  printf("\t4 - Visualizar todos os registros em ordem alfabética de nomes\n\n");
  printf("\t0 - Sair\n\n");

}
////////////////////////////////////////////////////////////////////////////////
Contato *removerRegistros(Contato *lista,char nome[]){
  Contato *aux,*aux1;
  int cont=0;

  for(aux = lista;aux != NULL;aux = aux->prox){
    if (!strcasecmp(aux->nome,nome)) {
      printf("\ncontato removido:\n");
      printf("%s\n",aux->nome);
      printf("%s\n",aux->celular);
      printf("%s\n",aux->endereco);
      printf("%u\n",aux->cep);
      printf("%s\n",aux->nascimento);
      printf("\n");
      if (aux->prox == NULL & aux->ant == NULL) {
        free(lista);
        return NULL;
      }else if(aux->prox == NULL){
        aux1= aux->ant;
        free(aux);
        aux1->prox = NULL;
      }else if(aux->ant == NULL){
        lista = aux->prox;
        lista->ant = NULL;
        free(aux);
        aux = lista;
      }else{
        aux1 = aux->ant;
        aux1->prox = aux->prox;
        aux1 = aux->prox;
        aux1->ant = aux->ant;
        free(aux);
      }
      cont++;
    }
  }
  if (!cont) {
    printf("\nnome não encontrado.\n");
  }
  return lista;
}
////////////////////////////////////////////////////////////////////////////////
void visualizarRegistroNome(Contato *lista,char nome[]){
  Contato *aux;
  long long int cont=0;

  for(aux = lista;aux != NULL && lista != NULL;aux = aux->prox){
    if(!strcasecmp(aux->nome,nome)){
      printf("\n%s\n",aux->nome);
      printf("%s\n",aux->celular);
      printf("%s\n",aux->endereco);
      printf("%u\n",aux->cep);
      printf("%s\n",aux->nascimento);
      printf("\n");
      cont++;
    }
  }
  if (!cont) {
    printf("\nnome não encontrado.\n");
  }
}
////////////////////////////////////////////////////////////////////////////////
void visualizarTodosRegistros(Contato *lista,char modo){
  Contato *aux;
  if (modo == '1') {
    for(aux = lista;aux != NULL && lista != NULL;aux = aux->prox){
      printf("%s\n",aux->nome);
      printf("%s\n",aux->celular);
      printf("%s\n",aux->endereco);
      printf("%u\n",aux->cep);
      printf("%s\n",aux->nascimento);
      printf("\n");
    }
  } else {
    for(aux = lista;aux->prox != NULL && lista != NULL;aux = aux->prox){
    }
    for (;aux != NULL && lista != NULL;aux = aux->ant) {
      printf("%s\n",aux->nome);
      printf("%s\n",aux->celular);
      printf("%s\n",aux->endereco);
      printf("%u\n",aux->cep);
      printf("%s\n",aux->nascimento);
      printf("\n");
    }
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
    if(aux->prox == NULL){
      free(aux);
    }
  }

  fclose(arq);

}
////////////////////////////////////////////////////////////////////////////////
Contato *carregaArquivoNaLista(){
  FILE *arq;
  Contato *contatos,*primeiro;
  char cifrao;

  if(arq = fopen("contatos.txt","r"),arq == NULL){
    printf("erro ao abrir o arquivo!\n");
    exit(1);
  }

  if (!feof(arq)) {
    if(contatos = (Contato*)malloc(sizeof(Contato)),contatos == NULL){
      printf("alocação falhou!\n");
    }

    fscanf(arq,"%[^\n]\n%s\n%[^\n]\n%u\n%s\n%c\n",contatos->nome,contatos->celular,contatos->endereco,&contatos->cep,contatos->nascimento,&cifrao);
    if (!strcasecmp(contatos->nome,"")) {
      return NULL;
    }
    contatos->ant = NULL;
    contatos->prox = NULL;
    primeiro = contatos;
  }

  while(!feof(arq)){
    if(contatos = (Contato*)malloc(sizeof(Contato)),contatos == NULL){
      printf("alocação falhou!\n");
    }

    fscanf(arq,"%[^\n]\n%s\n%[^\n]\n%u\n%s\n%c\n",contatos->nome,contatos->celular,contatos->endereco,&contatos->cep,contatos->nascimento,&cifrao);
    primeiro = insertSort(primeiro,contatos);
  }

  fclose(arq);

  return primeiro;
}
////////////////////////////////////////////////////////////////////////////////
Contato *insertSort(Contato *lista,Contato *termo){
  Contato *aux;

  if (lista == NULL) {
    lista = termo;
    termo->ant = NULL;
    termo->prox = NULL;
    return lista;
  }
  for (aux = lista; aux != NULL; aux = aux->prox) {
    if(strcasecmp(aux->nome,termo->nome) > 0){
      termo->prox = aux;
      termo->ant = aux->ant;
      aux->ant = termo;
      if (termo->ant != NULL) {
        termo->ant->prox = termo;
      }else{
        lista = termo;
      }
      return lista;
    }
    if(aux->prox == NULL){
      termo->prox = NULL;
      termo->ant = aux;
      aux->prox = termo;
      return lista;
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
int validaCelular(char celular[]){
  int aux;
  if(strlen(celular) != 10){
    puts("Número Invalido! Digite Novamente:");
    return 0;
  }
  else{
    for(aux = 0; aux <10; aux++){
      if(!isdigit(celular[aux]) && aux !=5){
        puts("Número Invalido! Digite Novamente:");
        return 0;
      }
      if(aux == 5){
        if(celular[aux] != '-'){
          puts("Número Invalido! Digite Novamente:");
          return 0;
        }
      }
    }
  }
  return 1;
}
////////////////////////////////////////////////////////////////////////////////
Contato *inserirRegistro(Contato *lista){
  Contato *novo;
  int dia,mes,ano;
  char day[3],month[3],year[5];

  if(novo = (Contato*)malloc(sizeof(Contato)),novo == NULL){
    printf("alocação falhou!\n");
  }

  printf("Digite o nome do novo contato:\n");
  scanf("%[^\n]",novo->nome);
  getchar();
  do{
    printf("Digite o celular do novo contato:\n");
    scanf("%[^\n]",novo->celular);
    getchar();
  }while(!validaCelular(novo->celular));
  printf("Digite o endereço do novo contato:\n");
  scanf("%[^\n]",novo->endereco);
  getchar();
  printf("Digite o cep do novo contato:\n");
  scanf(" %u",&novo->cep);
  printf("Digite a data de nascimento do novo contato:\n");
  do {
    printf("Dia:\n");
    scanf(" %d",&dia);
  } while(dia < 1 || dia > 31);
  do {
    printf("Mês:\n");
    scanf(" %d",&mes);
  } while(mes < 1 || mes > 12);
  printf("Ano:\n");
  scanf(" %d",&ano);
  sprintf(day, "%i", dia);
  sprintf(month, "%i", mes);
  sprintf(year, "%i", ano);
  sprintf(novo->nascimento,"%s/%s/%s",day,month,year);
  lista = insertSort(lista,novo);
  getchar();
  return lista;
}
////////////////////////////////////////////////////////////////////////////////
void continuar(){
  char c;
  printf("\naperte enter para continuar\n");
  do {
    c = getchar();
  } while(c != '\n');
}
