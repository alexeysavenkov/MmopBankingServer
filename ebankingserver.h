#include "qhttpserver/src/qhttpserverfwd.h"

#include <QObject>
#include <QScopedPointer>

#include "moopdatabase.h"
#include "smssender.h"

/// BodyData

class EBankingHttpServer : public QObject
{
    Q_OBJECT

public:
    EBankingHttpServer();

    SmsSender& smsSender() const;
    MmopDatabase& mmopDb() const;

private:
    SmsSender* _smsSender;
    MmopDatabase* _mmopDb;

private slots:
    void handleRequest(QHttpRequest *req, QHttpResponse *resp);
};

/// Responder

class Responder : public QObject
{
    Q_OBJECT

public:
    Responder(QHttpRequest *req, QHttpResponse *resp, EBankingHttpServer *server);
    ~Responder();

signals:
    void done();

private slots:
    void accumulate(const QByteArray &data);
    void reply();

private:
    QScopedPointer<QHttpRequest> m_req;
    QHttpResponse *m_resp;
    EBankingHttpServer *server;
};
