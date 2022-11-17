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
	char cpf[XV], nome[XL], endereco[XXX], cidade[XL], estado[XL], email[XL], status;
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
//	char arq[4][30] = {"pesssoas.dat", "cidades.dat", "voos.dat", "passagens.dat"};
//	for(i=0; i<4; i++) {
//		Ptr = fopen(arq[i], "ab");
//		fclose(Ptr);
//	}
Ptr = fopen("pesssoas.dat", "ab");
fclose(Ptr);
}

void InsercaoDiretaPessoa(FILE *PtrPessoa)
{
	TpPessoa aux;
	int QtdPessoas;
	

	
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
		printf("\nCPF: "), fflush(stdin), gets(reg.cpf);
	}
	fclose(PtrPessoa);
}

int main() {
	RotinaCriarArq();
	CadastroPessoa();
}
