#include "TARVB.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  TARVB *arvore = TARVB_Inicializa();
  TL *tab = TL_init();
  int t;
  printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
  scanf("%d", &t);
  if(t < 2) t = 2;
  int num = 0, from, to;
  while(1){
    menu();
    scanf("%d", &num);
    printf("\n\n");
    if(num == -9){ // Remover da arvore
      //scanf("%d", &from);
      //arvore = TARVB_Retira(arvore, from, t);
      TARVB_Imprime(arvore);
    }
    else if(num == -1){ //Encerrar
      printf("\n");
      TARVB_Libera(arvore);
      printf("\nPrograma encerrado\n");
      return 0;
    }
    else if (num == 1) { // Insercao de novo nó sem arquivo
      op1();
      scanf("%d", &num);
      if(num == 1){
        printf("\n");
        printf("Digite o nome do Node:\n");
        char nome[MAX_ARQ_SZ];
        scanf("%s", nome);
        printf("\n");
        if(checa_txt(nome))
          printf("formato nao suportado, favor usar arquivos de texto (.txt)");
        else if(TL_busca_nome(tab, nome))
          printf("Erro, nome de node ja existente");
        else 
          arvore = TARVB_insere_teclado(arvore, t, tab, nome);
      }
        else if(num == 2)
          arvore = TARVB_insere_arquivo(arvore, t, tab);
    }
    else if(num == 2){ // imprimir tabela de inodes
      printf("\n");
      TL_imprime(tab);
    }
    else if(num == 3){ // caso 3 => impressao da arvore
      printf("\n");
      TARVB_Imprime(arvore);
    }
    else if(num == 4){
      printf("\n");
      printf("Digite o nome do node a ser salvo\n");
      char snome[MAX_ARQ_SZ];
      scanf("%s", snome);
      printf("\n");
      Salva_Node(arvore, tab, snome);
    }
    else if(num == 0){
      op0();
      scanf("%d", &num);
      printf("\n");
      if(num==1){
        printf("Digite o nome do node que deseja imprimir\n");
        char arq[MAX_ARQ_SZ];
        scanf("%s", arq);
        TARQ_imp_seq(arvore, tab, arq);
      }
      else if(num==2)
        TL_imprime(tab);
      else if(num==3)
        TARVB_Imprime(arvore);
    }
    printf("\n\n");
  }
}