#include "removermesmo.h"
#include "ui_removermesmo.h"

removerMesmo::removerMesmo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::removerMesmo)
{
    ui->setupUi(this);
}

removerMesmo::~removerMesmo()
{
    delete ui;
}

void removerMesmo::on_btnSim_clicked()
{
    accept();
}

void removerMesmo::on_btnNao_clicked()
{
    reject();
}
