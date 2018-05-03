#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define IMAGENS 50
#define TAMCOD 256
#define TAMVET 536

void ilbp(int **matriz,int contLine,int contCol,double **caracteristicas,int cont);
void selecionaImagens(int *asfalto,int *grama,char *nomeArquivo,FILE *arq,int **matriz,int *contLine,int *contCol,int seletor);
int geraNumeroAleatorio();
void fazIlbpQuadrante(int **matriz,int linha,int coluna,double **caracteristicas,int cont);
int AchaMenorValor(int *vetor,int menor,int cont);
int fazBinParaDecimal(int *bin);
void rotacionaVetor(int *vetor);
void normalizaVetor(double *vetor,int tamVetor);
void fazMedia(double **caracteristicas,double *mediaGrama,double *mediaAsfalto);
void fazEuclidiana(double **caracteristicas,double *mediaAsfalto,double *mediaGrama,int *taxaAcerto,int *taxaFalsaAceitacao,int *taxaFalsaRejeicao);
void glcm(int **matriz,int linha,int coluna,double **caracteristicas,int cont);
double calculaEnergia(int **matriz);
double calculaHomogeneidade(int **matriz);
double calculaContraste(int **matriz);
void selecionaImagensTreino(int *asfalto,int *grama,char *nomeArquivo,FILE *arq,int **matriz,int *contLine,int *contCol,int seletor);

