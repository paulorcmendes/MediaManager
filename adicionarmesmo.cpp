#include "adicionarmesmo.h"
#include "ui_adicionarmesmo.h"

adicionarMesmo::adicionarMesmo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adicionarMesmo)
{
    ui->setupUi(this);
}

adicionarMesmo::~adicionarMesmo()
{
    delete ui;
}


void adicionarMesmo::enviaNomeMedia(char *item){
    char text[400];
    strcpy(text, (char *)"A mídia ");
    strcat(text, item);
    strcat(text, (char *)" já está indexada em outro diretório.\nEla ficará marcada em vermelho.");
    ui->lblMedia->setText((*new QString(text)));
}

void adicionarMesmo::on_btnOk_clicked()
{
    accept();
}
