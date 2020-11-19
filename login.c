#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "login.h"
#include "io.h"

#define WARN_MARK "#"
#define ENTER_MARK ">"

/* Main control chars definition */
#define  ENTER 13
#define TAB 9
#define BKSP 8 /* espaco */

static void __registrar_usuario(Usuario *usuario) {
    FILE *fp;

    fp = fopen(NOME_ARQ_USUARIO, "ab");

    if (fp == NULL) {
        fprintf(stderr, "Erro ao abrir %s para escrita!\n", NOME_ARQ_USUARIO);
        exit(1);
    }
    fwrite(usuario, sizeof(Usuario), 1, fp);
    fclose(fp);
}

void registrar_usuario(Usuario *usuario) {
    int i;
    char ch;

    flush_buffer();
    printf("%s Registrar usuario:\n", WARN_MARK);
    printf("%s Login: ", ENTER_MARK);
    fflush(stdin);
    for (i = 0; i < MAXLOGIN; i++) {
        usuario->login[i] = getc(stdin);
        if (usuario->login[i] == '\n') {
            usuario->login[i] = '\0';
            break;
        }
    }

    printf("%s Senha: ", ENTER_MARK);
    fflush(stdin);
    system ("/bin/stty raw");    
    for (i = 0; i < MAXPW; i++) {    
        ch = getch();

        if(ch == ENTER || ch == TAB) {
            usuario->senha[i] = '\0';
            break;
        } else if (ch == BKSP) {
            i--;
            printf("\b \b");
        } else {
            usuario->senha[i] = ch;
            printf("* \b");
        }
    }
    system ("/bin/stty cooked");    
    
    printf("\n%s\n", usuario->senha);

    __registrar_usuario(usuario);
}

int checar_usuario() {
    FILE *fp;
    char ch, login[MAXLOGIN];
    char senha[MAXPW];
    Usuario usuario;
    int i;
  
    flush_buffer();
    printf("%s Autenticacao do usuario:\n", WARN_MARK);
    printf("%s Login: ", ENTER_MARK);
    fflush(stdin);
    for (i = 0; i < MAXLOGIN; i++) {
        login[i] = getc(stdin);
        if (login[i] == '\n') {
            login[i] = '\0';
            break;
        }
    }

    printf("%s Senha: ", ENTER_MARK);
    fflush(stdin);
    system ("/bin/stty raw");    
    for (i = 0; i < MAXPW; i++) {    
        ch = getch();

        if(ch == ENTER || ch == TAB) {
            senha[i] = '\0';
            break;
        } else if (ch == BKSP) {
            i--;
            printf("\b \b");
        } else {
            senha[i] = ch;
            printf("* \b");
        }
    }
    system ("/bin/stty cooked");    
    
    fp = fopen(NOME_ARQ_USUARIO, "rb");

    if (fp == NULL) {
        fprintf(stderr, "Erro ao abrir %s para leitura!\n", NOME_ARQ_USUARIO);
        exit(1);
    }

    while (!feof(fp)) {
        fread(&usuario, sizeof(Usuario), 1, fp);
        if (strncmp(&usuario.login[0], login, MAXLOGIN) == 0) {
            if (strncmp(&usuario.senha[0], senha, MAXPW) == 0) {
                printf("\nAviso: autenticacao realizada com sucesso.\n");
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}

