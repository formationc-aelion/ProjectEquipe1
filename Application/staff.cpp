#include "staff.h"
#include <QDate>


Staff::Staff():
    Staff("nom",QDate(), "nationaliteA", "","professionA","","", QByteArray(),"")
{

}

Staff::~Staff()
{

}

Staff::Staff(QString nom, QDate dateNaissance, QString nationaliteA, QString professionA):
    Staff(nom, dateNaissance, nationaliteA, "", professionA, "", "", QByteArray(), "")
{

}

Staff::Staff(QString nom, QDate dateNaissance, QString nationaliteA, QString nationaliteB, QString professionA, QString professionB, QString professionC, QByteArray photo, QString bio):
    mNom(nom), mDateNaissance(dateNaissance), mNationaliteA(nationaliteA), mNationaliteB(nationaliteB), mProfessionA(professionA),mProfessionB(professionB), mProfessionC(professionC), mPhoto(photo), mBio(bio)
{

}

QString Staff::nom() const
{
    return mNom;
}

void Staff::setNom(const QString &nom)
{
    mNom = nom;
}

QDate Staff::dateNaissance() const
{
    return mDateNaissance;
}

void Staff::setDateNaissance(const QDate &dateNaissance)
{
    mDateNaissance = dateNaissance;
}

QString Staff::nationaliteA() const
{
    return mNationaliteA;
}

void Staff::setNationaliteA(const QString &nationaliteA)
{
    mNationaliteA = nationaliteA;
}

QString Staff::nationaliteB() const
{
    return mNationaliteB;
}

void Staff::setNationaliteB(const QString &nationaliteB)
{
    mNationaliteB = nationaliteB;
}

QString Staff::professionA() const
{
    return mProfessionA;
}

void Staff::setProfessionA(const QString &professionA)
{
    mProfessionA = professionA;
}

QString Staff::professionB() const
{
    return mProfessionB;
}

void Staff::setProfessionB(const QString &professionB)
{
    mProfessionB = professionB;
}

QString Staff::professionC() const
{
    return mProfessionC;
}

void Staff::setProfessionC(const QString &professionC)
{
    mProfessionC = professionC;
}

QByteArray Staff::photo() const
{
    return mPhoto;
}

void Staff::setPhoto(const QByteArray &photo)
{
    mPhoto = photo;
}

QString Staff::bio() const
{
    return mBio;
}

void Staff::setBio(const QString &bio)
{
    mBio = bio;
}
