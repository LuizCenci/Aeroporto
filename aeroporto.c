#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include <time.h>

typedef struct NoFila* PtrNoFila;

typedef struct NoFila{
	int chave;
	int tempo;
	PtrNoFila proximo;
} NoFila;

typedef struct{
	PtrNoFila inicio;
	PtrNoFila fim;
	int qtdElementos;
} FilaDinamica;

void iniciaFilaDinamica(FilaDinamica *f){
	f->inicio = NULL;
	f->fim = NULL;
	f->qtdElementos = 0;
}
bool estaVaziaFilaDinamica(FilaDinamica *f){
	return(f->inicio == NULL);
}

void chegada_aviao(FilaDinamica *prat, int valor){
	srand(time(NULL));
	PtrNoFila aux = malloc(sizeof(NoFila));
	aux->chave = valor;
	aux->tempo = rand() % 120 +200;
	aux->proximo = NULL;
	if(estaVaziaFilaDinamica(prat)){
		prat->inicio = aux;
	}
	else{
		prat->fim->proximo = aux;
	}
	prat->fim = aux;
	prat->qtdElementos++;
}

void saida_aviao(FilaDinamica *prat, int valor){
	PtrNoFila aux = malloc(sizeof(NoFila));
	aux->chave = valor;

	aux->proximo = NULL;
	if(estaVaziaFilaDinamica(prat)){
		prat->inicio = aux;
	}
	else{
		prat->fim->proximo = aux;
	}
	prat->fim = aux;
	prat->qtdElementos++;
}

void removerFilaDinamica(FilaDinamica *prat){
	if(!estaVaziaFilaDinamica(prat)){
		PtrNoFila aux;
		aux = prat->inicio;
		prat->inicio = prat->inicio->proximo;
		free(aux);
		prat->qtdElementos--;
	}
	else{
		printf("Pista Vazia!\n");
	}
}
void ingressa_pista(FilaDinamica *pista, FilaDinamica *prat){
	removerFilaDinamica(pista);
	if(!estaVaziaFilaDinamica(pista)){
		printf("Impossível adicionar aviao. Pista cheia\n");
	}else{
		chegada_aviao(pista, prat->inicio->chave);
		removerFilaDinamica(prat);
	}
}

void imprimirPistadePouso(FilaDinamica *pista){
	printf("Pista de pouso/decolagem[");
	PtrNoFila aux;
	for(aux=pista->inicio;aux!=NULL;aux=aux->proximo){
		printf("%d ", aux->chave);
	}
	printf("]\n");
}

void imprimirPrat(FilaDinamica *prat){
	printf("Fila de pouso/decolagem[");
	PtrNoFila aux;
	for(aux=prat->inicio;aux!=NULL;aux=aux->proximo){
		printf("%d ", aux->chave);
	}
	printf("]\n");
}
int main(){
	
	FilaDinamica pista1;	
	iniciaFilaDinamica(&pista1);
	
	FilaDinamica prat1;
	FilaDinamica prat2;
	FilaDinamica prat3;
	iniciaFilaDinamica(&prat1);
	iniciaFilaDinamica(&prat2);
	
	chegada_aviao(&prat1, 0);
	ingressa_pista(&pista1, &prat1);
	imprimirPistadePouso(&pista1);
	
	chegada_aviao(&prat2, 2);
	ingressa_pista(&pista1, &prat2);
	imprimirPistadePouso(&pista1);
	
	saida_aviao(&prat3, 1);
	ingressa_pista(&pista1, &prat3);
	imprimirPistadePouso(&pista1);
    return 0;
}
