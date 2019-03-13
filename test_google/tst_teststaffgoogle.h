#pragma once
#include<QString>
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QDate>
#include "staff.h"

using namespace testing;


TEST(TestStaffConstructor, Default)
{
    //given
    //when
        Staff Pitt;
    //then
        EXPECT_EQ(Pitt.nom(), "nom");
        EXPECT_EQ(Pitt.dateNaissance(), QDate());
        EXPECT_EQ(Pitt.nationaliteA(), "nationaliteA");
        EXPECT_EQ(Pitt.nationaliteB(),"");
        EXPECT_EQ(Pitt.professionA(), "professionA");
        EXPECT_EQ(Pitt.professionB(), "");
        EXPECT_EQ(Pitt.professionC(), "");
        EXPECT_EQ(Pitt.photo(), QByteArray());
        EXPECT_EQ(Pitt.bio(), "");
}


TEST(TestStaffConstructor, Synthese)
{
    //given
        QString nom = "Pitt";
        QDate dateNaissance(1963,12,18);
        QString nationaliteA = "Etats-Unis";
        QString professionA = "Acteur";

    //when
        Staff Pitt (nom, dateNaissance, nationaliteA, professionA);
    //then
        EXPECT_EQ(Pitt.nom(), nom);
        EXPECT_EQ(Pitt.dateNaissance(), dateNaissance);
        EXPECT_EQ(Pitt.nationaliteA(), nationaliteA);
        EXPECT_EQ(Pitt.professionA(), professionA);
}


TEST(TestStaffConstructor, Complet)
{
    //given
        QString nom = "Godard";
        QDate dateNaissance(1930,12,3);
        QString nationaliteA = "France";
        QString nationaliteB= "Suisse";
        QString professionA = "Realisateur";
        QString professionB = "Scénariste";
        QString professionC = "Producteur";
        QByteArray photo = QByteArray();
        QString bio = "";

    //when
        Staff Godard (nom, dateNaissance, nationaliteA, nationaliteB, professionA, professionB, professionC, photo, bio);

    //then
        EXPECT_EQ(Godard.nom(), nom);
        EXPECT_EQ(Godard.dateNaissance(), dateNaissance);
        EXPECT_EQ(Godard.nationaliteA(), nationaliteA);
        EXPECT_EQ(Godard.nationaliteB(), nationaliteB);
        EXPECT_EQ(Godard.professionA(), professionA);
        EXPECT_EQ(Godard.professionB(), professionB);
        EXPECT_EQ(Godard.professionC(), professionC);
        EXPECT_EQ(Godard.photo(), photo);
        EXPECT_EQ(Godard.photo(), bio);
}


