#include "clientmanager.h"

ClientManager::ClientManager()
{
    // подключение осуществляется в DatabaseManager, потому конструктор пустой
}

bool ClientManager::addClient(const QString &companyName, const QString &inn, const QString &address,
                   const QString &lastName, const QString &firstName, const QString &middleName,
                   const QString &phone, const QString &email, const QString &notes)
{
    QSqlQuery query;

    query.prepare("INSERT INTO clients (company_name, inn, address, last_name, first_name, middle_name, phone, email, notes) "
                  "VALUES (:company_name, :inn, :address, :last_name, :first_name, :middle_name, :phone, :email, :notes)");

    query.bindValue(":company_name", companyName);
    query.bindValue(":inn", inn);
    query.bindValue(":address", address);
    query.bindValue(":last_name", lastName);
    query.bindValue(":first_name", firstName);
    query.bindValue(":middle_name", middleName);
    query.bindValue(":phone", phone);
    query.bindValue(":email", email);
    query.bindValue(":notes", notes);

    if (!query.exec())
    {
        qDebug() << "Ошибка добавления клиента:" << query.lastError().text();
        return false;
    }

    return true;
}