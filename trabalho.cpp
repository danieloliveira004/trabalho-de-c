#include <conio2.h>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

//____________________________________ CONSTANTES ____________________________________
#define XV 15
#define XL 40
#define XXX 30

//____________________________________ DECLARACOES DAS STRUCTS ____________________________________
struct TpData {
	int dia, mes, ano;
};

struct TpPessoa{
	char cpf[XV], nome[XL], endereco[XXX], cidade[XL], estado[3], email[XL], status;
};
struct TpCidade{
	int codCidade;
	char nomeCidade[XL], estCidade[2], status;
};
struct TpVoo{
	int codVoo, codCidadeOrigem, codCidadeDestino, nrLugares, QtdeLugarVendido;
	TpData dataVoo;
	char status;
};
struct TpPassagem{
	int poltrona, nrPassagem, codVoo;
	TpData dataCompra;
	char cpf[XV], status;
};

//____________________________________ FUN��ES ____________________________________
void RotinaCriarArq(void) {
	FILE *Ptr;
	int i;
	char arq[4][30] = {"pessoas.dat", "cidades.dat", "voos.dat", "passagens.dat"};
	for(i=0; i<4; i++) {
		Ptr = fopen(arq[i], "ab");
		fclose(Ptr);
	}
}

// VALIDAÇÕES
int validarData(TpData data);

void tabelaASCII(void);
void titulo(char title[]);
void opcoesMenu(int posic, char texto[]);
int escolherOpcao(int itens);
void limparOpcoes(void);
void mensagem(char msg[], int status);
void estruturaBase(void);
void limparTela(void);
int continuar(int y);
void linha(int y, int color);
void limparLinha(int y);
void irCampo(int posic[2]);
void limparCampos(int qtd, int posic[][2]);
void limparCampoUnico(int posic[2]);
int confirmar(int y);
//int escolhaPoltrona(tpVoo tabVoos[TFV], int TLV, tpPassagem tabPassagens[TFPG], int TLPG, int codVoo);
void limparParteDaTela(int x1, int y1, int x2, int y2);


//____________________________________ FUNCOES DE INSERCAO DIRETA ____________________________________
void InsercaoDiretaPessoa(FILE *Ptr)
{
	TpPessoa regA, regB;
	int i;
	i = ftell(Ptr) / sizeof(TpPessoa) - 1;
	if(i > 0) {
		fseek(Ptr, sizeof(TpPessoa) * i, SEEK_SET);
		fread(&regA, sizeof(TpPessoa), 1, Ptr);
		fseek(Ptr, sizeof(TpPessoa) * (i-1), SEEK_SET);
		fread(&regB, sizeof(TpPessoa), 1, Ptr);
		while(i > 0 && stricmp(regA.nome, regB.nome) < 0) {
			fseek(Ptr, sizeof(TpPessoa) * i, SEEK_SET);
			fwrite(&regB, sizeof(TpPessoa), 1, Ptr);
			fseek(Ptr, sizeof(TpPessoa) * (i-1), SEEK_SET);
			fwrite(&regA, sizeof(TpPessoa), 1, Ptr);
			i--;
			if(i>0) {
				fseek(Ptr, sizeof(TpPessoa) * i, SEEK_SET);
				fread(&regA, sizeof(TpPessoa), 1, Ptr);
				fseek(Ptr, sizeof(TpPessoa) * (i-1), SEEK_SET);
				fread(&regB, sizeof(TpPessoa), 1, Ptr);
			}
		}
	}
}

//Inser��o direta - ordenado pelo nome da cidade
void InsercaoDiretaCidade(FILE *PtrCidade){
	TpCidade regA, regB;
	int i;
	
	i = ftell(PtrCidade) / sizeof(TpCidade) - 1;
	if(i > 0) {
		fseek(PtrCidade, sizeof(TpCidade) * i, SEEK_SET);
		fread(&regA, sizeof(TpCidade), 1, PtrCidade);
		fseek(PtrCidade, sizeof(TpCidade) * (i-1), SEEK_SET);
		fread(&regB, sizeof(TpCidade), 1, PtrCidade);
		
		while(i > 0 && stricmp(regA.nomeCidade, regB.nomeCidade) < 0) {
			fseek(PtrCidade, sizeof(TpCidade) * i, SEEK_SET);
			fwrite(&regB, sizeof(TpCidade), 1, PtrCidade);
			fseek(PtrCidade, sizeof(TpCidade) * (i-1), SEEK_SET);
			fwrite(&regA, sizeof(TpCidade), 1, PtrCidade);
			i--;
			
			if(i > 0) {
				fseek(PtrCidade, sizeof(TpCidade) * i, SEEK_SET);
				fread(&regA, sizeof(TpCidade), 1, PtrCidade);
				fseek(PtrCidade, sizeof(TpCidade) * (i-1), SEEK_SET);
				fread(&regB, sizeof(TpCidade), 1, PtrCidade);
			}
		}
	}
}

