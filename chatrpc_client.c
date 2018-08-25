#include <stdio.h>
#include <stdlib.h>
#include "chatrpc.h"

int conectar(CLIENT **,char *,usuario **);
void desconectar(CLIENT **, usuario **, int);
void falar(CLIENT *, int);
void ler_mensagens(CLIENT *);

int main(int argc, char *argv[])
{
  CLIENT *client = NULL;
  usuario *user = NULL;
  int userid;

  if (argc != 2)
  {
    printf("Uso: ./chatrpc_client host\n");
    return 1;
  }

  userid = conectar(&client, argv[1], &user);
  falar(client, userid);
  printf("\n=====Mensagens=====\n");
  ler_mensagens(client);

  return 0;
}

int conectar(CLIENT **client, char *host, usuario **user)
{
  *user = malloc(sizeof(usuario));
  *client = clnt_create(host, CHATRPC, CHATRPC_VERSION, "udp");

  printf("Digite o login: ");
  scanf("%9s", (*user)->login);
  return *conectar_1(*user, *client);
}

void desconectar(CLIENT **client, usuario **user, int userid)
{
  int result = 0;
  result = *desconectar_1(&userid, *client);
  if(result != 0)
    printf("Erro ao desconectar\n");
  free(*client);
  free(*user);
}

void falar(CLIENT *client, int userid)
{
  msg mensagem;

  printf("Digite aqui: ");
  scanf("%99s", mensagem.text);
  mensagem.userid = userid;

  if(*falar_1(&mensagem, client) < 0)
    printf("Erro ao enviar mensagem\n");
}

void ler_mensagens(CLIENT *client)
{
  msg mensagem;
  usuario user;
  int i;
  int mensagens = 0;
  void *p;
  mensagens = *get_msg_num_1(p, client);

  for(i=0; i<mensagens; i++)
  {
    mensagem = *get_msg_1(&i, client);
    user = *get_usuario_1(&(mensagem.userid), client);
    printf("%s: %s\n", user.login, mensagem.text);
  }
}
