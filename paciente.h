#ifndef PACIENTE_H_INCLUDED
#define PACIENTE_H_INCLUDED

#define MAXNOME 128
#define TAMCPF 15
#define NOME_ARQ_PACIENTE "paciente.bin"
#define NOME_ARQ_RISCO "risco.txt"

#define TAMCEP 11
#define TAMFONE 16

typedef struct endereco_struct {
    char logradouro[MAXNOME];
    int numero;
    char complemento[MAXNOME];
    char bairro[MAXNOME];
    char cidade[MAXNOME];
    char estado[2];
    char cep[TAMCEP];
} Endereco;

typedef struct data_struct {
    int dia;
    int mes;
    int ano;
} Data;

enum comorbidade_enum {DIABETES=0, OBESIDADE, HIPERTENSAO, TUBERCULOSE};

typedef struct paciente_struct {
    char nome[MAXNOME];
    char cpf[TAMCPF];
    Endereco endereco;
    Data aniversario;
    Data diagnostico;
    char telefone[TAMFONE];
    char email[MAXNOME];
    int comorbidades[4];
} Paciente;

extern void gravar_paciente();
extern void registrar_usuario();

#endif // PACIENTE_H
