#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

#define TAMLOGIN 32
#define TAMSENHA 32
#define NOME_ARQ_USUARIO "usuario.bin"

typedef struct usuario_struct {
    char login[TAMLOGIN];
    char senha[TAMSENHA];
} Usuario;

extern int checar_usuario();
extern void registrar_usuario(Usuario *usuario);

#endif // LOGIN_H_INCLUDED
