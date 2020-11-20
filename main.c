#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "paciente.h"
#include "login.h"
#include "io.h"

#define WARN_MARK "#"
#define ENTER_MARK "*"


int print_menu_paciente() {
  int op;

  clrscr();
  printf("|--------------------------------------------------------------|\n");
  printf("|      CADASTRO PACIENTES DIAGNOSTICADOS COM SARS-COV-2        |\n");
  printf("|--------------------------------------------------------------|\n");
  printf("|                                                              |\n");
  printf("|   [1] Novo Cadastro           	                             |\n");
  printf("|   [2] Buscar Paciente                                        |\n");
  printf("|   [3] Encerrar o Programa                                    |\n");
  printf("|                                                              |\n");
  printf("|______________________________________________________________|\n");


  printf("%s Selecione uma opcao: ", ENTER_MARK);
  (void)scanf("%i", &op);

  return op;
}

void menu_pacientes(){
        Paciente paciente;
        int op=-1, ok=0;

        do{
           op =print_menu_paciente();
            switch(op){
                case 1:
                  printf("%s%s Novo Cadastro\n", WARN_MARK, WARN_MARK);
                  gravar_paciente();
                  ok = 1;
                break;
                case 2:
                    buscar_paciente(&paciente);
                    printf("Achou o louco do %s com CPF %s\n", paciente.nome, paciente.cpf);
                    ok = 1;
                break;
                case 3:
                    printf("\n\t  >> Opcao selecionada: 3 - Encerrar o Programa");
                    exit(EXIT_SUCCESS);
                break;
                default:
                    printf("\n\n\t  >> Opcao invalida");
            }
        }while(ok == 1);
}

int print_menu_login () {
  int op;

  clrscr();
  printf("|---------------------------------------------------------------------|\n");
  printf("|       SISTEMA CADASTRO COVID-19                                     |\n");
  printf("|---------------------------------------------------------------------|\n");
  printf("|                                                                     |\n");
  printf("|   [1] Cadastrar Novo Usuario                                        |\n");
  printf("|   [2] Acessar Menu Principal                                        |\n");
  printf("|   [3] Encerrar o Programa                                           |\n");
  printf("|                                                                     |\n");
  printf("|_____________________________________________________________________|\n");

  printf("* Selecione uma opcao: ");
  scanf("%d", &op);
  return op;
}


int menu_login(){
        int op=-1, ok=0;
        Usuario usuario;

        do {
          op = print_menu_login();

          switch(op){
            case 1:
              printf("%s Novo Cadastro\n", WARN_MARK);
              registrar_usuario(&usuario);
              break;
            case 2:
              printf("%s Acesso ao menu\n", WARN_MARK);
              printf("\t%s Realizar login: \n", WARN_MARK);
              return checar_usuario();
              ok = 1;
              break;
            case 3:
              printf("%s Encerrando o program, gracas a Deus\n", WARN_MARK);
              ok = 1;
              break;
              default:
                fprintf(stderr, "FATAL: Opcao %d invalida\n", op);
                exit(EXIT_FAILURE);
              break;
            }
        } while(ok != 1);

   return 0;
}

int main(int argc, char**argv) {
  int ok=0;

  ok = menu_login();

  if (ok) {
    menu_pacientes();
  } else {
    fprintf(stderr, "Voce nao tem permissao para acessar o menu dos pacientes, por favor cadastre um usuário e senha!!!\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
