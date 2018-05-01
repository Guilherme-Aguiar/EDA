#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

void ilbp(int **matriz,int contLine,int contCol,int *frequencia);
void selecionaImagens(char *nomeArquivo,FILE *arq,int **matriz,int *contLine,int *contCol);
int geraNumeroAleatorio();
void completaMatriz(int linha, int coluna, FILE *arq,int **matriz);
void fazIlbpQuadrante(int **matriz,int linha,int coluna,int *frequencia);
int AchaMenorValor(int *vetor,int menor,int cont);
int fazBinParaDecimal(int *bin);
void rotacionaVetor(int *vetor);

int main() {
  FILE *arq;
  int **matriz;
  int contLine=0,contCol=0,i,j,pixel;
  int *frequencia;
  char aux;
  char nomeArquivo[20]= "";

  frequencia = (int*)calloc(536,sizeof(int));

  selecionaImagens(nomeArquivo,arq,matriz,&contLine,&contCol);

  matriz = (int**)malloc(contLine*sizeof(int*));
  for(i = 0; i<contLine; i++){
    *(matriz+i) = (int*)malloc(contCol*sizeof(int));
  }

  arq = fopen(nomeArquivo,"r");

  for(i = 0; i<contLine; i++)
    for(j = 0; j<contCol; j++){
      fscanf(arq,"%d%c",&pixel,&aux);
      *(*(matriz+i)+j) = pixel;
    }

  ilbp(matriz,contLine,contCol,frequencia);

  for (i = 0; i < 536; i++) {
    printf("%d %d\n",i,frequencia[i]);
  }

  return 0;
}


// int someInt = 368;
// char str[12];
// sprintf(str, "%d", someInt);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void selecionaImagens(char *nomeArquivo,FILE *arq,int **matriz,int *contLine,int *contCol){
  int numeroAleatorio;
  char stringNumeroAleatorio[4];
  int pixel;
  char aux;
  strcat(nomeArquivo,"grass/grass_");
  numeroAleatorio = geraNumeroAleatorio();
  sprintf(stringNumeroAleatorio,"%02d",numeroAleatorio);
  strcat(nomeArquivo,stringNumeroAleatorio);
  strcat(nomeArquivo,".txt");
  printf("%s\n",nomeArquivo);
  arq = fopen(nomeArquivo,"r");
  while(!feof(arq)){
    fscanf(arq, "%d%c",&pixel,&aux);
    if(aux == ';'){
      *contCol += 1;
    }
    else if(aux == '\n'){
      *contLine += 1;
    }
  }
  *contLine -= 1;
  *contCol = *contCol/(*contLine)+1;
  printf("%d %d\n",*contLine,*contCol);
  fclose(arq);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int geraNumeroAleatorio(){
  srand(time(NULL));
  return (rand() % 49) + 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void completaMatriz(int linha, int coluna, FILE *arq,int **matriz){
  int i, j, pixel;
  char aux;
  rewind(arq);
  for(i = 0; i<linha; i++)
    for(j = 0; j<coluna; j++){
      fscanf(arq,"%d%c",&pixel,&aux);
      matriz[i][j] = pixel;

    }
    printf("\n3 primeiros elementos: %d e %d e %d\n",matriz[0][0],matriz[0][1],matriz[0][2]);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ilbp(int **matriz,int contLine,int contCol,int *frequencia){
  int i,j;
  for(i = 1; i < contLine-1; i++) {
    for (j = 1; j < contCol-1; j++) {
      fazIlbpQuadrante(matriz,i,j,frequencia);
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fazIlbpQuadrante(int **matriz,int linha,int coluna,int *frequencia){
  float total=0.0;
  int cont=0,menorValor;
  int vetor[9];
  for (int i = linha-1; i <= linha+1; i++) {
    for (int j = coluna-1; j <= coluna+1; j++) {
      total += *(*(matriz+i)+j);
      vetor[cont] = matriz[i][j];
      cont++;
    }
  }
  for (int i = 0; i < 9; i++) {
    if (total/9 >= vetor[i]) {
      vetor[i] = 1;
    } else {
      vetor[i] = 0;
    }
  }
  menorValor = AchaMenorValor(vetor,255,0);
  if (menorValor == 1) {
    printf("foda-se\n");
  }
  frequencia[menorValor]++;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchaMenorValor(int *vetor,int menor,int cont){
  int n;
  if (cont == 9) {
    return menor;
  } else {
    n = fazBinParaDecimal(vetor);
    if (n < menor) {
      menor = n;
    }
    rotacionaVetor(vetor);
    return AchaMenorValor(vetor,menor,cont+1);
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int fazBinParaDecimal(int *bin){
  int decimal=0;
  for (int i = 0; i < 9; i++) {
    decimal += pow(2,(8-i))*bin[i];
  }
  return decimal;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rotacionaVetor(int *vetor){
  int aux = vetor[0];
  int aux1;
  vetor[0] = vetor[8];
  for (int i = 1; i < 9; i++) {
    aux1 = vetor[i];
    vetor[i] = aux;
    aux = aux1;
  }
}
