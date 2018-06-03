#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

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
int vazia(Fila*);

Lista *insere_inicio(Lista*,Info*);
Lista *insere_fim(Lista*,Info*);
Lista *retira_inicio(Lista*);
Lista *retira_fim(Lista*);

void fila_insere_inicio(Fila*);
void fila_insere_fim(Fila*);
Info fila_retira_inicio(Fila*);
Info fila_retira_fim(Fila*);




int main(int argc, char ** argv)
{
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
	int nVoos,nAproximacoes,nDecolagens,combA;
	Lista *l;

	nAproximacoes=geraNumeroAproxDecol();
	nDecolagens=geraNumeroAproxDecol();

	nVoos = nAproximacoes + nDecolagens;
	return 0;
}


int geraNumeroAproxDecol(){
  srand(time(NULL));
  return 10+(rand() % (22)) + 1;
}

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

/* função auxiliar: retira do início */
Lista *retira_inicio (Lista* ini) {
   Lista* p = ini->prox;
   if (p != NULL)   /* verifica se lista não ficou vazia */
      p->ant = NULL;
   free(ini);
   return p;
}
/* função auxiliar: retira do fim */
Lista *retira_fim (Lista* fim) {
   Lista* p = fim->ant;
   if (p != NULL)   /* verifica se lista não ficou vazia */
      p->prox = NULL;
   free(fim);
   return p;
}

void fila_insere_inicio (Fila* f) {
	 Info *i = (Info*)calloc(1,sizeof(Info));
   f->ini = insere_inicio(f->ini,i);
   if (f->fim==NULL)  /* fila antes vazia? */
      f->fim = f->ini;
}
void fila_insere_fim (Fila* f) {
	 Info *i = (Info*)calloc(1,sizeof(Info));
   f->fim = insere_fim(f->fim,i);
   if (f->ini==NULL)  /* fila antes vazia? */
      f->ini = f->fim;
}

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

int vazia (Fila* f)
{
   return (f->ini==NULL);
}