//Inser��o direta - ordenado pela data do voo --------------  N�O FINALIZADA!!
void InsercaoDiretaVoo(FILE *PtrVoo){
	TpVoo regA, regB;
	int i;
	
	i = ftell(PtrVoo) / sizeof(TpVoo) - 1;
	if(i > 0) {
		fseek(PtrVoo, sizeof(TpVoo) * i, SEEK_SET);
		fread(&regA, sizeof(TpVoo), 1, PtrVoo);
		fseek(PtrVoo, sizeof(TpVoo) * (i-1), SEEK_SET);
		fread(&regB, sizeof(TpVoo), 1, PtrVoo);
		
		while(i > 0 /*&& (AQUI PRECISA TER A VERIFICACAO DE QUAL DATA � MAIOR)*/) { // ATEN��O NESSA PARTE (N�o sei como vamos verificar e como a data vai ficar no final das contas
			fseek(PtrVoo, sizeof(TpVoo) * i, SEEK_SET);
			fwrite(&regB, sizeof(TpVoo), 1, PtrVoo);
			fseek(PtrVoo, sizeof(TpVoo) * (i-1), SEEK_SET);
			fwrite(&regA, sizeof(TpVoo), 1, PtrVoo);
			i--;
			
			if(i > 0) {
				fseek(PtrVoo, sizeof(TpVoo) * i, SEEK_SET);
				fread(&regA, sizeof(TpVoo), 1, PtrVoo);
				fseek(PtrVoo, sizeof(TpVoo) * (i-1), SEEK_SET);
				fread(&regB, sizeof(TpVoo), 1, PtrVoo);
			}
		}
	}
}

//____________________________________ FUNCOES DE BUSCA ____________________________________
//Busca EXAUSTIVA pelo c�digo da cidade
int BuscaCodCidade(FILE *PtrCidade, int codCidade){
	TpCidade Registro; 
	
	//Posiciona o Ponteiro no Inicio
	rewind(PtrCidade); 
	//apartir da onde esta o ponteiro, vai pegar 1x o tamanho da estrutura e vai jogar p variavel Registro
	fread(&Registro,sizeof(TpCidade),1,PtrCidade); 
	
	while(!feof(PtrCidade) && codCidade != Registro.codCidade)
		//preciso ler de novo (o ponteiro anda a cada lida)
		fread(&Registro,sizeof(TpCidade),1,PtrCidade); 
		
	//ou posso perg --> stricmp(codCidade,Registro.codCidade) - em arquivo n�o tem problema de acessar lixo
	if(!feof(PtrCidade) && Registro.status == 'A') 
		//o "-sizeof" (menos) � pq ele para na frente do arq ent�o precisa voltar p pegar a posicao correta
		return ftell(PtrCidade)-sizeof(TpCidade); 
	else
		return -1;
}

//Busca SEQUENCIAL COM SENTINELA pelo c�digo do voo
int BuscaCodVoo(FILE *PtrVoo, int codVoo){
	TpVoo Registro; 
	int QtdeReg, i;
	
	Registro.codVoo = codVoo;
	Registro.status = 'A';
	//coloquei o ponteiro no final
	fseek(PtrVoo,0,SEEK_END);
	//inseri o cod e status na ultima posi��o (as demais informa��es foi com lixo)
	fwrite(&Registro,sizeof(TpVoo),1,PtrVoo);
	//posicionei o ponteiro no inicio
	rewind(PtrVoo); 
	
	fread(&Registro,sizeof(TpVoo),1,PtrVoo); 
	while(codVoo != Registro.codVoo) 
		fread(&Registro,sizeof(TpVoo),1,PtrVoo); 
		
	if(!feof(PtrVoo) && Registro.status == 'A') {
		i = ftell(PtrVoo)-sizeof(TpVoo);
		
		fseek(PtrVoo,0,SEEK_END);
		QtdeReg = ftell(PtrVoo)-sizeof(TpVoo); 
		fread(&Registro,QtdeReg*sizeof(TpVoo),1,PtrVoo);
		Registro.status = 'I';
		fwrite(&Registro,sizeof(TpVoo),1,PtrVoo);
		
		return i; 
	}else{
		fseek(PtrVoo,0,SEEK_END);
		QtdeReg = ftell(PtrVoo)-sizeof(TpVoo); 
		fread(&Registro,QtdeReg*sizeof(TpVoo),1,PtrVoo);
		Registro.status = 'I';
		fwrite(&Registro,sizeof(TpVoo),1,PtrVoo);
		
		return -1;
	}
}

