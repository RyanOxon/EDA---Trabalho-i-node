#include "TARVB.h"

void menu(){
  printf("...::MENU DO USUARIO::...\n");
  printf("NUM [-1] > Encerra o programa\n");
  printf("NUM [ 0] > Impressoes\n");
  printf("NUM [ 1] > Adicionar novo inode\n");
  printf("NUM [ 2] > Imprimir tabela de inodes\n");
  printf("NUM [ 3] > Imprimir Arvore Binaria\n");
  printf("NUM [ 4] > Salvar iNodes em arquivos de texto\n");
  printf("NUM [-9] > Remover um inode\n");
  printf(".......:::::::::::.......\n");
}

void op0(){
  printf("...::OP:[0]-Impressoes::...\n");
  printf("NUM [ 1] > Imprimir sequencia de um inode\n");
  printf("NUM [ 2] > Imprimir tabela de inodes\n");
  printf("NUM [ 3] > Imprimir Arvore Binaria\n");
}

void op1(){
  printf("...::OP:[1]-Insercoes::...\n");
  printf("NUM [ 1] > Inserir inode pelo teclado\n");
  printf("NUM [ 2] > Inserir inode por arquivo de texto\n");
}

TARQ* TL_busca_nome(TL *tab, char nome[MAX_ARQ_SZ]){
  int i = 0;
  ND *lista = tab->prim;
  while(lista){
    if(strcmp(lista->nome, nome))
      lista = lista->prox;
    else return lista->info;
  }
  return NULL;
  
}

void TL_imp_rec(ND *tab){
 if(tab->prox){
    TL_imp_rec(tab->prox);
  }
  if(tab->info->prox_id == -1){
      printf("ID: %d | ID_Prox: %d | Nome: %s\n", tab->info->id, tab->info->prox_id, tab->nome);
    }
  else{
    printf("ID: %d | ID_Prox: %d | Nome: %s\n", tab->info->id, tab->info->prox_id, tab->nome);  
  }
}

void TL_imprime(TL *tab){
  int i=0;
  printf("___________TABELA_INODE___________\n");
  TL_imp_rec(tab->prim);
  printf("__________________________________\n");
}

TL *TL_init(){
  TL *novo = (TL*)malloc(sizeof(TL));
  novo->prim = NULL;
  return novo;
}

void TL_insere(TL *l, TARQ *N){
  ND *NO = (ND*)malloc(sizeof(ND));
  NO->info = N;
  strcpy(NO->nome, N->nome);
  NO->prox = l->prim;
  l->prim = NO;
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

TARQ *TARQ_aloca(){
  TARQ *novo = (TARQ*)malloc(sizeof(TARQ));
  return novo;
}

void TARQ_imp(TARVB *a, TARQ *node){
  printf(">ID: %d \n", node->id);
  printf("> Id Anterior: %d \n", node->pai);
  printf("> Id Proximo : %d \n", node->prox_id);
  printf("> Texto contido: \n [%s]\n\n", node->texto);
  if(node->prox_id !=-1){
    TARQ *N = TARQ_busca(a, node->prox_id);
    TARQ_imp(a, N);
  }
}

void TARQ_imp_seq(TARVB *a, TL *tab, char *arq){
  ND *lista = tab->prim;
  while(strcmp(lista->nome, arq)){
    lista = lista->prox;
    if(!lista){
      printf("Nao existe nenhum inode com esse nome, verifique na tabela de inodes\n\n");
      return;
    }
  }
  printf("\n>Nome: %s\n", arq);
  TARQ_imp(a,lista->info);
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
  if(TARVB_Busca(T,k)) return T;
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
      } else novo->texto[j] = '\0';
    }
    novo->texto[CHAR_SZ-1] = '\0';
    novo->id = Maior_id(T)+1;
    novo->prox_id = -1;
    strcpy(novo->nome, nome);
    if(!ant){
      TL_insere(tab, novo);    
      novo->pai = -1;
    }
    else if(ant){ 
      ant->prox_id = novo->id;
      novo->pai = ant->id;
    }
    ant = novo;
    T = TARVB_Insere(T, novo->id, t, novo);
    printf("> id: %d Adicionado na arvore\n", novo->id);
    printf("Texto: %s \n", novo->texto);
  }
  return T;
}

