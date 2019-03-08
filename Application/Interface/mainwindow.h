#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <qsortfilterproxymodel.h>
#include "ajouterfilm.h"
#include<QDataWidgetMapper>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void ajouter_Film();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *mFilmModel;
    QSortFilterProxyModel *mFilmFilteredModel;
};

#endif // MAINWINDOW_H