// Busca pessoa pelo CPF
int BuscaCPF(FILE *Ptr, char cpf[]) {
	TpPessoa reg;
	// Ponteiro no come�o
	rewind(Ptr);
	fread(&reg, sizeof(TpPessoa), 1, Ptr);
	while(!feof(Ptr) && strcmp(cpf, reg.cpf) != 0)
		fread(&reg, sizeof(TpPessoa), 1, Ptr);
	if(!feof(Ptr))
		return ftell(Ptr) - sizeof(TpPessoa); // Encontrou
	else
		return -1; // Nao Encontrou
}

//____________________________________ FUNCOES DE CADASTRO ____________________________________
void CadastroPessoa(void)
{
	FILE *PtrPessoa = fopen("pessoas.dat", "rb+");
	TpPessoa reg;
	
	int inputs[6][2] = {{28, 5}, {29, 7}, {30, 9}, {31, 11}, {31, 13}, {35, 15}};
	
	//CAMPOS
	gotoxy(23, 5), printf("CPF: ");
	gotoxy(23, 7), printf("Nome: ");
	gotoxy(23, 9), printf("Email: "); 
	gotoxy(23, 11), printf("Estado: "); 
	gotoxy(23, 13), printf("Cidade: "); 
	gotoxy(23, 15), printf("Logradouro: ");
	
	do {
		mensagem("Digite os dados necessarios...", 0);
		limparLinha(17);
		limparCampos(6, inputs);
		fflush(stdin), irCampo(inputs[0]), gets(reg.cpf);
		fflush(stdin), irCampo(inputs[1]), gets(reg.nome);
		fflush(stdin), irCampo(inputs[2]), gets(reg.email);
		fflush(stdin), irCampo(inputs[3]), gets(reg.estado);
		fflush(stdin), irCampo(inputs[4]), gets(reg.cidade);
		fflush(stdin), irCampo(inputs[5]), gets(reg.endereco);
		reg.status = 'A';
		
		// Cadastrando Pessoa
		fseek(PtrPessoa, 0, SEEK_END);
		fwrite(&reg, sizeof(TpPessoa), 1, PtrPessoa);
		InsercaoDiretaPessoa(PtrPessoa);
		mensagem("Pessoa cadastrado com sucesso!", 1);
	} while(continuar(17) != 27);
	
	fclose(PtrPessoa);
}

void CadastroCidade(void) {
	TpCidade Registro;
	int pos, inputs[3][2]={{41, 5}, {39,7}, {41,9}};	
	FILE *PtrCidade = fopen("cidades.dat","rb+");

	gotoxy(23,5),printf("Codigo da cidade: ");
	gotoxy(23,7),printf("Nome da cidade: ");
	gotoxy(23,9),printf("Estado da cidade: ");

	do {
		mensagem("Digite os dados necessarios...", 0);
		limparLinha(11);
		limparCampos(3, inputs);
		irCampo(inputs[0]), scanf("%d", &Registro.codCidade);
		
		//busca para verificar se j� existe o c�digo dessa cidade cadastrado
		pos = BuscaCodCidade(PtrCidade,Registro.codCidade);
		if(pos==-1){
			fflush(stdin), irCampo(inputs[1]), gets(Registro.nomeCidade);
			fflush(stdin), irCampo(inputs[2]), gets(Registro.estCidade);
			Registro.status = 'A';
			
			fwrite(&Registro,sizeof(TpCidade),1,PtrCidade);
			mensagem("CIDADE CADASTRADA COM SUCESSO!", 1);
			//gravo o arquivo dentro da inser��o direta
			InsercaoDiretaCidade(PtrCidade);
		} else mensagem("CIDADE JA CADASTRADA!", -1);			
	} while(continuar(11) != 27);
	fclose(PtrCidade);
}

