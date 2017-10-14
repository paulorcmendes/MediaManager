#include "medias.h"

int verifica(nodeFolder *list, int codigo){
    char dataAtual[100];
    int op = 0;
    nodeFolder *tmp = list;
    while(tmp != NULL){
        ultimaModificacao(dataAtual, tmp->var->caminho);
        if(strcmp(tmp->var->mdf, dataAtual) || codigo == CODIGOVERMELHO){
            ultimaModificacao(tmp->var->mdf, tmp->var->caminho);
            dobbyIsFreeMedia(tmp->var->list);
            tmp->var->list = NULL;
            indexa(tmp->var->caminho, &(tmp->var->list));
            gravarMedias(tmp->var);
            reescreve(list);
            op++;
        }
        tmp = tmp->prox;
    }
    return op;
}
/*void gravarFolder(folder *fd){
    FILE *arq = fopen("folders.bdlegal", "a+");
    fwrite(fd, sizeof(folder), 1, arq);
    fclose(arq);
    gravarMedias(fd);
}*/
void gravarFolder(folder *fd){
    FILE *arq = fopen("folders.bdlegal", "a+");
    fprintf(arq, "%s\n", fd->caminho);
    fprintf(arq, "%s", fd->mdf);
    fclose(arq);
    gravarMedias(fd);
}
void gravarMedias(folder *fd){
    FILE *arq;
    nodeMedia *list = fd->list;
    char nomeArquivo[200];
    traduz(nomeArquivo, fd->caminho);
    arq = fopen(nomeArquivo, "w");
    printf("Gravando---\n");
    while(list!=NULL){
        printf("%s\n", list->arq);
        fprintf(arq, "%s", list->arq);
        if(list->prox!=NULL){
            fprintf(arq, "%s", "\n");
        }
        list = list->prox;
    }
    fclose(arq);

}
void traduz(char *nomeArq, char *nomeDir){
    int i = 0, tam;
    tam = strlen(nomeDir);
    for(i = 0; i<tam; i++){
        if(nomeDir[i] == '/')
            nomeArq[i] = '-';
        else if(nomeDir[i] == ':')
            nomeArq[i] = '_';
        else
            nomeArq[i] = nomeDir[i];
    }
    nomeArq[i] = '\0';
    strcat(nomeArq, ".medias");
}
void recupera(nodeFolder **list){
    FILE* arq;
    folder *fd;
    char nomeDir[300], mdf[100];
    arq = fopen("folders.bdlegal", "r");

    if(arq){
        while(!feof(arq)){
            fd = (folder *)malloc(sizeof(folder));
            fgets(nomeDir, 250, arq);
            fgets(mdf, 100, arq);
            //printf("\n%s", fd->caminho);
            nomeDir[strlen(nomeDir)-1] = '\0';
            strcpy(fd->caminho, nomeDir);
            strcpy(fd->mdf, nomeDir);
            if(isADir(fd->caminho)){
                //printf(" foi");

                //mdf[strlen(mdf)-1] = '\0';
                fd->list = NULL;
                insertFolder(list, fd, RECUPERACAO);
            }else{
                free(fd);
            }
        }
    }
    fclose(arq);
}
/*void recupera(nodeFolder **list){
    FILE* arq;
    folder *fd;
    int i, tam;
    arq = fopen("folders.bdlegal", "r");

    if(arq){
        fseek(arq, 0, SEEK_END);
        tam = ftell(arq)/sizeof(folder);
        rewind(arq);
        for(i = 0; i<tam; i++){
            fd = (folder *)malloc(sizeof(folder));
            fread(fd, sizeof(folder), 1, arq);
            //printf("\n%s", fd->caminho);
            if(isADir(fd->caminho)){
                //printf(" foi");
                fd->list = NULL;
                insertFolder(list, fd, RECUPERACAO);
            }else{
                free(fd);
            }
        }
    }
    fclose(arq);
}*/
void recuperaMedia(char *caminho, nodeMedia **lista){
    FILE *arq;
    //nodeMedia *md;
    char nomeArquivo[200];
    int tam;
    traduz(nomeArquivo, caminho);
    arq = fopen(nomeArquivo, "r");    
    if(arq){
        fseek(arq, 0, SEEK_END);
        tam = ftell(arq);
        rewind(arq);
        //md = (nodeMedia *)malloc(sizeof(nodeMedia));
        printf("Recuperando---");
        //for(i = 0; i<tam; i++){
        while(!feof(arq)){
            //fread(md, sizeof(node\Media), 1, arq);
            fgets(nomeArquivo, 200, arq);
            if(ftell(arq)!=tam){
                nomeArquivo[strlen(nomeArquivo)-1]='\0';
            }
            printf("\n%s", nomeArquivo);
            insertMedia(lista, nomeArquivo);
        }
       // free(md);
    }
    fclose(arq);
}
int existeFolder(nodeFolder *list, char *nome){
    nodeFolder *tmp = list;

    while(tmp!=NULL){
        if(strcmp(tmp->var->caminho, nome)==0){
            return 1;
        }
        tmp  = tmp->prox;
    }
    return 0;
}