TARVB *TARVB_insere_node(TARVB *T, int t, TL *tab, TARQ *ant, char nome[MAX_ARQ_SZ], char *entry){
  TARQ *novo = TARQ_aloca();
  while(ant->prox_id!=-1) ant = TARQ_busca(T, ant->prox_id);
  strcpy(novo->texto, entry);
  strcpy(novo->nome, nome);
  novo->id = Maior_id(T)+1;
  ant->prox_id = novo->id;
  novo->prox_id = -1;
  novo->pai = ant->id;
  T = TARVB_Insere(T, novo->id, t, novo);
  printf("> id: %d Adicionado na arvore\n", novo->id);
  printf("Texto: %s \n", novo->texto);
  return T;
}

int checa_txt(char *texto){
  char str1[MAX_ARQ_SZ];
  char *str2 = ".txt";
   for(int i = 4; i>0; i--)
    str1[4-i] = texto[strlen(texto)-i];
  str1[4] = '\0';
  return strcmp(str1, str2);
  
}

TARVB *TARVB_insere_arquivo(TARVB *T, int t, TL *tab){
  printf("Digite o nome do arquivo a ser inserido:\n");
  char nArq[MAX_ARQ_SZ];
  scanf("%s", nArq);
  if(checa_txt(nArq)){
    printf("formato de arquivo invalido (.txt)\n");
    return T;
  }
  TARQ *lista = TL_busca_nome(tab, nArq);
  if(lista){
    printf("Ja existe um node com esse nome! Para alterar um node ja existente use a opcao de editar\n");
    return T;
  }
  FILE *fp;
  fp = fopen(nArq, "r");
  char texto[CHAR_SZ];
  printf(".\n");
  while(fread(texto, sizeof(texto)-1, 1, fp)){
    texto[CHAR_SZ-1] = '\0';
    printf(".\n");
    if(!lista){
        printf("Texto: %s\n", texto);
      T = TARVB_insere_novo_node(T, t, tab, nArq, texto);
      lista = TL_busca_nome(tab, nArq);
      printf(".\n");
    } else
      T = TARVB_insere_node(T, t, tab, lista, nArq, texto);
    printf(".\n");
  }
  fclose(fp);
  return T;
}

TARVB *TARVB_insere_teclado(TARVB *T, int t, TL *tab, char nome[MAX_ARQ_SZ]){
  printf("Digite o texto a ser inserido:\n");
  char *entry = malloc(MAX_ENTRY_SZ);
  fflush(stdin);
  fgets(entry, MAX_ENTRY_SZ, stdin);
  if((strlen(entry)>0) && (entry[strlen(entry)-1]=='\n'))
    entry[strlen(entry)-1]= '\0';
  printf("\n");
  T = TARVB_insere_novo_node(T, t, tab, nome, entry);
}

void Salva_Node(TARVB *T, TL *tab, char *nome){
  TARQ *lista = TL_busca_nome(tab, nome);
  if(!lista){
    printf("Nao existe nenhum inode com esse nome, verifique na tabela de inodes\n\n");
    return;
  }
  char nArq[MAX_ARQ_SZ];
  strcpy(nArq,nome);
  char texto[10];
    printf("Preparando para salvar no arquivo %s\n", nArq);
  FILE *fp = fopen(nArq, "w");
  TARQ *node = lista;
  while(node){
    strcpy(texto,node->texto);
    fwrite(texto,1,strlen(texto),fp);
    node = TARQ_busca(T, node->prox_id);
  }
  fclose(fp);
  printf("Salvo\n");
}

void Limpa_Remocao(TARVB *a){
  if(!a) return;
  int i;
  for(i = 0; i <= a->nchaves; i++) a->filho[i] = NULL;
}
