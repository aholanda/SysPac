#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "paciente.h"
#include "login.h"

int main(int argc, char**argv) {
    //setlocale(LC_ALL, "Portuguese"); //adaptação do programa ao idioma desejado

    char login[32], senha[32];
    int i=0, ok=0, pos=0;
    int nome_ok = 1;
    char c;

    nome_label:
    printf("Nome:");
    pos =0;
    c = '\0';
    while(c != '\n') {
        c=getchar();
        login[pos++] = c;
        if (isdigit(c)) {
            nome_ok = 0;
        }
    }
    login[pos] = '\0';
    if (!nome_ok){
        printf("numeros nao permitidos\n");
        goto nome_label;
    }

    printf("login=%s\n", login);
    printf("Fone:");
    return 0;

    registrar_usuario();

    while (i < 3 ) {
        // MENU LOGIN
        printf("Login:");
        scanf("%s", &login[0]);
        printf("Senha:");
        scanf("%s", &senha[0]);
        if (checar_usuario(login, senha) == 1) {
            ok =1;
            break;
        } else {
            fprintf(stderr, "Login %s não existe!\n", login);
            fprintf(stderr, "Tente de novo!\n");
        }
        i++;
    }

    //  MENU PACIENTES
    if (ok) {
        gravar_paciente();
}
}
