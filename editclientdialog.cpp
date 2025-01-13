#include "editclientdialog.h"
#include "clientmanager.h"

EditClientDialog::EditClientDialog(ClientData data, QWidget *parent)
    : QDialog(parent), clientData(data)
{
    setWindowTitle("Редактирование клиента");

    auto *formLayout = new QFormLayout(this);

    companyNameInput = new QLineEdit(clientData.companyName, this);

    innInput = new QLineEdit(clientData.inn, this);
    innInput->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{12}"), this));

    addressInput = new QLineEdit(clientData.address, this);

    lastNameInput = new QLineEdit(clientData.lastName, this);
    firstNameInput = new QLineEdit(clientData.firstName, this);
    middleNameInput = new QLineEdit(clientData.middleName, this);

    phoneInput  = new QLineEdit(clientData.phone, this);

    emailInput   = new QLineEdit(clientData.email, this);
    emailInput->setValidator(new QRegularExpressionValidator(QRegularExpression(R"((\w+)(\.\w+)*@(\w+)(\.\w+)+)"), this));

    notesInput    = new QTextEdit(clientData.notes, this);

    formLayout->addRow("Название компании:", companyNameInput);
    formLayout->addRow("ИНН:", innInput);
    formLayout->addRow("Юридический адрес:", addressInput);

    // Заголовок "Контакт"
    QLabel *contactLabel = new QLabel("Контактное лицо", this);
    contactLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    formLayout->addRow(contactLabel);

    formLayout->addRow("Фамилия:", lastNameInput);
    formLayout->addRow("Имя:", firstNameInput);
    formLayout->addRow("Отчество:", middleNameInput);

    formLayout->addRow("Телефон:", phoneInput);
    formLayout->addRow("Электронная почта:", emailInput);

    formLayout->addRow("Комментарии:", notesInput);

    auto *saveButton = new QPushButton("Сохранить", this);

    connect(saveButton, &QPushButton::clicked, this, &EditClientDialog::onSaveButtonClicked);

    formLayout->addWidget(saveButton);  // добавляем кнопку в форму
    setLayout(formLayout);  // форма как основной макет диалога
}

ClientData EditClientDialog::getClientData() const
{
    return clientData;  // возвращаем данные клиента
}

void EditClientDialog::onSaveButtonClicked()
{
    // Обновляем данные клиента из полей ввода
    clientData.companyName = companyNameInput->text();
    clientData.inn = innInput->text();
    clientData.address = addressInput->text();
    clientData.lastName = lastNameInput->text();
    clientData.firstName = firstNameInput->text();
    clientData.middleName = middleNameInput->text();
    clientData.phone = phoneInput->text();
    clientData.email = emailInput->text();
    clientData.notes = notesInput->toPlainText();

    ClientManager clientManager;

    // Сохраняем изменения в БД
    if (clientManager.updateClient(clientData))  // Предполагается наличие метода updateClient в ClientManager
    {
        QMessageBox::information(this, "Успех", "Данные клиента успешно обновлены!");
        accept();  // Закрываем диалог
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось обновить данные клиента.");
    }
}
