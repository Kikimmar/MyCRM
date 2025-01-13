#include "clientmanager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

ClientManager::ClientManager() {}

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

bool ClientManager::updateClient(const ClientData &client)
{
    QSqlQuery query;
    query.prepare("UPDATE clients SET company_name = :company_name, inn = :inn, address = :address,"
                  "last_name = :last_name, first_name = :first_name, middle_name = :middle_name,"
                  "phone = :phone, email = :email, notes = :notes WHERE inn = :inn");  // уникальность по ИНН

    query.bindValue(":company_name", client.companyName);
    query.bindValue(":inn", client.inn);  // Используем ИНН для поиска записи
    query.bindValue(":address", client.address);
    query.bindValue(":last_name", client.lastName);
    query.bindValue(":first_name", client.firstName);
    query.bindValue(":middle_name", client.middleName);
    query.bindValue(":phone", client.phone);
    query.bindValue(":email", client.email);
    query.bindValue(":notes", client.notes);

    if (!query.exec())
    {
        qDebug() << "Ошибка добавления клиента:" << query.lastError().text();
        return false;
    }
    return true;
}
