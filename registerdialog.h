#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QLineEdit>

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    RegisterDialog(QWidget *parent = nullptr);

signals:
    void registrationSuccessful();

private slots:
    void onRegisterButtonClicked();

private:
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
};

#endif // REGISTERDIALOG_H
