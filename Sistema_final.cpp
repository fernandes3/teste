/****************************************************************** Developer: 3º Período, AED2-2020: Alisson, Matheus e Pedro.******************************************************************************************************/
#include <iostream>
#include <conio.h>
#include <math.h>
#include <locale.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "filas.h"
#include "lo.h"
#include "pilhas.h"
#include "LE.h"	//Lista encadeada simples (substituída pela LDE)
#include "lc.h"
#include "LDE.h"

Ficha fichaPaciente;
Fila filaPaciente;									
NoLDE *LDEpaciente, *auxLDE, *auxTriagem, *auxEspecialidade2;
NoLO *Ordena, *auxLO, *auxLO2;										//Variáveis universais
NodoFila *auxFila;
NoLC *LC,*percorreLC, *auxLC;
FuncionarioEnfermaria func;
No *PilhaRelatorio;
int QtdeAtendimentos,controle; //para a função de porcentagem.
char answerSwitch;
FILE *arquivoLDE, *arquivoLC, *arquivoPilha;

void Cadastro();
void Atendimento(); 		//Declaração de funções.
void Relatorios();
void Exportar();
float Porcentagem(int *x);
 
using namespace std;

int main()
{
	setlocale(LC_ALL,"PORTUGUESE");
	int menu, menu3;
	criarLDE(LDEpaciente);
	criarFila(filaPaciente);
	criarPilha(PilhaRelatorio);
	criarLC(LC);

	arquivoLDE = fopen("arquivoLDE.dat","a+b");
	arquivoLC = fopen("arquivoLC.dat","a+b");
	arquivoPilha = fopen("arquivoPilha.dat","a+b");

	do
	{
		if(arquivoLDE == NULL ||  arquivoLC == NULL || arquivoPilha == NULL)
		{
			printf(" Falha ao carregar o arquivo !\n");	
		}
		else
		{	
			printf(" Arquivos carregados com sucesso !\n");	
		}	
	} while(arquivoLDE == NULL || arquivoLC == NULL || arquivoPilha == NULL);
	
	rewind(arquivoLDE);
	rewind(arquivoLC);
	rewind(arquivoPilha);
	
	while(!feof(arquivoLDE))
	{
		if(fread(&fichaPaciente,sizeof(fichaPaciente),1,arquivoLDE) != NULL)
		{
			inserirNaLDE(LDEpaciente,fichaPaciente,0);
		}	
	}
	
	while(!feof(arquivoLC))
	{
		if(fread(&func,sizeof(func),1,arquivoLC) != NULL)
		{
			inserirNaLC(LC,func,0);
		}
	}
	
	while(!feof(arquivoPilha))
	{
		if(fread(&fichaPaciente,sizeof(fichaPaciente),1,arquivoPilha) != NULL)
		{
			empilhar(PilhaRelatorio,fichaPaciente);
		}
	}
	
	fclose(arquivoLDE);
	fclose(arquivoLC);
	fclose(arquivoPilha);
	
	do
	{
		system("cls");
		controle=1;
	    printf(" ------------------------------------------------ ");
	    printf("\n¦ \t\t Menu Principal \t\t ¦");
	    printf("\n ------------------------------------------------ ");
		printf("\n¦\t\t\t\t\t\t ¦\n¦\t\t\t\t\t\t ¦\n¦\t   { 1 } Cadastros \t\t\t ¦\n¦\t\t\t\t\t\t ¦\n¦\t   { 2 } Atendimento \t\t\t ¦\n¦\t\t\t\t\t\t ¦\n¦\t   { 3 } Relatórios \t\t\t ¦\n¦\t\t\t\t\t\t ¦\n¦\t   { 4 } Manipulação de Arquivo \t ¦\n¦\t\t\t\t\t\t ¦\n¦\t   { 5 } Exit\t\t\t\t ¦\n¦\t\t\t\t\t\t ¦\n¦\t\t\t\t\t\t ¦");
		printf("\n ------------------------------------------------\n OPÇÃO ->  ");
		scanf("%i", &menu);
		switch(menu)
		{
			case 1:
				Cadastro();
				break;
			case 2:
				Atendimento();
				break;
			case 3:
				Relatorios();
				break;
			case 4:
				Exportar();
				break;
			case 5:
				cout << "\n Saindo do sistema.....";
				return 0;
				break;					
			default: 
				printf("\n Opção inválida!");
				break;
		}
		if(controle!=2)
		printf("\n Voltar ao menu principal? ([S]im / [N]ão) \n -> ");

		scanf("%c", &answerSwitch);

	} while (toupper(answerSwitch) != 'N');	
	
	return 0;	
}

