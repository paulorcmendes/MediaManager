#ifndef REMOVERMESMO_H
#define REMOVERMESMO_H

#include <QDialog>

namespace Ui {
class removerMesmo;
}

class removerMesmo : public QDialog
{
    Q_OBJECT

public:
    explicit removerMesmo(QWidget *parent = 0);
    ~removerMesmo();

private slots:
    void on_btnSim_clicked();

    void on_btnNao_clicked();

private:
    Ui::removerMesmo *ui;
};

#endif // REMOVERMESMO_H
