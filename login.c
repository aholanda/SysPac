#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "login.h"

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

static char*get_pass(char senha[]) {
    int pos=0;
    int c;

    while((c=getc(stdin))!='\n'){
        printf("%c", c);
        senha[pos++]=c;
        putchar('*');
    }
    return &senha[0];
}
void registrar_usuario() {
    Usuario usuario;

    printf("Registrar usuario:\n");
    printf("Login:");
    scanf("%s", &usuario.login[0]);

    printf("Senha:");
    get_pass(&usuario.senha[0]);

    __registrar_usuario(&usuario);
}


int checar_usuario(char *login, char *senha) {
    FILE *fp;
    Usuario u;

    fp = fopen(NOME_ARQ_USUARIO, "rb");

    if (fp == NULL) {
        fprintf(stderr, "Erro ao abrir %s para leitura!\n", NOME_ARQ_USUARIO);
        exit(1);
    }

    while (!feof(fp)) {
        fread(&u, sizeof(Usuario), 1, fp);
        if (strncmp(&u.login[0], login, TAMLOGIN) == 0) {
            if (strncmp(&u.senha[0], senha, TAMSENHA) == 0) {
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}