/******************************* FUNÇÕES DO MENU *********************************/

void Cadastro()
{
	long int cpfBusca ;
	int menuCadastro;
	char answerCaseOne, answerFila, answerCadastro, answerCaseTwo, answerCase;
	int c = 0, b = 0, d = 0;
	do
	{
		system("cls");
	    printf(" ------------------------------------------------ ");
	    printf("\n¦ \t\t Cadastro \t\t\t ¦");
	    printf("\n ------------------------------------------------ ");
		printf("\n [1] Cadastro de Paciente \n [2] Cadastro de funcionarios \n [3] Exclusão de Cadastro \n {0} Retornar Menu Principal\n  -> ");
		scanf("%i", &menuCadastro);
		switch (menuCadastro)
		{
			case 1 : 
				do
				{
					system("cls");
					printf(" ------------------------------------------------ ");
			    	printf("\n¦ \t Cadastro >> Pacientes \t\t\t ¦");
			    	printf("\n ------------------------------------------------ ");
			    	if(func.RegistoConselho == NULL)
					{	
				    	cout<<"\n É necessário cadastrar pelo menos um funcionário antes de cadastrar pacientes!\n\n ";
						system("pause");
						break;
					}
					cin.sync();
					printf("\n Insira o CPF:\n -> ");
					scanf("%ld", &cpfBusca);
					cin.sync();
					auxLDE = LDEpaciente;
					while(auxLDE!=NULL)
					{
						if(auxLDE->ficha.cpf == cpfBusca)
						{
							printf(" Paciente já possui cadastro! Deseja inseri-lo na fila? ([S]im / [N]ão)\n -> ");
							c=1;
							scanf(" %c",&answerFila);
							break;	
						}
					auxLDE=auxLDE->prox;
					}
					if(c!=1)
					{
						printf("\n Paciente NÃO cadastrado! Deseja cadastrar? ([S]im / [N]ão)\n -> ");
						scanf(" %c",&answerCadastro);
						cin.sync();
						if(toupper(answerCadastro)!= 'N')
						{
							system("cls");
							printf(" ------------------------------------------------ ");
						    printf("\n¦ \t Cadastro >> Pacientes \t\t\t ¦");
						    printf("\n ------------------------------------------------ ");
							printf("\n Nome:\n -> ");
							gets(fichaPaciente.Nome);
							fichaPaciente.cpf = cpfBusca;
							printf(" Idade:\n -> ");
							scanf("%i",&fichaPaciente.idade);
							cin.sync();
							printf(" Sexo ([M]asc/[F]em):\n -> ");
							scanf("%c", &fichaPaciente.Sexo);
							cin.sync();
							printf(" Cidade:\n -> ");
							gets(fichaPaciente.endereco.Cidade);
							cin.sync();
							printf("< Endereço > \n  RUA:\n  -> ");
							gets(fichaPaciente.endereco.Rua);
							printf("  Bairro:\n   -> ");
							gets(fichaPaciente.endereco.Bairro);
							printf("  Número:\n   -> ");
							scanf("%i",&fichaPaciente.endereco.Num);
							cin.sync();
							printf("  Complemento:\n   -> ");
							gets(fichaPaciente.endereco.Complemento);
							printf("  CEP:\n   -> ");
							scanf("%s", &fichaPaciente.endereco.Cep);
							printf("  UF:\n   -> ");
							scanf("%s",fichaPaciente.endereco.Uf);
							printf(" Horário de Entrada (XX:XX):\n -> ");
	                        cin.sync();
	                        scanf("%s",&fichaPaciente.horaEntrada);
	                        cin.sync();
	                        system("cls");
							printf(" ------------------------------------------------ ");
							printf("\n¦ \t Cadastro >> Pacientes \t\t\t ¦");
							printf("\n ------------------------------------------------ "); 
							printf("\n Paciente cadastrado com sucesso!\n");
							inserirNaLDE(LDEpaciente,fichaPaciente, 0);
							b = 1;
							printf("\n Colocar paciente na fila de espera? ([S]im / [N]ão)\n -> ");
							scanf(" %c", &answerFila);
						}
					}
					if(toupper(answerFila) != 'N' && b == 1)
					{
						enfileirar(filaPaciente,fichaPaciente);
					} 
					if (c == 1)
					{
						auxFila = filaPaciente.prim;
						while(auxFila != NULL)
						{
							if(auxFila->ficha.cpf == cpfBusca && toupper(answerFila) != 'N')
							{
								printf("\n Presente na fila!");
								d = 1;
								break;	
							}			
						auxFila = auxFila->prox;
						}
					}
					if (c == 1 && d != 1 && toupper(answerFila) != 'N')
					{
						enfileirar(filaPaciente,fichaPaciente);
					}	
					printf("\n Cadastrar outro Paciente? ([S]im / [N]ão)\n -> ");
					scanf(" %c",&answerCaseOne);
					c = 0;
					b = 0;
					d = 0;
					cin.sync();
				} while(toupper(answerCaseOne) != 'N');	
			break;
			case 2 : 
				do
				{
					system("cls"); 
					cin.sync();
					printf(" ------------------------------------------------ ");
					printf("\n¦ \t Cadastro >> Funcionários \t\t ¦");
					printf("\n ------------------------------------------------ ");
					printf("\n Nome:\n -> ");
					gets(func.NomeEnf);
					cin.sync();
					printf(" Registro Conselho do funcionário:\n -> ");
					scanf("%ld",&func.RegistoConselho);
					cin.sync();
					inserirNaLC(LC, func, 0);
					printf("\n Cadastrar outro funcionário ([S]im / [N]ão)\n -> ");
					scanf(" %c",&answerCaseTwo);
				}while(toupper(answerCaseTwo) != 'N');
			break;
			case 3:
			char answerCaseThree;
				do
				{
					system("cls");
					printf(" ------------------------------------------------ ");
					printf("\n¦ \t\t Remover Cadastro \t\t ¦");
					printf("\n ------------------------------------------------ ");
					long int cpfRemoveLDE;
					printf("\n Informe o CPF do paciente que deseja remover do cadastro:\n -> ");
					scanf("%ld", &cpfRemoveLDE);
					removerDaLDE(LDEpaciente, cpfRemoveLDE);
					printf("\n Remover mais algum cadastro? ([S]im / [N]ão)\n -> ");
					scanf(" %c", &answerCaseThree);
				}while(toupper(answerCaseThree) != 'N');
			break;
			case 0:	
				answerCase = 'N';
				answerSwitch = 'S';
			break;
		}
	}while(toupper(answerCase) != 'N');	
}

