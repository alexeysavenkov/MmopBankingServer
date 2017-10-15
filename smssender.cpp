#include "smssender.h"

#include <QVariant>
#include <QDebug>

SmsSender::SmsSender(QObject *parent) {

    this->turboSmsDatabase = QSqlDatabase::addDatabase("QMYSQL", "turboSmsDatabase");
    this->turboSmsDatabase.setHostName("94.249.146.189");
    this->turboSmsDatabase.setDatabaseName("users");
    this->turboSmsDatabase.setUserName("alexeysavenkov");
    this->turboSmsDatabase.setPassword("zzzz1234");

    bool ok = this->turboSmsDatabase.open();

    if(!ok) {
        qDebug() << "Failed to open TurboSMS database";
    }

}

void SmsSender::sendSms(const QString &phoneNumber, const QString &message) {
    QSqlQuery query(this->turboSmsDatabase);

    query.prepare("INSERT INTO alexeysavenkov (number, sign, message, wappush) VALUES (:phone, 'Msg', :message,'')");
    query.bindValue(QString(":phone"), QVariant(phoneNumber));
    query.bindValue(QString(":message"), QVariant(message));

    bool ok = query.exec();

    if(ok) {
        qDebug() << "Sms sent!";
    }
}

void SmsSender::sendLoginCode(const QString &phoneNumber, const QString &loginCode) {
    this->sendSms(phoneNumber, loginCode + ". Welcome to MOOP E-banking!");
    qDebug() << "Login code " << loginCode << " sent to " << phoneNumber << " via TurboSMS";
}
