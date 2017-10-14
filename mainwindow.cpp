#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogdeletedirect.h"
#include "adicionarmesmo.h"
#include "removermesmo.h"
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QDebug>

nodeFolder *lista;
nodeExtensao *listaExt;

void gerateTabela(QTableWidget *tblShow);
void showFiles(nodeFolder *lista, QTableWidget *tblShow, QWidget *pai);
void pesquisaMedia(nodeFolder *list, char *file, QTableWidget *tblShow);
void atualizaTabela(QTableWidget *tblShow, QWidget *pai, QLineEdit *linePesq, int code);
void atualizaExtensoes(QTableWidget *tblExtensoes);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(width(), height());
    lista = NULL;
    listaExt = NULL;
    recupera(&lista);
    carregarExtensoes(&listaExt);

    atualizaTabela(ui->tblArquivos, this, ui->txtPesquisa, NORMAL);
    atualizaExtensoes(ui->tblExtensoes);
}

MainWindow::~MainWindow()
{
    dobbyIsFreeFolder(lista);
    gravarExtensao(listaExt);
    dobbyIsFreeExtensao(listaExt);
    delete ui;
}

void MainWindow::on_actionAdicionar_Diret_rio_triggered()
{
    char name[300];
    QString dir = QFileDialog::getExistingDirectory(this, tr("Selecione a Pasta"),"/home",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    strcpy(name, (char *)dir.toStdString().c_str());
    insertFolder(&lista, createFolder(name), NORMAL);
    atualizaTabela(ui->tblArquivos, this, ui->txtPesquisa, NORMAL);
}
void geraTabela(QTableWidget *tblShow){
    QStringList headers;
    headers << "Mídia"<<"Diretório";
    tblShow->setColumnCount(2);
    tblShow->setRowCount(0);
    tblShow->setHorizontalHeaderLabels(headers);
    tblShow->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tblShow->horizontalHeader()->setStretchLastSection( true );
}
void showFiles(nodeFolder *lista, QTableWidget *tblShow, QWidget *pai){
    nodeFolder *tmp1 = lista;
    nodeMedia *tmp2;
    char textTbl[300];
    int size, i, repetido = 0;
    adicionarMesmo dial(pai);

    while(tmp1 != NULL){
       tmp2 = tmp1->var->list;
       while(tmp2!=NULL){
           if(listaExt == NULL || extensaoEsta(listaExt, getExtensao(tmp2->arq))){
               size = tblShow->rowCount();
               for(i = 0; i<size; i++){
                   strcpy(textTbl, (char *)tblShow->item(i, 0)->text().toStdString().c_str());
                   if(strcmp(textTbl, tmp2->arq)==0){
                       repetido = 1;
                       dial.enviaNomeMedia(tmp2->arq);
                       //result = dial.exec();
                       dial.exec();
                       break;
                   }
               }
              if(!repetido){
                  tblShow->insertRow(size);
                  tblShow->setItem(size, 0, new QTableWidgetItem(tmp2->arq));
                  tblShow->setItem(size, 1, new QTableWidgetItem(tmp1->var->caminho));
                  tblShow->resizeColumnsToContents();
                  tblShow->horizontalHeader()->setStretchLastSection( true );
              }else{
                  //if(result == QDialog::Accepted){
                  tblShow->insertRow(size);
                  tblShow->setItem(size, 0, new QTableWidgetItem(tmp2->arq));
                  tblShow->setItem(size, 1, new QTableWidgetItem(tmp1->var->caminho));
                  tblShow->item(size, 0)->setBackground(Qt::red);
                  tblShow->resizeColumnsToContents();
                  tblShow->horizontalHeader()->setStretchLastSection( true );
                  //}
              }
              repetido = 0;
            }
           tmp2 = tmp2 ->prox;
       }
        tmp1=tmp1->prox;
    }

}
void pesquisaMedia(nodeFolder *list, char *file, QTableWidget *tblShow){
    nodeFolder *tmpF = list;
    nodeMedia *tmpM = NULL;
    char textTbl[300];
    int size, i;
    geraTabela(tblShow);
    while(tmpF != NULL){
        tmpM = tmpF->var->list;
        while(tmpM!=NULL){

            if(strstr(tmpM->arq, file)!=NULL){
                size = tblShow->rowCount();
                tblShow->insertRow(size);
                tblShow->setItem(size, 0, new QTableWidgetItem(tmpM->arq));
                tblShow->setItem(size, 1, new QTableWidgetItem(tmpF->var->caminho));
                tblShow->resizeColumnsToContents();
                tblShow->horizontalHeader()->setStretchLastSection( true );
                for(i = 0; i<size; i++){

                    strcpy(textTbl, (char *)tblShow->item(i, 0)->text().toStdString().c_str());
                    if(strcmp(textTbl, tmpM->arq)==0){
                        tblShow->item(size, 0)->setBackground(Qt::red);
                        break;
                    }
                }

            }
            tmpM = tmpM->prox;
        }
        tmpF = tmpF->prox;
    }
}
void atualizaTabela(QTableWidget *tblShow, QWidget *pai, QLineEdit *linePesq, int code){
    verifica(lista, code);
    geraTabela(tblShow);
    showFiles(lista, tblShow, pai);
    linePesq->setText("");

}
void atualizaExtensoes(QTableWidget *tblExtensoes){
    nodeExtensao *tmp = listaExt;
    QStringList headers;
    int size;
    headers<<"Extensões";
    tblExtensoes->setColumnCount(1);
    tblExtensoes->setRowCount(0);
    tblExtensoes->setHorizontalHeaderLabels(headers);
    tblExtensoes->horizontalHeader()->setStretchLastSection( true );

    while(tmp!=NULL){
        size = tblExtensoes->rowCount();
        tblExtensoes->insertRow(size);
        tblExtensoes->setItem(size, 0, new QTableWidgetItem(tmp->ext->name));
        tblExtensoes->item(size,0)->setTextAlignment(Qt::AlignCenter);
        tmp = tmp->prox;
    }
}

void MainWindow::on_actionRemover_Diret_rio_triggered()
{
    char diretorio[300];
    int ret;
    dialogDeleteDirect dial(this);
    nodeFolder *tmp = lista;

    while(tmp!=NULL){
        dial.enviaComboItem(tmp->var->caminho);
        tmp = tmp->prox;
    }

    ret = dial.exec();

    if(ret == QDialog::Accepted){
        strcpy(diretorio, (char *)dial.diretorio().toStdString().c_str());
        remover(&lista, diretorio); 
        atualizaTabela(ui->tblArquivos, this, ui->txtPesquisa, NORMAL);
    }
}

void MainWindow::on_btnPesquisa_clicked()
{
    pesquisaMedia(lista, (char*)ui->txtPesquisa->text().toStdString().c_str(), ui->tblArquivos);
}

void MainWindow::on_tblArquivos_cellDoubleClicked(int row, int column)
{
    char path[300], text[100];
    strcpy(path,(char *)ui->tblArquivos->item(row, 1)->text().toStdString().c_str());
    if(column == 0){
        strcpy(text,(char *)ui->tblArquivos->item(row, 0)->text().toStdString().c_str());
        strcat(path, (char *)"/");
        strcat(path, text);
    }

    QDesktopServices::openUrl( QUrl::fromLocalFile(path) );
}

void MainWindow::on_btnDelete_clicked()
{
    QList<QTableWidgetItem *>  selected =  ui->tblArquivos->selectedItems();
    char path[300];
    int result, qtd=0;
    removerMesmo dial(this);
    result = dial.exec();
    if(result == QDialog::Accepted){
        foreach (QTableWidgetItem *item , selected){
            if(item->column()==0){
                strcpy(path, ui->tblArquivos->item(item->row(), 1)->text().toStdString().c_str());
                strcat(path, (char *)"/");
                strcat(path, (char *)item->text().toStdString().c_str());
                remove(path);
                qtd++;
            }
        }
    }
    atualizaTabela(ui->tblArquivos, this, ui->txtPesquisa, CODIGOVERMELHO);

}

void MainWindow::on_btnAddExt_clicked()
{
    char ext[30];
    strcpy(ext, (char *)ui->txtExtensao->text().toStdString().c_str());
    if(strcmp(ext, "") && !extensaoEsta(listaExt, ext)){
        inserirExtensao(&listaExt, createExtensao(ext));
        atualizaExtensoes(ui->tblExtensoes);
        atualizaTabela(ui->tblArquivos, this, ui->txtPesquisa, NORMAL);
    }
    ui->txtExtensao->setText("");

}

void MainWindow::on_btnRemExt_clicked()
{
    QList<QTableWidgetItem *>  selected =  ui->tblExtensoes->selectedItems();
    char ext[30];

    foreach (QTableWidgetItem *item , selected){
         strcpy(ext, ui->tblExtensoes->item(item->row(), item->column())->text().toStdString().c_str());
         removerExtensao(&listaExt, ext);
    }
    atualizaExtensoes(ui->tblExtensoes);
    atualizaTabela(ui->tblArquivos, this, ui->txtPesquisa, NORMAL);
}

void MainWindow::on_btnRefresh_clicked()
{
    atualizaTabela(ui->tblArquivos, this, ui->txtPesquisa, CODIGOVERMELHO);
}
