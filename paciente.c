#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "paciente.h"

char *comorbidade_name[4] = {"DIABETES", "OBESIDADE", "HIPERTENSAO", "TUBERCULOSE"};

void exemplo() {
    enum comorbidade_enum coms[4] = {0, 1, 0, 0};
    if (coms[OBESIDADE] == 1) {
        printf("Paciente tem %s\n", comorbidade_name[DIABETES]);
    }
    if (coms[OBESIDADE] == 1) {
        printf("Paciente tem %s\n", comorbidade_name[OBESIDADE]);
    }
    if (coms[OBESIDADE] == 1) {
        printf("Paciente tem %s\n", comorbidade_name[HIPERTENSAO]);
    }
    if (coms[OBESIDADE] == 1) {
        printf("Paciente tem %s\n", comorbidade_name[TUBERCULOSE]);
    }
}

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
        FILE *fp = fopen(NOME_ARQ_RISCO, "w");
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

        system("cls");
        printf("\n |--------------------------------------------------------------------------------------------------------------------|");
        printf("\n |                                             NOVO CADASTRO                                                          |");
        printf("\n |--------------------------------------------------------------------------------------------------------------------|");

        printf("\n\n\tDados do paciente: ");

        printf("Nome:");
        fflush(stdin);
        fgets(&paciente.nome[0], MAXNOME, stdin);

        printf("CPF: (XXX.XXX.XXX-XX)");
        fflush(stdin);
        fgets(&paciente.cpf[0], TAMCPF, stdin);

        printf("\n\tTelefone: ");
        fflush(stdin);
        fgets(&paciente.telefone[0], TAMFONE, stdin);

//        printf("\tE-mail: ");
//        fflush(stdin);
//        scanf("%s[^\n]", &paciente.email);
//
//        system("cls");
//        printf("\n\n\tData de Nascimento:");
//
//        printf("\t\tDia: ");
//        fflush(stdin);
//        scanf("%d[^\n]",paciente.aniversario.dia);
//
//        printf("\t\tMês: ");
//        fflush(stdin);
//        scanf("%s[^\n]",paciente.aniversario.mes);
//
//        printf("Ano de nascimento:");
//        fflush(stdin);
//        scanf("%d[^\n]", &paciente.aniversario.ano);
//
//        system("cls");
//        printf("\n\n\tEndereço do Paciente:");
//
//        printf("\n\n\n\t\tLogradouro: ");
//        fflush(stdin);
//        scanf("%s[^\n]",paciente.endereco.logradouro);
//
//        printf("\t\tNúmero: ");
//        fflush(stdin);
//        scanf("%s[^\n]",paciente.endereco.numero);
//
//        printf("\t\tBairro: ");
//        fflush(stdin);
//        scanf("%s[^\n]",paciente.endereco.bairro);
//
//        printf("\t\tCidade: ");
//        fflush(stdin);
//        scanf("%s[^\n]",paciente.endereco.cidade);
//
//        printf("\t\tEstado: ");
//        fflush(stdin);
//        scanf("%s[^\n]",paciente.endereco.estado);
//
//        printf("\t\tCEP: ");
//        fflush(stdin);
//        scanf("%s[^\n]",paciente.endereco.cep);
//
//        system("cls");
//        printf("\n\n\tData do diagnóstico: ");
//
//        printf("\n\n\n\t\tDia: ");
//        fflush(stdin);
//        scanf("%d[^\n]", &paciente.diagnostico.dia);
//
//        printf("\t\tMês: ");
//        fflush(stdin);
//        scanf("%d[^\n]", &paciente.diagnostico.mes);
//
//        printf("\t\tAno: ");
//        fflush(stdin);
//        scanf("%d[^\n]", &paciente.diagnostico.ano);
//
//        system("cls");
//        printf("\n\tComorbidades:\n");
//
//        printf("Paciente  é diabético?");
//        printf("[0] NÃO \n [1]SIM");
//        fflush(stdin);
//        scanf("%d", &paciente.comorbidades[DIABETES]);
//
//        printf("Paciente é obeso?)");
//        printf("[0] NÃO \n [1]SIM");
//        fflush(stdin);
//        scanf("%d", &paciente.comorbidades[OBESIDADE]);
//
//        printf("Paciente  é hipertenso?");
//        printf("[0] NÃO \n [1]SIM");
//        fflush(stdin);
//        scanf("%d", &paciente.comorbidades[HIPERTENSAO]);
//
//        printf("Paciente  possui tuberculose?");
//        printf("[0] NÃO \n [1]SIM");
//        fflush(stdin);
//        scanf("%d", &paciente.comorbidades[TUBERCULOSE]);
//
//    __gravar_paciente(&paciente);
//
//    checar_grupo_risco(&paciente);
}

int buscar_paciente(char *cpf) {
    FILE *fp;
    Paciente p;

    fp = fopen(NOME_ARQ_PACIENTE, "rb");

    if (fp == NULL) {
        fprintf(stderr, "Erro ao abrir %s para leitura!\n", NOME_ARQ_PACIENTE);
        exit(1);
    }

    while (!feof(fp)) {
        fread(&p, sizeof(Paciente), 1, fp);
        if (strncpy(cpf, p.cpf, TAMCPF) == 0) {
           return &p;
        }
    }
    fclose(fp);

    fprintf(stderr, "O paciente com CPF %s nao existe!\n", cpf);
    exit(1);
}
