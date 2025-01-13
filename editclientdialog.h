#ifndef EDITCLIENTDIALOG_H
#define EDITCLIENTDIALOG_H

#include "clientdata.h"

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QLabel>

class EditClientDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EditClientDialog(ClientData clientData, QWidget *parent = nullptr);

    ClientData getClientData() const;

private slots:
    void onSaveButtonClicked();

private:
    QLineEdit *companyNameInput;
    QLineEdit *innInput;
    QLineEdit *addressInput;
    QLineEdit *lastNameInput;
    QLineEdit *firstNameInput;
    QLineEdit *middleNameInput;
    QLineEdit *phoneInput;
    QLineEdit *emailInput;
    QTextEdit *notesInput;

    ClientData clientData;  // сохранение даннх клиента для редактирования
};

#endif // EDITCLIENTDIALOG_H
