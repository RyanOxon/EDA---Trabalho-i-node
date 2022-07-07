#include "TARVB.h"
#include <string.h>
#include <stdio.h>


void TH_inicializa(TH tab, int n){
  int i;
  for(i = 0; i < n; i++)tab[i] = NULL;
}

TARQ* TH_busca_nome(TH tab, char nome[MAX_ARQ_SZ]){
  int i = 0;
  while(tab[i]){
    if(strcmp(tab[i]->nome, nome))
      i++;
    else break;
  }
  return tab[i];
}

void TH_insere(TH tab, TARQ *N){
  int i=0;
  while(tab[i]) i++;
  tab[i] = (TARQ*)malloc(sizeof(TARQ));
  tab[i] = N;
}

void TH_imprime(TH tab){
  int i=0;
  printf("___________TABELA_INODE___________\n");
  while(tab[i]){
    if(tab[i]->prox_id==NULL)
      printf("[%d] | ID: %d | ID_Proximo: -1 | Nome: %s\n", i, tab[i]->id, tab[i]->prox_id->id, tab[i]->nome);
    else printf("[%d] | ID: %d | ID_Proximo: %d | Nome: %s\n", i, tab[i]->id, tab[i]->prox_id->id, tab[i]->nome);
    i++;
  } 
  printf("__________________________________\n");
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
      for(i = 0; i <= a->nchaves; i++){
       TARVB_Libera(a->filho[i]);
       if(i!= a->nchaves)
        free(a->info[i]);
      }
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

TARVB *TARVB_Busca(TARVB* x, int ch){
  if(!x) return NULL;
  int i = 0;
  while(i < x->nchaves && ch > x->info[i]->id) i++;
  if(i < x->nchaves && ch == x->info[i]->id) return x;
  if(x->folha) return NULL;
  return TARVB_Busca(x->filho[i], ch);
}

TARQ *TARQ_busca(TARVB *x, int ch){
  if(!x || ch == -1) return NULL;
  int i = 0;
  while(i < x->nchaves && ch > x->info[i]->id) i++;
  if(i < x->nchaves && ch == x->info[i]->id) return x->info[i];
  if(x->folha)
   return NULL;
  return TARQ_busca(x->filho[i], ch);
}

TARVB *TARVB_Inicializa(){
  return NULL;
}

TL *TL_init(){
  TL *novo = (TL*)malloc(sizeof(TL));
  novo->prim = NULL;
  return novo;
}

void TL_insere(TL *l, ND *N){
  N->prox = l->prim;
  l->prim = N;
}

TARQ *TARQ_aloca(){
  TARQ *novo = (TARQ*)malloc(sizeof(TARQ));
  return novo;
}

int Maior_id(TARVB *T){
  int num;
  if(!T)
    return 0;
  int i = T->nchaves;
  if(!T->folha)
    if(T->filho[i]) 
      return Maior_id(T->filho[i]);
    if(T->filho[i-1])
      return Maior_id(T->filho[i-1]);

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
  printf(".\n");
  if(TARVB_Busca(T,k)) return T;
  printf(".\n");
  if(!T){ // 1CASO
    T=TARVB_Cria(t);
    T->info[0] = N;
    T->nchaves= 1;
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

TARVB *TARVB_insere_novo_node(TARVB *T, int t, TL *tab, char nome[MAX_ARQ_SZ], char *entry){
  int size_txt = strlen(entry);
  TARQ *ant = NULL;
  TARQ *novo;
  int id;
  for(int i=0; i<size_txt; i+=(CHAR_SZ-1)){
    novo = TARQ_aloca();
    for(int j=0; j<(CHAR_SZ-1); j++){
      if((i+j) < size_txt){
        novo->texto[j] = entry[i+j];
      } else novo->texto[j] = ' ';
    }
    novo->texto[CHAR_SZ-1] = '\0';
    novo->id = Maior_id(T)+1;
    novo->prox_id = NULL;
    strcpy(novo->nome, nome);
    printf(".\n");
    if(!ant)
      TL_insere(tab, novo);
    else if(ant){ 
      ant->prox_id = novo;
      novo->pai = ant;
    }
    ant = novo;
    printf(".\n");
    T = TARVB_Insere(T, novo->id, t, novo);
    printf("Adicionado na arvore > id: %d\n", novo->id);
    printf("Info = %s\n", novo->texto);
    
  }
  return T;
}

void Salva_Node(TARVB *T, TH tab, char *nome){
  char nArq[MAX_ARQ_SZ];
  strcpy(nArq,nome);
  strcat(nArq,".txt");
  int i =0;
  char texto[10];
  while(strcmp(tab[i]->nome, nome)){
      i++;
    if(!tab[i])
      return;
  }
  //char nArq[5] = ".txt";
  //strcat(nome,nArq);
  printf("Preparando para salvar no arquivo %s\n", nArq);
  FILE *fp = fopen(nArq, "w");
  TARQ *node = tab[i];
  while(node){
    strcpy(texto,node->texto);
    fwrite(texto,1,strlen(texto),fp);
    node = TARQ_busca(T, node->prox_id->id);
    printf(".\n");
  }
  fclose(fp);
  printf("Salvo\n");
}

void Limpa_Remocao(TARVB *a){
  if(!a) return;
  int i;
  for(i = 0; i <= a->nchaves; i++) a->filho[i] = NULL;
}
