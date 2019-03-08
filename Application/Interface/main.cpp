#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "connexionBDDfilm");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("Application_Film");
    db.setUserName("postgres");
    db.setPassword("");
    bool ok = db.open();

    qDebug ()<< ok;

    if (ok==false)
    {
        qDebug() <<"la connexion a échouée";
        exit(0);
    }

    MainWindow w;
    w.show();

    return a.exec();
}
