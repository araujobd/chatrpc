# Instruções

Para criar o makefile rode:

```
  $ rpcgen -Sm chatrpc.x > Makefile
```

Altere as seguintes linhas (9 e 11):

```
SOURCES_CLNT.c = $(CLIENT).c
```

```
SOURCES_SVC.c = $(SERVER).c
```

Para compilar rode:

```
  $ make
```
