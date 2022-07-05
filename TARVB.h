#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define CHAR_TXT 9
#define MAX_ENTRY_SZ 256

typedef struct TabNode{
  char *nome;
  struct iNode *node;
  struct TabNode *prox;
}TBND;

typedef struct iNode{
  char *nome;
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

TBND *TBND_Inicializa();
TBND *TBND_busca_nome(TBND *tab, char *nome);

TARVB *TARVB_insere_novo_node(TARVB *T, int t, TBND *tab, char *nome);
TARVB *TARVB_Inicializa();
TARVB *TARVB_Cria(int t);
TARVB *TARVB_Libera(TARVB *a);
TARVB *TARVB_Busca(TARVB *x, int ch);
TARVB *TARVB_Insere(TARVB *T, int k, int t, TARQ *N);
//TARVB *TARVB_Retira(TARVB *arv, int k, int t);
void TARVB_Imprime(TARVB *a);

