#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
// PtrNoArvore = NoArvore* -> PtrNoArvore
typedef struct NoArvore* PtrNoArvore;
// NoArvore
typedef struct NoArvore {
  int chave; // valor armazenado
//  char* chave;
  PtrNoArvore direita;
  PtrNoArvore esquerda;
} NoArvore;


void iniciaArvoreBinaria(PtrNoArvore *r) {
  (*r) = NULL;
}

bool estaVaziaArvoreBinaria(PtrNoArvore *r) {
  return((*r) == NULL);
}
// ---------------------------------------
// ---------------------------------------
bool inserirArvoreBinaria(PtrNoArvore *no, int valor) {
//bool inserirArvoreBinaria(PtrNoArvore *no, char* valor) {
  // clausulas base (true, false)
  // 1. NULL (ponto de inser??o)
  // Toda vez que achar um NULL ? onde vamos inserir o novo elemento:
  if((*no) == NULL) {
    (*no) = malloc(sizeof(NoArvore));
    (*no)->chave = valor;
//    strcpy((*no)->chave, valor);
    (*no)->direita = NULL;
    (*no)->esquerda = NULL;
    return (true);
  }
  // 2. no que j? possui o valor que eu quero inserir
  if((*no)->chave == valor) return (false); // warning
//  if(strcmp((*no)->chave, valor)==0) return (false); // warning

  // clausula recursiva
  if(valor > (*no)->chave) {
//  if(strcmp(valor,(*no)->chave)==1){
    return(inserirArvoreBinaria(&(*no)->direita, valor));
  } else{
    return(inserirArvoreBinaria(&(*no)->esquerda, valor));
  }
}


void PreOrdemArvoreBinaria(PtrNoArvore *no) {
  if((*no) == NULL) return; //clausula base
  printf("%d ", (*no)->chave);
  PreOrdemArvoreBinaria(&(*no)->esquerda);
  PreOrdemArvoreBinaria(&(*no)->direita);
}

void PreOrdemPrincipal(PtrNoArvore *no) {
  printf("PreOrdem = { ");
  PreOrdemArvoreBinaria(&(*no));
  printf("}\n");
}


void EmOrdemArvoreBinaria(PtrNoArvore *no) {
  if((*no) == NULL) return; //clausula base
  EmOrdemArvoreBinaria(&(*no)->esquerda);
  printf("%d ", (*no)->chave);
  EmOrdemArvoreBinaria(&(*no)->direita);
}

void EmOrdemPrincipal(PtrNoArvore *no) {
  printf("EmOrdem = { ");
  EmOrdemArvoreBinaria(&(*no));
  printf("}\n");
}

bool pesquisaArvoreBinaria(PtrNoArvore *no, int valor) {
  // clausulas base - recursao
  // se o elemento nao existir -> false [ ptr == NULL] [X]
  if((*no) == NULL) return false;
  // se existir o elemento -> true [X]
  if((*no)->chave == valor) return (true);
  // recursiva
  if(valor > (*no)->chave) {
    return(pesquisaArvoreBinaria(&(*no)->direita, valor));
  } else { // <
    return(pesquisaArvoreBinaria(&(*no)->esquerda, valor));
  }
}

PtrNoArvore pegarMaiorElemento(PtrNoArvore *no) {
  // vai ter que andar p direita, at? que ...
  // o ultimo n? aponta para nulo (dir)
  while ((*no)->direita != NULL) {
    (*no) = (*no)->direita;
  }
  // terminou o while, (*no) cont?m o maior elemento
  // esse cara ? quem a gente precisa retornar
  PtrNoArvore ret = (*no);
  (*no) = (*no)->esquerda; // NULL ou n?o NULL
  return(ret);
}

// ---------------------------------------
// ---------------------------------------

bool removerArvoreBinaria(PtrNoArvore *no, int valor) {
  if((*no) == NULL) return false;
  if((*no)->chave == valor) {
    PtrNoArvore rm = (*no);
    // Aqui dentro tem um tratamento maior
    // 4 casos de remo??o
    //  c1: n? que possui filho da direita, mas n?o tem o da esquerda (sub-arvore da esquerda ? nula)
    if((*no)->esquerda == NULL && (*no)->direita != NULL) {
      printf("Debug: caso 1 - sub-arvore esquerda nula\n");
      (*no) = (*no)->direita;
    }
    // c2: n? que ? folha (n?o tem subarvore direita, nem esquerda)
    else if((*no)->direita == NULL && (*no)->esquerda == NULL) {
      printf("Debug: caso 2 - folha\n");
      (*no) = NULL;
    }
    // c3: n? que possui filho da esquerda, mas n?o tem o da direita (sub-arvore direita ? nula)
    else if((*no)->esquerda != NULL && (*no)->direita == NULL) {
      printf("Debug: caso 3 - sub-arvore direita nula\n");
      (*no) = (*no)->esquerda;
    }
    // **c4**: n? que tem ambas as sub-arvores
    else {  // op1: maior da subarvore esquerda
      printf("Debug: caso 4 - existem ambas sub-arvores\n");
      rm = pegarMaiorElemento(&(*no)->esquerda);
      // AQUI (no) = no->esq
      (*no)->chave = rm->chave;
    }
    free(rm);
    return true;
  }
  // recursiva
  if(valor > (*no)->chave) {
    return(removerArvoreBinaria(&(*no)->direita, valor));
  } else { // <
    return(removerArvoreBinaria(&(*no)->esquerda, valor));
  }
}
//--------------------------------------

int internal(PtrNoArvore *no) {
    int cont = 0;
    if ((*no) != NULL) {
        if ((*no)->esquerda != NULL || (*no)->direita != NULL) {
            cont++;
            cont += internal(&(*no)->esquerda);
            cont += internal(&(*no)->direita);
        }
    }
    return cont;
}

void cut(PtrNoArvore *no, int d, int profundidade){
	if((*no) != NULL){
		if (profundidade < d){
			printf("profundidade %d\n", profundidade);
			cut(&(*no)->esquerda, d, profundidade + 1);
			printf("checando arvore esquerda \n");
			cut(&(*no)->direita, d, profundidade + 1);
			printf("checando arvore direita \n");
		}else{
			(*no)->chave = 0;
		}
	}
}



int main(){
	PtrNoArvore raiz;
	iniciaArvoreBinaria(&raiz);
	inserirArvoreBinaria(&raiz, 5);
	inserirArvoreBinaria(&raiz, 4);
	inserirArvoreBinaria(&raiz, 3);
	inserirArvoreBinaria(&raiz, 2);
	inserirArvoreBinaria(&raiz, 8);
	inserirArvoreBinaria(&raiz, 9);
	inserirArvoreBinaria(&raiz, 10);
	inserirArvoreBinaria(&raiz, 8);
	
	
	cut(&raiz, 2, 0);
	PreOrdemPrincipal(&raiz);
	return 0;
}
