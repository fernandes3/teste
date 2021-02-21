#include <iostream>
#include <conio.h>
#include <string.h>

struct NoLDE
{
	Ficha ficha;
	NoLDE *prox;
	NoLDE *ant;
};

void criarLDE(NoLDE *&LDE)
{
	LDE = NULL;
}

int LDEvazia(NoLDE *LDE)
{
	return (LDE == NULL);
}

void inserirNaLDE(NoLDE *&LDE, Ficha X, int inicio)
{
	NoLDE *novo = new(NoLDE);
	novo->ficha = X;
	if(LDEvazia(LDE))
	{
		LDE = novo;
		novo->ant = NULL; 
		novo->prox = NULL;
	}
	else if(inicio == 1)
	{
		LDE->ant = novo;
		novo->prox = LDE;
		novo->ant = NULL;
		LDE = novo;
	}		
	else	
	{
		NoLDE *ult = LDE;
		while(ult->prox != NULL)
		{
			ult = ult->prox;
		}
		ult->prox = novo;
		novo->ant = ult;
		novo->prox = NULL;
	}
}

long int removerDaLDE(NoLDE *&LDE, long int X)
{
	NoLDE *aux = LDE;
	while(aux != NULL)
	{
		if(aux->ficha.cpf == X)
		{
			break;
		}
	aux = aux->prox;	
	}	
	if(aux == NULL)
	{
		printf("\nNão consta na lista!\n");
		//system("pause");
	}
	else
	{
		if(aux == LDE)
		{
			LDE->ant = NULL;
			LDE = LDE->prox;
			printf("%s removido da LDE!\n", aux->ficha.Nome);
			system("pause");	
		}
		else
		{
			aux->ant->prox = aux->prox;
			if(aux->prox != NULL)
				aux->prox->ant = aux->ant;
			printf("%s removido da LDE!\n", aux->ficha.Nome);	
			system("pause");	
		}
	}
	delete(aux);
	return X;
}

void imprimirLDE(NoLDE *LDE)
{
	system("cls");
	if(!LDEvazia(LDE))
	{
		NoLDE *imprime = LDE;
		while(imprime != NULL)
		{
			printf("%s, %i, %s, %s <=> ", imprime->ficha.Nome, imprime->ficha.triagem.ClassificacaoRisco, imprime->ficha.triagem.profissionalEnf, imprime->ficha.triagem.atendimento.profissional);
			imprime = imprime->prox;	
		}	
	}
	else
		printf("LDE vazia!");	
	printf("\n\n");
	system("pause");	
}
