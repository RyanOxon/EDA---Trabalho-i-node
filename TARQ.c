#include "TARVB.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>


TBND *TBND_Inicializa(){
  return NULL;
}

TBND *TBND_insere(TBND *A, TARQ *N){
    TBND *novo = (TBND*)malloc(sizeof(TBND));
    novo->node = N;
    novo->nome = N->nome;
    novo->prox = A;
    printf("inseri um node na tabela \n");
    return novo;
}

TARVB *TARVB_Cria(int t){
  TARVB* novo = (TARVB*)malloc(sizeof(TARVB));
  novo->nchaves = 0;
  novo->folha=1;
  novo->filho = (TARVB**)malloc(sizeof(TARVB*)*t*2);
  novo->info = (TARQ**)malloc(sizeof(TARQ*)*((t*2)-1));
  int i;
  for(i = 0; i < ((t*2)-1); i++) novo->info[i] = NULL;
  for(i = 0; i < (t*2); i++) novo->filho[i] = NULL;
  return novo;
}

TARVB *TARVB_Libera(TARVB *a){
  if(a){
    if(!a->folha){
      int i;
      for(i = 0; i <= a->nchaves; i++) TARVB_Libera(a->filho[i]);
    }
    free(a->info);
    free(a->filho);
    free(a);
    return NULL;
  }
}

void imp_rec(TARVB *a, int andar){
  if(a){
    int i,j;
    TARQ *A;
    for(i=0; i<=a->nchaves-1; i++){
      imp_rec(a->filho[i],andar+1);
      for(j=0; j<=andar; j++) printf("\t");
      A = a->info[i];
      printf("%d\n", A->id);
    }
    imp_rec(a->filho[i],andar+1);
  }
}

void TARVB_Imprime(TARVB *a){
  imp_rec(a, 0);
}

TBND *TBND_busca_nome(TBND *tab, char *nome){
  printf("buscando...\n");
  if(!tab){
    printf("tabela vazia\n");
    return tab;
  }
  if (strcmp(tab->nome, nome)) return tab;
  return TBND_busca_nome(tab->prox, nome);
}

TARVB *TARVB_Busca(TARVB* x, int ch){
  if(!x) return NULL;
  int i = 0;
  while(i < x->nchaves && ch > x->info[i]->id) i++;
  if(i < x->nchaves && ch == x->info[i]->id) return x;
  if(x->folha) return NULL;
  return TARVB_Busca(x->filho[i], ch);
}

TARVB *TARVB_Inicializa(){
  return NULL;
}

TARQ *TARQ_aloca(){
  TARQ *novo = (TARQ*)malloc(sizeof(TARQ));
  return novo;
}

int Maior_id(TARVB *T){
  int num;
  if(!T){
    return 0;
  }
  int i = T->nchaves;
  if(!T->folha){
    if(T->filho[i]) 
      return Maior_id(T->filho[i]);
    if(T->filho[i-1])
      return Maior_id(T->filho[i-1]);
  }

  return T->info[i-1]->id;
}

TARVB *Divisao(TARVB *x, int i, TARVB* y, int t){ //S=x ; T=y
  TARVB *z=TARVB_Cria(t);
  y->pai = x;
  z->pai = x;
  z->nchaves= t - 1;
  z->folha = y->folha;
  int j;
  for(j=0;j<t-1;j++) 
    z->info[j] = y->info[j+t];
  if(!y->folha){
    for(j=0;j<t;j++){
      z->filho[j] = y->filho[j+t];
      y->filho[j+t] = NULL;
    }
  }
  y->nchaves = t-1;
  for(j=x->nchaves; j>=i; j--) 
    x->filho[j+1]=x->filho[j];
  x->filho[i] = z;
  for(j=x->nchaves; j>=i; j--) 
    x->info[j] = x->info[j-1];
  x->info[i-1] = y->info[t-1];
  x->nchaves++;
  return x;
}

