#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

void ilbp(int **matriz,int contLine,int contCol,int **caracteristicas,int cont);
void selecionaImagens(int *asfalto,int *grama,char *nomeArquivo,FILE *arq,int **matriz,int *contLine,int *contCol,int seletor);
int geraNumeroAleatorio();
void completaMatriz(int linha, int coluna, FILE *arq,int **matriz);
void fazIlbpQuadrante(int **matriz,int linha,int coluna,int **caracteristicas,int cont);
int AchaMenorValor(int *vetor,int menor,int cont);
int fazBinParaDecimal(int *bin);
void rotacionaVetor(int *vetor);
void normalizaVetor(int *vetor,int tamVetor);
void fazMedia(int **caracteristicas,int *mediaGrama,int *mediaAsfalto);

int main() {
  FILE *arq;
  int **matriz;
  int contLine,contCol,i,j,pixel,cont=0;
  int **caracteristicas;
  char aux;
  char nomeArquivo[20]= "";
  static int asfalto[50],grama[50];
  int *mediaAsfalto,*mediaGrama;

  mediaAsfalto = (int*)calloc(536,sizeof(int));

  mediaGrama = (int*)calloc(536,sizeof(int));

  caracteristicas = (int**)calloc(50,sizeof(int*));
  for(i = 0; i<50; i++){
    *(caracteristicas+i) = (int*)calloc(536,sizeof(int));
  }

  for (cont = 0; cont < 6; cont++) {

    contLine=0;
    contCol=0;

    selecionaImagens(asfalto,grama,nomeArquivo,arq,matriz,&contLine,&contCol,cont%2);

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

    ilbp(matriz,contLine,contCol,caracteristicas,cont);

    fclose(arq);

    for(i = 0; i<contLine; i++){
      free(*(matriz+i));
    }
    free(matriz);

    strcpy(nomeArquivo, "" );

  }

  for (i = 0; i < 50; i++) {
    normalizaVetor(*(caracteristicas+i),536);
  }

  fazMedia(caracteristicas,mediaGrama,mediaAsfalto);

  for (cont = 0; cont < 50; cont++) {

    contLine=0;
    contCol=0;

    selecionaImagens(asfalto,grama,nomeArquivo,arq,matriz,&contLine,&contCol,cont%2);

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

    ilbp(matriz,contLine,contCol,caracteristicas,cont);

    fclose(arq);

    for(i = 0; i<contLine; i++){
      free(*(matriz+i));
    }
    free(matriz);

    strcpy(nomeArquivo, "" );
  }

    for (i = 0; i < 50; i++) {
      normalizaVetor(*(caracteristicas+i),536);
    }

//    fazEuclidiana(caracteristicas,mediaAsfalto,mediaGrama);





  for(i = 0; i<50; i++){
    free(*(caracteristicas+i));
  }
  free(caracteristicas);

  free(mediaGrama);

  free(mediaAsfalto);

  return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void selecionaImagens(int *asfalto,int *grama,char *nomeArquivo,FILE *arq,int **matriz,int *contLine,int *contCol,int seletor){
  int numeroAleatorio;
  char stringNumeroAleatorio[4];
  int pixel;
  char aux;
  if (seletor) {
    strcat(nomeArquivo,"grass/grass_");
    numeroAleatorio = geraNumeroAleatorio();
    while(grama[numeroAleatorio-1]) {
      numeroAleatorio = geraNumeroAleatorio();
    }
    grama[numeroAleatorio-1] = 1;
  } else {
    strcat(nomeArquivo,"asphalt/asphalt_");
    numeroAleatorio = geraNumeroAleatorio();
    while(asfalto[numeroAleatorio-1]) {
      numeroAleatorio = geraNumeroAleatorio();
    }
    asfalto[numeroAleatorio-1] = 1;
  }
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
void ilbp(int **matriz,int contLine,int contCol,int **caracteristicas,int cont){
  int i,j;
  for(i = 1; i < contLine-1; i++) {
    for (j = 1; j < contCol-1; j++) {
      fazIlbpQuadrante(matriz,i,j,caracteristicas,cont);
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fazIlbpQuadrante(int **matriz,int linha,int coluna,int **caracteristicas,int aux){
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
  if (aux%2) {
    caracteristicas[(aux-1)/2][menorValor]++;
  } else {
    caracteristicas[25+aux/2][menorValor]++;
  }
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void normalizaVetor(int *vetor,int tamVetor){

  int maior=0,menor=255,i;
  for (i = 0; i < tamVetor; i++) {
    if (vetor[i] < menor) {
      menor = vetor[i];
    }else if(vetor[i] > maior){
      maior = vetor[i];
    }
  }
  if (maior == menor) {
    return;
  }
  for (i = 0; i < tamVetor; i++) {
    vetor[i] = (vetor[i] - menor)/(maior - menor);
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fazMedia(int **caracteristicas,int *mediaGrama,int *mediaAsfalto){

  int i,j,total=0;

  for (j = 0; j < 536; j++) {
    for (i = 0; i < 25; i++) {
      total+= caracteristicas[i][j];
    }
    mediaGrama[j] = total/25;
    total = 0;
    for (; i < 50; i++) {
      total+= caracteristicas[i][j];
    }
    mediaAsfalto[j] = total/25;
    total = 0;
  }

}
