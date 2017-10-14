#ifndef ADICIONARMESMO_H
#define ADICIONARMESMO_H

#include <QDialog>

namespace Ui {
class adicionarMesmo;
}

class adicionarMesmo : public QDialog
{
    Q_OBJECT

public:
    explicit adicionarMesmo(QWidget *parent = 0);
    ~adicionarMesmo();
    void enviaNomeMedia(char *item);

private slots:

    void on_btnOk_clicked();

private:
    Ui::adicionarMesmo *ui;
};

#endif // ADICIONARMESMO_H
