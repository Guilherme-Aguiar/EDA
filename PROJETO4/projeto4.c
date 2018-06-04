#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#define UnTempo 5

typedef struct info {
	int id;
	char tipo;
	int combustivel;
} Info;

typedef struct lista {
	Info info;
	struct lista* ant;
	struct lista* prox;
} Lista;

typedef struct fila {
	Lista* ini;
	Lista* fim;
} Fila;


int geraNumeroAproxDecol();
char geraTipoDeVoo(int *auxDeco,int *auxAprox,int nAproximacoes,int nDecolagens);
int geraNumeroComb();

void eventos(Fila *,int,int*,char cod[64][6]);
void reduzCombustivel(Fila *, int);
int editarRelogio(int,int);

Lista *insere_inicio(Lista*,Info*);
Lista *insere_fim(Lista*,Info*);
Lista *retira_inicio(Lista*);
Lista *retira_fim(Lista*);


Fila *cria();
void fila_insere_emergencia(Fila*, int, char, int);
void fila_insere_inicio(Fila*,int);
void fila_insere_fim(Fila*,int,int *auxDeco,int *auxAprox,int nAproximacoes,int nDecolagens);
Info fila_retira_inicio(Fila*);
Info fila_retira_fim(Fila*);
void imprime(Fila*);
void checaTempo(Fila*, int);
Lista *busca(Fila*);
int busca_total(Fila*);
Fila *retira(Fila *);
int vazia(Fila*);



int main(int argc, char ** argv){
	char codVoos[64][6] =  {"VG3001", "JJ4404", "LN7001", "TG1501", "GL7602", "TT1010", "AZ1009",
													"AZ1008","AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603", "RL7880",
													"AL0012", "TT4544", "TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002",
													"AZ1002", "AZ1007", "GL7604", "AZ1006", "TG1503", "AZ1003", "JJ4403",
													"AZ1001", "LN7003", "AZ1004", "TG1504", "AZ1005", "TG1502", "GL7601",
													"TT4500", "RL7801", "JJ4410", "GL7607", "AL0029", "VV3390", "VV3392",
													"GF4681", "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", "AZ1065",
													"LF0978", "RL7867", "TT4502", "GL7645", "LF0932", "JJ4434", "TG1510",
													"TT1020", "AZ1098", "BA2312", "VG3030", "BA2304", "KL5609","KL5610",
													"KL5611"};
	int nVoos,nAproximacoes,nDecolagens,combA,aux,tempo = 1000;
	int auxAprox=0;
	int auxDeco=0;
	Lista *l;
	Fila *f,*auxiliar;
	srand(time(NULL));
	f = cria();
	nAproximacoes=geraNumeroAproxDecol();
	nDecolagens=geraNumeroAproxDecol();
	nVoos = nAproximacoes + nDecolagens;
	for(aux = 0; aux < nVoos; aux++){
		fila_insere_fim(f,aux+1,&auxDeco,&auxAprox,nAproximacoes,nDecolagens);
	}
	puts("-----------------------------------------------------");
	puts("Aeroporto Internacional de Brasília");
	puts("Hora Inicial: 10:00");
	puts("Fila de Pedidos:[código do voo – P/D – 	prioridade]");
	printf("NVoos: %d\n",nVoos);
	printf("NAproximacoes: %d\n",nAproximacoes);
	printf("nDecolagens: %d\n",nDecolagens);
	puts("-----------------------------------------------------");
	eventos(f,nVoos,&tempo,codVoos);
	free(f);
	printf("%d %d\n",auxDeco,auxAprox);
	return 0;
}

