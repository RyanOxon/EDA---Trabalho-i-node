#include "TARVB.h"

void menu(){
  printf("...::MENU DO USUARIO::...\n");
  printf("NUM [-1] > Encerra o programa\n");
  printf("NUM [ 0] > Impressoes\n"); //feito
  printf("NUM [ 1] > Insercoes de nodes novos\n"); //feito
  printf("NUM [ 2] > Edicao dos nodes\n");
  printf("NUM [ 3] > Salvar iNodes em arquivos de texto\n");
  printf("NUM [ 4] > Buscar informacao dentro de um node\n");
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

void op2(){
  printf("...::OP:[2]- Edicao::...\n");
  printf("NUM [ 1] > Remover uma parte de um node\n");
  printf("NUM [ 2] > Inserir uma nova parte em um node\n");
  printf("NUM [ 3] > Remover um arquivo por completo\n");
  printf("NUM [ 4] > Remover um id da arvore\n");
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
  ND* node = tab->prim;
  if(node)
    TL_imp_rec(tab->prim);
  else
    printf("\n\n");
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

void TL_deleta_id(TL *tab, int id ){
  printf("preparando para deletar o node\n");
  ND *ant;
  ND *atual = tab->prim;
  while(atual){
    if(atual->info->id != id){
      ant = atual;
      atual = atual->prox;
    } else break;
  }
  if(!ant)
    tab->prim = atual->prox;
  else
    ant->prox = atual->prox;
  free(atual);
}

void TL_deleta(TL *tab, char nArq[MAX_ARQ_SZ]){
  printf("preparando para deletar o node\n");
  ND *ant = NULL;
  ND *atual = tab->prim;
  while(atual){
    printf(".\n");
    if(strcmp(atual->nome, nArq)){
      printf("..\n");
      ant = atual;
      atual = atual->prox;
    } else break;
  }
  if(!ant){
    printf("...\n");
    tab->prim = atual->prox;
  }
  if(ant) {
    printf("....\n");
    ant->prox = atual->prox;
  }
  free(atual);
}

ND *TL_busca_id(TL *tab, int ch){
  ND *atual = tab->prim;
  while(atual){
    if(atual->info->id != ch)
      atual = atual->prox;
    else return atual;
  }
  return NULL;
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
  for(int i=0; i<size_txt; i+=(CHAR_SZ)){
    novo = TARQ_aloca();
    for(int j=0; j<(CHAR_SZ); j++){
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

TARVB *TARVB_insere_meio(TARVB *T, int t, TL *tab){
  printf("Digite o nome do arquivo a ser editado:\n");
  char nArq[MAX_ARQ_SZ];
  scanf("%s", nArq);
  TARQ *node = TL_busca_nome(tab, nArq);
  TARQ *ant;
  if(!node){
    printf("Nenhum node com esse nome \n");
    return T;
  }
  printf("Digite a id aonde ira ser feita a insercao\n");
  int ch , pos;
  scanf("%d", &ch);
  printf("Inserir antes ou depois ( Digite [0] para antes, [1] para depois )\n");
  scanf("%d", &pos);
  while((node->id!=ch)&&(node)){ 
    ant = node;
    node = TARQ_busca(T, node->prox_id);
  } if(!node){
    printf("Id inexistente na sequencia do node informado \n");
    return T;
  }
  printf("Digite o texto a ser inserido:\n");
  char *entry = malloc(MAX_ENTRY_SZ);
  fflush(stdin);
  fgets(entry, MAX_ENTRY_SZ, stdin);
  if((strlen(entry)>0) && (entry[strlen(entry)-1]=='\n'))
    entry[strlen(entry)-1]= '\0';
  printf("\n");
  if(pos){ // inserindo depois do id
    ant = node;
    node = TARQ_busca(T, node->prox_id);
  }
  TARQ *novo = TARQ_aloca();
  strcpy(novo->texto, entry);
  strcpy(novo->nome, nArq);
  novo->id = Maior_id(T)+1;
  ant->prox_id = novo->id;
  novo->pai = ant->id;
  novo->prox_id = -1;
  if(node){
    novo->prox_id = node->id;
    node->pai = novo->id;
  }
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

int Busca_info_node(TARVB *T, TL *tab, char nome[MAX_ARQ_SZ], char text[MAX_ENTRY_SZ]){
  TARQ *node = TL_busca_nome(tab, nome);
  while(strcmp(node->texto, text)){
    node = TARQ_busca(T, node->prox_id);
    if(!node) return 0;
  }
  return 1;
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
  char texto[CHAR_SZ+1];
  printf(".\n");
  while(fgets(texto,CHAR_SZ,fp)){
    texto[strlen(texto)+1] = '\0';
    printf(".\n");
    if(!lista){
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

TARVB* remover(TARVB* arv, int ch, int t, TL *tab){
  if(!arv) return arv;
  int i;
  TARQ *aux;
  printf("Removendo %d...\n", ch);
  for(i = 0; i<arv->nchaves && arv->info[i]->id < ch; i++);
  if(i < arv->nchaves && ch == arv->info[i]->id){ //CASOS 1, 2A, 2B e 2C
    if(arv->folha){ //CASO 1
      printf("\nCASO 1\n");
      int j;
      aux = arv->info[i];
      for(j=i; j<arv->nchaves-1;j++)
        arv->info[j] = arv->info[j+1];
      TARQ *ant = TARQ_busca(arv, aux->pai);
      TARQ *prox = TARQ_busca(arv, aux->prox_id);
      printf("\nArrumando o inode\n");
      if(!ant && !prox){
        printf("\nInode vazio! deletando\n");
        TL_deleta(tab, aux->nome);
      } else if(!ant){
        ND *inode = TL_busca_id(tab, ch);
        inode->info = prox;
        prox->pai=-1;
      } else if(!prox){
        ant->prox_id = -1;
      } else {
        ant->prox_id = prox->id;
        prox->pai = ant->id;
      }
      printf("\nInode arrumado\n");
      free(aux);
      arv->nchaves--;
      if(!arv->nchaves){ //ultima revisao: 04/2020
        TARVB_Libera(arv);
        arv = NULL;
      }
      return arv;      
    }
    if(!arv->folha && arv->filho[i]->nchaves >= t){ //CASO 2A
      printf("\nCASO 2A\n");
      TARVB *y = arv->filho[i];  //Encontrar o predecessor k' de k na árvore com raiz em y
      while(!y->folha) y = y->filho[y->nchaves];
      TARQ *temp = y->info[y->nchaves-1];
      arv->filho[i] = remover(arv->filho[i], temp->id, t, tab); 
      //Eliminar recursivamente K e substitua K por K' em x
      arv->info[i] = temp;
      return arv;
    }
    if(!arv->folha && arv->filho[i+1]->nchaves >= t){ //CASO 2B
      printf("\nCASO 2B\n");
      TARVB *y = arv->filho[i+1];  //Encontrar o sucessor k' de k na árvore com raiz em y
      while(!y->folha) y = y->filho[0];
      TARQ* temp = y->info[0];
      y = remover(arv->filho[i+1], temp->id, t, tab); //Eliminar recursivamente K e substitua K por K' em x
      arv->info[i] = temp;
      return arv;
    }
    if(!arv->folha && arv->filho[i+1]->nchaves == t-1 && arv->filho[i]->nchaves == t-1){ //CASO 2C
      printf("\nCASO 2C\n");
      TARVB *y = arv->filho[i];
      TARVB *z = arv->filho[i+1];
      y->info[y->nchaves] = TARQ_busca(arv, ch);          //colocar ch ao final de filho[i]
      int j;
      for(j=0; j<t-1; j++)                //juntar chave[i+1] com chave[i]
        y->info[t+j] = z->info[j];
      for(j=0; j<=t; j++){                //juntar filho[i+1] com filho[i]
        y->filho[t+j] = z->filho[j];
        z->filho[j] = NULL; //ultima revisao: 04/2020
      }
      //TARVB_Libera(z);
      y->nchaves = 2*t-1;
      for(j=i; j < arv->nchaves-1; j++)   //remover ch de arv
        arv->info[j] = arv->info[j+1];
      for(j=i+1; j < arv->nchaves; j++)  
        arv->filho[j] = arv->filho[j+1]; //remover ponteiro para filho[i+1]
      //Limpa_Remocao(arv->filho[j]);
      //TARVB_Libera(arv->filho[j]);
      arv->filho[j] = NULL;
      arv->nchaves--;
      if(!arv->nchaves){ //ultima revisao: 04/2020
        TARVB *temp = arv;
        arv = arv->filho[0];
        temp->filho[0] = NULL;
        TARVB_Libera(temp);
        arv = remover(arv, ch, t, tab);
      }
      else arv->filho[i] = remover(arv->filho[i], ch, t, tab);
      return arv;   
    }   
  }

  TARVB *y = arv->filho[i], *z = NULL;
  if (y->nchaves == t-1){ //CASOS 3A e 3B
    if((i < arv->nchaves) && (arv->filho[i+1]->nchaves >=t)){ //CASO 3A
      printf("\nCASO 3A: i menor que nchaves\n");
      z = arv->filho[i+1];
      y->info[t-1] = arv->info[i];   //dar a y a chave i da arv
      y->nchaves++;
      arv->info[i] = z->info[0];     //dar a arv uma chave de z
      int j;
      for(j=0; j < z->nchaves-1; j++)  //ajustar chaves de z
        z->info[j] = z->info[j+1];
      y->filho[y->nchaves] = z->filho[0]; //enviar ponteiro menor de z para o novo elemento em y
      for(j=0; j < z->nchaves; j++)       //ajustar filhos de z
        z->filho[j] = z->filho[j+1];
      z->nchaves--;
      arv->filho[i] = remover(arv->filho[i], ch, t, tab);
      return arv;
    }
    if((i > 0) && (!z) && (arv->filho[i-1]->nchaves >=t)){ //CASO 3A
      printf("\nCASO 3A: i igual a nchaves\n");
      z = arv->filho[i-1];
      int j;
      for(j = y->nchaves; j>0; j--)               //encaixar lugar da nova chave
        y->info[j] = y->info[j-1];
      for(j = y->nchaves+1; j>0; j--)             //encaixar lugar dos filhos da nova chave
        y->filho[j] = y->filho[j-1];
      y->info[0] = arv->info[i-1];              //dar a y a chave i da arv
      y->nchaves++;
      arv->info[i-1] = z->info[z->nchaves-1];   //dar a arv uma chave de z
      y->filho[0] = z->filho[z->nchaves];         //enviar ponteiro de z para o novo elemento em y
      z->nchaves--;
      arv->filho[i] = remover(y, ch, t, tab);
      return arv;
    }
    if(!z){ //CASO 3B
      if(i < arv->nchaves && arv->filho[i+1]->nchaves == t-1){
        printf("\nCASO 3B: i menor que nchaves\n");
        z = arv->filho[i+1];
        y->info[t-1] = arv->info[i];     //pegar chave [i] e coloca ao final de filho[i]
        y->nchaves++;
        int j;
        for(j=0; j < t-1; j++){
          y->info[t+j] = z->info[j];     //passar filho[i+1] para filho[i]
          y->nchaves++;
        }
        if(!y->folha){
          for(j=0; j<t; j++){
            y->filho[t+j] = z->filho[j];
            z->filho[j] = NULL; //ultima revisao: 04/2020
          }
          TARVB_Libera(z);
        }
        for(j=i; j < arv->nchaves-1; j++){ //limpar referências de i
          arv->info[j] = arv->info[j+1];
          arv->filho[j+1] = arv->filho[j+2];
        }
        arv->filho[arv->nchaves] = NULL;
        arv->nchaves--;
        if(!arv->nchaves){ //ultima revisao: 04/2020
          TARVB *temp = arv;
          arv = arv->filho[0];
          temp->filho[0] = NULL;
          TARVB_Libera(temp);
        }
        arv = remover(arv, ch, t, tab);
        return arv;
      }
      if((i > 0) && (arv->filho[i-1]->nchaves == t-1)){ 
        printf("\nCASO 3B: i igual a nchaves\n");
        z = arv->filho[i-1];
        if(i == arv->nchaves)
          z->info[t-1] = arv->info[i-1]; //pegar chave[i] e poe ao final de filho[i-1]
        else
          z->info[t-1] = arv->info[i];   //pegar chave [i] e poe ao final de filho[i-1]
        z->nchaves++;
        int j;
        for(j=0; j < t-1; j++){
          z->info[t+j] = y->info[j];     //passar filho[i+1] para filho[i]
          z->nchaves++;
        }
        if(!z->folha){
          for(j=0; j<t; j++){
            z->filho[t+j] = y->filho[j];
            y->filho[j] = NULL; //ultima revisao: 04/2020
          }
          TARVB_Libera(y);
        }
        arv->filho[arv->nchaves] = NULL;
        arv->nchaves--;
        if(!arv->nchaves){ //ultima revisao: 04/2020
          TARVB *temp = arv;
          arv = arv->filho[0];
          temp->filho[0] = NULL;
          TARVB_Libera(temp);
        }
        else arv->filho[i-1] = z;
        arv = remover(arv, ch, t, tab);
        return arv;
      }
    }
  }  
  arv->filho[i] = remover(arv->filho[i], ch, t, tab);
  return arv;
}

TARVB* TARVB_Retira(TARVB* arv, int k, int t,TL *tab){
  if(!arv || !TARVB_Busca(arv, k)) return arv;
  return remover(arv, k, t, tab);
}

TARVB *Recorta_node(TARVB *T, int t, TL *tab, int id){
  printf("Digite o texto a ser recortado:\n");
  char *entry = malloc(MAX_ENTRY_SZ);
  fflush(stdin);
  fgets(entry, MAX_ENTRY_SZ, stdin);
  if((strlen(entry)>0) && (entry[strlen(entry)-1]=='\n'))
    entry[strlen(entry)-1]= '\0';
  printf("\n");
  if(strlen(entry)>=CHAR_SZ){
    printf("Texto informado maior que a capacidade do no\n");
    return T;
  }
  TARQ *node = TARQ_busca(T, id);
  if(!node){
    printf("Id inexistente\n");
    return T;
  }
  char comp[strlen(entry)+1];
  int tam = strlen(entry);
  int i, l = 0;
  for(i = 0;i<tam;i++){
    comp[i]= node->texto[i];
  }
  while(strcmp(comp,entry)){
    l++;
    for(int j=0;j<tam;j++){
      comp[j] = node->texto[j+l];
    }
    i++;
    if(i>strlen(node->texto)){
      printf("texto inexistente na reparticao informada\n");
      return T;
    }
  }
  for(int k = 0; k<tam; k++){
    if((l+tam+k) >= CHAR_SZ){
      node->texto[l+k]= '\0';
    }
    node->texto[l+k] = node->texto[(l+tam+k)];
  }
  if(strlen(node->texto)== 0){
    printf("Texto da reparticao zerado, reparticao sera removida\n");
    T = TARVB_Retira(T, id, t, tab);
    return T;
  }
  printf("Recorte realizado, texto restante na reparticao: %s\n", node->texto);
  return T;
}

TARVB *TARVB_remove_rec(TARVB *T, int t, TARQ *node, TL *tab){
  if(node->prox_id != -1){
    TARQ *prox = TARQ_busca(T, node->prox_id);
    T = TARVB_Retira(T, node->id, t, tab);
    T = TARVB_remove_rec(T, t, prox, tab);
  }
  T = TARVB_Retira(T, node->id, t, tab);
  return T;
}

TARVB *TARVB_remove_completo(TARVB *T, int t, TL *tab){
  printf("Digite o nome do arquivo a ser Removido:\n");
  char nArq[MAX_ARQ_SZ];
  scanf("%s", nArq);
  printf("\n");
        if(checa_txt(nArq))
          printf("formato nao suportado, favor usar arquivos de texto (.txt)");
  TARQ *node = TL_busca_nome(tab, nArq);
  TARQ *ant;
  if(!node){
    printf("Nenhum node com esse nome \n");
    return T;
  }
  T = TARVB_remove_rec(T, t, node, tab);
  return T;
}
