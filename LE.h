#include <string.h>
#include <conio.h>
#include <iostream>

struct NoLE
{
	Ficha ficha;
	NoLE *next;
};

void criarLE (NoLE *&X)
{
	X = NULL;
}

NoLE *fim;
int LEVazia (NoLE *&X)
{
	return (X == NULL);
}

void inserirNaLE (NoLE *&X, Ficha Y)
{
	NoLE *novo = new(NoLE);
	novo->ficha = Y;
	novo->next = NULL;
	if(X == NULL)
		{
			X = novo;
		}
	else
		{
			fim->next = novo;
		}
	fim = novo;
}

void imprimirLE (NoLE *&X)
{
	system("cls");
	if (!LEVazia(X))
	{
		NoLE *aux = X;
		while (aux != NULL)
		{
			printf("%s, %ld, %.1f, %.1f, %s -> ", aux->ficha.Nome, aux->ficha.cpf, aux->ficha.triagem.Peso, aux->ficha.triagem.Temperatura, aux->ficha.triagem.atendimento.profissional);
			aux = aux->next;
		}
	}
	else
		printf("Lista encadeada simples vazia!");
	printf("\n\n");
	system("pause");	
}
