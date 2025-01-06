#include "registerdialog.h"
#include "databasemanager.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>

RegisterDialog::RegisterDialog(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    usernameInput = new QLineEdit(this);
    usernameInput->setPlaceholderText("Логин");

    passwordInput = new QLineEdit(this);
    passwordInput->setPlaceholderText("Пароль");
    passwordInput->setEchoMode(QLineEdit::Password);

    QPushButton *registerButton = new QPushButton("Зарегистрироваться", this);

    layout->addWidget(usernameInput);
    layout->addWidget(passwordInput);
    layout->addWidget(registerButton);

    connect(registerButton, &QPushButton::clicked, this, &RegisterDialog::onRegisterButtonClicked);
}

void RegisterDialog::onRegisterButtonClicked()
{
    DatabaseManager dbManager;

    // Получаем введенные данные
    QString username = usernameInput->text();
    QString password = passwordInput->text();



    // Добавляем пользователя в базу данных
    if (dbManager.addUser(username, password))
    {
        emit registrationSuccessful();  // если регистрация успешна
        accept();  // закрываем диалог
    }
    else
    {

        usernameInput->clear();
        passwordInput->clear();
        usernameInput->setFocus();
    }
}
