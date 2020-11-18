#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "paciente.h"
#include "login.h"
 
#define SELECT_MARK "*"

int print_menu_paciente() {
  int op; 
  printf("|--------------------------------------------------------------|\n");
  printf("|      CADASTRO PACIENTES DIAGNOSTICADOS COM SARS-COV-2        |\n");
  printf("|--------------------------------------------------------------|\n");
  printf("|                                                              |\n");
  printf("|   [1] Novo Cadastro           	                             |\n");
  printf("|   [2] Buscar Paciente                                        |\n");
  printf("|   [3] Encerrar o Programa                                    |\n");
  printf("|                                                              |\n");
  printf("|______________________________________________________________|\n");

            
  
  printf("\n%s Selecione uma opcao: ", SELECT_MARK);
  scanf("%d", &op);

  return op;
}

void menu_pacientes(){
        Paciente paciente;
        int op=-1;
        
        do{
           op =print_menu_paciente();
            switch(op){
                case 1:
                    printf("\n\t  >> Opcao selecionada: 1 - Novo Cadastro");
                    gravar_paciente();
                break;
                case 2:
                    flush_buffer();                    
                    buscar_paciente(&paciente);
                    printf("Achou o louco do %s com CPF %s\n", paciente.nome, paciente.cpf);
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

int print_menu_login () {
  int op;

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


void menu_login(){
        int op=-1, ok=0;
        Usuario usuario;

        do {
          op =print_menu_login();

          switch(op){
            case 1:
              printf("\n\t  >> Opcao 1 - Novo Cadastro");
              registrar_usuario(&usuario);
              ok = 1;
              break;
            case 2:
              printf("\n\t  >> Opcao 2 - Acesso ao menu");
              printf("\n\t  >> Realizar login: \n");
              checar_usuario();
              break;
            case 3:
              printf("\n\t  >> Opcao 3 - Encerrar o Programa");
              exit(0);
              break;
              default:
              printf("\n\t  >> Opcao invalida");
              break;
            }
        } while(ok != 1);
}

int main(int argc, char**argv) {
	//menu_login();

  menu_pacientes();

}