void CadastroVoo(void) {
	TpVoo Registro;
	TpData data;
	int pos, valido=1, inputs[5][2]={{38, 5}, {47,7}, {42,9}, {41,11}, {42,13}};
	FILE *PtrVoo = fopen("voos.dat", "rb+");

	gotoxy(23, 5), printf("Codigo do Voo: ");
	gotoxy(23, 7), printf("Data do Voo [dd mm aa]: ");
	gotoxy(23, 9), printf("Numero de Lugares: ");
	gotoxy(23, 11), printf("Cidade de Origem: ");
	gotoxy(23, 13), printf("Cidade de Destino: ");
	
	do {
		valido = 1;
		mensagem("Digite os dados para cadastrar o voo...", 0);
		limparLinha(15);
		limparCampos(5, inputs);
		irCampo(inputs[0]), scanf("%d", &Registro.codVoo);
		//busca para verificar se j� existe o c�digo desse voo cadastrado - SEQUENCIAL COM SENTINELA
		pos = BuscaCodVoo(PtrVoo,Registro.codVoo);
		if(pos != -1){
			irCampo(inputs[1]), scanf("%d %d %d", &data.dia, &data.mes, &data.ano);
			if(!validarData(data)) {
				valido = 0;
				mensagem("DATA INVALIDA!", -1);
			} else Registro.dataVoo = data;
			if(valido) {
				irCampo(inputs[2]), scanf("%d", &Registro.nrLugares);
				if(Registro.nrLugares <= 0) {
					valido = 0;
					mensagem("NUMERO DE LUGARES INVALIDO", -1);
				}
			}
			FILE *PtrCidade = fopen("cidades.dat","rb");
			if(valido) {
				irCampo(inputs[3]), scanf("%d", &Registro.codCidadeOrigem);
				//abro o arquivo da cidade para pesquisar se a cidade origem esta cadastrada 
				if(BuscaCodCidade(PtrCidade,Registro.codCidadeOrigem) == -1)  {
					mensagem("CIDADE NAO ENCONTRADA", -1);
					valido = 0;
				}
			}
			if(valido) {
				irCampo(inputs[4]), scanf("%d", &Registro.codCidadeDestino);
				if(BuscaCodCidade(PtrCidade, Registro.codCidadeDestino)==-1) {
					mensagem("CIDADE NAO ENCONTRADA", -1);
					valido = 0;
				}
			}
			fclose(PtrCidade);
			// Todos os dados valido, realizar cadastro
			if(valido) {
				Registro.QtdeLugarVendido = 0;
				Registro.status = 'A';
				mensagem("CADASTO REALIZADO COM SUCESSO!", 1);
				fwrite(&Registro,sizeof(TpVoo),1,PtrVoo);
				//gravo o arquivo dentro da inser��o direta
				InsercaoDiretaVoo(PtrVoo);
			}	
		} else mensagem("VOO JA CADASTRADO!", -1);
	} while(continuar(15) != 27);
	fclose(PtrVoo);
}

void AlterarPessoa(void)
{
	TpPessoa reg, aux;
	int pos, inputs[6][2]={{34, 7}, {35, 9}, {36, 11}, {37, 13}, {38, 15}, {41, 17}};
	FILE *PtrPessoa = fopen("pessoas.dat", "rb+");
	char op;
	
	do {
		limparTela();
		mensagem("Digite o CPF para buscar a pessoa!", 0);
		gotoxy(23, 5), printf("BUSCA PELO CPF: "), fflush(stdin), gets(reg.cpf);
		pos = BuscaCPF(PtrPessoa, reg.cpf);
		if(pos != -1) {
			// Lendo registro
			fseek(PtrPessoa, pos, SEEK_SET);
			fread(&reg, sizeof(TpPessoa), 1, PtrPessoa);

			gotoxy(23, 7), printf("[A] - CPF: %s", reg.cpf);
			gotoxy(23, 9), printf("[B] - Nome: %s", reg.nome);
			gotoxy(23, 11), printf("[C] - Email: %s", reg.email); 
			gotoxy(23, 13), printf("[D] - Estado: %s", reg.estado); 
			gotoxy(23, 15), printf("[E] -  Cidade: %s", reg.cidade); 
			gotoxy(23, 17), printf("[F] - Endereco: %s", reg.endereco);
			
			gotoxy(23, 19), printf("[S] - SALVAR");
			gotoxy(23, 20), printf("[ESQ] - VOLTAR");
			gotoxy(23, 22), printf("OPCAO: ");
			
			do {
				limparLinha(24);
				gotoxy(30, 22), op = toupper(getch());
				switch(op)
				{
					case 'A':
						gotoxy(23, 24), printf("EDITAR CPF: "), fflush(stdin), gets(aux.cpf);
						strcpy(reg.cpf, aux.cpf);
						limparCampoUnico(inputs[0]), irCampo(inputs[0]), textcolor(3), printf("%s", reg.cpf), textcolor(7);
						break;
					case 'B':
						gotoxy(23, 24), printf("EDITAR NOME: "), fflush(stdin), gets(aux.nome);
						strcpy(reg.nome, aux.nome);
						limparCampoUnico(inputs[1]), irCampo(inputs[1]), textcolor(3), printf("%s", reg.nome), textcolor(7);
						break;
					case 'C':
						gotoxy(23, 24), printf("EDITAR EMAIL: "), fflush(stdin), gets(aux.email);
						strcpy(reg.email, aux.email);
						limparCampoUnico(inputs[2]), irCampo(inputs[2]), textcolor(3), printf("%s", reg.email), textcolor(7);
						break;
					case 'D':
						gotoxy(23, 24), printf("EDITAR ESTADO: "), fflush(stdin), gets(aux.estado);
						strcpy(reg.estado, aux.estado);
						limparCampoUnico(inputs[3]), irCampo(inputs[3]), textcolor(3), printf("%s", reg.estado), textcolor(7);
						break;
					case 'E':
						gotoxy(23, 24), printf("EDITAR CIDADE: "), fflush(stdin), gets(aux.cidade);
						strcpy(reg.cidade, aux.cidade);
						limparCampoUnico(inputs[4]), irCampo(inputs[4]), textcolor(3), printf("%s", reg.cidade), textcolor(7);
						break;
					case 'F':
						gotoxy(23, 24), printf("EDITAR ENDEREÇO: "), fflush(stdin), gets(aux.endereco);
						strcpy(reg.endereco, aux.endereco);
						limparCampoUnico(inputs[5]), irCampo(inputs[5]), textcolor(3), printf("%s", reg.endereco), textcolor(7);
						break;
					case 'S':
						mensagem("ALTERACAO CONCLUIDA", 1);
						// Salvando edição
						fseek(PtrPessoa, pos, SEEK_SET);
						fwrite(&reg, sizeof(TpPessoa), 1, PtrPessoa);
						// Alterar em outras tebelas #ALTERAR
						break;
					case 27:
						mensagem("ALTERACOES CANCELADAS", -1);
						break;
				}
			} while(op != 27 && op != 'S');
		} else 
			mensagem("CLIENTE NAO CADASTRADO!", -1);
		limparLinha(24);
	} while(continuar(24) != 27);
	fclose(PtrPessoa);
}

