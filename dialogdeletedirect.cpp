#include "dialogdeletedirect.h"
#include "ui_dialogdeletedirect.h"

dialogDeleteDirect::dialogDeleteDirect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogDeleteDirect)
{
    ui->setupUi(this);
}

dialogDeleteDirect::~dialogDeleteDirect()
{
    delete ui;
}
QString dialogDeleteDirect::diretorio() const{
    return ui->cmbDir->currentText();
}
void dialogDeleteDirect::on_btnOk_clicked()
{
    accept();
}
void dialogDeleteDirect::enviaComboItem(char *item){
    ui->cmbDir->addItem(item);
}
