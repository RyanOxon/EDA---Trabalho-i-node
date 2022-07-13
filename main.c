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
    if(num == -1){ //Encerrar
      printf("\n");
      TARVB_Libera(arvore);
      printf("\nPrograma encerrado\n");
      return 0;
    }
    else if(num == 0){
      op0();
      scanf("%d", &num);
      printf("\n");
      if(num==1){
        printf("Digite o nome do node que deseja imprimir\n");
        char arq[MAX_ARQ_SZ];
        scanf("%s", arq);
        if(checa_txt(arq))
          printf("formato nao suportado, favor usar arquivos de texto (.txt)");
        else
          TARQ_imp_seq(arvore, tab, arq);
      }
      else if(num==2)
        TL_imprime(tab);
      else if(num==3)
        TARVB_Imprime(arvore);
    }
    else if (num == 1) {
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
    else if(num == 2){
      op2();
      scanf("%d", &num);
      printf("\n");
      if(num == 1){
        printf("Digite o id do node:\n");
        int n;
        scanf("%d", &n);
        arvore = Recorta_node(arvore, t, tab, n);
      }
      else if(num == 2){
        arvore = TARVB_insere_meio(arvore, t,tab);
      } 
      else if(num == 3){
        arvore = TARVB_remove_completo(arvore, t, tab);
      }
      else if(num==4){
        printf("Digite o id do node:\n");
        int n;
        scanf("%d", &n);
        arvore = TARVB_Retira(arvore, n, t, tab);
      }
    }
    else if(num == 3){
      printf("\n");
      printf("Digite o nome do node a ser salvo\n");
      char snome[MAX_ARQ_SZ];
      scanf("%s", snome);
      printf("\n");
      Salva_Node(arvore, tab, snome);
    }
    else if(num == 4){
      printf("Digite o nome do Node:\n");
      char nome[MAX_ARQ_SZ];
      scanf("%s", nome);
      printf("\n");
      printf("Digite o texto a ser Buscado:\n");
      char text[MAX_ENTRY_SZ];
      scanf("%s", text);
      if(checa_txt(nome))
        printf("formato nao suportado, favor usar arquivos de texto (.txt)");
      else if(strlen(text)>CHAR_SZ)
        printf("O texto informado e maior do que permitido na node\n");
      else if(Busca_info_node(arvore, tab, nome, text))
        printf(" A info: %s esta contida no node: %s \n", text, nome);
      else
        printf("Nao foi possivel encontrar a info dentro deste node\n");
    }
    printf("\n\n");
  }
}