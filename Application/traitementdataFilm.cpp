#include "traitementdataFilm.h"
#include <QImage>
#include <QPixmap>
#include <QBuffer>

QSqlTableModel* CreateModelFilm (QObject *ui)
{
    QSqlDatabase db = QSqlDatabase::database("connexionBDDfilm");
    QSqlTableModel *mFilmModel = new QSqlTableModel (ui,db);
    mFilmModel->setTable("film");
    mFilmModel->select();
    mFilmModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    return mFilmModel;
}

QSortFilterProxyModel* CreateSortingModelFilm (QObject *ui,QSqlTableModel *FilmModel)
{
    QSqlDatabase db = QSqlDatabase::database("connexionBDDfilm");
    QSortFilterProxyModel *mFilmSortingModel = new QSortFilterProxyModel(ui);
    mFilmSortingModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    mFilmSortingModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    mFilmSortingModel->sort(1, Qt::AscendingOrder);
    mFilmSortingModel->setDynamicSortFilter(true);
    mFilmSortingModel->setSourceModel(FilmModel);
    return mFilmSortingModel;
}



int Conversionint(QString DureeFilm){
    QString conversion_galere = DureeFilm;

    //CaseInsensitive gere h et H et aussi min et MIN
    //fct contains me renvoi un bool
    bool contient_h = conversion_galere.contains('h', Qt::CaseInsensitive);
    bool contient_min = conversion_galere.contains("min", Qt::CaseInsensitive);

    if (contient_h == 1 && contient_min == 1)
    {

        QStringList list1 = conversion_galere.split('h',QString::SkipEmptyParts);
        list1[1] = list1[1].remove("min");
        list1[1] = list1[1].left(2);
        QString element_heure = list1.at(0);
        int heure = element_heure.toInt();
        heure *= 60;
        QString element_minutes = list1.at(1);
        int minutes = element_minutes.toInt();
        int resultat = heure + minutes;
        qDebug()<< resultat;
        return heure + minutes;

    }
    else if (contient_h == 0 && contient_min == 1)
    {
        QString element_minutes = conversion_galere.left(2);
        int minutes = element_minutes.toInt();
        qDebug()<< minutes;
        return minutes;
    }

    else if (contient_h == 1 && contient_min == 0)

    {
        QString element_heure = conversion_galere.left(1);
        int heure = element_heure.toInt();
        heure *= 60;
        qDebug()<< heure;

        return heure;

    }

    else
    {
        int a = 0;
        return a;
    }

}

void AjoutFilm(Film FilmAdd,QSqlTableModel *FilmModel )
{
    FilmModel->insertRow(FilmModel->rowCount());
    int lastrow=FilmModel->rowCount()-1;

    FilmModel->setData(FilmModel->index(lastrow,1),FilmAdd.titre());
    FilmModel->setData(FilmModel->index(lastrow,2),FilmAdd.annee());
    FilmModel->setData(FilmModel->index(lastrow,3),FilmAdd.genre());
    FilmModel->setData(FilmModel->index(lastrow,4),FilmAdd.duree());
    FilmModel->setData(FilmModel->index(lastrow,5),FilmAdd.langue());
    FilmModel->setData(FilmModel->index(lastrow,6),FilmAdd.photo());
    FilmModel->setData(FilmModel->index(lastrow,7),FilmAdd.info());

    FilmModel->submitAll();
}

QString ConversionMinHeure(int DureeMin){

    QString conversion_en_heure;

    if (DureeMin == 60)
    {
        conversion_en_heure = "1h";
        qDebug () << conversion_en_heure <<"condition 1h";
    }
    else if (DureeMin > 60)
    {
        //int a = conversion_en_heure.toInt();
        int resultat = DureeMin/60;
        int modulo = DureeMin%60;
        char heure = 'h';
        QString minutes = "min";;
        QString modulo_avec_zero = QString ("%1")
                .arg(modulo);

        if (modulo < 10)

        { modulo_avec_zero = QString("%1%2")
                    .arg("0")
                    .arg(modulo);
            qDebug () << modulo_avec_zero << "condition ou module<10";
        }


        conversion_en_heure = QString ("%1%2%3")
                .arg(resultat)
                .arg(heure)
                .arg(modulo_avec_zero);
        qDebug () << conversion_en_heure << "condition 1het qques min";
    }
    else {
        conversion_en_heure += "min";
        qDebug () << conversion_en_heure << "condition min";
    }

    return conversion_en_heure;

}

void DeleteFilm(QSortFilterProxyModel *FilmSortingModel,QModelIndex IndexASuppr,QSqlTableModel *FilmModel){


    FilmSortingModel->removeRow(IndexASuppr.row());

    FilmModel->submitAll();
    FilmModel->select();
}

void modificationfilm(Film FilmAdd,QSqlTableModel *FilmModel,QSortFilterProxyModel *FilmSortingModel,QModelIndex IndexAModifier)
{

    FilmSortingModel->setData(FilmSortingModel->index(IndexAModifier.row(),1),FilmAdd.titre());
    FilmSortingModel->setData(FilmSortingModel->index(IndexAModifier.row(),2),FilmAdd.annee());
    FilmSortingModel->setData(FilmSortingModel->index(IndexAModifier.row(),3),FilmAdd.genre());
    FilmSortingModel->setData(FilmSortingModel->index(IndexAModifier.row(),4),FilmAdd.duree());
    FilmSortingModel->setData(FilmSortingModel->index(IndexAModifier.row(),5),FilmAdd.langue());
    FilmSortingModel->setData(FilmSortingModel->index(IndexAModifier.row(),6),FilmAdd.photo());
    FilmSortingModel->setData(FilmSortingModel->index(IndexAModifier.row(),7),FilmAdd.info());

    FilmModel->submitAll();


}

QPixmap photobytearraytoPixmap(QSortFilterProxyModel *FilmSortingModel, QModelIndex indexselected)
{
    QVariant datacurrent = FilmSortingModel->data(FilmSortingModel->index(indexselected.row(), 6));
    QByteArray image = datacurrent.toByteArray();

    QImage affiche;

    if (image.isNull())
    {
        //voir comment le gerer dans le .qrc
        affiche.load(":/img/Interface/img/cinema.jpg");
    }
    else
    {
        affiche.loadFromData(image);//conversion
    }
    QPixmap PhotoPix;
    PhotoPix.convertFromImage(affiche);
    return PhotoPix;
}


QByteArray photoPixMaptoBytearray(const QPixmap *image )
{

    // Preparation of our QPixmap
    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    image->save(&buffer, "PNG");

    return bArray;
}
