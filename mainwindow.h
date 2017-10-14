#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

extern "C" {
   #include "medias.h"
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    void on_actionAdicionar_Diret_rio_triggered();

    void on_actionRemover_Diret_rio_triggered();

    void on_btnPesquisa_clicked();

    void on_tblArquivos_cellDoubleClicked(int row, int column);

    void on_btnDelete_clicked();

    void on_btnAddExt_clicked();

    void on_btnRemExt_clicked();

    void on_btnRefresh_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