nodeFolder * createNodeFolder(folder *fd){
    nodeFolder *tmp = (nodeFolder *)malloc(sizeof(nodeFolder));
    tmp->var = fd;
    tmp->prox = NULL;

    return tmp;
}
folder * createFolder(char *caminho){
    folder *tmp;
    if(isADir(caminho)){
        tmp = (folder*)malloc(sizeof(folder));
        strcpy(tmp->caminho, caminho);
        ultimaModificacao(tmp->mdf, caminho);
        tmp->list = NULL;
        return tmp;
    }
    return NULL;
}
nodeMedia * createNodeMedia(char *arq){
    nodeMedia *tmp = (nodeMedia *)malloc(sizeof(nodeMedia));
    tmp->prox = NULL;
    strcpy(tmp->arq, arq);

    return tmp;
}
void insertMedia(nodeMedia **lista, char *arq){
    nodeMedia *tmp = *lista;
    nodeMedia *novo = createNodeMedia(arq);
    if(tmp == NULL){
        *lista = novo;
    }else{
        while(tmp->prox !=NULL){
            tmp = tmp->prox;
        }
        tmp->prox = novo;
    }
}
void insertFolder(nodeFolder **lista, folder *fd, int tipo){
    nodeFolder *tmp = *lista;
    nodeFolder *pesq = *lista;
    nodeFolder *novo;
    int op = 1;
    if(fd!=NULL){
        novo = createNodeFolder(fd);
        if(tipo == NORMAL)
            indexa(fd->caminho, &(fd->list));
        else if(tipo == RECUPERACAO){
            recuperaMedia(fd->caminho ,&(fd)->list);
            //printf(fd->caminho);
        }
        if(tmp == NULL){
            *lista = novo;
            if(tipo == NORMAL) gravarFolder(fd);
        }else{
            while(pesq !=NULL && op){
                if(strcmp(pesq->var->caminho, novo->var->caminho)==0){
                    op = 0;
                    printf("\nDiretorio ja existe, filhao");
                }
                if(tmp->prox!=NULL){
                    tmp = tmp->prox;}
                pesq = pesq->prox;
            }
            if(op){
                tmp->prox = novo;
                if(tipo == NORMAL) gravarFolder(fd);
            }
        }
    }
}
void indexa(char *caminho, nodeMedia **lista){
  DIR *d;
  struct dirent *dir;
  char test[300];
  strcpy(test, caminho);  

  d = opendir(caminho);
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
        strcat(test, "/");
        strcat(test, dir->d_name);
        if(isAFile(test))
            insertMedia(lista, dir->d_name);
        strcpy(test, caminho);
    }
    closedir(d);
  }
}
void showFiles(nodeMedia *list){
    nodeMedia *tmp = list;

     while(tmp!=NULL){
        printf("File: %s\n", tmp->arq);
        tmp = tmp->prox;
    }
}
void showFolders(nodeFolder *list){
    nodeFolder *tmp = list;

    while(tmp!=NULL){
        printf("\nCaminho: %s\nTime: %s\n", tmp->var->caminho, tmp->var->mdf);
        showFiles(tmp->var->list);
        tmp = tmp->prox;
    }
}
void dobbyIsFreeMedia(nodeMedia *lista){
    nodeMedia *atual, *prox;
    atual = lista;
    while(atual != NULL){
        prox = atual->prox;
        free(atual);
        atual = prox;
    }
}
void dobbyIsFreeFolder(nodeFolder *lista){
    nodeFolder *atual, *prox;
    atual = lista;
    while(atual != NULL){
        prox = atual->prox;
        dobbyIsFreeMedia(atual->var->list);
        free(atual->var);
        free(atual);
        atual = prox;
    }
}
int isAFile(char *nameFile){
    struct stat path_stat;
    stat(nameFile, &path_stat);
    return S_ISREG(path_stat.st_mode);
}
int isADir(char *nameDir){
    struct stat s;
    int err = stat(nameDir, &s);
    if(-1 == err) {
        return 0;
    } else {
        if(S_ISDIR(s.st_mode)) {
            return 1;
        } else {
            return 0;
        }
    }
}
void ultimaModificacao(char *ret, char *nameFile) {
    char buffer[200];
    struct stat attr;
    stat(nameFile, &attr);
    sprintf(buffer, "%s", ctime(&attr.st_mtime));
    strcpy(ret, buffer);
}
void remover(nodeFolder **tira, char *nome){
    nodeFolder *ant, *aux = *tira;
    char nomeArq[200];

    if(*tira!=NULL){
        if(strcmp(nome, (aux->var->caminho)) == 0){
            traduz(nomeArq, aux->var->caminho);
            remove(nomeArq);
            *tira = aux->prox;
            reescreve(*tira);
            dobbyIsFreeMedia(aux->var->list);
            free(aux->var);
            free(aux);

        }else{
            ant = aux;
            aux = aux->prox;
            while((aux!=NULL) &&(strcmp(nome, aux->var->caminho))){
                ant = aux;
                aux = aux->prox;
            }
            if(aux!=NULL){
                ant->prox = aux->prox;
                reescreve(*tira);
                traduz(nomeArq, aux->var->caminho);
                remove(nomeArq);
                dobbyIsFreeMedia(aux->var->list);
                free(aux->var);
                free(aux);
            }
        }
    }
}
/*void reescreve(nodeFolder *list){
    FILE *arq = fopen("folders.bdlegal", "w");
    while(list!=NULL){
        fwrite(list->var, sizeof(folder), 1, arq);
        list = list->prox;
    }
    fclose(arq);
}*/
void reescreve(nodeFolder *list){
    FILE *arq = fopen("folders.bdlegal", "w");
    fclose(arq);
    while(list!=NULL){
        gravarFolder(list->var);
        list = list->prox;
    }
}

