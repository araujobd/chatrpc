enum STATUS {ONLINE = 0, OFFLINE};

struct usuario {
  char login[10];
  STATUS status;
};

struct msg {
  int userid;
  char text[100];
};

program CHATRPC {
  version CHATRPC_VERSION {
    int CONECTAR(usuario u) = 1;
    int DESCONECTAR(int userid) = 2;
    int GET_USUARIOS_NUM() = 3;
    usuario GET_USUARIO(int userid) = 4;
    int FALAR(msg m) = 5;
    int GET_MSG_NUM() = 6;
    msg GET_MSG(int msgid) = 7;
  } = 1;
} = 200000001;

/*
program CHATRPC {
  version CHATRPC_VERSION {
    int CONECTAR(usuario u) = 1;
    int DESCONECTAR(usuario u) = 2;
    int GET_USUARIOS_NUM() = 3;
    usuario GET_USUARIO(int userid) = 4;
    int FALAR(msg m) = 5;
    int GET_MSG_NUM() = 6;
    msg GET_MSG(int msgid) = 7;
  } = 1;
} = 200000001;
*/
