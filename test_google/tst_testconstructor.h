#pragma once
#include<QString>
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "film.h"

using namespace testing;

TEST(TestFilmConstructor, Default)
{
    //given
    //when
        Film Terminator;
    //then
        EXPECT_EQ(Terminator.titre(), "titre");
        EXPECT_EQ(Terminator.genre(), "genre");
        EXPECT_EQ(Terminator.langue(), "langue");
        EXPECT_EQ(Terminator.annee(), 0);
        EXPECT_EQ(Terminator.duree(), 0);
        EXPECT_EQ(Terminator.photo(), QByteArray());
        EXPECT_EQ(Terminator.info(), "");
}

TEST(TestFilmConstructor, NewOne)
{
    //given
        QString titre = "Terminator";
        QString genre = "Science-Fiction";
        QString langue = "Anglais";
        int annee = 1990;
        int duree = 120;

    //when
        Film Terminator (titre,genre,langue,annee,duree);
    //then
        EXPECT_EQ(Terminator.titre(), titre);
        EXPECT_EQ(Terminator.genre(), genre);
        EXPECT_EQ(Terminator.langue(), langue);
        EXPECT_EQ(Terminator.annee(), annee);
        EXPECT_EQ(Terminator.duree(), duree);       
}

TEST(TestFilmConstructor, Complet)
{
    //given
        QString titre = "Terminator";
        QString genre = "Science-Fiction";
        QString langue = "Anglais";
        int annee = 1990;
        int duree = 120;
        QByteArray photo = QByteArray();
        QString info = "";

    //when
        Film Terminator (titre,genre,langue,annee,duree);
    //then
        EXPECT_EQ(Terminator.titre(), titre);
        EXPECT_EQ(Terminator.genre(), genre);
        EXPECT_EQ(Terminator.langue(), langue);
        EXPECT_EQ(Terminator.annee(), annee);
        EXPECT_EQ(Terminator.duree(), duree);
        EXPECT_EQ(Terminator.photo(), photo);
        EXPECT_EQ(Terminator.info(), info);
}