void ExclusaoLogicaPessoa(void)
{
	TpPessoa reg;
	FILE *PtrPessoa = fopen("pessoas.dat", "rb+");
	int pos;
	do {
		limparLinha(19);
		limparTela();
		mensagem("Digite o CPF para bucar a pessoa!", 0);
		gotoxy(23, 5), printf("BUSCA PELO CPF: "), fflush(stdin), gets(reg.cpf);
		pos = BuscaCPF(PtrPessoa, reg.cpf);
		if(pos != -1) {
			// Lendo registro
			fseek(PtrPessoa, pos, SEEK_SET);
			fread(&reg, sizeof(TpPessoa), 1, PtrPessoa);

			gotoxy(23, 7), printf("[A] - CPF: %s", reg.cpf);
			gotoxy(23, 9), printf("[B] - Nome: %s", reg.nome);
			gotoxy(23, 11), printf("[C] - Email: %s", reg.email); 
			gotoxy(23, 13), printf("[D] - Estado: %s", reg.estado); 
			gotoxy(23, 15), printf("[E] -  Cidade: %s", reg.cidade); 
			gotoxy(23, 17), printf("[F] - Endereco: %s", reg.endereco);

			mensagem("Confirma exclusao ?", -1);
			if(confirmar(19) == 13) {
				// Exclusao Logica
				reg.status = 'I';
				// Outra tabelas #ALTERAR
				fseek(PtrPessoa, pos, SEEK_SET);
				fwrite(&reg, sizeof(TpPessoa), 1, PtrPessoa);
				mensagem("Exclusao concluida!", 1);
			} else mensagem("Exclusao cancelada!", 0);
		} else mensagem("PESSOA NAO CADASTRADA!", -1);
		limparLinha(19);
	} while(continuar(19) != 27);
	fclose(PtrPessoa);
}

void RelatorioPessoa(void)
{
	TpPessoa reg;
	int y, i, page=0, pages, qtd;
	char op;
	FILE *PtrPessoa = fopen("pessoas.dat", "rb");

	// Calcular as paginas
	fread(&reg, sizeof(TpPessoa), 1, PtrPessoa);
	qtd=0;
	while(!feof(PtrPessoa)) {
		if(reg.status == 'A') 
			qtd++;
		fread(&reg, sizeof(TpPessoa), 1, PtrPessoa);
	}
	pages = qtd / 3;
	if(qtd % 3 == 1)
		pages++;
		
	// Mensagem
	mensagem("Escolha uma opcao: ", 0);

	do {
		limparParteDaTela(23, 6, 79, 24);

		// Voltar
		gotoxy(69, 4), printf("[ESQ] SAIR");

		if(page+1 <= pages)
			gotoxy(65, 25), printf("[P] PROXIMO ->");
		if(pages-1 > 0)
			gotoxy(23, 25), printf("<- ANTERIOR [A]");

		// Pagination
		gotoxy(23, 4), printf("PAGINA (%d/%d)", page+1, pages+1);

		y=0;
		fseek(PtrPessoa, sizeof(TpPessoa)*(page * 3), SEEK_SET);
		fread(&reg, sizeof(TpPessoa), 1, PtrPessoa);
		i=0;
		while(i<3 && !feof(PtrPessoa)) {
			if(reg.status == 'A') {
				gotoxy(23, 6 + y), textcolor(3), printf("%c - Nome: ", reg.status), textcolor(7), printf("%s", reg.nome);
				gotoxy(23, 7 + y), textcolor(3), printf("Email: "), textcolor(7), printf("%s", reg.email);
				gotoxy(23, 8 + y), textcolor(3), printf("Estado: "), textcolor(7), printf("%s", reg.estado);
				gotoxy(33, 8 + y), textcolor(3), printf(" | Cidade: "), textcolor(7), printf("%s", reg.cidade);
				gotoxy(23, 9 + y), textcolor(3), printf("Endereco: "), textcolor(7), printf("%s", reg.endereco);
				linha(10 + y, 3);
				y += 6;
				i++;
			}
			fread(&reg, sizeof(TpPessoa), 1, PtrPessoa);
		}
		op = toupper(getch());
		if(op == 'P' && pages >= page+1)
			page++;
		if(op == 'A' && page-1 >= 0)
			page--;
	} while(op != 27);
	fclose(PtrPessoa);
}

