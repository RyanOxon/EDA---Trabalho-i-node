#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define CHAR_TXT 11
#define MAX_ENTRY_SZ 256

typedef struct iNode{
  int id, pai; 
  char texto[CHAR_TXT];
  int prox_id;
}TARQ;

typedef struct ArvB{
  int nchaves, folha, *chave;
  struct ArvB *pai;
  struct ArvB **filho;
  struct iNode **info;
}TARVB;

TARVB *TARVB_insere_nodes(TARVB *T, int t);
TARVB *TARVB_insere_manual(TARVB *T, int t, char *txt);
TARVB *TARVB_Inicializa();
TARVB *TARVB_Cria(int t);
TARVB *TARVB_Libera(TARVB *a);
TARVB *TARVB_Busca(TARVB *x, int ch);
TARVB *TARVB_Insere(TARVB *T, int k, int t, TARQ *N);
//TARVB *TARVB_Retira(TARVB *arv, int k, int t);
TARQ *Inode_cria(TARQ *T);
void TARVB_Imprime(TARVB *a);

