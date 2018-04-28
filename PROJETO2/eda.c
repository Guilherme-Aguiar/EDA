#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

void selecionaImagens();
int geraNumeroAleatorio();
void alocaMatriz(int, int, FILE *);

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
  char nomeArquivo[20],stringNumeroAleatorio[4];
  strcat(nomeArquivo,"grass/grass_");
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
  alocaMatriz(contLine-1,contCol/(contLine-1)+1,arq);
   printf("%d %d",contLine-1,contCol/(contLine-1)+1);
}

int geraNumeroAleatorio(){
  srand(time(NULL));
  return (rand() % 49) + 1;
}

void alocaMatriz(int linha, int coluna, FILE *arq){
  int i, j, **matriz, pixel;
  char aux;
  rewind(arq);
  matriz = (int**)malloc(linha*sizeof(int *));
  for(i = 0; i<linha; i++)
    *(matriz+i) = (int*)malloc(coluna*sizeof(int));

  for(i = 0; i<linha; i++)
    for(j = 0; j<coluna; j++){
      fscanf(arq,"%d%c",&pixel,&aux);
      matriz[i][j] = pixel;
    }
    printf("\n3 primeiros elementos: %d e %d e %d\n",matriz[0][0],matriz[0][1],matriz[0][2]);
}
