#include <stdio.h>
#include <string.h>
#include "chatrpc.h"

#define MAXIMOUSUARIOS 100
#define MAXIMOMSGS 1000

int usuario_existe(usuario *u);
int novo_usuario(usuario *u);

usuario usuarios[MAXIMOUSUARIOS];
msg mensagens[MAXIMOMSGS];
int tamanhoUsuarios = 0;
int tamanhoMsgs = 0;

int * conectar_1_svc(usuario *u, struct svc_req *rqstp)
{
  static int result;

  if(tamanhoUsuarios < MAXIMOUSUARIOS)
  {
    int userid = usuario_existe(u);
    if(userid < 0)
      userid = novo_usuario(u);
    else
      usuarios[userid].status = ONLINE;
    result = userid;
  }
  else
    result = -1;

  return &result;
}

int * desconectar_1_svc(int *userid, struct svc_req *rqstp)
{
  static int result;

  if(*userid<0 || *userid>=tamanhoUsuarios)
    result = -1;
  else
  {
    usuarios[*userid].status = OFFLINE;
    result = 0;
  }

  return &result;
}

int * get_usuarios_num_1_svc(void *argp, struct svc_req *rqstp)
{
  static int result;

  int i;
  int total_conectados = 0;
  for(i=0; i<tamanhoUsuarios; i++)
    if(usuarios[i].status == ONLINE)
      total_conectados++;
  result = total_conectados;

  return &result;
}

usuario * get_usuario_1_svc(int *userid, struct svc_req *rqstp)
{
  static usuario result;

  if(*userid>=0 && *userid<tamanhoUsuarios)
    result = usuarios[*userid];

  return &result;
}

int * falar_1_svc(msg *m, struct svc_req *rqstp)
{
  static int result;

  if(tamanhoMsgs < MAXIMOMSGS)
  {
    mensagens[tamanhoMsgs] = *m;
    result = tamanhoMsgs++;
  }
  else
    result = -1;

  return &result;
}

int * get_msg_num_1_svc(void *argp, struct svc_req *rqstp)
{
  static int result;

  result = tamanhoMsgs;

  return &result;
}

msg * get_msg_1_svc(int *msgid, struct svc_req *rqstp)
{
  static msg result;

  if(*msgid>=0 && *msgid<tamanhoMsgs)
    result = mensagens[*msgid];

  return &result;
}

int usuario_existe(usuario *u)
{
  int i;
  for(i=0; i<tamanhoUsuarios; i++)
    if(strcmp(usuarios[i].login, u->login) == 0)
      return i;
  return -1;
}

int novo_usuario(usuario *u)
{
  u->status = ONLINE;
  usuarios[tamanhoUsuarios] = *u;
  return tamanhoUsuarios++;
}
