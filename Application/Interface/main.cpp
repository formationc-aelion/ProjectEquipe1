#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include<QDebug>
#include<QTranslator>
#include<QLocale>
#include<QLibraryInfo>

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

    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
