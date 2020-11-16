#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "login.h"

static void flush_buffer() {
    char ch;
    while ((ch = getchar() != '\n') && (ch != EOF));
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
    char c='\0';
    int continua=1;
    int i, pos=0;

    printf("\n\n\t  >> Registrar usuario:\n");
    printf("\n\n\t  >> Login:");
    scanf("%s", usuario->login);
    
    flush_buffer();
    
    while (continua) {
      fflush(stdin);
      printf("\n\t  >> Senha:");
      for (i=0; i<pos; i++)
        printf("*"); 
      c=fgetc(stdin);
      usuario->senha[pos++]=c;
      if (c == '\n') {
        continua = 0;
        usuario->senha[pos] = '\0';
      } 
    } 
  
    printf("\n%s\n",usuario->senha);

    __registrar_usuario(usuario);
}

int checar_usuario() {
    FILE *fp;
    char login[TAMLOGIN];
    char senha[TAMSENHA];
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
        if (strncmp(&usuario.login[0], login, TAMLOGIN) == 0) {
            if (strncmp(&usuario.senha[0], senha, TAMSENHA) == 0) {
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}

