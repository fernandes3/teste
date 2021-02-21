struct Especialidade  //consulta médica e/ou procedimento.
{
	char horaSaida[6];
	char profissional[15]; //Medico: Ortopedia, Dermatologia, Urologia...
	char Anamnese[40]; //Historico do paciente
	char FaltaDeAR;
};


struct Triagem // Usar LO para ordenar prioridade de atendimento.
{
	char Pressao[5];		
	int ClassificacaoRisco, Altura; // {1, 2, 3 e 4}: Do Menor para o maior risco. 
	float Peso, Temperatura;
	char profissionalEnf[30], data[11];
	long int Conselho;
	Especialidade atendimento;
	char ObservacoesPaciente[30]; //Alergico, Fator de risco (diabetico, hipertenso).
			
};

struct Endereco
{
	char Rua[20];
	int Num;
	char Bairro[15], Complemento[10];
	char Cidade[20], Uf[2], Cep[8];
};

struct Ficha //Fila
{
	char Nome[20], Sexo;
	long int cpf; // 6 primeiros digitos.		
	int idade;
	Endereco endereco;
	char horaEntrada[6];
	Triagem triagem;
};

struct FuncionarioEnfermaria //Lista Circular
{
	char NomeEnf[30];
	long int RegistoConselho;
};




