#ifndef ADDCLIENTDIALOG_H
#define ADDCLIENTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QPointer>

struct ClientData
{
    QString companyName;
    QString inn;
    QString address;
    QString lastName;
    QString firstName;
    QString middleName;
    QString phone;
    QString email;
    QString notes;
};

class AddClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddClientDialog(QWidget *parent = nullptr);

private slots:
    void onSaveButtonClicked();  // слои для обработки кнопки "Сохранить"

private:
    QPointer<QLineEdit> companyNameInput;  // поле для названия компании
    QPointer<QLineEdit> innInput;  // поле для ИНН
    QPointer<QLineEdit> addressInput;  // поле для юр адреса
    QPointer<QLineEdit> lastNameInput;  // пооле для фамилии
    QPointer<QLineEdit> firstNameInput;  // поле для имени
    QPointer<QLineEdit> middleNameInput;  // поле для отчества
    QPointer<QLineEdit> phoneInput;  // поле для телефона
    QPointer<QLineEdit> emailInput;  // поле для эл почты
    QPointer<QTextEdit> notesInput;  // поле для заметок
};

#endif // ADDCLIENTDIALOG_H