TARVB *Insere_Nao_Completo(TARVB *x, int k, int t, TARQ *N){ // ARVB = x, k = id, t=chaveMax, N=inode
  int i = x->nchaves-1;
  if(x->folha){
    while((i>=0) && (k<x->info[i]->id)){
      x->info[i+1]= x->info[i];
      i--;
    }
    x->info[i+1] = N;
    N->pai = (int)x->pai;
    x->nchaves++;
    return x; // CASO FOLHA
  }
  while((i>=0) && (k<x->info[i]->id)) i--;
  i++;
  if(x->filho[i]->nchaves == ((2*t)-1)){ 
    x = Divisao(x, (i+1), x->filho[i], t);
    if(k>x->info[i]->id) i++;
  }
  x->filho[i] = Insere_Nao_Completo(x->filho[i], k, t, N);
  return x;
}

TARVB *TARVB_Insere(TARVB *T, int k, int t, TARQ *N){
  if(TARVB_Busca(T,k)) return T;
  if(!T){ // 1CASO
    T=TARVB_Cria(t);
    T->info[0] = N;
    N->pai = (int)T;
    T->nchaves=1;
    return T;
  }
  if(T->nchaves == (2*t)-1){ //CASO NCHAVE CHEIO
    TARVB *S = TARVB_Cria(t);
    S->nchaves=0;
    S->folha = 0;
    S->filho[0] = T;
    S = Divisao(S,1,T,t);
    S = Insere_Nao_Completo(S,k,t,N);
    return S;
  }
  T = Insere_Nao_Completo(T,k,t,N);
  return T;
}

TARVB *TARVB_insere_novo_node(TARVB *T, int t, TBND *tab, char *nome){
  char *entry = malloc(MAX_ENTRY_SZ);
  fflush(stdin);
  fgets(entry, MAX_ENTRY_SZ, stdin);
  if((strlen(entry)>0) && (entry[strlen(entry)-1]=='\n'))
    entry[strlen(entry)-1]= '\0';
  int size_txt = strlen(entry);
  TARQ *ant = NULL;
  TARQ *novo;
  int id;
  for(int i=0; i<size_txt; i+=(CHAR_TXT-1)){
    novo = TARQ_aloca();
    for(int j=0; j<(CHAR_TXT-1); j++){
      if((i+j) < size_txt){
        novo->texto[j] = entry[i+j];
      } else novo->texto[j] = ' ';
    }
    novo->texto[CHAR_TXT-1] = '\0';
    novo->id = Maior_id(T)+1;
    novo->prox_id = -1;
    if(!ant){
      ant = TARQ_aloca();
      ant = novo;
      tab = TBND_insere(tab, novo);
    } else if(ant) 
      ant->prox_id = novo->id;
    printf(".....\n");
    T = TARVB_Insere(T, novo->id, t, novo);
    printf("Adicionado na arvore > id: %d\n", novo->id);
    printf("A info = %s\n", novo->texto);
    
  }
  return T;
}

TARVB *TARVB_Insere_ARQ(TARVB *T, int t, char *arq){
  FILE *fp = fopen(arq, "rb+");
  if(!fp){
    printf("Erro na abertura do arquivo\n");
    exit(1);}
  int pos;
  fseek(fp, 0, SEEK_SET);
  TARQ *novo = TARQ_aloca();
  TARQ *ant;
  while(fread(novo, sizeof(TARQ), 1, fp) != EOF){
    if(!TARVB_Busca(T, novo->id)){
      T = TARVB_Insere(T, novo->id, t, novo);
      ant = novo;
      novo = TARQ_aloca();
    } 
    else printf("Erro no arquivo, Encontrado uma ID repetida. Pulando a insecao da id: %d \n", novo->id);
  }
  fclose(fp);
  return T;
}

void Limpa_Remocao(TARVB *a){
  if(!a) return;
  int i;
  for(i = 0; i <= a->nchaves; i++) a->filho[i] = NULL;
}

