######################################################################
# Automatically generated by qmake (3.0) Sun Oct 15 21:14:53 2017
######################################################################

TEMPLATE = app
TARGET = src
INCLUDEPATH += . qhttpserver/src qhttpserver/http-parser

# Input
HEADERS += ebankingserver.h \
           moopdatabase.h \
           smssender.h \
           qhttpserver/http-parser/http_parser.h \
           qhttpserver/src/qhttpconnection.h \
           qhttpserver/src/qhttprequest.h \
           qhttpserver/src/qhttpresponse.h \
           qhttpserver/src/qhttpserver.h \
           qhttpserver/src/qhttpserverapi.h \
           qhttpserver/src/qhttpserverfwd.h
SOURCES += EBankingServer.cpp \
           moopdatabase.cpp \
           smssender.cpp \
           qhttpserver/http-parser/bench.c \
           qhttpserver/http-parser/http_parser.c \
           qhttpserver/http-parser/test.c \
           qhttpserver/src/qhttpconnection.cpp \
           qhttpserver/src/qhttprequest.cpp \
           qhttpserver/src/qhttpresponse.cpp \
           qhttpserver/src/qhttpserver.cpp \
           qhttpserver/http-parser/contrib/parsertrace.c \
           qhttpserver/http-parser/contrib/url_parser.c
