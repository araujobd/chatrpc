#include <stdio.h>
#include <stdlib.h>
#include "chatrpc.h"

int conectar(CLIENT **,char *,usuario **);
int desconectar(CLIENT **, usuario **, int);
void falar(int, CLIENT *);
void ler_mensagens(CLIENT *);
char * status_string(STATUS);
int menu();
void usuarios_logados_num(CLIENT *);

int main(int argc, char *argv[])
{
  CLIENT *client = NULL;
  usuario *user = NULL;
  int opcao = 0;
  int userid;

  if (argc != 2)
  {
    printf("Uso: ./chatrpc_client host\n");
    return 1;
  }

  userid = conectar(&client, argv[1], &user);
  do
  {
    opcao = menu();
    switch(opcao)
    {
      case 0:
        break;
      case 1:
        usuarios_logados_num(client);
        break;
      case 2:
        falar(userid, client);
        break;
      case 3:
        ler_mensagens(client);
        break;
      default:
        printf("Opção Inválida\n");
        break;
    }
  } while(opcao != 0);

  return desconectar(&client, &user, userid);
}

int conectar(CLIENT **client, char *host, usuario **user)
{
  *user = malloc(sizeof(usuario));
  *client = clnt_create(host, CHATRPC, CHATRPC_VERSION, "udp");

  printf("Digite o login: ");
  scanf("%9s", (*user)->login);
  return *conectar_1(*user, *client);
}

int desconectar(CLIENT **client, usuario **user, int userid)
{
  int result = 0;
  result = *desconectar_1(&userid, *client);

  if(result != 0)
    printf("Erro ao desconectar\n");

  free(*client);
  free(*user);

  return result;
}

void falar(int userid, CLIENT *client)
{
  msg mensagem;

  printf("Digite aqui: ");
  scanf("\n%[^\n]%*c", mensagem.text);
  mensagem.userid = userid;

  if(*falar_1(&mensagem, client) < 0)
    printf("Erro ao enviar mensagem\n");
}

void ler_mensagens(CLIENT *client)
{
  msg *mensagem;
  usuario *user;
  int i;
  int mensagens = 0;
  void *p;
  mensagens = *get_msg_num_1(p, client);

  for(i=0; i<mensagens; i++)
  {
    mensagem = get_msg_1(&i, client);
    user = get_usuario_1(&(mensagem->userid), client);
    printf("%s (%s): %s\n", user->login, status_string(user->status), mensagem->text);
  }
}

char * status_string(STATUS status)
{
  if (status == ONLINE)
    return "ONLINE";
  else
    return "OFFLINE";
}

int menu()
{
  int opcao;

  printf("\nEscolha uma opção:\n");
  printf("\t0 - Desconectar\n");
  printf("\t1 - Número de usuários logados\n");
  printf("\t2 - Falar\n");
  printf("\t3 - Ler Mensagens\n");
  printf("Opção: ");

  scanf("%d", &opcao);
  return opcao;
}

void usuarios_logados_num(CLIENT * client)
{
  void * p;
  printf("\n\n %d usuários logados\n", *get_usuarios_num_1(p, client));
}