/////////////////////////////////////////////////////////////////////
int geraNumeroAproxDecol(){
  return 10+(rand() % (22)) + 1;
}
/////////////////////////////////////////////////////////////////////
char geraTipoDeVoo(int *auxDeco,int *auxAprox,int nAproximacoes,int nDecolagens){
	int n;
  n = rand() % (2);
	if (*auxAprox == nAproximacoes) {
		*auxDeco += 1;
		return 'D';
	}
	if (*auxDeco == nDecolagens) {
		*auxAprox += 1;
		return 'A';
	}
	if(n == 0){
		*auxAprox += 1;
		return 'A';
	}
	if(n == 1){
		*auxDeco += 1;
		return 'D';
	}
}
/////////////////////////////////////////////////////////////////////
int geraNumeroComb(){

  return (rand() % (13));
}
/////////////////////////////////////////////////////////////////////
/* função auxiliar: insere no início */
Lista *insere_inicio (Lista* ini, Info *i) {
   Lista* novo = (Lista*) malloc(sizeof(Lista));
   novo->info = *i;
   novo->prox = ini;
   novo->ant = NULL;
   if (ini != NULL)   /* verifica se lista não estava vazia */
      ini->ant = novo;
   return novo;
}
/////////////////////////////////////////////////////////////////////
/* função auxiliar: insere no fim */
Lista *insere_fim (Lista* fim, Info *i) {
   Lista* novo = (Lista*) malloc(sizeof(Lista));
   novo->info = *i;
   novo->prox = NULL;
   novo->ant = fim;
   if (fim != NULL)   /* verifica se lista não estava vazia */
      fim->prox = novo;
   return novo;
}
/////////////////////////////////////////////////////////////////////
/* função auxiliar: retira do início */
Lista *retira_inicio (Lista* ini) {
   Lista* p = ini->prox;
   if (p != NULL)   /* verifica se lista não ficou vazia */
      p->ant = NULL;
   free(ini);
   return p;
}
/////////////////////////////////////////////////////////////////////
/* função auxiliar: retira do fim */
Lista *retira_fim (Lista* fim) {
   Lista* p = fim->ant;
   if (p != NULL)   /* verifica se lista não ficou vazia */
      p->prox = NULL;
   free(fim);
   return p;
}
/////////////////////////////////////////////////////////////////////
Fila* cria (void)
{
   Fila* f = (Fila*) malloc(sizeof(Fila));
   f->ini = f->fim = NULL;
   return f;
}
/////////////////////////////////////////////////////////////////////
void fila_insere_inicio (Fila* f, int n) {
	 Info *i = (Info*)calloc(1,sizeof(Info));
   f->ini = insere_inicio(f->ini,i);
   if (f->fim==NULL)  /* fila antes vazia? */
      f->fim = f->ini;
}
/////////////////////////////////////////////////////////////////////
void fila_insere_fim (Fila* f,int n,int *auxDeco,int *auxAprox,int nAproximacoes,int nDecolagens) {
	 Info *i = (Info*)calloc(1,sizeof(Info));
	 i->id = n;
	 i->tipo = geraTipoDeVoo(auxDeco,auxAprox,nAproximacoes,nDecolagens);
	 if(i->tipo == 'A'){
		 i->combustivel = geraNumeroComb();
	 }
   f->fim = insere_fim(f->fim,i);
   if (f->ini==NULL)  /* fila antes vazia? */
      f->ini = f->fim;
}
/////////////////////////////////////////////////////////////////////
Info fila_retira_inicio (Fila* f) {
   Info v;
   if (vazia(f)) {
      printf("Fila vazia.\n");
      exit(1);         /* aborta programa */
   }
   v = f->ini->info;
   f->ini = retira_inicio(f->ini);
   if (f->ini == NULL)   /* fila ficou vazia? */
      f->fim = NULL;
   return v;
}
/////////////////////////////////////////////////////////////////////
Info fila_retira_fim (Fila* f) {
   Info v;
   if (vazia(f)) {
      printf("Fila vazia.\n");
      exit(1);         /* aborta programa */
   }
   v = f->fim->info;
   f->fim = retira_fim(f->fim);
   if (f->fim == NULL)   /* fila ficou vazia? */
      f->ini = NULL;
   return v;
}
/////////////////////////////////////////////////////////////////////
void imprime (Fila* f)
{
   Lista* q;
   for (q=f->ini; q!=NULL; q=q->prox)
      printf("[%d %c %d] ",q->info.id,q->info.tipo,q->info.combustivel);
}
/////////////////////////////////////////////////////////////////////
int vazia (Fila* f)
{
   return (f->ini==NULL);
}
/////////////////////////////////////////////////////////////////////
void eventos(Fila* f, int nVoos, int *tempo, char cod[64][6]){
	int pistasEmUso[3] = {0,0,0};
	int tempoPistas[3] = {0,0,0};
	int pistaAtual, contadorDaMorte = 0;
	int combZeroInicial=0;
	char codigo[7],strTempo[5];
	combZeroInicial = busca_total(f);
	for(int aux = 0; aux < combZeroInicial; aux++){
		f = retira(f);
	}
	for(int i = 0; i < nVoos; i ++){
		if(f->ini->info.combustivel < 0 && f->ini->info.tipo == 'A'){
			for(int j = 0; j < 6; j++){
				codigo[j] = cod[i][j];
			}
			printf("Código do Voo: %s / %d\n",codigo,f->ini->info.id);
			printf("Status: explodiu\n\n");
			fila_retira_inicio(f);
		}
		else {
			if(tempoPistas[0] == 0){
				puts(" ");
				puts("-----------------------------------");
				imprime(f);
				puts(" ");
				pistaAtual = 1;
				pistasEmUso[0] = 1;
			}else if(tempoPistas[1] == 0){
				puts(" ");
				puts("-----------------------------------");
				imprime(f);
				puts(" ");
				pistaAtual = 2;
				pistasEmUso[1] = 1;
			}else if((tempoPistas[2] == 0 && f->ini->info.tipo == 'D') || (tempoPistas[2] == 0  && f->ini->info.tipo == 'A' && f->ini->info.combustivel == 0)){
				puts(" ");
				puts("-----------------------------------");
				imprime(f);
				puts(" ");
				pistaAtual = 3;
				pistasEmUso[2] = 1;
			}else {
				if(tempoPistas[0] <= tempoPistas[1] && tempoPistas[0] <= tempoPistas[2] ){
					checaTempo(f,*tempo);
					*tempo =editarRelogio(*tempo,tempoPistas[0]);
					tempoPistas[1] -= tempoPistas[0];
					tempoPistas[2] -= tempoPistas[0];
					tempoPistas[0] = 0;
					pistaAtual = 1;
					puts(" ");
					puts("-----------------------------------");
					imprime(f);
					puts(" ");
				}else if(tempoPistas[1] <= tempoPistas[0] && tempoPistas[1] <= tempoPistas[2]){
					checaTempo(f,*tempo);
					*tempo =editarRelogio(*tempo,tempoPistas[1]);
					tempoPistas[0] -= tempoPistas[1];
					tempoPistas[2] -= tempoPistas[1];
					tempoPistas[1] = 0;
					pistaAtual = 2;
					puts(" ");
					puts("-----------------------------------");
					imprime(f);
					puts(" ");
				}else if((tempoPistas[2] <= tempoPistas[0] && tempoPistas[2] <= tempoPistas[1] && f->ini->info.tipo == 'D') ){
					checaTempo(f,*tempo);
					tempoPistas[0] -= tempoPistas[2];
					tempoPistas[1] -= tempoPistas[2];
					tempoPistas[2] = 0;
					pistaAtual = 3;
					puts(" ");
					puts("-----------------------------------");
					imprime(f);
					puts(" ");
				}else {
					if(tempoPistas[0] <= tempoPistas[1]){
						checaTempo(f,*tempo);
						*tempo =editarRelogio(*tempo,tempoPistas[0]);
						tempoPistas[1] -= tempoPistas[0];
						tempoPistas[0] = 0;
						pistaAtual = 1;
						puts(" ");
						puts("-----------------------------------");
						imprime(f);
						puts(" ");
					}else {
						checaTempo(f,*tempo);
						*tempo =editarRelogio(*tempo,tempoPistas[1]);
						tempoPistas[0] -= tempoPistas[1];
						tempoPistas[1] = 0;
						pistaAtual = 2;
						puts(" ");
						puts("-----------------------------------");
						imprime(f);
						puts(" ");
					}
				}
			}
			printf("tempo1 = %d, tempo 2 = %d, tempo 3 = %d\n",tempoPistas[0],tempoPistas[1],tempoPistas[2]);
			if(f->ini->info.combustivel < 0 && f->ini->info.tipo == 'A'){
				for(int j = 0; j < 6; j++){
					codigo[j] = cod[i][j];
				}
				printf("Código do Voo: %s / %d\n",codigo,f->ini->info.id);
				printf("Status: explodiu\n\n");
				fila_retira_inicio(f);
			}else {
				for(int j = 0; j < 6; j++){
					codigo[j] = cod[i][j];
				}
				printf("Código do Voo: %s / %d\n",codigo,f->ini->info.id);
				if(f->ini->info.tipo == 'A'){
					printf("Status: Aeronave Pousou\n");
					if(pistaAtual == 1){
						tempoPistas[0] += 4*UnTempo;
					}else if(pistaAtual == 2){
						tempoPistas[1] += 4*UnTempo;
					}else if(pistaAtual == 3){
						tempoPistas[2] += 4*UnTempo;
					}
				}
				else{
					printf("Status: Aeronave Decolou\n");
					if(pistaAtual == 1){
						tempoPistas[0] += 2*UnTempo;
					}else if(pistaAtual == 2){
						tempoPistas[1] += 2*UnTempo;
					}else if(pistaAtual == 3){
						tempoPistas[2] += 2*UnTempo;
					}
				}
				strcpy(strTempo,"");
				snprintf(strTempo,5, "%d",*tempo);


				printf("Horário do início do procedimento: %c%c:%c%c\n",strTempo[0],strTempo[1],strTempo[2],strTempo[3]);
				printf("tempo1 = %d, tempo 2 = %d, tempo 3 = %d\n",tempoPistas[0],tempoPistas[1],tempoPistas[2]);
				printf("Pista: %d\n\n\n",pistaAtual);

				fila_retira_inicio(f);
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////
int editarRelogio(int t,int n){
	int resultado;
	if(t < 1100){
		if(n+(t-1000) < 60){
			resultado = t+n;
		}else if(n+(t-1000) == 60){
			resultado = t +  (40 + n);
		}else if(n+(t-1000) > 60){
			resultado = t +  (40 + n) + 10;
		}
	}else if(t < 1200){
		if(n+(t-1100) < 60){
			resultado = t+n;
		}else if(n+(t-1100) == 60){
			resultado =t +  (40 + n);
		}else if(n+(t-1100) > 60){
			resultado = t +  (40 + n) + 10;
		}
	}else if(t < 1300){
		if(n+(t-1200) < 60){
			resultado = t+n;
		}else if(n+(t-1200) == 60){
			resultado =t +  (40 + n);
		}else if(n+(t-1200) > 60){
			resultado = t +  (40 + n) + 10;
		}
	}else if (t < 1400){
		if(n+(t-1300) < 60){
			resultado = t+n;
		}else if(n+(t-1300) == 60){
			resultado =t +  (40 + n);
		}else if(n+(t-1300) > 60){
			resultado = t +  (40 + n) + 10;
		}
	}
	return resultado;
}
/////////////////////////////////////////////////////////////////////
void checaTempo(Fila *f, int tempo){
  if(tempo >= 1050 && tempo < 1140){
		reduzCombustivel(f,1);
	}else if(tempo >= 1140 && tempo < 1230){
		reduzCombustivel(f,1);
	}else if(tempo >= 1230 && tempo < 1320){
		reduzCombustivel(f,1);
	}else if(tempo >= 1320 && tempo < 1410){
		reduzCombustivel(f,1);
	}else if(tempo >= 1410 && tempo < 1500){
		reduzCombustivel(f,1);
	}
}
/////////////////////////////////////////////////////////////////////
void reduzCombustivel(Fila *f,int n){
	Lista *q;
	int combZeroInicial=0;
	for(q=f->ini; q!=NULL; q=q->prox)
		q->info.combustivel-=1*n;
		combZeroInicial = busca_total(f);
		for(int aux = 0; aux < combZeroInicial; aux++){
			f = retira(f);
		}
}
/////////////////////////////////////////////////////////////////////
Lista* busca(Fila *f){
	Lista *q;
	for(q=f->fim; q!=NULL; q=q->ant)
		if(q->info.tipo == 'A')
			if(q->info.combustivel <= 0)
				return q;
	return NULL;
}
/////////////////////////////////////////////////////////////////////
int busca_total(Fila *f){
	Lista *q;
	int total=0;
	for(q=f->fim; q!=NULL; q=q->ant)
		if(q->info.tipo == 'A')
			if(q->info.combustivel <= 0)
				total++;
	return total;
}
/////////////////////////////////////////////////////////////////////
Fila* retira(Fila *f){


	Lista *q = busca(f);
	if(q == NULL){
		return f;
	}
	/* retira elemento do encadeamento */
	if (f->ini == q)
		f->ini = q->prox;
	else
		 q->ant->prox = q->prox;
	if (q->prox != NULL)
		q->prox->ant = q->ant;

	fila_insere_emergencia(f,q->info.id,q->info.tipo,q->info.combustivel);
	free(q);
	return f;
}
/////////////////////////////////////////////////////////////////////
void fila_insere_emergencia(Fila* f, int id, char tipo, int combustivel){
	Info *i = (Info*)calloc(1,sizeof(Info));
	i->id = id;
	i->tipo = tipo;
	i->combustivel = combustivel;
	f->ini = insere_inicio(f->ini,i);
	if (f->fim==NULL)  /* fila antes vazia? */
		 f->fim = f->ini;
}
