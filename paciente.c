#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "paciente.h"



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
    char numstr[TAMNUM];
    int ok=0, pos=0;

    char c;

    system("cls");
    printf("\n |--------------------------------------------------------------------------------------------------------------------|");
    printf("\n |                                             NOVO CADASTRO                                                          |");
    printf("\n |--------------------------------------------------------------------------------------------------------------------|");

        printf("\n\n\tDados do paciente: ");

            nome_label:
            printf("Nome:");
            ok = 1;
            pos =0;
            c = '\0';
            while(c != '\n') {
                c=getchar();
                paciente.nome[pos++] = c;
                if (isdigit(c)) {
                    ok = 0;
                }
            }
            paciente.nome[pos] = '\0';
            if (!ok){
                printf("numeros nao permitidos\n");
                goto nome_label;
            }

            cpf_label:
            printf("CPF:");
            ok = 1;
            pos =0;
            c = '\0';
            while(c != '\n') {
                c=getchar();
                paciente.cpf[pos++] = c;
                if (isalpha(c)) {
                    ok = 0;
                }
            }
            paciente.cpf[pos] = '\0';
            if (!ok){
                printf("Letras e caracteres nao permitidos\n");
                goto cpf_label;
            }

            telefone_label:
            printf("Telefone:");
            ok = 1;
            pos =0;
            c = '\0';
            while(c != '\n') {
                c=getchar();
                paciente.telefone[pos++] = c;
                if (isalpha(c)) {
                    ok = 0;
                }
            }
            paciente.telefone[pos] = '\0';
            if (!ok){
                printf("Letras e caracteres nao permitidos\n");
                goto telefone_label;
            }


            printf("\tE-mail: ");
            fgets(&paciente.email[0],MAXNOME, stdin);

            system("cls");
            printf("\n\n\tEndereco do Paciente:");

            logradouro_label:
            printf("Logradouro:");
            ok = 1;
            pos =0;
            c = '\0';
            while(c != '\n') {
                c=getchar();
                paciente.endereco.logradouro[pos++] = c;
                if (isdigit(c)) {
                    ok = 0;
                }
            }
            paciente.endereco.logradouro[pos] = '\0';
            if (!ok){
                printf("numeros nao permitidos\n");
                goto logradouro_label;
            }

            numero_label:
            printf("Numero:");
            ok = 1;
            pos =0;
            c = '\0';
            while(c != '\n') {
                c=getchar();
                numstr[pos++] = c;
                if (isalpha(c)) {
                    ok = 0;
                }
            }
            numstr[pos] = '\0';
            if (!ok){
                printf("Letras e caracteres nao permitidos\n");
                goto numero_label;
            }
            paciente.endereco.numero = atoi(numstr);

            printf("\t\tComplemento: ");
            fgets(&paciente.endereco.complemento[0], MAXNOME, stdin);

            bairro_label:
            printf("Bairro:");
            ok = 1;
            pos =0;
            c = '\0';
            while(c != '\n') {
                c=getchar();
                paciente.endereco.bairro[pos++] = c;
                if (isdigit(c)) {
                    ok = 0;
                }
            }
            paciente.endereco.bairro[pos] = '\0';
            if (!ok){
                printf("numeros nao permitidos\n");
                goto bairro_label;
            }

            cidade_label:
            printf("Cidade:");
            ok = 1;
            pos =0;
            c = '\0';
            while(c != '\n') {
                c=getchar();
                paciente.endereco.cidade[pos++] = c;
                if (isdigit(c)) {
                    ok = 0;
                }
            }
            paciente.endereco.cidade[pos] = '\0';
            if (!ok){
                printf("numeros nao permitidos\n");
                goto cidade_label;
            }

            estado_label:
            printf("Cidade:");
            ok = 1;
            pos =0;
            c = '\0';
            while(c != '\n') {
                c=getchar();
               paciente.endereco.estado[pos++] = c;
                if (isdigit(c)) {
                    ok = 0;
                }
            }
            paciente.endereco.estado[pos] = '\0';
            if (!ok){
                printf("numeros nao permitidos\n");
                goto estado_label;
            }

            system("cls");
            printf("\n\n\tData de Nascimento:");

           nascimento_dia_label:
            printf("Dia:");
            ok = 1;
            pos =0;
            c = '\0';
            while(c != '\n') {
                c=getchar();
                numstr[pos++] = c;
                if (isalpha(c)) {
                    ok = 0;
                }
            }
            numstr[pos] = '\0';
            if (!ok){
                printf("Letras e caracteres nao permitidos\n");
                goto nascimento_dia_label;
            }

            nascimento_mes_label:
            printf("Mes:");
            ok = 1;
            pos =0;
            c = '\0';
            while(c != '\n') {
                c=getchar();
                numstr[pos++] = c;
                if (isalpha(c)) {
                    ok = 0;
                }
            }
            numstr[pos] = '\0';
            if (!ok){
                printf("Letras e caracteres nao permitidos\n");
                goto nascimento_mes_label;
            }

            nascimento_ano_label:
            printf("Ano:");
            pos =0;
            c = '\0';
            while(c != '\n') {
                c=getchar();
               numstr[pos++] = c;
                if (isalpha(c)) {
                    ok = 0;
                }
            }
            numstr[pos] = '\0';
            if (!ok){
                printf("Letras e caracteres nao permitidos\n");
                goto nascimento_ano_label;
            }

            system("cls");
            printf("\n\n\tData do diagnostico: ");

            diagnostico_dia_label:
            printf("Dia:");
            pos =0;
            c = '\0';
            while(c != '\n') {
                c=getchar();
                numstr[pos++] = c;
                if (isalpha(c)) {
                    ok = 0;
                }
            }
            numstr[pos] = '\0';
            if (!ok){
                printf("Letras e caracteres nao permitidos\n");
                goto diagnostico_dia_label;
            }

            diagnostico_mes_label:
            printf("Mes:");
            ok = 1;
            pos =0;
            c = '\0';
            while(c != '\n') {
                c=getchar();
                numstr[pos++] = c;
                if (isalpha(c)) {
                    ok = 0;
                }
            }
            numstr[pos] = '\0';
            if (!ok){
                printf("Letras e caracteres nao permitidos\n");
                goto diagnostico_mes_label;
            }

            diagnostico_ano_label:
            printf("Ano:");
            ok = 1;
            pos =0;
            c = '\0';
            while(c != '\n') {
                c=getchar();
                numstr[pos++] = c;
                if (isalpha(c)) {
                   ok = 0;
                }
            }
            numstr[pos] = '\0';
            if (!ok){
                printf("Letras e caracteres nao permitidos\n");
                goto diagnostico_ano_label;
            }
        __gravar_paciente(&paciente);
}

void buscar_paciente(Paciente *p, char *cpf) {
    FILE *fp;

    fp = fopen(NOME_ARQ_PACIENTE, "rb");

    if (fp == NULL) {
        fprintf(stderr, "Erro ao abrir %s para leitura!\n", NOME_ARQ_PACIENTE);
        exit(1);
    }

    while (!feof(fp)) {
        fread(p, sizeof(Paciente), 1, fp);
        if (strncpy(cpf, p->cpf, TAMCPF) == 0) {
           return;
        }
    }
    fclose(fp);

    fprintf(stderr, "O paciente com CPF %s nao existe!\n", cpf);
    exit(1);
}