void Atendimento()
{
	int menu2;
	char answerSwitch2;
	do
	{
		system("cls");
	    printf(" ------------------------------------------------ ");
	    printf("\n¦ \t\t Atendimento \t\t\t ¦");
	    printf("\n ------------------------------------------------ ");
		printf("\n [1] Triagem \n [2] Especialidade\n {0} Retornar Menu Principal\n -> ");
		scanf("%i", &menu2);
		switch(menu2)
		{	
			case 1:
				criarLO(Ordena);
				auxFila = filaPaciente.prim;
				percorreLC = LC;
				while (auxFila != NULL )
				{
					auxTriagem = LDEpaciente;
					system("cls");
				    printf(" ------------------------------------------------ ");
				    printf("\n¦ \t Atendimento >> Triagem \t\t ¦");
				    printf("\n ------------------------------------------------ ");
					printf("\n Triagem de %s  \n",auxFila->ficha.Nome)   ;
					printf(" Peso:\n -> ");
					scanf("%f", &auxFila->ficha.triagem.Peso);
					printf(" Altura | Cm |: \n -> ");
					scanf("%i", &auxFila->ficha.triagem.Altura);
					printf(" Pressão (00x0):\n -> ");
					scanf("%s", &auxFila->ficha.triagem.Pressao);
					printf(" Temperatura:\n -> ");
					scanf("%f", &auxFila->ficha.triagem.Temperatura);
					cin.sync();
					printf(" Observações Paciente:\n -> ");
					gets(auxFila->ficha.triagem.ObservacoesPaciente);
					printf(" Data (00/00/0000):\n -> ");
					scanf("%s", &auxFila->ficha.triagem.data);
					printf(" Classificação de Risco{1 a 4}:\n -> ");
					scanf("%i", &auxFila->ficha.triagem.ClassificacaoRisco);
					strcpy(auxFila->ficha.triagem.profissionalEnf, percorreLC->funcionarioEnf.NomeEnf);
					auxFila->ficha.triagem.Conselho = percorreLC->funcionarioEnf.RegistoConselho;
					while (auxTriagem != NULL)
					{
						if (auxFila->ficha.cpf == auxTriagem->ficha.cpf)
						{
							auxTriagem->ficha.triagem = auxFila->ficha.triagem;
						}
						auxTriagem = auxTriagem->prox;
					}
					inserirNaLO(Ordena, auxFila->ficha);
					auxFila = auxFila->prox;
					percorreLC = percorreLC->prox;	
				}
				while (!filaVazia(filaPaciente))
				{
					desenfileirar(filaPaciente); 	
				}
				system("cls");	
				printf(" ------------------------------------------------ ");
				printf("\n¦ \t Atendimento >> Triagem \t\t ¦");
				printf("\n ------------------------------------------------ ");
				printf("\n Triagem concluída com sucesso!\n\n ");
				system("pause");
				answerSwitch2 = 'S';
				break;
			case 2: 
				auxLO = Ordena;
				while (auxLO != NULL)
				{
					auxEspecialidade2 = LDEpaciente;
					system("cls");
					controle=1;
					cin.sync();
				    printf(" ------------------------------------------------ ");
				    printf("\n¦ \t Atendimento >> Especialidade \t\t ¦");
				    printf("\n ------------------------------------------------ ");
					printf  ("\n Especialidade de %s ",auxLO->ficha.Nome);
					printf("\n Profissional:\n -> ");
					gets(auxLO->ficha.triagem.atendimento.profissional);
					cin.sync();
					printf(" Anamnese:\n -> ");
					gets(auxLO->ficha.triagem.atendimento.Anamnese);
					printf(" Paciente com falta de AR ou Tosse ([S]im / [N]ão):\n -> ");
					scanf("%c", &auxLO->ficha.triagem.atendimento.FaltaDeAR);
					printf(" Hora saída:(XX:XX)\n -> ");
                    cin.sync();
                    scanf("%s", &auxLO->ficha.triagem.atendimento.horaSaida);
                    cin.sync();
					while (auxEspecialidade2 != NULL)
					{
						if (auxLO->ficha.cpf == auxEspecialidade2->ficha.cpf)
						{
							auxEspecialidade2->ficha.triagem = auxLO->ficha.triagem; 
						}
					auxEspecialidade2 = auxEspecialidade2->prox;
					}
					auxLO = auxLO->prox;
				}
				auxLO2 = Ordena;
				while (auxLO2 != NULL)	// Percorre a LE completa de cadastro e busca cadastros que passaram pelo atendimento completo.
				{
					if(auxLO2->ficha.triagem.ClassificacaoRisco > 0) 
						empilhar(PilhaRelatorio, auxLO2->ficha); //A impressão da pilha estará no menu relatórios.
				auxLO2 = auxLO2->prox;		
				}
				while(!loVazia(Ordena))
				{
					removerDaLO(Ordena, Ordena->ficha);
				}
				system("cls");
				printf(" ------------------------------------------------ ");
				printf("\n¦ \t Atendimento >> Especialidade \t\t ¦");
				printf("\n ------------------------------------------------ ");
				printf("\n Especialidade concluída com sucesso!!!\n\n ");
				system("pause");
				controle=2;
				answerSwitch2 = 'N';
				answerSwitch = 'S';
				break;	
			case 0:
				answerSwitch2 = 'N';
				answerSwitch = 'S';
			break; 
		}
	} while(toupper(answerSwitch2) != 'N');
}
void Relatorios()
{
	system("cls");
	int MenuRelatorios,menuBusca;
	No *PercorrePilha, *PercorrePilha2;
	NoLDE *percorreLDE;
	printf(" ------------------------------------------------ ");
	printf("\n¦ \t\t Relatórios \t\t\t ¦");
	printf("\n ------------------------------------------------ ");
	printf("\n [1] Por Busca \n [2] Quantitativo\n [3] COVID-19 \n {0} Retornar Menu Principal\n -> ");
	scanf("%i", &MenuRelatorios);
	switch(MenuRelatorios)
	{
		case 1:
			cin.sync();
			system("cls");
			printf(" ------------------------------------------------ ");
			printf("\n¦ \t\t Relatórios >> Por Busca \t ¦");
			printf("\n ------------------------------------------------ ");
			printf("\n [1] Por CPF \n [2] Por data \n {0} Retornar Menu Principal\n -> ");
			scanf("%i",&menuBusca);
			if (menuBusca == 1)
			{
				cin.sync();
				PercorrePilha = PilhaRelatorio;
				long int cpfRelatorio = 0;
				int o=1;
				system("cls");
				printf(" ------------------------------------------------ ");
				printf("\n¦ \t Relatórios >> Por Busca >> Por CPF \t ¦");
				printf("\n ------------------------------------------------ ");
				printf("\nInsira o CPF que deseja buscar\n -> ");
				scanf("%ld",&cpfRelatorio);
				system("cls");
				printf(" ------------------------------------------------ ");
				printf("\n¦ \t Relatórios >> Por Busca >> Por CPF \t ¦");
				printf("\n ------------------------------------------------\n ");
				while(PercorrePilha  != NULL)
				{
					if(PercorrePilha->ficha.cpf == cpfRelatorio)
					{
						printf(" >> %iº Atendimento. ", o);
						printf("\n Nome do Paciente \n -> %s",PercorrePilha->ficha.Nome);
						printf("\n CPF \n -> %ld", PercorrePilha->ficha.cpf);
						printf("\n Hora de Entrada \n -> %s",PercorrePilha->ficha.horaEntrada);
						printf("\n Hora de Saída \n -> %s",PercorrePilha->ficha.triagem.atendimento.horaSaida);
						printf("\n Data do atendimento \n -> %s",PercorrePilha->ficha.triagem.data);
						printf("\n Pressão \n -> %s",PercorrePilha->ficha.triagem.Pressao);
						printf("\n Peso \n -> %.2f",PercorrePilha->ficha.triagem.Peso);
						printf("\n Temperatura \n -> %.2f",PercorrePilha->ficha.triagem.Temperatura);
						printf("\n Classificação de risco\n -> %i",PercorrePilha->ficha.triagem.ClassificacaoRisco);
						printf("\n Nome do Enfermeiro(a) \n -> %s",PercorrePilha->ficha.triagem.profissionalEnf);
						printf("\n Número do Conselho \n -> %ld",PercorrePilha->ficha.triagem.Conselho);
						printf("\n Observações \n -> %s",PercorrePilha->ficha.triagem.ObservacoesPaciente);
						printf("\n----------------------------------------------------------------------\n");
						o++;
					}
					PercorrePilha = PercorrePilha->prox;
				}	
				if (PercorrePilha == NULL && o == 1)
				{
					printf("\n Paciente não encontrado!\n\n ");
				}	
				system("pause");
			}
			if (menuBusca == 2)
			{
				cin.sync();
				PercorrePilha2 = PilhaRelatorio;
				char datacomp[11];
				int o = 1;
				system("cls");
				printf(" ------------------------------------------------ ");
				printf("\n¦ \t Relatórios >> Por Busca >> Por Data \t ¦");
				printf("\n ------------------------------------------------ ");
				printf("\n Insira a data que deseja buscar\n -> ");
				gets(datacomp);	
				system("cls");
				printf(" ------------------------------------------------ ");
				printf("\n¦ \t Relatórios >> Por Busca >> Por Data \t ¦");
				printf("\n ------------------------------------------------\n ");
				while(PercorrePilha2  != NULL)
				{	
					if(strcmp(PercorrePilha2->ficha.triagem.data , datacomp)==0)
					{
						printf(" >> %iº Atendimento do dia. ", o);
						printf("\n Nome do Paciente \n -> %s",PercorrePilha2->ficha.Nome);
						printf("\n CPF \n -> %ld", PercorrePilha2->ficha.cpf);
						printf("\n Hora de Entrada \n -> %s",PercorrePilha2->ficha.horaEntrada);
						printf("\n Hora de Saída \n -> %s",PercorrePilha2->ficha.triagem.atendimento.horaSaida);
						printf("\n Data do atendimento \n -> %s",PercorrePilha2->ficha.triagem.data);
						printf("\n Pressão \n -> %s",PercorrePilha2->ficha.triagem.Pressao);
						printf("\n Peso \n -> %.2f",PercorrePilha2->ficha.triagem.Peso);
						printf("\n Temperatura \n -> %.2f",PercorrePilha2->ficha.triagem.Temperatura);
						printf("\n Classificação de risco\n -> %i",PercorrePilha2->ficha.triagem.ClassificacaoRisco);
						printf("\n Nome do Enfermeiro(a) \n -> %s",PercorrePilha2->ficha.triagem.profissionalEnf);
						printf("\n Número do Conselho \n -> %ld",PercorrePilha2->ficha.triagem.Conselho);
						printf("\n Observações \n -> %s",PercorrePilha2->ficha.triagem.ObservacoesPaciente);
						printf("\n----------------------------------------------------------------------\n");
						o++;
					}
					PercorrePilha2 = PercorrePilha2->prox;
				}
					if (PercorrePilha2 == NULL && o == 1)
					{
						printf("Nesta data não houveram consultas!\n\n ");
					}	
				system("pause");
			}
		break;
		case 2:
			int ContaRisco1, ContaRisco2, ContaRisco3, ContaRisco4;
			ContaRisco1 = ContaRisco2 = ContaRisco3 = ContaRisco4 = QtdeAtendimentos = 0;
			int ContaIdadeRN, ContaIdadeCrianca, ContaIdadeJovem, ContaIdadeAdulto, ContaIdadeIdoso;
			ContaIdadeRN = ContaIdadeCrianca = ContaIdadeJovem = ContaIdadeAdulto = ContaIdadeIdoso = 0;
			float IMC; 
			IMC = 0.0;
			int IMC1, IMC2, IMC3, IMC4, IMC5, IMC6, ContaMasc, ContaFem, ContaTemp1, ContaTemp2, ContaTemp3, ContaTemp4, ContaTemp5;
			IMC1 = IMC2 = IMC3 = IMC4 = IMC5 = IMC6 = ContaMasc = ContaFem = ContaTemp1 = ContaTemp2 = ContaTemp3 = ContaTemp4 = ContaTemp5 = 0;
			
			PercorrePilha = PilhaRelatorio;
			while(PercorrePilha != NULL)
			{
				QtdeAtendimentos++;
				
				if(PercorrePilha->ficha.triagem.ClassificacaoRisco == 1)
					ContaRisco1++;
				else if(PercorrePilha->ficha.triagem.ClassificacaoRisco == 2)
					ContaRisco2++;
				else if(PercorrePilha->ficha.triagem.ClassificacaoRisco == 3)
					ContaRisco3++;
				else
					ContaRisco4++;
					
				if(PercorrePilha->ficha.idade == 0)
					ContaIdadeRN++;
				else if(PercorrePilha->ficha.idade > 0 && PercorrePilha->ficha.idade <= 11)
					ContaIdadeCrianca++;
				else if (PercorrePilha->ficha.idade > 11 && PercorrePilha->ficha.idade < 18)
					ContaIdadeJovem++;
				else if (PercorrePilha->ficha.idade >= 18 && PercorrePilha->ficha.idade < 60)
					ContaIdadeAdulto++;
				else
					ContaIdadeIdoso++;				
								
				IMC = (PercorrePilha->ficha.triagem.Peso / pow(PercorrePilha->ficha.triagem.Altura, 2))*10000;
				if(IMC < 18.5)
					IMC1++;
				else if(IMC >= 18.5 && IMC < 25)
					IMC2++;
				else if(IMC >= 25 && IMC < 30)
					IMC3++;
				else if(IMC >= 30 && IMC < 35)
					IMC4++;
				else if(IMC >= 35 && IMC <40)
					IMC5++;
				else
					IMC6++;	
				
				if (toupper(PercorrePilha->ficha.Sexo) == 'M')
					ContaMasc++;
				else
					ContaFem++;	
					
				if(PercorrePilha->ficha.triagem.Temperatura <= 36.0)
					ContaTemp1++;
				else if(PercorrePilha->ficha.triagem.Temperatura > 36.0 && PercorrePilha->ficha.triagem.Temperatura <= 37.5)
					ContaTemp2++;
				else if(PercorrePilha->ficha.triagem.Temperatura > 37.5 && PercorrePilha->ficha.triagem.Temperatura <= 39.5)
					ContaTemp3++;
				else if(PercorrePilha->ficha.triagem.Temperatura > 39.5 && PercorrePilha->ficha.triagem.Temperatura <= 41.0)
					ContaTemp4++;
				else
					ContaTemp5++;					
														
			PercorrePilha = PercorrePilha->prox;
			}
			system("cls");
			printf(" -------------------------------------------------------- ");
			printf("\n¦ \t\t Relatórios >> Quantitativo \t\t ¦");
			printf("\n -------------------------------------------------------- ");
			printf(" \n\t >> Número de atendimentos: %i \n", QtdeAtendimentos);
			printf(" \n\t >> Sexo: \n\n");
				printf("\t\t Masculino: %i (%.1f%) \n \t\t Feminino: %i (%.1f%) \n\n", ContaMasc, Porcentagem(&ContaMasc), ContaFem, Porcentagem(&ContaFem));
			printf(" \n\t >> Variações de Temperatura: \n\n");
				printf("\t\t Hipotermia/Subnormal: %i (%.1f%) \n \t\t Normal: %i (%.1f%)\n \t\t Febril/Subfebril: %i (%.1f%) \n \t\t Febre alta: %i (%.1f%) \n \t\t Hipertermia: %i (%.1f%) \n\n",
				ContaTemp1, Porcentagem(&ContaTemp1), ContaTemp2, Porcentagem(&ContaTemp2), ContaTemp3, Porcentagem(&ContaTemp3), ContaTemp4, Porcentagem(&ContaTemp4), ContaTemp5, Porcentagem(&ContaTemp5));	
			printf(" \n\t >> Classificação de Risco: \n\n");
				printf("\t\t Não Urgente: %i (%.1f%) \n \t\t Pouco Urgente: %i (%.1f%)\n \t\t Urgente: %i (%.1f%) \n \t\t Emergência: %i (%.1f%) \n\n", 
				ContaRisco1, Porcentagem(&ContaRisco1), ContaRisco2, Porcentagem(&ContaRisco2), ContaRisco3, Porcentagem(&ContaRisco3), ContaRisco4, Porcentagem(&ContaRisco4));
			printf(" \n\t >> Faixa etária: \n\n ");
				printf("\t\t Recém-nascido: %i (%.1f%) \n \t\t Criança: %i (%.1f%)\n \t\t Jovem: %i (%.1f%) \n \t\t Adulto: %i (%.1f%)\n \t\t Idoso: %i (%.1f%)  \n\n", 
				ContaIdadeRN, Porcentagem(&ContaIdadeRN), ContaIdadeCrianca, Porcentagem(&ContaIdadeCrianca), ContaIdadeJovem, Porcentagem(&ContaIdadeJovem), ContaIdadeAdulto, Porcentagem(&ContaIdadeAdulto), ContaIdadeIdoso, Porcentagem(&ContaIdadeIdoso));
			printf(" \n\t >> Peso: \n\n");
				printf("\t\t Abaixo do peso: %i (%.1f%) \n \t\t Peso Normal : %i (%.1f%)\n \t\t Excesso de Peso: %i (%.1f%) \n \t\t Obesidade Grau I: %i (%.1f%)\n \t\t Obesidade Grau II: %i (%.1f%)\n \t\t Obesidade Grau III: %i (%.1f%)  \n\n", 
				IMC1, Porcentagem(&IMC1), IMC2, Porcentagem(&IMC2), IMC3, Porcentagem(&IMC3), IMC4, Porcentagem(&IMC4), IMC5, Porcentagem(&IMC5), IMC6, Porcentagem(&IMC6));	
			system("pause");	
			break;
		case 3:
			int QtdeCOVID;
			char listagem;
			QtdeCOVID = QtdeAtendimentos = 0;
			PercorrePilha = PilhaRelatorio;
			while(PercorrePilha != NULL)
			{
				QtdeAtendimentos++;
				if(PercorrePilha->ficha.triagem.Temperatura >= 37.5 && toupper(PercorrePilha->ficha.triagem.atendimento.FaltaDeAR) == 'S')
				{
					QtdeCOVID++;
				}
				PercorrePilha = PercorrePilha->prox;
			}
			system("cls");
			printf(" -------------------------------------------------------- ");
			printf("\n¦ \t\t Relatórios >> COVID-19 \t\t ¦");
			printf("\n -------------------------------------------------------- ");
			printf("\nEsta seção informa os suspeitos de COVID-19 com base nos dados de atendimento.\n");
			printf("Principais sintomas: Febre, Tosse e Falta de ar! \n\n");
			printf(" \n\t >> Suspeitos: %i (%.1f%) \n\n", QtdeCOVID, Porcentagem(&QtdeCOVID));
			printf("\n\nObservação: Trate esses dados com atenção. \nA porcentagem exibida é a relação de suspeitos com o total de atendimentos.\n\n");
			cin.sync();
			printf("\n Deseja listar os suspeitos?(S/N)\n  -> ");
			scanf("%c", &listagem);
			if(listagem == 's'|| listagem == 'S')
			{
				system("cls");
				printf(" -------------------------------------------------------- ");
				printf("\n¦ \t\t Relatórios >> COVID-19 >>Listagem \t ¦");
				printf("\n -------------------------------------------------------- ");
				PercorrePilha = PilhaRelatorio;
				while(PercorrePilha != NULL)
				{
					if(PercorrePilha->ficha.triagem.Temperatura >= 37.5 && toupper(PercorrePilha->ficha.triagem.atendimento.FaltaDeAR) == 'S')
					{
						printf("\n Nome: %s ", PercorrePilha->ficha.Nome);
						printf("\n CPF: %ld ", PercorrePilha->ficha.cpf);
						printf("\n Idade: %i ", PercorrePilha->ficha.idade);
						printf("\n < Endereço > \n  RUA:\n  -> %s ", PercorrePilha->ficha.endereco.Rua);
						printf("\n  Bairro:\n   -> %s ", PercorrePilha->ficha.endereco.Bairro);
						printf("\n  Número:\n   -> %i ", PercorrePilha->ficha.endereco.Num);
						printf("\n  Complemento:\n   -> %s ", PercorrePilha->ficha.endereco.Complemento);
						printf("\n  Cidade:\n   -> %s", PercorrePilha->ficha.endereco.Cidade);
						printf("\n----------------------------------------------------------------------\n");
					}
					PercorrePilha = PercorrePilha->prox;
				}
			}
		cout << "\n";	
		system("pause");
		answerSwitch = 'S';
		break;	
		case 0:
			answerSwitch = 'S';
		break;		
	}
}

