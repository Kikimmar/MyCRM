#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>

class DatabaseManager
{
    public:
        static DatabaseManager& getInstance();

        bool connectToDatabase();

        void closeDatabase();

        bool validateUser(const QString &username, const QString &password);  // проверка логина и пароля

        bool userExists(const QString &username);  // проверка существования пользователя

        bool addUser(const QString &username, const QString &password); //  добавление пользователя

    private:
        DatabaseManager();
        ~DatabaseManager();

        DatabaseManager(const DatabaseManager&) = delete;  // удаляем оператор копирования
        DatabaseManager& operator=(const DatabaseManager&) = delete;  // удаляем оператор присваивания

        QSqlDatabase db;
};
#endif // DATABASEMANAGER_H