//Extensao
char *getExtensao(char *nome) {
    char *ponto = strrchr(nome, '.');
    if(!ponto || ponto == nome) return "";
    return ponto + 1;
}
void removerExtensao(nodeExtensao **tira, char *ext){
    nodeExtensao *ant;
    nodeExtensao *aux = *tira;
    if(*tira!=NULL){
        if(strcmp(ext, (aux->ext->name)) == 0){
            *tira = aux->prox;
            free(aux);
        }else{
            ant = aux;
            aux = aux->prox;
            while((aux!=NULL) &&(strcmp(ext, aux->ext->name))){
                ant = aux;
                aux = aux->prox;
            }
            if(aux!=NULL){
                ant->prox = aux->prox;
                free(aux);
            }
        }
    }
}
nodeExtensao * createNodeExtensao(extensao *ext){
    nodeExtensao *elm = (nodeExtensao *)malloc(sizeof(nodeExtensao));
    elm->ext = ext;
    elm->prox = NULL;
    return elm;
}
extensao * createExtensao(char *ext){
    extensao *elm = (extensao *)malloc(sizeof(extensao));
    strcpy(elm->name, ext);
    return elm;
}
void inserirExtensao(nodeExtensao **list, extensao *ext){
    nodeExtensao *tmp = *list;
    nodeExtensao *novo = createNodeExtensao(ext);
    if(tmp == NULL){
        *list = novo;
    }else{
        while(tmp->prox != NULL){
            tmp = tmp->prox;
        }
        tmp->prox = novo;
    }
}
void dobbyIsFreeExtensao(nodeExtensao *lista){
    nodeExtensao *atual, *prox;
    atual = lista;

    while(atual != NULL){
        prox = atual->prox;
        free(atual->ext);
        free(atual);
        atual = prox;
    }
}
void gravarExtensao(nodeExtensao *lista){
    nodeExtensao *tmp = lista;
    FILE *arq = fopen("extensoes.ext", "w");
    while(tmp!=NULL){
        fwrite(tmp->ext, sizeof(extensao), 1, arq);
        tmp = tmp->prox;
    }
}
int extensaoEsta(nodeExtensao *lista, char *ext){
    nodeExtensao *tmp = lista;
    while(tmp!=NULL){
        if(strcmp(ext, tmp->ext->name)==0) return 1;
        tmp = tmp->prox;
    }
    return 0;
}
void carregarExtensoes(nodeExtensao **lista){
    int tam, i;
    FILE *arq = fopen("extensoes.ext", "r");
    extensao *ext;
    if(arq!=NULL){
        fseek(arq, 0, SEEK_END);
        tam = ftell(arq)/sizeof(extensao);
        rewind(arq);
        for(i = 0; i<tam; i++){
            ext = (extensao *)malloc(sizeof(extensao));
            fread(ext, sizeof(extensao), 1, arq);
            inserirExtensao(lista, ext);
        }
    }
    fclose(arq);
}
void showExtensoes(nodeExtensao *lista){
    nodeExtensao *tmp = lista;

    while(tmp!=NULL){
        printf("\n---%s----", tmp->ext->name);
        tmp = tmp->prox;
    }
}

