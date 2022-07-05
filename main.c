#include "TARVB.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  TARVB *arvore = TARVB_Inicializa();
  TBND *nodeTab = TBND_Inicializa();
  int t;
  char *texto;
  printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
  scanf("%d", &t);
  if(t < 2) t = 2;
  int num = 0, from, to;
  while(num != -1){
    printf("Digite 1 para adicionar um novo texto. 0 para imprimir. e -1 para sair\n");
    scanf("%d", &num);
    if(num == -9){
      //scanf("%d", &from);
      //arvore = TARVB_Retira(arvore, from, t);
      TARVB_Imprime(arvore);
    }
    else if(num == -1){
      printf("\n");
      TARVB_Imprime(arvore);
      TARVB_Libera(arvore);
      return 0;
    }
    else if(!num){
      printf("\n");
      TARVB_Imprime(arvore);
    }
    else if (num == 1) {
      printf("Digite o nome do Node:");
      char nome[32];
      scanf("%s", &nome);
      while(TBND_busca_nome(nodeTab, nome)){
        printf("Nome ja existente, escolha outro nome: (Aperte enter para voltar)");
        scanf("%s", &nome);
        if(strcmp(nome,'\0')) break;
      }
      arvore = TARVB_insere_novo_node(arvore, t, nodeTab, nome); 
    }
    printf("\n\n");
  }
}