#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

#define TAMLOGIN 32
#define TAMSENHA 32
#define NOME_ARQ_USUARIO "usuario.bin"

typedef struct usuario_struct {
    char login[TAMLOGIN];
    char senha[TAMSENHA];
} Usuario;

extern int checar_usuario(char* login, char* senha);

#endif // LOGIN_H_INCLUDED