void menu(void)
{
	char op, opSub;
	do {
		estruturaBase();
		titulo("SISTEMA AREO");
		mensagem("Seja Bem-Vind@! escolher uma opcao ao lado.", 0);
		limparTela();
		limparOpcoes();
		// Menu
		opcoesMenu(1, "CONSULTA");
		opcoesMenu(2, "RELATORIO");
		opcoesMenu(3, "EDITAR");
		opcoesMenu(4, "CADASTRAR");
		opcoesMenu(5, "EXCLUIR");
		opcoesMenu(6, "SAIR");	
		op = toupper(escolherOpcao(7));
		switch(op)
		{
			// CONSULTA 			
			case 'A':
				titulo("SISTEMA AREO - CONSULTA");
				limparOpcoes();
				opcoesMenu(1, "PESSOAS");
				opcoesMenu(2, "PASSAGENS");
				opcoesMenu(3, "CADASTRAR");
				opSub = toupper(escolherOpcao(4));
				while(opSub != 27) {
					switch(opSub)
					{
						case 'A':
							break;
						case 'B':
							break;
						case 'C':
							break;
					}
					opSub = toupper(escolherOpcao(4));
				}
				break;
			case 'B':
				titulo("SISTEMA AREO - RELATORIO");
				limparOpcoes();
				opcoesMenu(1, "PESSOAS");
				opcoesMenu(2, "PASSAGENS");
				opcoesMenu(3, "CADASTRAR");
				opSub = toupper(escolherOpcao(4));
				while(opSub != 27) {
					switch(opSub)
					{
						case 'A':
							RelatorioPessoa();
							break;
						case 'B':
							break;
						case 'C':
							break;
					}
					opSub = toupper(escolherOpcao(4));
				}
				break;
			case 'C':
				titulo("SISTEMA AREO - EDITAR");
				limparOpcoes();
				opcoesMenu(1, "PESSOAS");
				opcoesMenu(2, "PASSAGENS");
				opcoesMenu(3, "CADASTRAR");
				opcoesMenu(4, "VOOS");
				opSub = toupper(escolherOpcao(5));
				while(opSub != 27) {
					switch(opSub)
					{
						case 'A':
							AlterarPessoa();
							break;
						case 'B':
							break;
						case 'C':
							break;
					}
					limparTela();
					opSub = toupper(escolherOpcao(5));
				}
				break;
			case 'D':
				titulo("SISTEMA AREO - CADASTRO");
				limparOpcoes();
				opcoesMenu(1, "PESSOAS");
				opcoesMenu(2, "PASSAGENS");
				opcoesMenu(3, "VOOS");
				opcoesMenu(4, "CIDADES");
				opcoesMenu(5, "SAIR");
				opSub = toupper(escolherOpcao(6));
				while(opSub != 27) {
					switch(opSub)
					{
						case 'A':
							CadastroPessoa();
							break;
						case 'B':
							break;
						case 'C':
							CadastroVoo();
							break;
						case 'D':
							CadastroCidade();
							break;
					}
					opSub = toupper(escolherOpcao(6));
				}
				break;
			case 'E':
			titulo("SISTEMA AREO - CADASTRO");
				limparOpcoes();
				opcoesMenu(1, "PESSOAS");
				opcoesMenu(2, "PASSAGENS");
				opcoesMenu(3, "VOOS");
				opcoesMenu(4, "CIDADES");
				opcoesMenu(5, "SAIR");
				opSub = toupper(escolherOpcao(6));
				while(opSub != 27) {
					switch(opSub)
					{
						case 'A':
							ExclusaoLogicaPessoa();
							break;
						case 'B':
							break;
						case 'C':
							break;
						case 'D':
							break;
					}
					opSub = toupper(escolherOpcao(6));
				}
				break;
		}
	} while(op != 27);
}


