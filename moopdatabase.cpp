#include "moopdatabase.h"

MmopDatabase::MmopDatabase(QObject *parent) : QObject(parent)
{
    this->mmopDatabase = QSqlDatabase::addDatabase("QMYSQL", "mmopDatabase");
    this->mmopDatabase.setHostName("mmop-db.cs9tngvh7qnb.us-east-2.rds.amazonaws.com");
    this->mmopDatabase.setDatabaseName("mmop");
    this->mmopDatabase.setUserName("admin");
    this->mmopDatabase.setPassword("zzzz1234");

    bool ok = this->mmopDatabase.open();

    if(!ok) {
        qDebug() << "Failed to open MMOP database";
    }
}

const QString MmopDatabase::generateSmsCodeForPhoneNumber(const QString &phoneNumber) {

    QSqlRecord user = this->getUserByPhoneNumber(phoneNumber);

    QString smsCode = this->generateRandomString("0123456789abcdefghijklmnopqrstuvwxyz", 5);

    this->execQuery(
         "UPDATE `User` SET smsLoginCode = :smsCode WHERE phone = :phone",
                QHash<QString, QString>({
                    {":phone", phoneNumber},
                    {":smsCode", smsCode}
                })
    );

    qDebug() << "Sms code " << smsCode << " generated and added to DB for phone " << phoneNumber;

    return smsCode;
}

QSqlRecord MmopDatabase::getUserByPhoneNumber(const QString &phoneNumber) {
    const QSharedPointer<QSqlQueryModel> q =
        this->execQuery(
             "SELECT * FROM `User` WHERE phone = :phone",
                    QHash<QString, QString>({
                        {":phone", phoneNumber}
                    })
        );

    if(q->rowCount() == 0) {
        return this->createNewUser(phoneNumber);
    } else {
        qDebug() << "Returning existing user";
        return q->record(0);
    }
}

QSqlRecord MmopDatabase::createNewUser(const QString &phoneNumber) {
   QString publicToken = this->generateRandomString("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-", 36);

   this->execQuery("INSERT INTO `User`(phone, publicToken) VALUES(:phone, :publicToken)",
                    QHash<QString, QString>({
                          {":phone", phoneNumber},
                          {":publicToken", publicToken}
                    })
   );

    qDebug() << "User created and added to DB : " << phoneNumber << " " << publicToken;

   return this->getUserByPhoneNumber(phoneNumber);
}

QSharedPointer<QSqlQueryModel> MmopDatabase::execQuery(const QString &queryString, QHash<QString, QString> bindedValues) {
    QSqlQuery query(this->mmopDatabase);
    query.prepare(queryString);
    for(const QString &key : bindedValues.keys()) {
        const QString &value = bindedValues[key];
        qDebug() << "Binding " << key << " = " << value;
        query.bindValue(key, value);
    }

    bool ok = query.exec();

    if(!ok) {
        qDebug() << "Query " << query.lastQuery() << " executed with error";
        qDebug() << query.lastError();
    }

    QSqlQueryModel *queryModel = new QSqlQueryModel;
    queryModel->setQuery(query);

    return QSharedPointer<QSqlQueryModel>(queryModel);
}

QString MmopDatabase::generateRandomString(const QString& possibleCharacters, const int randomStringLength) const {
    QString randomString;
    for(int i=0; i<randomStringLength; ++i)
    {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }
    return randomString;
}
