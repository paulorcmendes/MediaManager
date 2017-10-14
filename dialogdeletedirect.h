#ifndef DIALOGDELETEDIRECT_H
#define DIALOGDELETEDIRECT_H

#include <QDialog>

namespace Ui {
class dialogDeleteDirect;
}

class dialogDeleteDirect : public QDialog
{
    Q_OBJECT

public:
    explicit dialogDeleteDirect(QWidget *parent = 0);
    ~dialogDeleteDirect();
    void enviaComboItem(char *item);
    QString diretorio() const;

private slots:
    void on_btnOk_clicked();

private:
    Ui::dialogDeleteDirect *ui;
};

#endif // DIALOGDELETEDIRECT_H
