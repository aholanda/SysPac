#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

#define MAXLOGIN 32
#define MAXPW 32
#define NOME_ARQ_USUARIO "usuario.bin"

typedef struct usuario_struct {
    char login[MAXLOGIN];
    char senha[MAXPW];
} Usuario;

extern int checar_usuario();
extern void registrar_usuario(Usuario *usuario);

static void flush_buffer() {
    char ch;
    while ((ch = getchar() != '\n') && (ch != EOF));
}

#endif // LOGIN_H_INCLUDED
