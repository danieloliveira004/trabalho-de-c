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

int main() {
	RotinaCriarArq();
//	CadastroPessoa();
	AlterarPessoa();
	FILE *Ptr = fopen("pessoas.dat", "rb");
	TpPessoa reg;
	fread(&reg, sizeof(TpPessoa), 1, Ptr);
	while(!feof(Ptr)) {
		printf("%s\n", reg.nome);
		fread(&reg, sizeof(TpPessoa), 1, Ptr);
	}
	fclose(Ptr);
}
