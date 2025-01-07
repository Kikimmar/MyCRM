#include "logindialog.h"
#include "databasemanager.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCryptographicHash>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    usernameInput = new QLineEdit(this);  // инициализация указателя на поле ввода логина
    usernameInput->setPlaceholderText("Логин");

    passwordInput = new QLineEdit(this);  // инициализация указателя на поле ввода пароля
    passwordInput->setPlaceholderText("Пароль");
    passwordInput->setEchoMode(QLineEdit::Password);

    QPushButton *loginButton = new QPushButton("Войти", this);
    QPushButton *registerButton = new QPushButton("Регистрация", this);

    layout->addWidget(usernameInput);
    layout->addWidget(passwordInput);
    layout->addWidget(loginButton);
    layout->addWidget(registerButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginButtonClicked);
    connect(registerButton, &QPushButton::clicked, this, &LoginDialog::onRegisterButtonClicked);
}

// Слот для входа по логину и паролю
void LoginDialog::onLoginButtonClicked()
{
    DatabaseManager& dbManager = DatabaseManager::getInstance();

    // Получаем введенные данные
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    // Проверка пользователя
    if (dbManager.validateUser(username, password))
    {
        emit loginSuccessful();  // если проверка успешна, сигнализируем о входе
        accept();  // закрываем диалог
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль.");
        usernameInput->clear();
        passwordInput->clear();
        usernameInput->setFocus();
    }
}

// Слот для регистрации
void LoginDialog::onRegisterButtonClicked()
{
    DatabaseManager& dbManager = DatabaseManager::getInstance();

    QString username = usernameInput->text();
    QString password = passwordInput->text();

    // Проверяем, что поля пустые
    if (username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста заполните все поля.");
        return;
    }

    // Проверка на существование пользователя
    if (dbManager.userExists(username))
    {
        QMessageBox::warning(this, "Ошибка", "Пользователь с таким логином уже существует.");
        return;
    }

    //Добавление пользователя
    dbManager.addUser(username, password);
    QMessageBox::information(this, "Успех", "Пользователь успешно зарегистрирован.");
}

// Переопределение события закрытия окна
void LoginDialog::closeEvent(QCloseEvent *event)
{
    reject();  // отмена диалога при закрытии окна
}
