#ifndef MMOPDATABASE_H
#define MMOPDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlResult>
#include <QHash>
#include <QDebug>
#include <QSharedPointer>
#include <QSqlError>

class MmopDatabase : public QObject
{
    Q_OBJECT
public:
    explicit MmopDatabase(QObject *parent = nullptr);

    const QString generateSmsCodeForPhoneNumber(const QString &phoneNumber);

    QSqlRecord getUserByPhoneNumber(const QString &phoneNumber);
    QSqlRecord createNewUser(const QString &phoneNumber);

private:
    QSqlDatabase mmopDatabase;
    QSharedPointer<QSqlQueryModel> execQuery(const QString &query, QHash<QString, QString> bindedValues);

    QString generateRandomString(const QString& possibleCharacters, int length) const;
signals:

public slots:
};

#endif // MMOPDATABASE_H
