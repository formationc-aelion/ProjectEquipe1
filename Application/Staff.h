#ifndef STAFF_H
#define STAFF_H

#include <QObject>
#include <QDate>

class Staff
{
public:
    Staff();
    ~Staff();
    Staff(QString nom, QDate dateNaissance, QString nationaliteA,QString professionA);
    Staff(QString nom, QDate dateNaissance, QString nationaliteA, QString nationaliteB, QString professionA, QString professionB, QString professionC, QByteArray photo, QString info);


    QString nom() const;
    void setNom(const QString &nom);

    QDate dateNaissance() const;
    void setDateNaissance(const QDate &dateNaissance);

    QString nationaliteA() const;
    void setNationaliteA(const QString &nationaliteA);

    QString nationaliteB() const;
    void setNationaliteB(const QString &nationaliteB);

    QString professionA() const;
    void setProfessionA(const QString &professionA);

    QString professionB() const;
    void setProfessionB(const QString &professionB);

    QString professionC() const;
    void setProfessionC(const QString &professionC);

    QByteArray photo() const;
    void setPhoto(const QByteArray &photo);

    QString bio() const;
    void setBio(const QString &info);


private:
    QString mNom;
    QDate mDateNaissance;
    QString mNationaliteA;
    QString mNationaliteB;
    QString mProfessionA;
    QString mProfessionB;
    QString mProfessionC;
    QByteArray mPhoto;
    QString mBio;
};

#endif // PERSONNE_H
