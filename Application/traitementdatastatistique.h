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
    QSqlDatabase db = QSqlDatabase::database("connexionBDDfilm");
    QSqlQuery genres("SELECT DISTINCT fi_genre FROM film",db);
    int i =0;
    while (genres.next()){
        QString genre = genres.value(0).toString();
        qDebug()<<genre;
        ComboBox->addItem(genre);
    }
}






#endif // TRAITEMENTDATASTATISTIQUE_H
