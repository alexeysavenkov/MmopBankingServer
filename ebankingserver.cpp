#include "ebankingserver.h"

#include <QCoreApplication>
#include <QRegExp>
#include <QStringList>
#include <QDebug>

#include "qhttpserver/src/qhttpserver.h"
#include "qhttpserver/src/qhttpconnection.h"
#include "qhttpserver/src/qhttprequest.h"
#include "qhttpserver/src/qhttpresponse.h"

#include "smssender.h"
#include "moopdatabase.h"

/// BodyData

EBankingHttpServer::EBankingHttpServer()
{
    QHttpServer *server = new QHttpServer(this);
    connect(server, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),
        this, SLOT(handleRequest(QHttpRequest*, QHttpResponse*)));

    this->_mmopDb = new MmopDatabase();
    this->_smsSender = new SmsSender();

    server->listen(QHostAddress::Any, 8080);
}

SmsSender& EBankingHttpServer::smsSender() const {
    return *(this->_smsSender);
}

MmopDatabase& EBankingHttpServer::mmopDb() const {
    return *(this->_mmopDb);
}

void EBankingHttpServer::handleRequest(QHttpRequest *req, QHttpResponse *resp)
{
    new Responder(req, resp, this);
}

/// Responder

Responder::Responder(QHttpRequest *req, QHttpResponse *resp, EBankingHttpServer *server)
    : m_req(req)
    , m_resp(resp)
    , server(server)
{
    QRegExp exp("/auth/send-sms\\?phone=([\\d\\+]+)");
    qDebug() << "kek" << req->url().url();
    if (exp.indexIn(req->url().url()) == -1)
    {
        resp->writeHead(403);
        resp->end(QByteArray("You aren't allowed here!"));
        /// @todo There should be a way to tell request to stop streaming data
        return;
    }

    QString phone = exp.capturedTexts()[1];
    QString smsCode = this->server->mmopDb().generateSmsCodeForPhoneNumber(phone);
    this->server->smsSender().sendLoginCode(phone, smsCode);

    resp->setHeader("Content-Length", "0");
    resp->setHeader("Content-Type", "text/html");
    resp->writeHead(200);

    connect(req, SIGNAL(data(const QByteArray&)), this, SLOT(accumulate(const QByteArray&)));
    connect(req, SIGNAL(end()), this, SLOT(reply()));
    connect(m_resp, SIGNAL(done()), this, SLOT(deleteLater()));
}

Responder::~Responder()
{
}

void Responder::accumulate(const QByteArray &data)
{
    m_resp->write(data);
}

void Responder::reply()
{
    m_resp->end(QByteArray("</p></body></html>"));
}

/// main

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    EBankingHttpServer bodydata;
    app.exec();
}
