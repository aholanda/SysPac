#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "paciente.h"
#include "login.h"

void menu_pacientes(){
        char cpf[TAMCPF];
        Paciente paciente;
        int op;
        do{
            system("cls");
            printf("\n |---------------------------------------------------------------------------------------------------|");
            printf("\n |                         CADASTRO PACIENTES DIAGNOSTICADOS COM SARS-COV-2                          |");
            printf("\n |---------------------------------------------------------------------------------------------------|");
            printf("\n |                                                                                                   |");
            printf("\n |   [1] Novo Cadastro           	                                                                   |");
            printf("\n |   [2] Buscar Paciente                                                                             |");
            printf("\n |   [3] Encerrar o Programa                                                                         |");
            printf("\n |                                                                                                   |");
            printf("\n |___________________________________________________________________________________________________|");

            printf("\n\n\t  >> Selecione uma opcao:  ");
            scanf("%i", &op);

            switch(op){
                case 1:
                    printf("\n\t  >> Opcao selecionada: 1 - Novo Cadastro");
                    gravar_paciente();
                break;
                case 2:
                    printf("Opcao selecionada: 2 - Buscar Cadastro\n");
                    printf("\n\t  >> Informe o CPF:");
                    fgets(&cpf[0], TAMCPF, stdin);
                    buscar_paciente(&paciente, &cpf[0]);
                break;
                case 3:
                    printf("\n\t  >> Opcao selecionada: 3 - Encerrar o Programa");
                    exit(0);
                break;
                default:
                    printf("\n\n\t  >> Opcao invalida");
            }
        }while(op != 3);

}

void menu_login(){
        int op, ok=0;
        do{
            system("cls");
            printf("\n |---------------------------------------------------------------------------------------------------|");
            printf("\n |                                     SISTEMA CADASTRO COVID-19                                     |");
            printf("\n |---------------------------------------------------------------------------------------------------|");
            printf("\n |                                                                                                   |");
            printf("\n |   [1] Cadastrar Novo Usuario                                                                      |");
            printf("\n |   [2] Acessar Menu Principal                                                                      |");
            printf("\n |   [3] Encerrar o Programa                                                                         |");
            printf("\n |                                                                                                   |");
            printf("\n |___________________________________________________________________________________________________|");

            printf("\n\n\t  >> Selecione uma opcao:  ");
            scanf("%d", &op);

            switch(op){
                case 1:
                    printf("\n\t  >> Opcao selecionada: 1 - Novo Cadastro");
                    registrar_usuario();
                    ok = 1;
                break;
                case 2:
                    printf("\n\t  >> Opcao selecionada: 2 - Acesso ao menu");
                    printf("\n\t  >> Realizar login: \n");
                    checar_usuario();
                break;
                case 3:
                    printf("\n\t  >> Opcao selecionada: 3 - Encerrar o Programa");
                    exit(0);
                break;
                default:
                    printf("\n\t  >> Opcao invalida");
                    break;
            }

        } while(op != 3 || ok != 1);

}

int main(int argc, char**argv) {
	menu_login();

    //menu_pacientes();

}
