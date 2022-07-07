#include "TARVB.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  TARVB *arvore = TARVB_Inicializa();
  TL *tab = TL_init();
  TH_inicializa(tab, TAB_SZ);
  int t;
  printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
  scanf("%d", &t);
  if(t < 2) t = 2;
  int num = 0, from, to;
  while(num != -1){
    printf("...::MENU DO USUARIO::...\n");
    printf("NUM [-1] > Encerra o programa\n");
    printf("NUM [ 1] > Adicionar novo inode com o teclado\n");
    printf("NUM [ 2] > Imprimir tabela de inodes\n");
    printf("NUM [ 3] > Imprimir Arvore Binaria\n");
    printf("NUM [ 4] > Salvar iNodes em arquivos de texto\n");    
    printf("NUM [-9] > Remover um inode\n");
    printf(".......:::::::::::.......\n");
    scanf("%d", &num);
    printf("\n\n\n\n");
    if(num == -9){ // Remover da arvore
      //scanf("%d", &from);
      //arvore = TARVB_Retira(arvore, from, t);
      TARVB_Imprime(arvore);
    }
    else if(num == -1){ //Encerrar
      printf("\n");
      TARVB_Imprime(arvore);
      TARVB_Libera(arvore);
      printf("\nPrograma encerrado\n");
      return 0;
    }
    else if(num == 4){
      printf("\n");
      printf("Digite o nome do node a ser salvo\n");
      char snome[MAX_ARQ_SZ];
      scanf("%s", snome);
      printf("\n");
      if(TH_busca_nome(tab, snome)){
        printf("nchaves = %d\n", arvore->nchaves);
        Salva_Node(arvore, tab, snome);
      } else printf("Nao existe nenhum inode com esse nome, verifique na tabela de inodes\n\n");*/
    }
    else if(num == 3){ // caso 3 => impressao da arvore
      printf("\n");
      TARVB_Imprime(arvore);
    }
    else if (num == 1) { // Insercao de novo nó sem arquivo
      printf("Digite o nome do Node:\n");
      char nome[MAX_ARQ_SZ];
      scanf("%s", nome);
      printf("\n");
      if(TH_busca_nome(tab, nome))
        printf("Erro, nome de node ja existente");
      else {
        printf("Digite o texto a ser inserido:\n");
        char *entry = malloc(MAX_ENTRY_SZ);
        fflush(stdin);
        fgets(entry, MAX_ENTRY_SZ, stdin);
        if((strlen(entry)>0) && (entry[strlen(entry)-1]=='\n'))
          entry[strlen(entry)-1]= '\0';
        printf("\n");
        arvore = TARVB_insere_novo_node(arvore, t, tab, nome, entry);
      }
    }
    else if(num == 2){ // imprimir tabela de inodes
      printf("\n");
      TH_imprime(tab);
    }
    printf("\n\n\n\n");
  }
}