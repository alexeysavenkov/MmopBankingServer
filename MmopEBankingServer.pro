QT -= gui
QT += network
QT += sql

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    qhttpserver/src/qhttpconnection.cpp \
    qhttpserver/src/qhttprequest.cpp \
    qhttpserver/src/qhttpresponse.cpp \
    qhttpserver/src/qhttpserver.cpp \
#    main.cpp \
    qhttpserver/http-parser/contrib/parsertrace.c \
    qhttpserver/http-parser/contrib/url_parser.c \
    qhttpserver/http-parser/bench.c \
    qhttpserver/http-parser/http_parser.c \
    qhttpserver/http-parser/test.c \
    ebankingserver.cpp \
    smssender.cpp \
    moopdatabase.cpp

#TEMPLATE = SUBDIRS

#SUBDIRS += qhttpserver

SUBDIRS += \
    #qhttpserver/src/src.pro \
    #qhttpserver/qhttpserver.pro \
    MmopEBankingServer.pro

DISTFILES += \
    qhttpserver/qhttpserver.pri \
    qhttpserver/http-parser/README.md \
    qhttpserver/README.md \
    qhttpserver/docs/pages/examples.dox \
    qhttpserver/docs/pages/main-page.dox \
    qhttpserver/docs/Doxyfile \
    qhttpserver/http-parser/http_parser.gyp \
    qhttpserver/http-parser/LICENSE-MIT \
    qhttpserver/LICENSE \
    qhttpserver/TODO \
    qhttpserver/http-parser/AUTHORS

HEADERS += \
    qhttpserver/http-parser/http_parser.h \
    qhttpserver/src/qhttpconnection.h \
    qhttpserver/src/qhttprequest.h \
    qhttpserver/src/qhttpresponse.h \
    qhttpserver/src/qhttpserver.h \
    qhttpserver/src/qhttpserverapi.h \
    qhttpserver/src/qhttpserverfwd.h \
    ebankingserver.h \
    smssender.h \
    moopdatabase.h
