#ifndef PACIENTE_H_INCLUDED
#define PACIENTE_H_INCLUDED

#define MAXNOME 128
#define TAMCPF 15
#define NOME_ARQ_PACIENTE "paciente.bin"
#define NOME_ARQ_RISCO "risco.txt"

#define TAMCEP 11
#define TAMFONE 16
#define TAMNUM 16

#define MAXCOMORBS 256

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

   typedef struct paciente_struct {
    char nome[MAXNOME];
    char cpf[TAMCPF];
    char telefone[TAMFONE];
    char email[MAXNOME];
    Endereco endereco;
    Data aniversario;
    Data diagnostico;
    char comorbs[MAXCOMORBS]; /* comorbidades */
} Paciente;


extern void gravar_paciente();
extern void buscar_paciente(Paciente *p);
extern void print_paciente(Paciente *p);
#endif // PACIENTE_H
