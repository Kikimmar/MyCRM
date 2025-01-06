#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>

class DatabaseManager
{
    public:
        DatabaseManager();

        bool connectToDatabase();

        bool validateUser(const QString &username, const QString &password);  // проверка логина и пароля

        bool userExists(const QString &username);  // проверка существования пользователя

        bool addUser(const QString &username, const QString &password); //  добавление пользователя

    private:
        QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
