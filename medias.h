#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>

#define RECUPERACAO 1
#define NORMAL 2
#define CODIGOVERMELHO 5673

typedef struct nodeMedia_{
    char arq[225];
    struct nodeMedia_ *prox;
}nodeMedia;

typedef struct folder_{
    char caminho[200];
    char mdf[100];
    nodeMedia *list;
}folder;

typedef struct nodeFolder_{
    folder *var;
    struct nodeFolder_ *prox;
}nodeFolder;

typedef struct extensao_{
    char name[30];
}extensao;

typedef struct nodeExtensao_{
    extensao *ext;
    struct nodeExtensao_ *prox;
}nodeExtensao;

int verifica(nodeFolder *list, int codigo);
folder * createFolder(char *caminho);
nodeMedia * createNodeMedia(char *arq);
void insertMedia(nodeMedia **lista, char *arq);
void insertFolder(nodeFolder **lista, folder *fd, int tipo);
void indexa(char *caminho, nodeMedia **lista);
void showFiles(nodeMedia *list);
void dobbyIsFreeMedia(nodeMedia *lista);
void dobbyIsFreeFolder(nodeFolder *lista);
int isAFile(char *nameFile);
int isADir(char *nameDir);
void showFolders(nodeFolder *list);
void recupera(nodeFolder **list);
void ultimaModificacao(char *ret, char *nameFile);
void gravarMedias(folder *fd);
void traduz(char *nomeArq, char *nomeDir);
void recuperaMedia(char *caminho, nodeMedia **lista);
void remover(nodeFolder **tira, char *nome);
void reescreve(nodeFolder *list);

char *getExtensao(char *nome);
void removerExtensao(nodeExtensao **tira, char *ext);
nodeExtensao * createNodeExtensao(extensao *ext);
extensao * createExtensao(char *ext);
void inserirExtensao(nodeExtensao **list, extensao *ext);
void dobbyIsFreeExtensao(nodeExtensao *lista);
void gravarExtensao(nodeExtensao *lista);
int extensaoEsta(nodeExtensao *lista, char *ext);
void carregarExtensoes(nodeExtensao **lista);
void showExtensoes(nodeExtensao *lista);