int main() {
	RotinaCriarArq();
	menu();
	estruturaBase();
	// RelatorioPessoa();
////	CadastroPessoa();
//	AlterarPessoa();
//	FILE *Ptr = fopen("pessoas.dat", "rb");
//	TpPessoa reg;
//	fread(&reg, sizeof(TpPessoa), 1, Ptr);
//	while(!feof(Ptr)) {
//		printf("%s\n", reg.nome);
//		fread(&reg, sizeof(TpPessoa), 1, Ptr);
//	}
//	fclose(Ptr);
}

// VALIDAÇÔES
//VALIDAR DATA
int validarData(TpData data) {
	if(data.ano < 1900 || data.mes <= 0 || data.mes > 12  || data.dia <= 0)
		return 0;
	if(data.mes % 2 == 0)
		if(data.dia > 30)
			return 0;
	else
		if(data.dia > 31)
			return 0;
	if(data.ano % 4 == 0)
		if(data.dia > 29)
			return 0;
	else
		if(data.dia > 28)
			return 0;
	// VALIDO
	return 1;	
}

// ESTUTURA DO SISTEMA
void tabelaASCII(void)
{
	int i;
	for(i=0; i<=255; i++)
		printf("%d - %c\n", i, i);	
}

void estruturaBase()
{
	int x1=1, x2=80, y1=1, y2=30, i;
	for(i=x1+1; i<x2; i++) {
		gotoxy(i, y1), printf("%c", 196);
		gotoxy(i, y2), printf("%c", 196);
		gotoxy(i, y1+2), printf("%c", 196);
		if(i>20)
			gotoxy(i, y2-4), printf("%c", 196);
	}
	for(i=y1+1; i<y2; i++) {
		gotoxy(x1, i), printf("%c", 179);
		gotoxy(x2, i), printf("%c", 179);
		if(i > 3)
			gotoxy(x1+20, i), printf("%c", 179);
	}
	
	// LADOS
	gotoxy(x1, y1), printf("%c", 218);
	gotoxy(x1, y2), printf("%c", 192);
	gotoxy(x2, y1), printf("%c", 191);
	gotoxy(x2, y2), printf("%c", 217);
	// FECHAR TITULO
	gotoxy(x1, y1+2), printf("%c", 195);
	gotoxy(x2, y1+2), printf("%c", 180);
	// FECHAR MENU
	gotoxy(x1+20, y1+2), printf("%c", 194);
	gotoxy(x1+20, y2), printf("%c", 193);
	gotoxy(7, 4), printf("# MENU #");
	// FECHAR MENSAGENS
	gotoxy(x1+20, y2-4), printf("%c", 195);
	gotoxy(x2, y2-4), printf("%c", 180);
	textcolor(3);
	gotoxy(x1+22, y2-2), printf("Mensagens: ");
	textcolor(7);
	
	gotoxy(80,35);
}

void titulo(char title[])
{
	int len = strlen(title), y=1, x = 80 / 2 - (len/2 + 4), i;
	for(i=2; i<79; i++)
		gotoxy(i, y+1), printf(" ");
	textcolor(3);	
	gotoxy(x, y+1), printf("### %s ###", title);
	textcolor(7);
}

void opcoesMenu(int posic, char texto[])
{
	int x1=1, y1=5, i;
	for(i=x1+2; i<x1+18; i++)
		gotoxy(i, y1+posic), printf(" ");
	gotoxy(x1+2, y1+posic), printf("[%c] - %s", 64+posic, texto);
}

int escolherOpcao(int itens)
{
	int x1=1, y1=5;
	gotoxy(x1+2, y1+itens+2), printf("OPCAO: ");
	return toupper(getch());
}

void limparOpcoes(void)
{
	int i, j, x1=2, x2=21, y1=6, y2=30;
	for(i=x1; i<x2; i++)
		for(j=y1; j<y2; j++)
			gotoxy(i, j), printf(" ");
	
}

void mensagem(char msg[], int status)
{
	// -1 ERRO, 0 NEUTRO, 1 SUCESSO
	if(status == 1)
		textcolor(10);
	else
		if(status == -1)
			textcolor(RED);
	int y2=30, x2=80, i;
	for(i=34; i<x2-1; i++)
		gotoxy(i, y2-2), printf(" ");
	gotoxy(34, y2-2), printf("%s", msg);
	textcolor(7);
}

void linha(int y, int color)
{
	int i;
	for(i=23; i<79; i++)
		gotoxy(i, y), textcolor(color), printf("_");
	textcolor(7);
}

void limparTela(void)
{
	int x1=22, x2=80, y1=4, y2=30, i, j;
	for(i=x1; i<x2; i++) 
		for(j=y1; j<y2-4; j++)
			gotoxy(i, j), printf(" ");
}