int main() {
  FILE *arq;
  int **matriz;
  int contLine,contCol,i,j,pixel,cont=0,taxaAcerto=0,taxaFalsaRejeicao=0,taxaFalsaAceitacao=0;
  double **caracteristicas;
  char aux;
  char nomeArquivo[20]= "";
  static int asfalto[IMAGENS],grama[IMAGENS];
  double *mediaAsfalto,*mediaGrama;

  if(mediaAsfalto = (double*)calloc(TAMVET,sizeof(double)),mediaAsfalto == NULL){
    printf("alocação falhou!\n");
    exit(1);
  }

  if(mediaGrama = (double*)calloc(TAMVET,sizeof(double)),mediaGrama == NULL){
    printf("alocação falhou!\n");
    exit(1);
  }

  if(caracteristicas = (double**)calloc(IMAGENS,sizeof(double*)),caracteristicas == NULL){
    printf("alocação falhou!\n");
    exit(1);
  }
  for(i = 0; i<IMAGENS; i++){
    if(*(caracteristicas+i) = (double*)calloc(TAMVET,sizeof(double)),*(caracteristicas+i) == NULL){
      printf("alocação falhou!\n");
      exit(1);
    }
  }

  for (cont = 0; cont < IMAGENS; cont++) {

    contLine=0;
    contCol=0;

    selecionaImagens(asfalto,grama,nomeArquivo,arq,matriz,&contLine,&contCol,cont%2);

    if(matriz = (int**)malloc(contLine*sizeof(int*)),matriz == NULL){
      printf("alocação falhou!\n");
    }
    for(i = 0; i<contLine; i++){
      if(*(matriz+i) = (int*)malloc(contCol*sizeof(int)),*(matriz+i) == NULL){
        printf("alocação falhou!\n");
      }
    }

    if(arq = fopen(nomeArquivo,"r"),arq == NULL){
      printf("erro ao abrir o arquivo!\n");
      exit(1);
    }
    for(i = 0; i<contLine; i++)
      for(j = 0; j<contCol; j++){
        fscanf(arq,"%d%c",&pixel,&aux);
        *(*(matriz+i)+j) = pixel;
      }

    ilbp(matriz,contLine,contCol,caracteristicas,cont);
    glcm(matriz,contLine,contCol,caracteristicas,cont);


    fclose(arq);

    for(i = 0; i<contLine; i++){
      free(*(matriz+i));
    }
    free(matriz);

    strcpy(nomeArquivo, "" );

  }

  for (i = 0; i < IMAGENS; i++) {
    normalizaVetor(*(caracteristicas+i),TAMVET);
  }

  fazMedia(caracteristicas,mediaGrama,mediaAsfalto);

  for(i = 0; i<IMAGENS; i++){
    free(*(caracteristicas+i));
  }
  free(caracteristicas);

  if(caracteristicas = (double**)calloc(IMAGENS,sizeof(double*)),caracteristicas == NULL){
    printf("alocação falhou!\n");
    exit(1);
  }
  for(i = 0; i<IMAGENS; i++){
    if(*(caracteristicas+i) = (double*)calloc(TAMVET,sizeof(double)),*(caracteristicas+i) == NULL){
      printf("alocação falhou!\n");
      exit(1);
    }
  }

  for (cont = 0; cont < IMAGENS; cont++) {

    contLine=0;
    contCol=0;

    selecionaImagensTreino(asfalto,grama,nomeArquivo,arq,matriz,&contLine,&contCol,cont%2);

    if(matriz = (int**)malloc(contLine*sizeof(int*)),matriz == NULL){
      printf("alocação falhou!\n");
    }
    for(i = 0; i<contLine; i++){
      if(*(matriz+i) = (int*)malloc(contCol*sizeof(int)),*(matriz+i) == NULL){
        printf("alocação falhou!\n");
      }
    }

    if(arq = fopen(nomeArquivo,"r"),arq == NULL){
      printf("erro ao abrir o arquivo!\n");
      exit(1);
    }
    for(i = 0; i<contLine; i++)
      for(j = 0; j<contCol; j++){
        fscanf(arq,"%d%c",&pixel,&aux);
        *(*(matriz+i)+j) = pixel;
    }

    ilbp(matriz,contLine,contCol,caracteristicas,cont);
    glcm(matriz,contLine,contCol,caracteristicas,cont);

    fclose(arq);

    for(i = 0; i<contLine; i++){
      free(*(matriz+i));
    }
    free(matriz);

    strcpy(nomeArquivo, "" );
  }

  for (i = 0; i < IMAGENS; i++) {
    normalizaVetor(*(caracteristicas+i),TAMVET);
  }

  fazEuclidiana(caracteristicas,mediaAsfalto,mediaGrama,&taxaAcerto,&taxaFalsaAceitacao,&taxaFalsaRejeicao);

  printf("Taxa de acerto: %d%%\n",taxaAcerto*100/IMAGENS);
  printf("Taxa de falsa aceitação: %d%%\n",taxaFalsaAceitacao*100/IMAGENS);
  printf("Taxa de falsa rejeição: %d%%\n",taxaFalsaRejeicao*100/IMAGENS);

  for(i = 0; i<IMAGENS; i++){
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
  if(arq = fopen(nomeArquivo,"r"),arq == NULL){
    printf("erro ao abrir o arquivo!\n");
    exit(1);
  }
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
  fclose(arq);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int geraNumeroAleatorio(){
  srand(time(NULL));
  return (rand() % (IMAGENS)) + 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ilbp(int **matriz,int contLine,int contCol,double **caracteristicas,int cont){
  int i,j;
  for(i = 1; i < contLine-1; i++) {
    for (j = 1; j < contCol-1; j++) {
      fazIlbpQuadrante(matriz,i,j,caracteristicas,cont);
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fazIlbpQuadrante(int **matriz,int linha,int coluna,double **caracteristicas,int aux){
  double total=0.0;
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
  menorValor = AchaMenorValor(vetor,TAMCOD,0);
  if (aux%2) {
    caracteristicas[(aux-1)/2][menorValor]+=1;
  } else {
    caracteristicas[IMAGENS/2+aux/2][menorValor]+=1;
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
void normalizaVetor(double *vetor,int tamVetor){

  int maior=0,menor=10000,i;
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
void fazMedia(double **caracteristicas,double *mediaGrama,double *mediaAsfalto){

  int i,j;
  double total=0.0;

  for (j = 0; j < TAMVET; j++) {
    for (i = 0; i < IMAGENS/2; i++) {
      total+= caracteristicas[i][j];
    }
    mediaGrama[j] = total/(IMAGENS/2);
    total = 0.0;
    for (i = IMAGENS/2; i < IMAGENS; i++) {
      total+= caracteristicas[i][j];
    }
    mediaAsfalto[j] = total/(IMAGENS/2);
    total = 0.0;
  }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fazEuclidiana(double **caracteristicas,double *mediaAsfalto,double *mediaGrama,int *taxaAcerto,int *taxaFalsaAceitacao,int *taxaFalsaRejeicao){
  double total = 0.0,distEuclidGrama,distEuclidAsfalto;
  int i,j;
  for (i = 0; i < IMAGENS; i++) {
    for (j = 0; j < TAMVET; j++) {
      total+= pow(caracteristicas[i][j] - mediaGrama[j],2);
    }
    distEuclidGrama = sqrt(total);
    total = 0.0;
    for (j = 0; j < TAMVET; j++) {
      total+= pow(caracteristicas[i][j] - mediaAsfalto[j],2);
    }
    distEuclidAsfalto = sqrt(total);
    total = 0.0;
    if (i < IMAGENS/2) {
      if (distEuclidGrama < distEuclidAsfalto) {
        *taxaAcerto += 1;
      } else {
        *taxaFalsaRejeicao += 1;
      }
    } else{
      if (distEuclidGrama > distEuclidAsfalto) {
        *taxaAcerto += 1;
      } else {
        *taxaFalsaAceitacao += 1;
      }
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void glcm(int **matriz,int linha,int coluna,double **caracteristicas,int cont){
  int ***matrizesGlcm;
  int i,j,t;

  if(matrizesGlcm = (int***)calloc(8,sizeof(int**)),matrizesGlcm == NULL){
    printf("alocação falhou!\n");
  }
	for (i = 0; i < 8; i++) {
    if(matrizesGlcm[i] = (int**)calloc(TAMCOD,sizeof(int*)),matrizesGlcm[i] == NULL){
      printf("alocação falhou!\n");
    }
		for (j = 0; j < TAMCOD; j++) {
      if(matrizesGlcm[i][j] = (int*)calloc(TAMCOD,sizeof(int)),matrizesGlcm[i][j] == NULL){
        printf("alocação falhou!\n");
      }
		}
	}

  for (t = 0; t < 8; t++) {
    for (i = 1; i < linha-1; i++) {
      for (j = 1; j < coluna-1; j++) {
        switch (t) {
          case 0:
            matrizesGlcm[t][matriz[i][j]][matriz[i-1][j-1]]++;
            break;
          case 1:
            matrizesGlcm[t][matriz[i][j]][matriz[i-1][j]]++;
            break;
          case 2:
            matrizesGlcm[t][matriz[i][j]][matriz[i-1][j+1]]++;
            break;
          case 3:
            matrizesGlcm[t][matriz[i][j]][matriz[i][j-1]]++;
            break;
          case 4:
            matrizesGlcm[t][matriz[i][j]][matriz[i][j+1]]++;
            break;
          case 5:
            matrizesGlcm[t][matriz[i][j]][matriz[i+1][j-1]]++;
            break;
          case 6:
            matrizesGlcm[t][matriz[i][j]][matriz[i+1][j]]++;
            break;
          case 7:
            matrizesGlcm[t][matriz[i][j]][matriz[i+1][j+1]]++;
        }
      }
    }
    if (cont%2) {
      caracteristicas[(cont-1)/2][512+3*t] = calculaEnergia(matrizesGlcm[t]);
      caracteristicas[(cont-1)/2][512+3*t+1] = calculaHomogeneidade(matrizesGlcm[t]);
      caracteristicas[(cont-1)/2][512+3*t+2] = calculaContraste(matrizesGlcm[t]);
    } else {
      caracteristicas[IMAGENS/2+cont/2][512+3*t] = calculaEnergia(matrizesGlcm[t]);
      caracteristicas[IMAGENS/2+cont/2][512+3*t+1] = calculaHomogeneidade(matrizesGlcm[t]);
      caracteristicas[IMAGENS/2+cont/2][512+3*t+2] = calculaContraste(matrizesGlcm[t]);
    }
  }

  for (i = 0; i < 8; i++) {
    for (j = 0; j < TAMCOD; j++) {
      free(matrizesGlcm[i][j]);
    }
    free(matrizesGlcm[i]);
  }
  free(matrizesGlcm);

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
double calculaContraste(int **matriz){
  int i,j;
  double total=0.0;
  for (i = 0; i < TAMCOD; i++) {
    for (j = 0; j < TAMCOD; j++) {
      total += matriz[i][j]*pow(i-j,2);
    }
  }
  return total;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
double calculaHomogeneidade(int **matriz){
  int i,j;
  double total=0.0;
  for (i = 0; i < TAMCOD; i++) {
    for (j = 0; j < TAMCOD; j++) {
      total += matriz[i][j]/(1+abs(i-j));
    }
  }
  return total;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
double calculaEnergia(int **matriz){
  int i,j;
  double total=0.0;
  for (i = 0; i < TAMCOD; i++) {
    for (j = 0; j < TAMCOD; j++) {
      total += pow(matriz[i][j],2);
    }
  }
  return total;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void selecionaImagensTreino(int *asfalto,int *grama,char *nomeArquivo,FILE *arq,int **matriz,int *contLine,int *contCol,int seletor){
  int cont=0,numeroAleatorio;
  char stringNumeroAleatorio[4];
  int pixel;
  char aux;
  if (seletor) {
    strcat(nomeArquivo,"grass/grass_");
    while(grama[cont]) {
      cont++;
    }
    numeroAleatorio = cont+1;
    grama[cont] = 1;
  } else {
    strcat(nomeArquivo,"asphalt/asphalt_");
    while(asfalto[cont]) {
      cont++;
    }
    numeroAleatorio = cont+1;
    asfalto[cont] = 1;
  }
  sprintf(stringNumeroAleatorio,"%02d",numeroAleatorio);
  strcat(nomeArquivo,stringNumeroAleatorio);
  strcat(nomeArquivo,".txt");
  printf("%s\n",nomeArquivo);
  if(arq = fopen(nomeArquivo,"r"),arq == NULL){
    printf("erro ao abrir o arquivo!\n");
    exit(1);
  }
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
