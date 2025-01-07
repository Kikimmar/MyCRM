#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "databasemanager.h"

#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class ClientManager
{
public:
    ClientManager();

    // Метод добавления клиента
    bool addClient(const QString &companyName, const QString &inn, const QString &address,
                   const QString &lastName, const QString &firstName, const QString &middleName,
                   const QString &phone, const QString &email, const QString &notes);

private:
};

#endif // CLIENTMANAGER_H
