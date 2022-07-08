#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRY_SZ 1024 //Tamanho maximo da entrada de texto pelo teclado
#define CHAR_SZ 11 //Tamanho do recorte
#define MAX_ARQ_SZ 64 //Tamanho maximo do Nome do arquivo 

typedef struct Info{
  char nome[MAX_ARQ_SZ];
  int id; 
  int pai, prox_id; 
  char texto[CHAR_SZ];
}TARQ;

typedef struct ArvB{
  int nchaves, folha, *chave;
  struct ArvB *pai;
  struct ArvB **filho;
  struct Info **info;
}TARVB;

typedef struct Inode{
  char nome[MAX_ARQ_SZ];
  struct Info *info;
  struct Inode *prox;
}ND;

typedef struct lse{
  ND *prim;
}TL;


TL *TL_init();
void TL_insere(TL *tab, TARQ *N);
void TL_imprime(TL *tab);
TARQ* TL_busca_nome(TL *tab, char nome[MAX_ARQ_SZ]);

TARQ *TARQ_busca(TARVB *x, int ch);
void Salva_Node(TARVB *a, TL *tab, char *nome);
void TARQ_imp_seq(TARVB *a, TL *tab, char *arq);

TARVB *TARVB_Inicializa();
TARVB *TARVB_Cria(int t);
TARVB *TARVB_Libera(TARVB *a);
TARVB *TARVB_Busca(TARVB *x, int ch);
TARVB *TARVB_insere_teclado(TARVB *T, int t, TL *tab, char nome[MAX_ARQ_SZ]);
TARVB *TARVB_insere_arquivo(TARVB *T, int t, TL *tab);
TARVB *TARVB_Insere(TARVB *T, int k, int t, TARQ *N);
TARVB *TARVB_Retira(TARVB *arv, int k, int t);
void TARVB_Imprime(TARVB *a);
int checa_txt(char *texto);

void menu();
void op0();
void op1();
void op2();