void Exportar()
{
	system("cls");
	cin.sync();
	int menu4;
	printf(" ------------------------------------------------ ");
	printf("\n¦ \t\t Arquivo \t\t\t ¦");
	printf("\n ------------------------------------------------ ");
	printf("\n [1] Salvar dados \n [2] Deletar dados\n {0} Retornar Menu Principal\n -> ");
	scanf("%i", &menu4);
	switch(menu4)
	{
		case 1:
			No *invertePilha;
			while(!pilhaVazia(PilhaRelatorio))
			{
				empilhar(invertePilha,desempilhar(PilhaRelatorio));
			}
			arquivoLDE = fopen("arquivoLDE.dat","wb");
			arquivoLC = fopen("arquivoLC.dat","wb");
			arquivoPilha = fopen("arquivoPilha.dat","wb");
			NoLC *gravaLC;
			No *gravaPilha;
			NoLDE *gravaLDE;
			gravaPilha = invertePilha;
			gravaLC = LC;
			gravaLDE = LDEpaciente;
			
			while(gravaLDE != NULL)
			{
				fwrite(&gravaLDE->ficha,sizeof(gravaLDE->ficha),1,arquivoLDE);
				gravaLDE = gravaLDE->prox;
			}
			
			do
			{	
				fwrite(&gravaLC->funcionarioEnf,sizeof(gravaLC->funcionarioEnf),1,arquivoLC);
				gravaLC = gravaLC->prox;
			}while(gravaLC != LC);
			
			while(gravaPilha != NULL)
			{
				fwrite(&gravaPilha->ficha,sizeof(gravaPilha->ficha),1,arquivoPilha);
				gravaPilha = gravaPilha->prox;
			}
			
			fclose(arquivoLDE);
			fclose(arquivoLC);
			fclose(arquivoPilha);
			printf("\n Dados salvo com sucesso!\n ");
			system("pause");
			
			/******** RECARREGAR DADOS ********/
			
			arquivoLDE = fopen("arquivoLDE.dat","a+b");
			arquivoLC = fopen("arquivoLC.dat","a+b");
			arquivoPilha = fopen("arquivoPilha.dat","a+b");
			do
			{
				if(arquivoLDE == NULL ||  arquivoLC == NULL || arquivoPilha == NULL)
				{
					printf(" Falha ao carregar o arquivo !\n");	
				}
				else
				{	
					printf(" Arquivos carregados com sucesso !\n");	
				}	
			} while(arquivoLDE == NULL || arquivoLC == NULL || arquivoPilha == NULL);
			
			rewind(arquivoLDE);
			rewind(arquivoLC);
			rewind(arquivoPilha);
			
			while(!feof(arquivoLDE))
			{
				if(fread(&fichaPaciente,sizeof(fichaPaciente),1,arquivoLDE) != NULL)
				{
					inserirNaLDE(LDEpaciente,fichaPaciente,0);
				}	
			}
			
			while(!feof(arquivoLC))
			{
				if(fread(&func,sizeof(func),1,arquivoLC) != NULL)
				{
					inserirNaLC(LC,func,0);
				}
			}
			
			while(!feof(arquivoPilha))
			{
				if(fread(&fichaPaciente,sizeof(fichaPaciente),1,arquivoPilha) != NULL)
				{
					empilhar(PilhaRelatorio,fichaPaciente);
				}
			}
			fclose(arquivoLDE);
			fclose(arquivoLC);
			fclose(arquivoPilha);
			
			break;
		case 2:
				arquivoLDE = fopen("arquivoLDE.dat","w+b");
				arquivoLC = fopen("arquivoLC.dat","w+b");
				arquivoPilha = fopen("arquivoPilha.dat","w+b");
				fclose(arquivoLDE);
				fclose(arquivoLC);
				fclose(arquivoPilha);
				criarLDE(LDEpaciente);
				criarFila(filaPaciente);
				criarPilha(PilhaRelatorio);
				criarLC(LC);
				func.RegistoConselho = NULL;
				printf("\n Dados deletados com sucesso\n ");
				system("pause");
			break;
		case 0:

			break; 
		default:
				printf("\n Opção inválida\n ");
				system("pause");
	}
}

float Porcentagem(int *x) // calculo porcentagem pro menu relatorio.
{
	float Total;
	Total = QtdeAtendimentos;
	float P;
	P = 0.0;
	if(Total == 0)
		P = 0;
	else	
		P = (*x / Total) * 100;
	return P;
}
/****************************************************************** Developer: 3º Período, AED2-2020: Alisson, Matheus e Pedro.******************************************************************************************************/
