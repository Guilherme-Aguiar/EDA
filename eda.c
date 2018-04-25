#include <stdio.h>
#include <stdlib.h>

void ilbp();

int main() {

  ilbp();


  return 0;
}

void ilbp(){
  FILE *arq;
  arq = fopen("grass_01.txt","r");
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
