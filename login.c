#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "login.h"

int getch() {
    struct termios oldtc, newtc;
    int ch;
    tcgetattr(STDIN_FILENO, &oldtc);
    newtc = oldtc;
    newtc.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
    ch=getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);
    return ch;
}

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
    char senha[MAXPW] = {0};
    char ch = '\0';
    int i=0;

    printf("\n\n\t  >> Registrar usuario:\n");
    printf("\n\n\t  >> Login:");
    scanf("%s", usuario->login);
    flush_buffer();

    printf("\n\n\t Digite a senha e");
    printf("tecle Enter para sair.\n\n");

    for (;;) {
        ch = getch();
        senha[i++] = ch;
        printf("*");
        if(ch == '\n') {
            i--;
            senha[i] = '\0';
            break;
        }
    }
  
    printf("\n%s\n", senha);

    strncpy(usuario->senha, senha, MAXPW);

    __registrar_usuario(usuario);
}

int checar_usuario() {
    FILE *fp;
    char login[MAXLOGIN];
    char senha[MAXPW];
    Usuario usuario;
  
    printf("Autenticar usuario:\n");
    printf("Login:\n");
    scanf("%s", &login[0]);
    printf("Senha:\n");
    scanf("%s", &senha[0]);

    fp = fopen(NOME_ARQ_USUARIO, "rb");

    if (fp == NULL) {
        fprintf(stderr, "Erro ao abrir %s para leitura!\n", NOME_ARQ_USUARIO);
        exit(1);
    }

    while (!feof(fp)) {
        fread(&usuario, sizeof(Usuario), 1, fp);
        if (strncmp(&usuario.login[0], login, MAXLOGIN) == 0) {
            if (strncmp(&usuario.senha[0], senha, MAXPW) == 0) {
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}

