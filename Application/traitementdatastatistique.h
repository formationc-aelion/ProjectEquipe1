#ifndef TRAITEMENTDATASTATISTIQUE_H
#define TRAITEMENTDATASTATISTIQUE_H
#include <QObject>
#include"film.h"
#include "Staff.h"
#include<QDebug>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QSqlQuery>
#include <QComboBox>


void fillCbGenre(QComboBox* ComboBox)
{
    QSqlDatabase db1 = QSqlDatabase::addDatabase("QPSQL", "connexionBDDfilmgenre");
    db1.setHostName("127.0.0.1");
    db1.setDatabaseName("Application_Film");
    db1.setUserName("postgres");
    db1.setPassword("");
    bool ok = db1.open();

    qDebug ()<< ok;

    if (ok==false)
    {
        qDebug() <<"la connexion a échouée";
        exit(0);
    }


    QSqlQuery genres("SELECT DISTINCT fi_genre FROM film",db1);
    int i =0;
    while (genres.next()){
        QString genre = genres.value(0).toString();
        qDebug()<<genre;
        ComboBox->addItem(genre);
    }
}






#endif // TRAITEMENTDATASTATISTIQUE_H
