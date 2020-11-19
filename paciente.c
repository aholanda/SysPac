#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

#include "paciente.h"
#include "login.h"
#include "io.h"

#define INIT_MARK "#"
#define ENTER_MARK ">"

static void __gravar_paciente(Paciente *paciente) {
    FILE *fp;

    fp = fopen(NOME_ARQ_PACIENTE, "ab");

    if (fp == NULL) {
        fprintf(stderr, "Erro ao abrir %s para escrita!\n", NOME_ARQ_PACIENTE);
        exit(1);    }

    fwrite(paciente, sizeof(Paciente), 1, fp);

    fclose(fp);
}

void checar_grupo_risco(Paciente *paciente) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int idade = 1900 +  tm.tm_year;
    int dif = idade - paciente->aniversario.ano;
    
    if (dif > 65) {
        printf("Cuidado veio, voce tem %d, fica na goma\n", dif);
        FILE *fp = fopen(NOME_ARQ_RISCO, "aw");
        if (fp == NULL) {
            fprintf(stderr, "Erro ao abrir %s para escrita\n", NOME_ARQ_RISCO);
            exit(EXIT_FAILURE);
        }
        fprintf(fp, "%s;%d\n", paciente->endereco.cep, idade);
        fclose(fp);
    }
}

void gravar_paciente() {
    Paciente paciente;
    char numstr[TAMNUM];
    int i;

    printf("|--------------------------------------------------------------------------|\n");
    printf("|                            NOVO CADASTRO                                 |\n");
    printf("|--------------------------------------------------------------------------|\n");

    printf("%s Dados do paciente: \n", INIT_MARK);
            
    /* NOME */
    nome_label:
    flush_buffer();
    printf("%s Nome: ", ENTER_MARK);
    fflush(stdin);            
    for (i = 0; i < MAXNOME; i++) {
        paciente.nome[i] = getc(stdin);
        if (paciente.nome[i] == '\n') {
            paciente.nome[i] = '\0';
            break;
        }
        if (isdigit(paciente.nome[i])) {
            fprintf(stderr, "So letras por favor, senao fico brava!\n");
            flush_buffer();
            goto nome_label;
        }
    }
    
    /* CPF */
    cpf_label:
    printf("%s CPF: ", ENTER_MARK);
    fflush(stdin);
    for (i = 0; i < TAMCPF; i++) {
        paciente.cpf[i] = getc(stdin);
        if (paciente.cpf[i] == '\n') {
            paciente.cpf[i] = '\0';
            break;
        }
        if (isalpha(paciente.cpf[i])) {
            printf("Eh permitido somente numeros, \".\" e \"-\"\n");
            flush_buffer();
            goto cpf_label;
        }
    }

    telefone_label:
    printf("%s Telefone: ", ENTER_MARK);
    fflush(stdin);
    for (i = 0; i < TAMFONE; i++) {
        paciente.telefone[i] = getc(stdin);
        if (paciente.telefone[i] == '\n') {
            paciente.telefone[i] = '\0';
            break;
        }
        if (isalpha(paciente.telefone[i])) {
            printf("Letras e caracteres nao permitidos\n");
            flush_buffer();
            goto telefone_label;
        }
    }

   /* EMAIL */
    printf("%s E-mail: ", ENTER_MARK);
    fflush(stdin);
    for (i = 0; i < MAXNOME; i++) {
        paciente.email[i] = getc(stdin);
        if (paciente.email[i] == '\n') {
            paciente.email[i] = '\0';
            break;
        }
    }

    logradouro_label:
    printf("%s Endereco do Paciente \n", INIT_MARK);
    printf("%s Logradouro: ", ENTER_MARK);
    fflush(stdin);        
    for (i = 0; i < MAXNOME; i++) {
        paciente.endereco.logradouro[i] = getc(stdin);
        if (paciente.endereco.logradouro[i] == '\n') {
            paciente.endereco.logradouro[i] = '\0';
            break;
        }
        if (isdigit(paciente.endereco.logradouro[i])) {
            printf("numeros nao permitidos\n");
            flush_buffer();
            goto logradouro_label;
        }
    }

    numero_label:
    printf("%s Numero: ", ENTER_MARK);
    fflush(stdin);        
    for (i = 0; i < TAMNUM; i++) {
        numstr[i] = getc(stdin);
        if (numstr[i] == '\n') {
            numstr[i] = '\0';
            break;
        }
        if (!isdigit(numstr[i])) {
            printf("soh numeros nao permitidos\n");
            flush_buffer();
            goto numero_label;
        }
    }
    paciente.endereco.numero = atoi(numstr);

    /* COMPLEMENTO */
    printf("%s Complemento: ", ENTER_MARK);
    fflush(stdin);        
    for (i = 0; i < MAXNOME; i++) {
        paciente.endereco.complemento[i] = getc(stdin);
        if (paciente.endereco.complemento[i] == '\n') {
            paciente.endereco.complemento[i] = '\0';
            break;
        }
    }
 
    /* CEP */
    cep_label:
    printf("%s CEP: ", ENTER_MARK);
    fflush(stdin);        
    for (i = 0; i < TAMCEP; i++) {
        paciente.endereco.cep[i] = getc(stdin);
        if (paciente.endereco.cep[i] == '\n') {
            paciente.endereco.cep[i] = '\0';
            break;
        }
        if (isdigit(paciente.endereco.cep[i]) || (paciente.endereco.cep[i] == '-')) {
            continue;
        } else {
            printf("soh numeros %c e \"-\" nao permitidos\n", paciente.endereco.cep[i]);
            flush_buffer();
            goto cep_label;
        }
    }

    //bairro_label:
    printf("%s Bairro: ", ENTER_MARK);
    fflush(stdin);        
    for (i = 0; i < MAXNOME; i++) {
        paciente.endereco.bairro[i] = getc(stdin);
        if (paciente.endereco.bairro[i] == '\n') {
            paciente.endereco.bairro[i] = '\0';
            break;
        }
    }
    
    //cidade_label:    
    printf("%s Cidade: ", ENTER_MARK);
    fflush(stdin);        
    for (i = 0; i < MAXNOME; i++) {
        paciente.endereco.cidade[i] = getc(stdin);
        if (paciente.endereco.cidade[i] == '\n') {
            paciente.endereco.cidade[i] = '\0';
            break;
        }
    }
            
    estado_label:
    printf("%s Estado: ", ENTER_MARK);
    fflush(stdin);        
    for (i = 0; i < MAXNOME; i++) {
        paciente.endereco.estado[i] = getc(stdin);
        if (paciente.endereco.estado[i] == '\n') {
            paciente.endereco.estado[i] = '\0';
            break;
        }
        if (isdigit(paciente.endereco.estado[i])) {
            printf("numeros nao permitidos\n");
            flush_buffer();
            goto estado_label;
        }
    }

    printf("%s Data de nascimento\n", INIT_MARK);       
    nascimento_dia_label:
    printf("%s Dia: ", ENTER_MARK);
    fflush(stdin);        
    for (i = 0; i < 3; i++) {
        numstr[i] = getc(stdin);
        if (numstr[i] == '\n') {
            numstr[i] = '\0';
            break;
        }
        if (!isdigit(numstr[i])) {
            printf("soh numeros nao permitidos\n");
            flush_buffer();
            goto nascimento_dia_label;
        }
    }
    paciente.aniversario.dia = atoi(numstr);

    nascimento_mes_label:
    printf("%s Mes: ", ENTER_MARK);
    fflush(stdin);        
    for (i = 0; i < 3; i++) {
        numstr[i] = getc(stdin);
        if (numstr[i] == '\n') {
            numstr[i] = '\0';
            break;
        }
        if (!isdigit(numstr[i])) {
            printf("soh numeros nao permitidos\n");
            flush_buffer();
            goto nascimento_mes_label;
        }
    }
    paciente.aniversario.mes = atoi(numstr);

    nascimento_ano_label:
    printf("%s Ano: ", ENTER_MARK);
    fflush(stdin);        
    for (i = 0; i < 5; i++) {
        numstr[i] = getc(stdin);
        if (numstr[i] == '\n') {
            numstr[i] = '\0';
            break;
        }
        if (!isdigit(numstr[i])) {
            printf("soh numeros nao permitidos\n");
            flush_buffer();
            goto nascimento_ano_label;
        }
    }
    paciente.aniversario.ano = atoi(numstr);

    printf("%s Data do diagnostico\n", INIT_MARK);
    diagnostico_dia_label:
    printf("%s Dia: ", ENTER_MARK);
    fflush(stdin);        
    for (i = 0; i < 3; i++) {
        numstr[i] = getc(stdin);
        if (numstr[i] == '\n') {
            numstr[i] = '\0';
            break;
        }
        if (!isdigit(numstr[i])) {
            printf("soh numeros nao permitidos\n");
            flush_buffer();
            goto diagnostico_dia_label;
        }
    }
    paciente.diagnostico.dia = atoi(numstr);

    diagnostico_mes_label:
    printf("%s Mes: ", ENTER_MARK);
    fflush(stdin);        
    for (i = 0; i < 3; i++) {
        numstr[i] = getc(stdin);
        if (numstr[i] == '\n') {
            numstr[i] = '\0';
            break;
        }
        if (!isdigit(numstr[i])) {
            printf("soh numeros nao permitidos\n");
            flush_buffer();
            goto diagnostico_mes_label;
        }
    }
    paciente.diagnostico.mes = atoi(numstr);

    diagnostico_ano_label:
    printf("%s Ano: ", ENTER_MARK);
    fflush(stdin);        
    for (i = 0; i < 5; i++) {
        numstr[i] = getc(stdin);
        if (numstr[i] == '\n') {
            numstr[i] = '\0';
            break;
        }
        if (!isdigit(numstr[i])) {
            printf("soh numeros nao permitidos\n");
            flush_buffer();
            goto diagnostico_ano_label;
        }
    }
    paciente.diagnostico.ano = atoi(numstr);

    __gravar_paciente(&paciente);
    checar_grupo_risco(&paciente);
    exit(EXIT_SUCCESS);
}

 void print_paciente(Paciente *p) {
    printf("ACHEI PACIENTE, MAS MESMO ASSIM ESTOU BRAVA\n");
    printf("Nome: %s\n", p->nome);
    printf("CPF: %s\n", p->cpf);
    printf("Telefone: %s\n", p->telefone);
    printf("Email: %s\n", p->email);
    printf("Logradouro: %s\n", p->endereco.logradouro);
    printf("Numero: %d\n", p->endereco.numero);
    printf("Complemento: %s\n", p->endereco.complemento);
    printf("Bairro: %s\n", p->endereco.bairro);
    printf("Cidade: %s\n", p->endereco.cidade);
    printf("Estado: %s\n", p->endereco.estado);
    printf("Nascimento: %d/%d/%d\n", 
            p->aniversario.dia, 
            p->aniversario.mes, 
            p->aniversario.ano);
    printf("Data diagnostica: %d/%d/%d\n", 
            p->diagnostico.dia, 
            p->diagnostico.mes, 
            p->diagnostico.ano);
}

void buscar_paciente(Paciente *p) {
    FILE *fp;
    char cpf[TAMCPF];
    int i;

    flush_buffer();
    printf("%s Buscar Paciente\n", INIT_MARK);
    printf("%s Informe o CPF: ", ENTER_MARK);
    fflush(stdin);
    for (i = 0; i < TAMCPF; i++) {
        cpf[i] = getc(stdin);
        
        if (cpf[i] == '\n' || cpf[i]== '\t') {
            cpf[i] = '\0';
            break;
        }
    }

    printf("CPF: %s", cpf);

    fp = fopen(NOME_ARQ_PACIENTE, "rb");

    if (fp == NULL) {
        fprintf(stderr, "Erro ao abrir %s para leitura!\n", NOME_ARQ_PACIENTE);
        exit(EXIT_FAILURE);
    }

    while (!feof(fp)) {
        fread(p, sizeof(Paciente), 1, fp);
        if (strncmp(cpf, p->cpf, strlen(p->cpf)) == 0) {
            printf("%s\n", p->cpf);
            print_paciente(p);
            exit(EXIT_SUCCESS);
        }
    }
    fclose(fp);

    fprintf(stderr, "O paciente com CPF %s nao existe!\n", cpf);
    exit(EXIT_FAILURE);
}


