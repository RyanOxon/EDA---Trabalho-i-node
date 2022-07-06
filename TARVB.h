#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TAB_SZ 101
#define CHAR_SZ 9
#define MAX_ENTRY_SZ 256
#define MAX_ARQ_SZ 33

typedef struct iNode{
  char nome[MAX_ARQ_SZ];
  int id, pai; 
  char texto[CHAR_SZ];
  int prox_id;
}TARQ;

typedef struct ArvB{
  int nchaves, folha, *chave;
  struct ArvB *pai;
  struct ArvB **filho;
  struct iNode **info;
}TARVB;

typedef TARQ* TH[TAB_SZ];

void TH_insere(TH tab, TARQ *N);
void TH_inicializa(TH tab, int m);
void TH_imprime(TH tab);

TARQ* TH_busca_nome(TH tab, char nome[MAX_ARQ_SZ]);

TARVB *TARVB_insere_novo_node(TARVB *T, int t, TH tab, char nome[MAX_ARQ_SZ], char *entry);
TARVB *TARVB_Inicializa();
TARVB *TARVB_Cria(int t);
TARVB *TARVB_Libera(TARVB *a);
TARVB *TARVB_Busca(TARVB *x, int ch);
TARVB *TARVB_Insere(TARVB *T, int k, int t, TARQ *N);
//TARVB *TARVB_Retira(TARVB *arv, int k, int t);
void TARVB_Imprime(TARVB *a);
void TARVB_Salva(TARVB *a, TH tab);

