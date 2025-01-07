#include "databasemanager.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QDebug>

DatabaseManager::DatabaseManager() {}

DatabaseManager::~DatabaseManager()
{
    closeDatabase();
}

DatabaseManager& DatabaseManager::getInstance()
{
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("0103");

    if (!db.open())
    {
        qDebug() << "Ошибка подключения к базе данных: " << db.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::validateUser(const QString &username, const QString &password)
{
    QSqlQuery query;

    // Хушируем пароль
    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());

    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPassword);

    qDebug() << "Проверка пользователя:" << username << "с хешированным паролем:" << hashedPassword;

    if (!query.exec())
    {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return false;
    }

    // Проверка результата
    query.next();
    int count = query.value(0).toInt();
    qDebug() << "Количество найденных пользователей:" << count;
    // Если количество найденных записей больше 0, то пользователь существует
    return count > 0;
}

bool DatabaseManager::userExists(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec())
    {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return false;
    }

    query.next();
    return query.value(0).toInt() > 0;  // если количество найденных записей больше 0, то пользователь существует
}

bool DatabaseManager::addUser(const QString &username, const QString &password)
{
    QSqlQuery query;

    // Хешируем пароль перед сохранением
    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());

    query.prepare("INSERT INTO users (username, password) VALUES(:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPassword);

    if (!query.exec())
    {
        qDebug() << "Ошибка добавления пользователя:" << query.lastError().text();
        return false;
    }
    return true;
}

void DatabaseManager::closeDatabase()
{
    if (db.isOpen())
    {
        db.close();
        qDebug() << "База данных закрыта";
    }
}
