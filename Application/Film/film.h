#ifndef FILM_H
#define FILM_H

#include <QObject>

class Film
{
public:
    Film();
    Film(QString titre, QString genre, QString langue, int annee, int duree);

    QString titre() const;
    void setTitre(const QString &titre);

    QString genre() const;
    void setGenre(const QString &genre);

    QString langue() const;
    void setLangue(const QString &langue);

    int duree() const;
    void setDuree(int duree);

    int annee() const;
    void setAnnee(int annee);

private:
    QString mTitre;
    QString mGenre;
    QString mLangue;
    int mAnnee;
    int mDuree;


};

#endif // FILM_H
