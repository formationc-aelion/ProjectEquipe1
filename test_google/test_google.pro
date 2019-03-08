include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread


HEADERS += \
        tst_testconstructor.h

SOURCES += \
        main.cpp
		
include(../Application/film.pri)

INCLUDEPATH += ../Application/Film 
