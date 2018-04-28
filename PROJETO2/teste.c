#include <stdio.h>
#include <stdlib.h>

int main() {
	int nPontoVirgula = 0, nBarraN = 0;
	FILE *arq;
	char caracter;

	arq = fopen("test.txt","r");
	while(!feof(arq)) {
		fread(&caracter,sizeof(char),1,arq);
		if(caracter==';'){
			nPontoVirgula+=1;
		}
		if(caracter=='\n'){
			nBarraN+=1;
		}
	}

		printf("Numero de ponto e virgula: %d\n",((nPontoVirgula)/(nBarraN-1))+1);
		printf("Numero de barra N: %d\n",nBarraN-1);
		fclose(arq);
	return 0;
}
