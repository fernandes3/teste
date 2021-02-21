#include <string.h>
#include <conio.h>
#include <iostream>


struct NoLO {
	Ficha ficha;
	NoLO *prox;
};

void criarLO (NoLO *&LO) {
	LO = NULL;
}

int loVazia(NoLO *LO) {
	return (LO == NULL);
}

void inserirNaLO (NoLO *&LO, Ficha x) {
	NoLO *aux = new (NoLO);
	aux->ficha = x;
	
	NoLO *vizE = NULL;
	NoLO *vizD = LO;
	
	while ((vizD != NULL) && (x.triagem.ClassificacaoRisco < vizD->ficha.triagem.ClassificacaoRisco)) {
		vizE = vizD;
		vizD = vizD->prox;
	}
	
	if (vizE == NULL) {
		LO = aux;
	}
	else {
		vizE->prox = aux;
	}
	aux->prox = vizD;	
}

void removerDaLO (NoLO *&LO, Ficha ch) {
	
	NoLO *vizE = NULL;
	NoLO *vizD = LO;
	
	
	while ((vizD != NULL) && (ch.triagem.ClassificacaoRisco < vizD->ficha.triagem.ClassificacaoRisco)) {
		vizE = vizD;
		vizD = vizD->prox;
	}
	
	if (vizD != NULL && vizE == NULL) {
		LO = LO->prox;
		delete(vizD);
		printf("%s removido!", ch.Nome);
		return;
	}
	
	else if (vizD != NULL) {	
		NoLO *aux = vizD;
		vizD = vizD->prox;
		delete(aux);
	
		if (vizD != NULL) 
			vizE->prox = vizD;
		
		else {
			if (vizE == NULL) 
				LO = vizD;				
			else
				vizE->prox = vizD;
		}
		printf("%s removido!", ch.Nome);
		return;
	}
	
	printf("%s nao localizado na lista!", ch.Nome);
}

void imprimirLO (NoLO *LO) {
	system("cls");
	if (!loVazia(LO)) {	
		NoLO *aux = LO;	
		while (aux != NULL) {
			printf("%s, %i, %i -> ", aux->ficha.Nome, aux->ficha.cpf, aux->ficha.triagem.ClassificacaoRisco);
			aux = aux->prox;
		}
	}
	else
		printf("Lista vazia!");
	printf("\n\n");
	system("pause");
}
