#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = nullptr);

signals:
    void loginSuccessful();  // сигнал об успешном входе

private slots:
    void onLoginButtonClicked();  // слот для обработки кнопки "Войти"
    void onRegisterButtonClicked();  // слот для обработки кнопки "Регистрация"

protected:
    void closeEvent(QCloseEvent *event) override;  // переопределение события закрытия окна

private:
    QLineEdit *usernameInput;  // указатель на поле ввода логина
    QLineEdit *passwordInput;  // указатель на поле ввода пароля
};

#endif // LOGINDIALOG_H
