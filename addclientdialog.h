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

class AddClientDialog : public QDialog
{
    Q_OBJECT

public:
    AddClientDialog(QWidget *parent = nullptr);

private slots:
    void onSaveButtonClicked();  // слои для обработки кнопки "Сохранить"

private:
    QLineEdit *companyNameInput;  // поле для названия компании
    QLineEdit *innInput;  // поле для ИНН
    QLineEdit *addresInput;  // поле для юр адреса
    QLineEdit *lastNameInput;  // пооле для фамилии
    QLineEdit *firstNameInput;  // поле для имени
    QLineEdit *middleNameInput;  // поле для отчества
    QLineEdit *phoneInput;  // поле для телефона
    QLineEdit *emailInput;  // поле для эл почты
    QTextEdit *notesinput;  // поле для заметок
};

#endif // ADDCLIENTDIALOG_H
