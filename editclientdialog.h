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
#include <QPointer>

class EditClientDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EditClientDialog(ClientData clientData, QWidget *parent = nullptr);

    ClientData getClientData() const;

private slots:
    void onSaveButtonClicked();

private:
    QPointer<QLineEdit> companyNameInput;
    QPointer<QLineEdit> innInput;
    QPointer<QLineEdit> addressInput;
    QPointer<QLineEdit> lastNameInput;
    QPointer<QLineEdit> firstNameInput;
    QPointer<QLineEdit> middleNameInput;
    QPointer<QLineEdit> phoneInput;
    QPointer<QLineEdit> emailInput;
    QPointer<QTextEdit> notesInput;

    ClientData clientData;  // сохранение даннх клиента для редактирования
};

#endif // EDITCLIENTDIALOG_H