int continuar(int y)
{
	int x1=22;
	textcolor(3);
	gotoxy(x1+12, y), printf("[ENTER] - CONTINUAR & [ESQ] - SAIR");
	textcolor(7);
	return getch();
}

void limparLinha(int y)
{
	int x1=22, x2=80, i;
	for(i=x1; i<x2; i++)
		gotoxy(i, y), printf(" ");
}

void irCampo(int posic[2]) {
	gotoxy(posic[0], posic[1]);
}

void limparCampos(int qtd, int posic[][2])
{
	int i, j, x2=80;
	for(i=0; i<qtd; i++)
		for(j=posic[i][0]; j<x2; j++)
			gotoxy(j, posic[i][1]), printf(" ");
}

void limparCampoUnico(int posic[])
{
	int i, x2=80;
	for(i=posic[0]; i<x2; i++)
		gotoxy(i, posic[1]), printf(" ");
}

int confirmar(int y)
{
	int x1=22;
	textcolor(3);
	gotoxy(x1+10, y), printf("[ENTER] - CONFIRMAR & [ESQ] - CANCELAR ");
	textcolor(7);
	return getch();
}

void limparParteDaTela(int x1, int y1, int x2, int y2)
{
	int i, j;
	for(i=x1; i<x2; i++)
		for(j=y1; j<y2; j++)
			gotoxy(i, j), printf(" ");
	
}

void desenhoPoltronas(void)
{
	int x1=22, x2=80, y1=17, y2=26, i, j;
	for(i=y1; i<y2-1; i++) {
		gotoxy(47, i), printf("%c", 179);
		gotoxy(54, i), printf("%c", 179);
		gotoxy(x1+1, i), printf("%c", 179);
		gotoxy(x1+5, i), printf("%c", 179);
		gotoxy(x1+9, i), printf("%c", 179);
		gotoxy(x1+13, i), printf("%c", 179);
		gotoxy(x1+17, i), printf("%c", 179);
		gotoxy(x1+21, i), printf("%c", 179);
		
		gotoxy(54+4, i), printf("%c", 179);
		gotoxy(54+8, i), printf("%c", 179);
		gotoxy(54+12, i), printf("%c", 179);
		gotoxy(54+16, i), printf("%c", 179);
		gotoxy(54+20, i), printf("%c", 179);
		gotoxy(54+24, i), printf("%c", 179);
		
		gotoxy(x1+1, i), printf("%c", 179);
		gotoxy(x1+5, i), printf("%c", 179);
		gotoxy(x1+9, i), printf("%c", 179);
		gotoxy(x1+13, i), printf("%c", 179);
		gotoxy(x1+17, i), printf("%c", 179);
		gotoxy(x1+21, i), printf("%c", 179);		
	}
	
	for(i=x1+1, j=0; i<x2-1; i++, j++) {
		if(i<47 || i>54) {	
			gotoxy(i, y1-1), printf("%c", 196);
			gotoxy(i, y1+3), printf("%c", 196);
			gotoxy(i, y1+7), printf("%c", 196);
			if(j==4 && i+1 != x2) {
				gotoxy(i, y1-1), printf("%c", 194);
				gotoxy(i, y1+3), printf("%c", 197);
				gotoxy(i, y1+7), printf("%c", 193);
				j=0;
			}
		}
		if(i == 54)
		 j=0;
	}
	
	// BORDAS
	gotoxy(x1+1, y1-1), printf("%c", 218);
	gotoxy(47, y1-1), printf("%c", 191);
	gotoxy(x1+1, y2-2), printf("%c", 192);
	gotoxy(47, y2-2), printf("%c", 217);
	gotoxy(54, y1-1), printf("%c", 218);
	gotoxy(x2-2, y1-1), printf("%c", 191);
	gotoxy(54, y2-2), printf("%c", 192);
	gotoxy(x2-2, y2-2), printf("%c", 217);
	gotoxy(x1+1, y1+3), printf("%c", 195);
	gotoxy(47, y1+3), printf("%c", 180);
	gotoxy(54, y1+3), printf("%c", 195);
	gotoxy(x2-2, y1+3), printf("%c", 180);
}


// 1 - Maior(recente) 0 - Igual -1 - Menor(passado)
// Data1 comparda com Data2
// int compararData(TpData data1, TpData data2)
// {
// 	// Comparando anos
// 	if(data1.ano > data2.ano)
// 		return 1;
// 	else if (data1.ano < data2.ano)
// 		return -1;
	
// 	// Anos iguais -> comparar meses
// 	if(data1.mes > data2.mes)
// 			return 1;
// 	else if (data1.mes < data2.mes)
// 			return -1;

// 	// Meses iguais -> comparar datas
// 	if(data1.dia > data2.dia)
// 		return 1;
// 	else if(data1.dia < data2.dia)
// 		return -1;
	
// 	return 0; // Data igual
// }
