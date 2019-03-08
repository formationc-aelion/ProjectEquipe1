#include "film.h"

Film::Film():Film("titre","genre","langue",0,0)
{

}

Film::Film(QString titre, QString genre, QString langue, int annee, int duree):
    mTitre(titre), mGenre(genre), mLangue(langue), mAnnee(annee), mDuree(duree)
{
}

QString Film::titre() const
{
    return mTitre;
}

void Film::setTitre(const QString &titre)
{
    mTitre = titre;
}

QString Film::genre() const
{
    return mGenre;
}

void Film::setGenre(const QString &genre)
{
    mGenre = genre;
}

QString Film::langue() const
{
    return mLangue;
}

void Film::setLangue(const QString &langue)
{
    mLangue = langue;
}

int Film::duree() const
{
    return mDuree;
}

void Film::setDuree(int duree)
{
    mDuree = duree;
}

int Film::annee() const
{
    return mAnnee;
}

void Film::setAnnee(int annee)
{
    mAnnee = annee;
}
