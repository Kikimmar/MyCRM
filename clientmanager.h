#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "databasemanager.h"
#include "editclientdialog.h"

#include <QString>

class ClientManager
{
public:
    ClientManager();

    // Метод добавления клиента
    bool addClient(const QString &companyName, const QString &inn, const QString &address,
                   const QString &lastName, const QString &firstName, const QString &middleName,
                   const QString &phone, const QString &email, const QString &notes);

    bool updateClient(const ClientData &client);
private:
};
#endif // CLIENTMANAGER_H
