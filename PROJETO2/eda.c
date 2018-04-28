#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

void selecionaImagens();
int geraNumeroAleatorio();
void alocaMatriz(int, int);

int main() {

  selecionaImagens();


  return 0;
}


// int someInt = 368;
// char str[12];
// sprintf(str, "%d", someInt);
void selecionaImagens(){
  FILE *arq;
  int numeroAleatorio;
  char nomeArquivo[20] = "grass/grass_", stringNumeroAleatorio[4];
  numeroAleatorio = geraNumeroAleatorio();
  sprintf(stringNumeroAleatorio,"%02d",numeroAleatorio);
  strcat(nomeArquivo,stringNumeroAleatorio);
  strcat(nomeArquivo,".txt");
  printf("%s\n",nomeArquivo);
  arq = fopen(nomeArquivo,"r");
  int contLine=0,contCol=0,pixel;
  char aux;
  while(!feof(arq)){
    fscanf(arq, "%d%c",&pixel,&aux);
    if(aux == ';'){
      contCol++;
    }
    else if(aux == '\n'){
      contLine++;
    }
    else{
      printf(".");
    }
  }
  fclose(arq);
   printf("%d %d",contLine-1,contCol/(contLine-1)+1);
}

int geraNumeroAleatorio(){
  srand(time(NULL));
  return (rand() % 49) + 1;
}
