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
	char cpf[XV], nome[XL], endereco[XXX], cidade[XL], estado[2], email[XL], status;
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

//____________________________________ FUNÇÕES ____________________________________
void RotinaCriarArq(void) {
	FILE *Ptr;
	int i;
	char arq[4][30] = {"pessoas.dat", "cidades.dat", "voos.dat", "passagens.dat"};
	for(i=0; i<4; i++) {
		Ptr = fopen(arq[i], "ab");
		fclose(Ptr);
	}
}

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

// Busca pessoa pelo CPF
int BuscaCPF(FILE *Ptr, char cpf[]) {
	TpPessoa reg;
	// Ponteiro no começo
	rewind(Ptr);
	fread(&reg, sizeof(TpPessoa), 1, Ptr);
	while(!feof(Ptr) && strcmp(cpf, reg.cpf) == 0)
		fread(&reg, sizeof(TpPessoa), 1, Ptr);
	if(!feof(Ptr))
		return ftell(Ptr) - sizeof(TpPessoa); // Encontrou
	else
		return -1; // Nao Encontrou
}

void CadastroPessoa(void)
{
	FILE *PtrPessoa = fopen("pessoas.dat", "rb+");
	TpPessoa reg;
	printf("\nCPF: "), fflush(stdin), gets(reg.cpf);
	while(strcmp(reg.cpf, "\0") != 0) {
		printf("\nNome: "), fflush(stdin), gets(reg.nome);
		printf("\nEndereco: "), fflush(stdin), gets(reg.endereco);
		printf("\nCidade: "), fflush(stdin), gets(reg.cidade);
		printf("\nEstado: "), fflush(stdin), gets(reg.estado);
		printf("\nEmail: "), fflush(stdin), gets(reg.email);
		reg.status = 'A';
		printf("%s", reg.cpf);
		// Cadastrando Pessoa
		fseek(PtrPessoa, 0, SEEK_END);
		fwrite(&reg, sizeof(TpPessoa), 1, PtrPessoa);
		InsercaoDiretaPessoa(PtrPessoa);
		printf("\nCPF: "), fflush(stdin), gets(reg.cpf);
	}
	fclose(PtrPessoa);
}

void AlterarPessoa(void)
{
	TpPessoa reg;
	int pos;
	FILE *PtrPessoa = fopen("pessoas.dat", "rb+");
	printf("Digite o CPf: "), fflush(stdin), gets(reg.cpf);
	pos = BuscaCPF(PtrPessoa, reg.cpf);
	if(pos != -1) {
		fseek(PtrPessoa, pos, SEEK_SET), fread(&reg, sizeof(TpPessoa), 1, PtrPessoa);
		printf("\n\nNome: %s\n\n", reg.nome);	
	} else printf("\nCPF Nao encontrado!");
	fclose(PtrPessoa);
}

void tabelaASCII(void);
void titulo(char title[]);
void opcoesMenu(int posic, char texto[]);
int escolherOpcao(int itens);
void limparOpcoes(void);
void mensagem(char msg[], int status);
void estruturaBase(void);
void limparTela(void);
int continuar(int y);
void limparLinha(int y);
void limparCampos(int qtd, int posic[][2]);
void limparCampoUnico(int posic[2]);
int confirmar(int y);
//int escolhaPoltrona(tpVoo tabVoos[TFV], int TLV, tpPassagem tabPassagens[TFPG], int TLPG, int codVoo);
void limparParteDaTela(int x1, int y1, int x2, int y2);

void menu(void)
{
	estruturaBase();
	titulo("SISTEMA AREO");
	mensagem("Seja Bem-Vind@! escolher uma opcao ao lado.", 0);
	limparTela();
	limparOpcoes();
	// Menu
	opcoesMenu(1, "CONSULTA");
	opcoesMenu(2, "EDITAR");
	opcoesMenu(3, "CADASTRAR");
	opcoesMenu(4, "EXCLUIR");
	opcoesMenu(5, "SAIR");	
}


int main() {
	RotinaCriarArq();
	menu();
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

// DESENHO
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



