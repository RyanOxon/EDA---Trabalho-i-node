#include "TARVB.h"

int main(int argc, char *argv[]){
  TARVB *arvore = TARVB_Inicializa();
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
      arvore = TARVB_insere_nodes(arvore, t);
      //scanf ( "\n%[^\n]", texto);
      //printf(texto);
      //arvore = TARVB_insere_manual(arvore, t, texto);
      //printf("\n> id: %d \n", arvore->info[0]->id); 
    }
    printf("\n\n");
  }
}