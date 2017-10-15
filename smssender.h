#ifndef SMSSENDER_H
#define SMSSENDER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class SmsSender : public QObject
{
    Q_OBJECT

public:
    explicit SmsSender(QObject *parent = nullptr);
    void sendSms(const QString &phoneNumber, const QString &message);
    void sendLoginCode(const QString &phoneNumber, const QString &loginCode);

private:
    QSqlDatabase turboSmsDatabase;

signals:

public slots:
};

#endif // SMSSENDER_H
